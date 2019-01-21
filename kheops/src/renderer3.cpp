
#include "core3.h"
#include <math.h>
#include <assert.h>
#include <algorithm>
#include "objects3.h"
#include "scene3.h"
#include "renderer3.h"



namespace KHEOPS
{



RendererShape::RendererShape( const Object3D *inObject, const Shape3D *inShape, const Camera *inCamera)
: fObject( inObject), fShape( inShape), fCamera( inCamera), fCoords( NULL), fMaxZCoord( 0.0), fMaxZCoordIsDirty( true)
{
	if (fObject != NULL && inCamera != NULL)
		fCoords = fObject->GetCameraCoords( *fCamera);
}


RendererShape::~RendererShape()
{
}


real3 RendererShape::GetMaxZCoord()
{
	if (fMaxZCoordIsDirty)
	{
		for (ArrayOfIndex_citer iter = fShape->GetIndexes().begin() ; iter != fShape->GetIndexes().end() ; ++iter)
		{
			real3 zCoord = (*fCoords)[*iter].GetZ();
			if  (zCoord > fMaxZCoord)
				fMaxZCoord = zCoord;
		}
		fMaxZCoordIsDirty = false;
	}
	return fMaxZCoord;
}



class RendererShapeZOrderer
{
public:
	
	RendererShapeZOrderer() {;}
	virtual ~RendererShapeZOrderer() {;}
	
	bool operator() ( RendererShape *inFirstShape,  RendererShape *inSecondShape)
	{
		return (inFirstShape->GetMaxZCoord() > inSecondShape->GetMaxZCoord());
	} 
};




// ============================================================================
// class Renderer3D


Renderer3D::Renderer3D( Scene3D *inScene, GraphicContext *inContext)
{
    assert(inScene != NULL);
    fScene = inScene;
    fContext = inContext;
}


Renderer3D::~Renderer3D()
{
}


void Renderer3D::DrawObjectSegments( const Object3D *inObject, Camera *inCamera) const
{
    if (fScene != NULL && fContext != NULL && inObject != NULL)
    {
        // draw object
        Color color( 0xFF, 0xFF, 0xFF);
        if (inObject->GetColor() != NULL)
            color = *inObject->GetColor();

		const ArrayOfCoord2D *screenCoords = inObject->GetScreenCoords( *inCamera);
        if (screenCoords != NULL)
        {
			std::vector<Segment> segments;
            inObject->GetSegments( segments, *inCamera);
            fContext->DrawSegments( segments, *screenCoords, color);
        }

        // draw children
        for (  ArrayPtrOfObject3D_citer iter = inObject->GetChildren().begin() ; iter != inObject->GetChildren().end() ; ++iter )
        {
            const Object3D *child = *iter;
            if (child != NULL)
            {
                if (child->IsVisible())
                    DrawObjectSegments( child, inCamera);
            }
        }
    }
}


void Renderer3D::DrawShapesNormalVector( const Object3D *inObject, Camera *inCamera, bool inOnlyVisibleShape) const
{
    if (fScene != NULL && fContext != NULL && inObject != NULL)
    {
        for ( ArrayPtrOfShape3D_citer iter = inObject->GetShapes().begin() ; iter != inObject->GetShapes().end() ; ++iter )
        {
            const Shape3D *shape = *iter;
            if (shape != NULL)
            {
				bool visible = shape->IsVisibleByCamera( *inCamera);
				if (!inOnlyVisibleShape || visible)
				{
					Color color( 0x00, 0xFF, 0x00);
					if (!visible)
						color.Set( 0xFF, 0x00, 0x00);

					const ArrayOfCoord3D *cameraCoords = inObject->GetCameraCoords( *inCamera);
					if (cameraCoords != NULL)
					{
						Vector3D vnormal;
						if (shape->GetNormalVectorByCamera( *inCamera, vnormal))
						{
							Coord3D line_from;
							vnormal = vnormal * 25;
							if (shape->GetGravityCenter( *cameraCoords, line_from))
							{
								Coord3D line_to( line_from.GetX() + vnormal.GetVx(), line_from.GetY() + vnormal.GetVy(), line_from.GetZ() + vnormal.GetVz());
								_DrawSegment( line_from, line_to, color, inCamera);
							}
						}
					}
				}
            }
        }

        for (  ArrayPtrOfObject3D_citer iter = inObject->GetChildren().begin() ; iter != inObject->GetChildren().end() ; ++iter )
        {
            const Object3D *child = *iter;
            if (child != NULL)
            {
                if (child->IsVisible())
                    DrawShapesNormalVector( child, inCamera, inOnlyVisibleShape);
            }
        }
    }
}


void Renderer3D::DrawRootWorld( Camera *inCamera) const
{
	if (fContext != NULL && inCamera != NULL)
	{
		Coord3D xAxis( 100, 0, 0), yAxis( 0, 100, 0), zAxis( 0, 0, 100), center;
		Color color( 0x0D, 0xBC, 0x03);

		World3D::sRootWorld3D.Transform( center, *inCamera);
		World3D::sRootWorld3D.Transform( xAxis, *inCamera);
		World3D::sRootWorld3D.Transform( yAxis, *inCamera);
		World3D::sRootWorld3D.Transform( zAxis, *inCamera);

		_DrawSegment( center, xAxis, color, inCamera);
		_DrawSegment( center, yAxis, color, inCamera);
		_DrawSegment( center, zAxis, color, inCamera);
	}
}


void Renderer3D::DrawObjectPolygons( const Object3D *inObject, Camera *inCamera) const
{
#if 1

	if (fScene != NULL && fContext != NULL && inObject != NULL && inCamera != NULL)
	{
		ArrayPtrOfRendererShape rendererShapes;

		_GetObjectRendererShapes( rendererShapes, inObject, inCamera);

		RendererShapeZOrderer zOrderer;

		std::sort( rendererShapes.begin(), rendererShapes.end(), zOrderer);

		for (ArrayPtrOfRendererShape_iter shapeIter = rendererShapes.begin(); shapeIter != rendererShapes.end() ; ++shapeIter)
		{
			_DrawFilledShape( (*shapeIter)->GetShape(), (*shapeIter)->GetObject(), inCamera);
			delete *shapeIter;
		}
	}

#else

    if (inObject != NULL)
    {
        _DrawObjectPolygons( inObject, inCamera);

        for (  MapOfObject3D_citer iter = inObject->GetChildren().begin() ; iter != inObject->GetChildren().end() ; ++iter )
        {
            const Object3D *child = iter->second;
            if (child != NULL)
            {
                if (child->IsVisible())
                    _DrawObjectPolygons( child, inCamera);
            }
        }
    }

#endif
}


void Renderer3D::_DrawSegment( const Coord3D& inFrom, const Coord3D& inTo, const Color& inColor, Camera *inCamera) const
{
    if (fContext != NULL && inCamera != NULL)
    {
        Coord2D from, to;
		inCamera->GetScreenWorld().Transform( inFrom, *inCamera, from);
		inCamera->GetScreenWorld().Transform( inTo, *inCamera, to);
        fContext->DrawSegment( from, to, inColor);
    }
}


void Renderer3D::_DrawObjectPolygons( const Object3D *inObject, Camera *inCamera) const
{
    if (fScene != NULL && fContext != NULL && inObject != NULL)
    {
        for ( ArrayPtrOfShape3D_citer iter = inObject->GetShapes().begin() ; iter != inObject->GetShapes().end() ; ++iter )
        {
            const Shape3D *shape = *iter;
            if (shape != NULL)
            {
				if (shape->IsVisibleByCamera( *inCamera))
				{
					_DrawFilledShape( shape, inObject, inCamera);
				}
            }
        }
    }
}


void Renderer3D::_DrawFilledShape( const Shape3D *inShape, const Object3D *inObject, Camera *inCamera) const
{
	Color color( 0xFF, 0xFF, 0xFF);

	if (inShape->GetColor() != NULL)
		color = *inShape->GetColor();

	// Calculate the intensity received by the shape
	real3 shapeLightness = 0.0;
	std::vector<Light*> lights;
	fScene->GetLightCollection( lights);

	for (std::vector<Light*>::iterator iter = lights.begin() ; iter != lights.end() ; ++iter)
	{
		if (fScene->IsObjectLighted( *(*iter), inObject))
		{
			if (!(*iter)->HasCameraBinding() || ((*iter)->GetCameraBinding() == inCamera->GetID()))
			{
				real3 lightnessByLight = 0.0;
				inShape->GetLightnessByLight( *(*iter), lightnessByLight);
				shapeLightness += (lightnessByLight * ((real3)(*iter)->GetIntensity() / (real3)100));
			}
		}
	}

	if (shapeLightness > 1.0)
		shapeLightness = 1.0;
	
	real3 hue, saturation, clightness;
	color.ToHSL( hue, saturation, clightness);
	color.FromHSL( hue, saturation, clightness * shapeLightness);

	const ArrayOfCoord3D *cameraCoords = inObject->GetCameraCoords( *inCamera);
	const ArrayOfCoord2D *screenCoords = inObject->GetScreenCoords( *inCamera);
	if (cameraCoords != NULL && screenCoords != NULL)
	{
		fContext->FillPolygon( inShape->GetIndexes(), *screenCoords, color);
	}
}


void Renderer3D::_GetObjectRendererShapes( ArrayPtrOfRendererShape& outRendererShapes, const Object3D *inObject, const Camera *inCamera) const
{
    if (inObject != NULL)
    {
		if (inObject->HasCameraCoords( *inCamera))
		{
			for ( ArrayPtrOfShape3D_citer iter = inObject->GetShapes().begin() ; iter != inObject->GetShapes().end() ; ++iter )
			{
				const Shape3D *shape = *iter;
				if (shape != NULL)
				{
					if (shape->IsVisibleByCamera( *inCamera))
					{
						outRendererShapes.push_back( new RendererShape( inObject, shape, inCamera));
					}
				}
			}
		}

        for (  ArrayPtrOfObject3D_citer iter = inObject->GetChildren().begin() ; iter != inObject->GetChildren().end() ; ++iter )
        {
            const Object3D *child = *iter;
            if (child != NULL)
            {
                if (child->IsVisible())
                    _GetObjectRendererShapes( outRendererShapes, child, inCamera);
            }
        }
    }
}



} // namespace KHEOPS