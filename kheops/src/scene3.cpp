
// 22/02/2008

#include "core3.h"
#include <assert.h>
#include <algorithm>
#include "objects3.h"
#include "renderer3.h"
#include "scene3.h"




namespace KHEOPS
{



// ============================================================================






// ============================================================================



Scene3D::Scene3D()
{
    fParent = NULL;
    fInEdition = 0;
    fContainer = NULL;
    fDrawingSettings = 0;
	fNextCameraID = 1;
	fNextLightID = 1;
	fNextObjectID = 1;
}


Scene3D::Scene3D( Scene3D *inParent)
{
    fParent = inParent;
    fInEdition = 0;
    fContainer = NULL;
    fDrawingSettings = 0;
	fNextCameraID = 1;
	fNextObjectID = 1;
}


Scene3D::~Scene3D()
{
    delete fContainer;
    fContainer = NULL;
}


Object3D* Scene3D::GetRootObject()
{
    if (fContainer == NULL)
        fContainer = new Object3D();
    return fContainer;
}


const Object3D* Scene3D::GetRootObject() const
{
    if (fContainer == NULL)
        fContainer = new Object3D();
    return fContainer;
}


Camera* Scene3D::CreateCamera( const Coord3D& inPos)
{
	Camera *camera = new Camera( 0, inPos);

	if (camera != NULL)
	{
		RegisterCamera( camera);
	}

	return camera;
}


void Scene3D::RemoveCamera( Camera *inCamera)
{
	if (inCamera != NULL)
	{
		UnregisterCamera( inCamera);
		delete inCamera;
    }
}


bool Scene3D::RegisterCamera( Camera *inCamera)
{
	bool result = false;

	if (inCamera != NULL)
	{
		if (fCameras.find(inCamera->GetID()) == fCameras.end())
		{
			inCamera->SetID( fNextCameraID);
			fCameras[fNextCameraID] = inCamera;
			++fNextCameraID;
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


bool Scene3D::UnregisterCamera( Camera *inCamera)
{
	bool result = false;

	if (inCamera != NULL)
	{
		MapPtrOfCamera_iter found = fCameras.find( inCamera->GetID());
		if (found != fCameras.end())
		{
			inCamera->SetID( 0);
			fCameras.erase( found);
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


Camera* Scene3D::GetCamera( slong3 inID)
{
	MapPtrOfCamera_iter found = fCameras.find( inID);
	if (found != fCameras.end())
        return found->second;
    else
        return NULL;
}


Light* Scene3D::CreateLight( const Coord3D& inPos)
{
	Light *light = new Light( 0, inPos);

	if  (light != NULL)
	{
		RegisterLight( light);
	}

	return light;
}


void Scene3D::RemoveLight( Light *inLight)
{
	if (inLight != NULL)
	{
		UnregisterLight( inLight);
		delete inLight;
    }
}


bool Scene3D::RegisterLight( Light *inLight)
{
	bool result = false;

	if (inLight != NULL)
	{
		if (fLights.find(inLight->GetID()) == fLights.end())
		{
			inLight->SetID( fNextLightID);
			fLights[fNextLightID] = inLight;
			++fNextLightID;
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


bool Scene3D::UnregisterLight( Light *inLight)
{
	bool result = false;

	if (inLight != NULL)
	{
		MapPtrOfLight_iter found = fLights.find( inLight->GetID());
		if (found != fLights.end())
		{
			inLight->SetID( 0);
			fLights.erase( found);
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


Light* Scene3D::GetLight( slong3 inID)
{
	MapPtrOfLight_iter found = fLights.find( inID);
	if (found != fLights.end())
        return found->second;
    else
        return NULL;
}


void Scene3D::GetLightCollection( std::vector<Light*>& outLights) const
{
	for (MapPtrOfLight_citer iter = fLights.begin() ; iter != fLights.end() ; ++iter)
	{
		outLights.push_back( iter->second);
	}
}


bool Scene3D::RegisterObject( Object3D *inObject)
{
	bool result = false;

	if (inObject != NULL)
	{
		if (fObjects.find(inObject->GetID()) == fObjects.end())
		{
			inObject->SetID( fNextObjectID);
			fObjects[fNextObjectID] = inObject;
			++fNextObjectID;
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


bool Scene3D::UnregisterObject( Object3D *inObject)
{
	bool result = false;

	if (inObject != NULL)
	{
		MapOfObject3D_iter found = fObjects.find( inObject->GetID());
		if (found != fObjects.end())
		{
			inObject->SetID( 0);
			fObjects.erase( found);
			result = true;
		}
		else
		{
			assert(false);
		}
	}

	return result;
}


Object3D* Scene3D::GetObjectByID( ulong3 inID) const
{
	MapOfObject3D_citer found = fObjects.find( inID);
	if (found != fObjects.end())
		return found->second;

	return NULL;
}


void Scene3D::SetObjectLighted( const Light& inLight, const Object3D *inObject, bool inLighted)
{
	if (inObject != NULL)
	{
		std::map< slong3, std::vector<const Object3D*> >::iterator found = fUnlightedObjects.find(inLight.GetID());
		if (found != fUnlightedObjects.end())
		{
			std::vector<const Object3D*>::iterator objectIter = std::find( found->second.begin(), found->second.end(), inObject);
			if ((objectIter == found->second.end()) && !inLighted)
			{
				found->second.push_back( inObject);
			}
			else if ((objectIter != found->second.end()) && inLighted)
			{
				found->second.erase( objectIter);
			}
		}
		else if (!inLighted)
		{
			std::vector<const Object3D*> unlightedObjects;
			unlightedObjects.push_back( inObject);
			fUnlightedObjects[inLight.GetID()] = unlightedObjects;
		}
	}
}


bool Scene3D::IsObjectLighted( const Light& inLight, const Object3D *inObject) const
{
	bool lighted = true;

	if (inObject != NULL)
	{
		std::map< slong3, std::vector<const Object3D*> >::const_iterator found = fUnlightedObjects.find(inLight.GetID());
		if (found != fUnlightedObjects.end())
		{
			lighted = std::find( found->second.begin(), found->second.end(), inObject) == found->second.end();
		}
	}

	return lighted;
}


void Scene3D::BeginEdition()
{
    ++fInEdition;
}


void Scene3D::EndEdition()
{
    assert(fInEdition > 0);
    if (fInEdition > 0)
    {
        --fInEdition;
        if (fInEdition == 0)
        {
            UpdateViewCoords();
			UpdateLightness();
        }
    }
}


void Scene3D::SetDrawingSettings( ulong3 inDrawingSettings)
{
	fDrawingSettings = inDrawingSettings;
}


ulong3 Scene3D::GetDrawingSettings() const
{
	return fDrawingSettings;
}


void Scene3D::UpdateViewCoords()
{
    for ( MapPtrOfCamera_iter iter = fCameras.begin() ; iter != fCameras.end() ; ++iter )
    {
        Camera *camera = iter->second;
        if (camera != NULL)
        {
            UpdateViewCoords( camera);
        }
    }
}


void Scene3D::UpdateViewCoords( Camera *inCamera)
{
    if (fContainer != NULL && inCamera != NULL)
    {
		slong3 cameraID = inCamera->GetID();
        fContainer->SynchronizeWithCamera( *inCamera);
    }
}


void Scene3D::UpdateLightness()
{
    for ( MapPtrOfLight_iter iter = fLights.begin() ; iter != fLights.end() ; ++iter )
    {
        Light *light = iter->second;
        if (light != NULL)
        {
            UpdateLightness( light);
        }
    }
}


void Scene3D::UpdateLightness( Light *inLight)
{
	if (fContainer != NULL && inLight != NULL)
    {
        fContainer->SynchronizeWithLight( *inLight);
    }
}


void Scene3D::Draw( GraphicContext *inContext)
{
    if (inContext != NULL)
    {
        Renderer3D renderer( this, inContext);
        for ( MapPtrOfCamera_iter iter = fCameras.begin() ; iter != fCameras.end() ; ++iter )
        {
            Camera *camera = iter->second;
            if (camera != NULL)
            {
                Draw( &renderer, camera);
            }
        }

    }
}


void Scene3D::Draw( GraphicContext *inContext, Camera *inCamera)
{
    if (inContext != NULL && inCamera != NULL)
    {
        Renderer3D renderer( this, inContext);
        Draw( &renderer, inCamera);
    }
}


void Scene3D::Draw( Renderer3D *inRenderer, Camera *inCamera)
{
    if (inRenderer != NULL && inCamera != NULL)
    {
		if ((fDrawingSettings & kDrawFilled) != 0)
        {
            inRenderer->DrawObjectPolygons( fContainer, inCamera);
        }
        else 
        {
			inRenderer->DrawObjectSegments( fContainer, inCamera);
        }

		if ((fDrawingSettings & kDrawShapeNormalVector) != 0)
		{
			inRenderer->DrawShapesNormalVector( fContainer, inCamera, (fDrawingSettings & kDrawFilled) != 0);
		}

		if ((fDrawingSettings & kDrawRootWorld) != 0)
		{
			inRenderer->DrawRootWorld( inCamera);
		}
    }
}



} // namespace KHEOPS


