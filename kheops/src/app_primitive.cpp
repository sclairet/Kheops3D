

#include "core3.h"
#include <assert.h>
#include <math.h>
#include "objects3.h"
#include "objects3_behaviour.h"
#include "modeler3.h"
#include "renderer3.h"
#include "scene3.h"
#include "application3.h"
#include "app_primitive.h"



namespace KHEOPS
{



// ============================================================================



AppBase::AppBase()
{
    fShowMouseTarget = false;
	fObjectAnimationEnabled = false;
	
	fAlpha_x = 0;
    fAlpha_y = 45;
    fAlpha_z = 90;

	fLeftCamera = NULL;
	fTopRightCamera = NULL;
	fBottomRightCamera = NULL;

	fLeftCameraLight = NULL;
}


AppBase::~AppBase()
{
}


bool AppBase::Init()
{
	if (!Application3D::Init())
		return false;

	// init the top left camera
    fLeftCamera = fScene.CreateCamera( Coord3D ( 0.0, 0.0, -800));
	if (fLeftCamera != NULL)
	{
		// init the screen world
		fLeftCamera->GetScreenWorld().SetScreenPos( 0, 0);
		fLeftCamera->GetScreenWorld().SetScreenSize( 2*(kVirtualScreenWidth/3), kVirtualScreenHeight);
		fLeftCamera->GetScreenWorld().SetZ( 700);
		fLeftCamera->GetScreenWorld().InvertYAxis( true);

		fLeftCameraLight = fScene.CreateLight( Coord3D ( 0.0, 0.0, -800));
		if (fLeftCameraLight != NULL)
		{
			fLeftCameraLight->SetCameraBinding( fLeftCamera->GetID());
			fLeftCameraLight->SetIntensity( 30);
		}
	}

	// init the top right camera
    fTopRightCamera = fScene.CreateCamera( Coord3D ( 0, 1000, 0));
	if (fTopRightCamera != NULL)
	{
		fTopRightCamera->SetAxisOrientation( eZAxis, Vector3D( 0, -1, 0));

		// init the screen world
		fTopRightCamera->GetScreenWorld().SetScreenPos( 2*(kVirtualScreenWidth/3), 0);
		fTopRightCamera->GetScreenWorld().SetScreenSize( (kVirtualScreenWidth/3), (kVirtualScreenHeight/2));
		fTopRightCamera->GetScreenWorld().SetZ( 700);
		fTopRightCamera->GetScreenWorld().InvertYAxis( true);
	}

	// init  the bottom right camera
    fBottomRightCamera = fScene.CreateCamera( Coord3D ( 700, 700, -700));
	if (fBottomRightCamera != NULL)
	{
		Vector3D orientationAxis( -1, -1, 1);
		fBottomRightCamera->SetAxisOrientation( eZAxis, orientationAxis);

		// init the screen world
		fBottomRightCamera->GetScreenWorld().SetScreenPos( 2*(kVirtualScreenWidth/3), (kVirtualScreenHeight/2));
		fBottomRightCamera->GetScreenWorld().SetScreenSize( (kVirtualScreenWidth/3), (kVirtualScreenHeight/2));
		fBottomRightCamera->GetScreenWorld().SetZ( 700);
		fBottomRightCamera->GetScreenWorld().InvertYAxis( true);

		Light *light = fScene.CreateLight( Coord3D ( 700, 700, -700));
		if (light != NULL)
		{
			light->SetCameraBinding( fBottomRightCamera->GetID());
			light->SetIntensity( 10);
		}
	}

	Light *light = fScene.CreateLight( Coord3D( 0, 2000, 0));
	if (light != NULL)
		light->SetIntensity( 100);

	// Create primitives
	Object3D *object = ObjSpheric3D::CreateSphere( 250, eHighPrecision);
	if (object != NULL)
	{
		object->SetColor( eCheckerboardColoringPattern, Color( 0xFF, 0xFF, 0xFF), Color( 0xF8, 0x31, 0x2C));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eTestID] = object;
	}


	object = ObjCubic3D::CreateCube( 200);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eCubeID] = object;
	}


	object = ObjCylindric3D::CreateStraightCylinderPerpendicularToYAxis( 250, 250, 160, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eCylinderID] = object;
	}


	object = ObjCylindric3D::CreateHollowedCenterStraightCylinderPerpendicularToYAxis( 220, 250, 220, 250, 160, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eHollowedCenterCylinderID] = object;
	}


	object = ObjCylindric3D::CreateCylinderPerpendicularToYAxis( 210, 250, 160, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eRoundedCylinderID] = object;
	}


	object = ObjCylindric3D::CreateCylinderPerpendicularToYAxis( 250, 200, 160, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eHollowedCylinderID] = object;
	}


	object = ObjConic3D::CreateConePerpendicularToYAxis( 250, 160, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eConeID] = object;
	}


	object = ObjSpheric3D::CreateSphere( 250, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eSphereID] = object;
	}


	object = ObjSpheric3D::CreateSpintop( 250, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eSpintopID] = object;
	}


	object = ObjToric3D::CreateTorePerpendicularToYAxis( 190, 250, eHighPrecision);
	if (object != NULL)
	{
		object->SetPosBy( 0, 0, 0);
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fPrimitives[eToreID] = object;
	}


	object = ObjCylindric3D::CreateHollowedCenterStraightCylinderPerpendicularToYAxis( 220, 250, 220, 250, 20, eVeryHighPrecision);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eRingID] = object;
	}


	object = ObjPyramidal3D::CreateTriangularPyramidPerpendicularToYAxis( 250);
	if (object != NULL)
	{
		object->SetColor( Color( 0xBB, 0xBB, 0xBB));
		object->SetPosBy( 0, 0, 0);
		fPrimitives[eLastPrimitive] = object;
	}

	return true;
}


void AppBase::SelectPrimitive( ulong3 inPrimitiveID)
{
	MapOfObject3D_iter found = fPrimitives.find( inPrimitiveID);
	if (found != fPrimitives.end())
	{
		if (fScene.GetRootObject()->GetChildrenCount() == 1)
			fScene.GetRootObject()->RemoveNthChild(0);

		fScene.GetRootObject()->AddChild( found->second);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}
}


void AppBase::SetDrawingSettings( ulong3 inDrawingSettings)
{
	if ((inDrawingSettings & kDrawFilled) != 0)
	{
		SetScreenBackColor( Color( 0x35, 0x00, 0x35));
	}
	else
	{
		SetScreenBackColor( Color( 0x30, 0x30, 0x30));
	}

	fScene.SetDrawingSettings( inDrawingSettings);
}


void AppBase::SetObjectAnimationEnabled( bool inSet)
{
	fObjectAnimationEnabled = inSet;
}


bool AppBase::GetObjectAnimationEnabled() const
{
	return fObjectAnimationEnabled;
}


void AppBase::OnExpose( GraphicContext *inGC)
{
	Coord2D topLeft( 0, 0), bottomRight( kVirtualScreenWidth, kVirtualScreenHeight);
	inGC->FillRect( topLeft, bottomRight, fScreenBackColor);

	inGC->DrawSegment( Coord2D( 2*(kVirtualScreenWidth/3), 0), Coord2D( 2*(kVirtualScreenWidth/3), kVirtualScreenHeight), Color( 0xCC, 0xCC, 0xCC));
	inGC->DrawSegment( Coord2D( 2*(kVirtualScreenWidth/3), (kVirtualScreenHeight/2)), Coord2D( kVirtualScreenWidth, (kVirtualScreenHeight/2)), Color( 0xCC, 0xCC, 0xCC));

	fScene.Draw( inGC);

	if (fShowMouseTarget)
	{
		if (fLeftCamera != NULL)
		{
			slong3 screenHeight, screenWidth;
			fLeftCamera->GetScreenWorld().GetScreenSize( screenWidth, screenHeight);
			inGC->DrawSegment( Coord2D( (screenWidth/2)-10, screenHeight/2), Coord2D( (screenWidth/2)+10, screenHeight/2), Color( 0xFF, 0xFF, 0xFF));
			inGC->DrawSegment( Coord2D( (screenWidth/2), (screenHeight/2)-10), Coord2D( (screenWidth/2), (screenHeight/2)+10), Color( 0xFF, 0xFF, 0xFF));
		}
	}
}



const real3 kTranslationStep = 7;
const real3 kRotationStep = 0.001;

void AppBase::DoKeyDown( EKey inKey, ulong3 inRepeatCount)
{
	switch (inKey)
	{
	case eKeySpace:
		{
			SetObjectAnimationEnabled( !GetObjectAnimationEnabled());
		}
		break;

	case eKeyLeft:
	case eKeyUp:
	case eKeyRight:
	case eKeyDown:
		{
			if (fLeftCamera != NULL)
			{
				Vector3D vTranslation;

				if (inKey == eKeyLeft)
					vTranslation.SetCoordsTo( -1, 0, 0);
				else if (inKey == eKeyUp)
					vTranslation.SetCoordsTo( 0, 0, 1);
				else if (inKey == eKeyRight)
					vTranslation.SetCoordsTo( 1, 0, 0);
				else if (inKey == eKeyDown)
					vTranslation.SetCoordsTo( 0, 0, -1);
					
				fLeftCamera->Transform( vTranslation, World3D::sRootWorld3D);
				vTranslation.SetModule( kTranslationStep);
				
				Coord3D pos = fLeftCamera->GetPos();
				Math::TranslateBy( pos, vTranslation);
				fLeftCamera->SetPos( pos);
				
				if (fLeftCameraLight != NULL)
				{
					pos = fLeftCameraLight->GetPos();
					Math::TranslateBy( pos, vTranslation);
					fLeftCameraLight->SetPos( pos);
				}
			}
		}
		break;

	default:
		break;
	}
}


void AppBase::DoMouseMove( const Coord2D& inCursorPos)
{
}


void AppBase::_Run()
{
	if (GetObjectAnimationEnabled())
	{
		fAlpha_x = (fAlpha_x >= 360) ? 1 : (fAlpha_x + 1);
		fAlpha_y = (fAlpha_y >= 360) ? 1 : (fAlpha_y + 1);
		fAlpha_z = (fAlpha_z >= 360) ? 1 : (fAlpha_z + 1);

		real3 alpha_x = cos(Math::DegreeToRadian(fAlpha_x)) / 50;
		real3 alpha_y = cos(Math::DegreeToRadian(fAlpha_y)) / 25;
		real3 alpha_z = cos(Math::DegreeToRadian(fAlpha_z)) / 35;

		World3D center = World3D::sRootWorld3D;

		Object3D *obj = fScene.GetRootObject()->GetNthChild(0);
		if (obj != NULL)
		{
			Coord3D center;
			obj->GetCenter( center);
			World3D world( false, center);
			obj->RotateBy( world, alpha_x, alpha_y, alpha_z);
		}
	}

	if (GetCaptureMouse())
	{
		if (fLeftCamera != NULL)
		{
			Coord2D previousPos = fCursorPos, cursorPos;
			Engine3D::Get()->GetCursorPosition( cursorPos);
			Engine3D::Get()->SetCursorPosition( fCursorPos);
		
			real3 deltaX = cursorPos.GetX() - fCursorPos.GetX();
			real3 deltaY = fCursorPos.GetY() - cursorPos.GetY();

			if (deltaX != 0 || deltaY != 0)
			{
				Vector3D vOrientation( deltaX*kRotationStep, deltaY*kRotationStep, 1);
				fLeftCamera->Transform( vOrientation, World3D::sRootWorld3D);
				fLeftCamera->SetAxisOrientation( eZAxis, vOrientation);
			}
		}
	}
}


void AppBase::_DoBeginCaptureMouse()
{
	Engine3D::Get()->GetCursorPosition( fCursorPos);
	fShowMouseTarget = true;
}


void AppBase::_DoEndCaptureMouse()
{
	fShowMouseTarget = false;
}



// ============================================================================



AppPrimitive_test::AppPrimitive_test()
: fObject(NULL)
{
}


AppPrimitive_test::~AppPrimitive_test()
{
}


bool AppPrimitive_test::Init()
{
	if (!AppBase::Init())
		return  false;

	fObject = ObjSpheric3D::CreateSphere( 250, eHighPrecision);
	if (fObject)
	{
		fObject->SetColor( eCheckerboardColoringPattern, Color( 0xFF, 0xFF, 0xFF), Color( 0xF8, 0x31, 0x2C));
		fObject->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fObject);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_cube::AppPrimitive_cube()
: fCube(NULL)
{
}


AppPrimitive_cube::~AppPrimitive_cube()
{
}


bool AppPrimitive_cube::Init()
{
	if (!AppBase::Init())
		return  false;

	fCube = ObjCubic3D::CreateCube( 200);
	if (fCube)
	{
		fCube->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCube->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCube);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return  true;
}



// ============================================================================



AppPrimitive_cylinder::AppPrimitive_cylinder()
: fCylinder(NULL)
{
}


AppPrimitive_cylinder::~AppPrimitive_cylinder()
{
}


bool AppPrimitive_cylinder::Init()
{
	if (!AppBase::Init())
		return  false;

	fCylinder = ObjCylindric3D::CreateStraightCylinderPerpendicularToYAxis( 250, 250, 160, eVeryHighPrecision);
	if (fCylinder != NULL)
	{
		fCylinder->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCylinder->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCylinder);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_hollowedCenterCylinder::AppPrimitive_hollowedCenterCylinder()
: fCylinder(NULL)
{
}


AppPrimitive_hollowedCenterCylinder::~AppPrimitive_hollowedCenterCylinder()
{
}


bool AppPrimitive_hollowedCenterCylinder::Init()
{
	if (!AppBase::Init())
		return  false;

	fCylinder = ObjCylindric3D::CreateHollowedCenterStraightCylinderPerpendicularToYAxis( 220, 250, 220, 250, 160, eVeryHighPrecision);
	if (fCylinder != NULL)
	{
		fCylinder->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCylinder->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCylinder);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_roundedCylinder::AppPrimitive_roundedCylinder()
: fCylinder(NULL)
{
}


AppPrimitive_roundedCylinder::~AppPrimitive_roundedCylinder()
{
}


bool AppPrimitive_roundedCylinder::Init()
{
	if (!AppBase::Init())
		return  false;

	fCylinder = ObjCylindric3D::CreateCylinderPerpendicularToYAxis( 210, 250, 160, eVeryHighPrecision);
	if (fCylinder != NULL)
	{
		fCylinder->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCylinder->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCylinder);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_hollowedCylinder::AppPrimitive_hollowedCylinder()
: fCylinder(NULL)
{
}


AppPrimitive_hollowedCylinder::~AppPrimitive_hollowedCylinder()
{
}


bool AppPrimitive_hollowedCylinder::Init()
{
	if (!AppBase::Init())
		return  false;

	fCylinder = ObjCylindric3D::CreateCylinderPerpendicularToYAxis( 250, 200, 160, eVeryHighPrecision);
	if (fCylinder != NULL)
	{
		fCylinder->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCylinder->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCylinder);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_cone::AppPrimitive_cone()
: fCone(NULL)
{
}


AppPrimitive_cone::~AppPrimitive_cone()
{
}


bool AppPrimitive_cone::Init()
{
	if (!AppBase::Init())
		return  false;

	fCone = ObjConic3D::CreateConePerpendicularToYAxis( 250, 160, eVeryHighPrecision);
	if (fCone != NULL)
	{
		fCone->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fCone->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fCone);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_sphere::AppPrimitive_sphere()
: fSphere(NULL)
{
}


AppPrimitive_sphere::~AppPrimitive_sphere()
{
}


bool AppPrimitive_sphere::Init()
{
	if (!AppBase::Init())
		return  false;

	fSphere = ObjSpheric3D::CreateSphere( 250, eVeryHighPrecision);
	if (fSphere)
	{
		fSphere->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fSphere->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fSphere);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_spintop::AppPrimitive_spintop()
: fSpintop(NULL)
{
}


AppPrimitive_spintop::~AppPrimitive_spintop()
{
}


bool AppPrimitive_spintop::Init()
{
	if (!AppBase::Init())
		return  false;

	fSpintop = ObjSpheric3D::CreateSpintop( 250, eVeryHighPrecision);
	if (fSpintop)
	{
		fSpintop->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fSpintop->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fSpintop);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_tore::AppPrimitive_tore()
: fTore(NULL)
{
}


AppPrimitive_tore::~AppPrimitive_tore()
{
}


bool AppPrimitive_tore::Init()
{
	if (!AppBase::Init())
		return  false;

	fTore = ObjToric3D::CreateTorePerpendicularToYAxis( 190, 250, eHighPrecision);
	if (fTore)
	{
		fTore->SetPosBy( 0, 0, 0);
		fTore->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fScene.GetRootObject()->AddChild( fTore);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_ring::AppPrimitive_ring()
: fRing(NULL)
{
}


AppPrimitive_ring::~AppPrimitive_ring()
{
}


bool AppPrimitive_ring::Init()
{
	if (!AppBase::Init())
		return  false;

	fRing = ObjCylindric3D::CreateHollowedCenterStraightCylinderPerpendicularToYAxis( 220, 250, 220, 250, 20, eVeryHighPrecision);
	if (fRing != NULL)
	{
		fRing->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fRing->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fRing);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================



AppPrimitive_pyramid::AppPrimitive_pyramid()
: fPyramid(NULL)
{
}


AppPrimitive_pyramid::~AppPrimitive_pyramid()
{
}


bool AppPrimitive_pyramid::Init()
{
	if (!AppBase::Init())
		return  false;

	fPyramid = ObjPyramidal3D::CreateTriangularPyramidPerpendicularToYAxis( 250);
	if (fPyramid != NULL)
	{
		fPyramid->SetColor( Color( 0xBB, 0xBB, 0xBB));
		fPyramid->SetPosBy( 0, 0, 0);
		fScene.GetRootObject()->AddChild( fPyramid);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



// ============================================================================


#if 0

AppPrimitive_mug::AppPrimitive_mug()
{
}


AppPrimitive_mug::~AppPrimitive_mug()
{
}


bool AppPrimitive_mug::Init()
{
	if (!AppBase::Init())
		return  false;

	std::wstring modelPath;
	Engine3D::Get()->GetResourcesFolderPath( modelPath);
	modelPath.append( L"models\\mug.obj");

	Object3D *mug = Engine3D::Get()->GetModeler()->CreateFromFile( NULL, modelPath.c_str(), 100);
	if (mug != NULL)
	{
		mug->SetColor( Color( 0xBB, 0xBB, 0xBB));
		mug->SetPosBy( 0.0, 0.0, 0.0);
		fScene.GetRootObject()->AddChild( 0, mug);
		fScene.UpdateViewCoords();
		fScene.UpdateLightness();
	}

	return true;
}



AppPrimitive_mix::AppPrimitive_mix()
{
    fAlpha_x = 0;
    fAlpha_y = 45;
    fAlpha_z = 90;
}


AppPrimitive_mix::~AppPrimitive_mix()
{
}


const ulong3 kOBJECTID_MAINRING = 0;
const ulong3 kOBJECTID_BOTTOMRING = 1;
const ulong3 kOBJECTID_MIDDLESPHERE = 2;
const ulong3 kOBJECTID_CY1 = 10;
const ulong3 kOBJECTID_CY2 = 11;
const ulong3 kOBJECTID_CY3 = 12;
const ulong3 kOBJECTID_CY4 = 13;
const ulong3 kOBJECTID_CUBE1 = 100;
const ulong3 kOBJECTID_SPHERE1 = 101;
const ulong3 kOBJECTID_RING1 = 102;
const ulong3 kOBJECTID_TORE1 = 103;
const ulong3 kOBJECTID_PYRAMID1 = 104;
const ulong3 kOBJECTID_CONE1 = 105;
const ulong3 kOBJECTID_CYLINDER1 = 106;
const ulong3 kOBJECTID_CYLINDER2 = 107;

const ulong3 kCYLINDER_COUNT = 8;
const ulong3 kCYLINDER_ID[8] = { 10, 11, 12, 13, 14, 15, 16, 17};
const ulong3 kOBJECT_ID[8] = { 100, 101, 102, 103, 104, 105, 106, 107};
const real3 kARG[8] = { 0, kPI4, kPI2, kPI2 + kPI4, kPI, kPI + kPI4, kPI + kPI2, kPI + kPI2 + kPI4};


bool AppPrimitive_mix::Init()
{
	if (!Application3D::Init())
		return false;

	// init the left camera
    Camera *camera = fScene.CreateCamera( Coord3D ( 0, 750, -2350)/*, Rotation3D( kPI4 / 4, 0, 0)*/);
	if (camera != NULL)
	{
		// init the screen world
		camera->GetScreenWorld().SetScreenPos( 0, 0);
		camera->GetScreenWorld().SetScreenSize( 960, 760);
		camera->GetScreenWorld().SetZ( 700);
		camera->GetScreenWorld().InvertYAxis( true);

		Light *light = fScene.CreateLight( Coord3D ( 0, 500, -2000));
		if (light != NULL)
		{
			light->SetCameraBinding( camera->GetID());
			light->SetIntensity( 10);
		}
	}

	// init the bottom right camera
    camera = fScene.CreateCamera( Coord3D ( 0, 7000, 0)/*, Rotation3D( kPI2, 0, 0)*/);
	if (camera != NULL)
	{
		// init the screen world
		camera->GetScreenWorld().SetScreenPos( 960, 380);
		camera->GetScreenWorld().SetScreenSize( 320, 380);
		camera->GetScreenWorld().SetZ( 700);
		camera->GetScreenWorld().InvertYAxis( true);

		Light *light = fScene.CreateLight( Coord3D ( 0, 7000, 0));
		if (light != NULL)
		{
			light->SetCameraBinding( camera->GetID());
			light->SetIntensity( 10);
		}
	}

	// init the top right camera
    camera = fScene.CreateCamera( Coord3D ( 0, 0, -7000)/*, Rotation3D( 0, 0, 0)*/);
	if (camera != NULL)
	{
		// init the screen world
		camera->GetScreenWorld().SetScreenPos( 960, 0);
		camera->GetScreenWorld().SetScreenSize( 320, 380);
		camera->GetScreenWorld().SetZ( 700);
		camera->GetScreenWorld().InvertYAxis( true);

		Light *light = fScene.CreateLight( Coord3D ( 0, 0, -7000));
		if (light != NULL)
		{
			light->SetCameraBinding( camera->GetID());
			light->SetIntensity( 10);
		}
	}

	Object3D *mainRing = Engine3D::Get()->GetModeler()->CreateRing( NULL, 60, 800, 1200, kHigh);
	if (mainRing)
	{
		World3D rotationCenter;

		mainRing->SetColor( Color( 0xBB, 0xBB, 0xBB));

		for (ulong3 pos = 0 ; pos < kCYLINDER_COUNT ; ++pos)
		{
			Object3D *cy = Engine3D::Get()->GetModeler()->CreateCylinder_v2( NULL, 120, 120);
			if (cy)
			{
				cy->SetColor( Color( 0xBB, 0xBB, 0xBB));
				rotationCenter.SetPos( cy->GetPos());
				cy->RotateBy( rotationCenter, kPI2, 0, 0);
				real3 x = 0, z = 0;
				Math::GetCartesianCoord( 1000, kARG[pos], x, z);
				cy->SetPosBy( x, 90, z);
				mainRing->AddChild( kCYLINDER_ID[pos], cy);
			}
		}

		Object3D *cube1 = Engine3D::Get()->GetModeler()->CreateCube( NULL, 90);
		if (cube1)
		{
			cube1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, 0, x, z);
			cube1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_CUBE1, cube1);
		}

		Object3D *cylinder1 = Engine3D::Get()->GetModeler()->CreateCylinder_v2( NULL, 55, 6, kMedium);
		if (cylinder1)
		{
			cylinder1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI4, x, z);
			cylinder1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_CYLINDER1, cylinder1);
		}


		Object3D *sphere1 = Engine3D::Get()->GetModeler()->CreateSphere( NULL, 70, kMedium);
		if (sphere1)
		{
			sphere1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI2, x, z);
			sphere1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_SPHERE1, sphere1);
		}

		Object3D *pyramid1 = Engine3D::Get()->GetModeler()->CreateTriangularPyramid( NULL, 150);
		if (pyramid1)
		{
			pyramid1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI2 + kPI4, x, z);
			pyramid1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_PYRAMID1, pyramid1);

		}

		Object3D *ring1 = Engine3D::Get()->GetModeler()->CreateRing( NULL, 10, 55, 70, kMedium);
		if (ring1)
		{
			ring1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI, x, z);
			ring1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_RING1, ring1);

		}

		Object3D *cone1 = new Object3D();
		if (cone1)
		{
			slong3 height = 30, diameter = 10;
			Object3D *child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->SetPosBy( 0, 70, 0);
				cone1->AddChild( 0 , child);
			}

			child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->RotateBy( World3D::sRootWorld3D, kPI, 0, 0);
				child->SetPosBy( 0, -70, 0);
				cone1->AddChild( 1 , child);
			}

			child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->RotateBy( World3D::sRootWorld3D, 0, 0, -kPI2);
				child->SetPosBy( 70, 0, 0);
				cone1->AddChild( 2 , child);
			}

			child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->RotateBy( World3D::sRootWorld3D, 0, 0, kPI2);
				child->SetPosBy( -70, 0, 0);
				cone1->AddChild( 3 , child);
			}

			child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->RotateBy( World3D::sRootWorld3D, kPI2, 0, 0);
				child->SetPosBy( 0, 0, 70);
				cone1->AddChild( 4 , child);
			}

			child = Engine3D::Get()->GetModeler()->CreateCone( NULL, height, diameter, kMedium);
			if (child != NULL)
			{
				child->SetColor( Color( 0xBB, 0xBB, 0xBB));
				child->RotateBy( World3D::sRootWorld3D, -kPI2, 0, 0);
				child->SetPosBy( 0, 0, -70);
				cone1->AddChild( 5 , child);
			}

			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI + kPI4, x, z);
			cone1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_CONE1, cone1);
		}

		Object3D *tore1 = Engine3D::Get()->GetModeler()->CreateTore( NULL, 50, 70, kMedium);
		if (tore1)
		{
			tore1->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI + kPI2, x, z);
			tore1->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_TORE1, tore1);

		}

		Object3D *cylinder2 = Engine3D::Get()->GetModeler()->CreateCylinder_v2( NULL, 10, 120, kMedium);
		if (cylinder2)
		{
			cylinder2->SetColor( Color( 0xBB, 0xBB, 0xBB));
			real3 x = 0, z = 0;
			Math::GetCartesianCoord( 1000, kPI + kPI2 + kPI4, x, z);
			cylinder2->SetPosBy( x, 270, z);
			mainRing->AddChild( kOBJECTID_CYLINDER2, cylinder2);
		}

		mainRing->SetPosBy( 0.0, 0.0, 0.0);
		fScene.GetRootObject()->AddChild( kOBJECTID_MAINRING, mainRing);
	}
/*
	Object3D *bottomRing = Engine3D::Get()->GetModeler()->CreateRing( NULL, 60, 680, 780, kHigh);
	if (bottomRing != NULL)
	{
		bottomRing->SetColor( Color( 0xBB, 0xBB, 0xBB));
		bottomRing->SetPosBy( 0.0, 0.0, 0.0);
		fScene.GetRootObject()->AddChild( kOBJECTID_BOTTOMRING, bottomRing);
	}
*/
/*
	Object3D *middleSphere = Engine3D::Get()->GetModeler()->CreateSphere( NULL, 300, kHigh);
	if (middleSphere != NULL)
	{
		middleSphere->SetColor( Color( 0xBB, 0xBB, 0xBB));
		middleSphere->SetPosBy( 0.0, 0.0, 0.0);
		fScene.GetRootObject()->AddChild( kOBJECTID_MIDDLESPHERE, middleSphere);
	}
*/
	Light *light = fScene.CreateLight( Coord3D( 0, 450, -1000));
	if (light != NULL)
		light->SetIntensity( 75);

	fScene.UpdateViewCoords();
	fScene.UpdateLightness();

	return true;
}


void AppPrimitive_mix::SetDrawingSettings( ulong3 inDrawingSettings)
{
	if ((inDrawingSettings & kDrawFilled) != 0)
	{
		SetScreenBackColor( Color( 0x35, 0x00, 0x35));
	}
	else
	{
		SetScreenBackColor( Color( 0x30, 0x30, 0x30));
	}

	fScene.SetDrawingSettings( inDrawingSettings);
}


void AppPrimitive_mix::OnExpose( GraphicContext *inGC)
{
	slong3 width = 0, height = 0;
	Engine3D::Get()->GetScreenSize( width, height);

	Coord2D topLeft( 0, 0), bottomRight( width, height);
	inGC->FillRect( topLeft, bottomRight, fScreenBackColor);

	inGC->DrawSegment( Coord2D( 960, 0), Coord2D( 960, 760), Color( 0xCC, 0xCC, 0xCC));
	inGC->DrawSegment( Coord2D( 960, 380), Coord2D( 1280, 380), Color( 0xCC, 0xCC, 0xCC));

	fScene.Draw( inGC);
}


void AppPrimitive_mix::_Run()
{
	fAlpha_x = (fAlpha_x >= 360) ? 1 : (fAlpha_x + 1);
    fAlpha_y = (fAlpha_y >= 360) ? 1 : (fAlpha_y + 1);
    fAlpha_z = (fAlpha_z >= 360) ? 1 : (fAlpha_z + 1);

    real3 alpha_x = cos(Math::DegreeToRadian(fAlpha_x)) / 200;
    real3 alpha_y = cos(Math::DegreeToRadian(fAlpha_y)) / 100;
    real3 alpha_z = cos(Math::DegreeToRadian(fAlpha_z)) / 150;

	World3D center = World3D::sRootWorld3D;

	Object3D *obj = fScene.GetRootObject();
	if (obj != NULL)
	{
		Object3D *mainRing = obj->GetChild( kOBJECTID_MAINRING);
		if ( mainRing != NULL)
		{
			Object3D *cube1 = mainRing->GetChild( kOBJECTID_CUBE1);
			if ( cube1 != NULL)
			{
				center.SetPos( cube1->GetPos());
				cube1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *cylinder1 = mainRing->GetChild( kOBJECTID_CYLINDER1);
			if ( cylinder1 != NULL)
			{
				center.SetPos( cylinder1->GetPos());
				cylinder1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *sphere1 = mainRing->GetChild( kOBJECTID_SPHERE1);
			if ( sphere1 != NULL)
			{
				center.SetPos( sphere1->GetPos());
				sphere1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *pyramid1 = mainRing->GetChild( kOBJECTID_PYRAMID1);
			if ( pyramid1 != NULL)
			{
				center.SetPos( pyramid1->GetPos());
				pyramid1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *ring1 = mainRing->GetChild( kOBJECTID_RING1);
			if (ring1 != NULL)
			{
				center.SetPos( ring1->GetPos());
				ring1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *cone1 = mainRing->GetChild( kOBJECTID_CONE1);
			if (cone1 != NULL)
			{
				center.SetPos( cone1->GetPos());
				cone1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *tore1 = mainRing->GetChild( kOBJECTID_TORE1);
			if (tore1 != NULL)
			{
				center.SetPos( tore1->GetPos());
				tore1->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			Object3D *cylinder2 = mainRing->GetChild( kOBJECTID_CYLINDER2);
			if (cylinder2 != NULL)
			{
				center.SetPos( cylinder2->GetPos());
				cylinder2->RotateBy( center, alpha_x * 4, alpha_y * 4, alpha_z * 4);
			}

			center.SetPos( mainRing->GetPos());
			mainRing->RotateBy( center, 0, Math::DegreeToRadian(0.7), 0);
		}
/*
		Object3D *bottomRing = obj->GetChild( kOBJECTID_BOTTOMRING);
		if (bottomRing != NULL)
		{
			center.SetPos( bottomRing->GetPos());
			bottomRing->RotateBy( center, 0, -Math::DegreeToRadian(0.7), 0);
		}
*/
/*
		Object3D *middleSphere = obj->GetChild( kOBJECTID_MIDDLESPHERE);
		if (middleSphere != NULL)
		{
			center.SetPos( middleSphere->GetPos());
			middleSphere->RotateBy( center, 0, -Math::DegreeToRadian(0.7), 0);
		}
*/
	}
}

#endif



} // namespace KHEOPS
