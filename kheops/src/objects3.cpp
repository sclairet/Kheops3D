
// 07/02/2008

#include "core3.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include "objects3_behaviour.h"
#include "objects3.h"




namespace KHEOPS
{



// ============================================================================
// 3d objects classes declaration


Object3D::Object3D()
: fWorld(NULL),
fParent( NULL),
fStamp(0),
fVisible(true),
fColor(NULL),
fID(0),
fBehaviour( NULL)
{
}


Object3D::Object3D( Object3D_behaviour *inBehaviour)
: fWorld(NULL),
fParent( NULL),
fStamp(0),
fVisible(true),
fColor(NULL),
fID(0),
fBehaviour( inBehaviour)
{
}


Object3D::~Object3D()
{
	for (ArrayPtrOfShape3D_iter iter = fShapes.begin() ; iter != fShapes.end() ; ++iter)
	{
		delete *iter;
		*iter = NULL;
	}

	for (ArrayPtrOfObject3D_iter iter = fChildren.begin() ; iter != fChildren.end() ; ++iter)
	{
		delete *iter;
		*iter = NULL;
	}

	for (MapOfCameraCoords_iter iter = fCameraCoords.begin() ; iter != fCameraCoords.end() ; ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}

	for (MapOfScreenCoords_iter iter = fScreenCoords.begin() ; iter != fScreenCoords.end() ; ++iter)
	{
		delete iter->second;
		iter->second = NULL;
	}

    delete fColor;
    fColor = NULL;

	delete fBehaviour;
	fBehaviour = NULL;
}


void Object3D::SetID( ulong3 inID)
{
	fID = inID;
}


ulong3 Object3D::GetID() const
{
	return fID;
}


void Object3D::SetVisible( bool inVisible)
{
    fVisible = inVisible;
}


bool Object3D::IsVisible() const
{
    if (fParent != NULL)
        return fParent->IsVisible();

    return fVisible;
}


void Object3D::SetColor( const Color& inColor)
{
    if (fColor == NULL)
        fColor = new Color();

    fColor->Set( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue(), inColor.GetAlpha());

    for ( ArrayPtrOfShape3D_iter shapesIter = fShapes.begin() ; shapesIter != fShapes.end() ; ++shapesIter )
    {
        Shape3D *shape = *shapesIter;
        if (shape != NULL)
        {
			shape->SetColor( inColor);
        }
    }
}


void Object3D::SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor)
{
    if (fColor == NULL)
        fColor = new Color();

    fColor->Set( inFirstColor.GetRed(), inFirstColor.GetGreen(), inFirstColor.GetBlue(), inFirstColor.GetAlpha());

	if (fBehaviour != NULL)
		fBehaviour->SetColor( inPattern, inFirstColor, inSecondColor);
}


ulong3 Object3D::GetCoordsCount() const
{
	ulong3 count = fCoords.size();

    for( ArrayPtrOfObject3D_citer iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            count += object->GetCoordsCount();
    }

	return count;
}


ulong3 Object3D::GetShapesCount() const
{
	ulong3 count = fShapes.size();

    for( ArrayPtrOfObject3D_citer iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            count += object->GetShapesCount();
    }

	return count;
}


void Object3D::SetPosTo( real3 inX, real3 inY, real3 inZ)
{
    Coord3D oldPos( fPos);

    fPos.SetCoordsTo( inX, inY, inZ);
    for( ArrayOfCoord3D_iter iter = fCoords.begin() ; iter != fCoords.end() ; ++iter )
    {
		(*iter).SetCoordsBy( fPos.GetX()-oldPos.GetX(), fPos.GetY()-oldPos.GetY(), fPos.GetZ()-oldPos.GetZ());
    }

    // move childrens
    for( ArrayPtrOfObject3D_iter iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            object->SetPosTo( inX, inY, inZ);
    }
}


void Object3D::SetPosBy( real3 inTx, real3 inTy, real3 inTz)
{
    fPos.SetCoordsBy( inTx, inTy, inTz);
    for( ArrayOfCoord3D_iter iter = fCoords.begin() ; iter != fCoords.end() ; ++iter )
    {
        (*iter).SetCoordsBy( inTx, inTy, inTz);
    }

    // move childrens
    for( ArrayPtrOfObject3D_citer iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            object->SetPosBy( inTx, inTy, inTz);
    }
}


void Object3D::GetCenter( Coord3D& outCenter) const
{
	if (fBehaviour != NULL)
		fBehaviour->GetCenter( outCenter);
}


void Object3D::RotateBy( const World3D& inCenter, real3 inRx, real3 inRy, real3 inRz)
{
	// save shapes's normal vector end coord
	ArrayOfVector3D normalVectors;
    for ( ArrayPtrOfShape3D_citer shapesIter = fShapes.begin() ; shapesIter != fShapes.end() ; ++shapesIter )
    {
        Shape3D *shape = *shapesIter;
        if (shape != NULL)
        {
			normalVectors.push_back(  shape->GetNormalVector());
        }
    }

    // transform into inCenter world
    World3D::sRootWorld3D.Transform( fPos, inCenter);
    World3D::sRootWorld3D.Transform( fCoords, inCenter);
	World3D::sRootWorld3D.Transform( normalVectors, inCenter);

	// rotate by
    Math::RotateBy( fPos, inRx, inRy, inRz, World3D::sRootWorld3D.IsDirect());

    for( ArrayOfCoord3D_iter iter = fCoords.begin() ; iter != fCoords.end() ; ++iter )
    {
		Math::RotateBy( *iter, inRx, inRy, inRz, World3D::sRootWorld3D.IsDirect());
    }

	for ( ArrayOfVector3D_iter iter = normalVectors.begin() ; iter != normalVectors.end() ; ++iter )
    {
        Math::RotateBy( *iter, inRx, inRy, inRz, World3D::sRootWorld3D.IsDirect());
    }

    // transform into World3D::sRootWorld3 world
    inCenter.Transform( fPos, World3D::sRootWorld3D);
    inCenter.Transform( fCoords, World3D::sRootWorld3D);
	inCenter.Transform( normalVectors, World3D::sRootWorld3D);

	// update shapes's normal vector
    for ( ArrayPtrOfShape3D_citer shapesIter = fShapes.begin() ; shapesIter != fShapes.end() ; ++shapesIter )
    {
        Shape3D *shape = *shapesIter;
        if (shape != NULL)
        {
			shape->SetNormalVector( normalVectors[shapesIter - fShapes.begin()]);
        }
    }

    // rotate childrens
    for( ArrayPtrOfObject3D_citer iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            object->RotateBy( inCenter, inRx, inRy, inRz);
    }
}


void Object3D::SynchronizeWithCamera( const Camera& inCamera)
{
	slong3 cameraID = inCamera.GetID();
	
	ArrayOfCoord3D *cameraCoords = NULL;
	ArrayOfCoord2D *screenCoords = NULL;

    // Update the camera coords
	MapOfCameraCoords_citer found = fCameraCoords.find( inCamera.GetID());
	if (found != fCameraCoords.end())
	{
		cameraCoords = found->second;
	}
	else
	{
		cameraCoords = new ArrayOfCoord3D();
		if (cameraCoords != NULL)
			fCameraCoords[inCamera.GetID()] = cameraCoords;
	}

	if (cameraCoords != NULL)
	{
		*cameraCoords = fCoords;
		World3D::sRootWorld3D.Transform( *cameraCoords, inCamera);

		// update the shape's normal vector for camera
		for ( ArrayPtrOfShape3D_citer shapesIter = fShapes.begin() ; shapesIter != fShapes.end() ; ++shapesIter )
		{
			Shape3D *shape = *shapesIter;
			if (shape != NULL)
			{
				Vector3D normalVector( shape->GetNormalVector());
				World3D::sRootWorld3D.Transform( normalVector, inCamera);
				shape->SetNormalVectorByCamera( inCamera, normalVector);

				// update the shape visible state
				if (!normalVector.IsNull())
				{
					// on calcul un vecteur en direction de la camera
					Coord3D gravityCenter;
					shape->GetGravityCenter( *cameraCoords, gravityCenter);
					Vector3D vCameraOriented( -gravityCenter.GetX(), -gravityCenter.GetY(), -gravityCenter.GetZ());
	
					real3 alpha = acos( (vCameraOriented * normalVector) / (vCameraOriented.GetModule() * normalVector.GetModule()));
					shape->SetVisibleByCamera( inCamera, alpha < kPI2);
				}
				else
				{
					shape->SetVisibleByCamera( inCamera, false);
				}
			}
		}

		// update the screen coords
		MapOfScreenCoords_citer found = fScreenCoords.find( inCamera.GetID());
		if (found != fScreenCoords.end())
		{
			screenCoords = found->second;
		}
		else
		{
			screenCoords = new ArrayOfCoord2D();
			if (screenCoords != NULL)
				fScreenCoords[inCamera.GetID()] = screenCoords;
		}

		if (screenCoords != NULL)
		{
			screenCoords->resize( cameraCoords->size());

			inCamera.GetScreenWorld().Transform( *cameraCoords, inCamera, *screenCoords);
		}
    }

    // update childrens
    for( ArrayPtrOfObject3D_iter iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            object->SynchronizeWithCamera( inCamera);
    }
}


bool Object3D::HasCameraCoords( const Camera& inCamera) const
{
	MapOfCameraCoords_citer found = fCameraCoords.find( inCamera.GetID());
	return (found != fCameraCoords.end());
}


const ArrayOfCoord3D* Object3D::GetCameraCoords( const Camera& inCamera) const
{
	const ArrayOfCoord3D *result = NULL;

	MapOfCameraCoords_citer found = fCameraCoords.find( inCamera.GetID());
	if (found != fCameraCoords.end())
		result = found->second;

	return result;
}


void Object3D::SynchronizeWithLight( const Light& inLight)
{
	// update the shape's normal vector for light
	for ( ArrayPtrOfShape3D_citer shapesIter = fShapes.begin() ; shapesIter != fShapes.end() ; ++shapesIter )
	{
		Shape3D *shape = *shapesIter;
		if (shape != NULL)
		{
			Vector3D normalVector( shape->GetNormalVector());

			World3D::sRootWorld3D.Transform( normalVector, inLight);
			shape->SetNormalVectorByLight( inLight, normalVector);

			real3 lightness = 0.0;

			// update the shape lightness
			if (!normalVector.IsNull())
			{
				// on calcul un vecteur en direction de la source de lumiere
				Vector3D vLightOriented;

				Coord3D gravityCenter;
				shape->GetGravityCenter( fCoords, gravityCenter);
				vLightOriented.SetVx( inLight.GetPos().GetX() - gravityCenter.GetX());
				vLightOriented.SetVy( inLight.GetPos().GetY() - gravityCenter.GetY());
				vLightOriented.SetVz( inLight.GetPos().GetZ() - gravityCenter.GetZ());

				lightness = (vLightOriented * normalVector) / (vLightOriented.GetModule() * normalVector.GetModule());
				real3 alpha = acos( lightness);
				if (alpha >= kPI2)
					lightness = 0.0;
			}

			shape->SetLightnessByLight( inLight, lightness);
		}
	}

    // update childrens
    for( ArrayPtrOfObject3D_iter iter = fChildren.begin() ; iter != fChildren.end() ; ++iter )
    {
        Object3D *object = *iter;
        if (object != NULL)
            object->SynchronizeWithLight( inLight);
    }
}


bool Object3D::HasScreenCoords( const Camera& inCamera) const
{
	MapOfScreenCoords_citer found = fScreenCoords.find( inCamera.GetID());
	return (found != fScreenCoords.end());
}


const ArrayOfCoord2D* Object3D::GetScreenCoords( const Camera& inCamera) const
{
	const ArrayOfCoord2D *result = NULL;

	MapOfScreenCoords_citer found = fScreenCoords.find( inCamera.GetID());
	if (found != fScreenCoords.end())
		result = found->second;

	return result;
}


void Object3D::GetSegments( ArrayOfSegment& outSegments, const Camera& inCamera) const
{
    outSegments.clear();

	if (fSegments.empty())
	{
		for ( ArrayPtrOfShape3D_citer sh_iter = fShapes.begin() ; sh_iter != fShapes.end() ; ++sh_iter )
		{
			Shape3D *shape = *sh_iter;
			if (shape != NULL)
			{
				ArrayOfSegment shapeSegments;
				shape->GetSegments( shapeSegments);
				for ( ArrayOfSegment_iter seg_iter = shapeSegments.begin() ; seg_iter != shapeSegments.end() ; ++seg_iter )
				{
					if (!std::binary_search( fSegments.begin(), fSegments.end(), (*seg_iter)))    // avoid duplicate segments
					{
						fSegments.push_back( (*seg_iter));
						std::sort( fSegments.begin(), fSegments.end());
					}
				}
				shapeSegments.clear();
			}
		}
	}

	outSegments.insert( outSegments.end(), fSegments.begin(), fSegments.end());
}


ulong3 Object3D::GetChildrenCount() const
{
	return fChildren.size();
}


void Object3D::AddChild( Object3D *inObject)
{
	if (inObject != NULL)
	{
		assert(inObject->GetParent() == NULL);

		if (inObject->GetParent() == NULL)
		{
			inObject->_SetParent( this);
			fChildren.push_back( inObject);
		}
	}
}


const Object3D* Object3D::GetNthChild( ulong3 inNth) const
{
	if (inNth >= 0 && inNth < fChildren.size())
		return fChildren[inNth];

	return NULL;
}


Object3D* Object3D::GetNthChild( ulong3 inNth)
{
	if (inNth >= 0 && inNth < fChildren.size())
		return fChildren[inNth];

	return NULL;
}


void Object3D::RemoveChild( Object3D *inObject)
{
	if (inObject != NULL && inObject->GetParent() == this)
	{
		ArrayPtrOfObject3D_iter found = std::find( fChildren.begin(), fChildren.end(), inObject);
		if (found != fChildren.end())
		{
			inObject->_SetParent( NULL);
			fChildren.erase( found);
		}
	}
}


void Object3D::RemoveNthChild( ulong3 inNth)
{
	if (inNth >= 0 && inNth < fChildren.size())
	{
		fChildren[inNth]->_SetParent( NULL);
		fChildren.erase( fChildren.begin() + inNth);
	}
}


void Object3D::_SetParent( Object3D *inParent)
{
	fParent = inParent;
}



} // namespace KHEOPS
