

#include "core3.h"
#include <assert.h>
#include <math.h>
#include "objects3.h"
#include "modeler3.h"
#include "renderer3.h"
#include "scene3.h"
#include "application3.h"
#include "app_solar_system.h"



namespace KHEOPS
{


#if 0

AppSolarSystem::AppSolarSystem()
{
	fCameraID = -1;
}


AppSolarSystem::~AppSolarSystem()
{
}


const ulong3 kOBJECTID_SUN = 10;
const ulong3 kOBJECTID_MERCURE = 11;
const ulong3 kOBJECTID_VENUS = 12;
const ulong3 kOBJECTID_EARTH = 13;
const ulong3 kOBJECTID_MARS = 14;
const ulong3 kOBJECTID_JUPITER = 15;
const ulong3 kOBJECTID_SATURN = 16;
const ulong3 kOBJECTID_URANUS = 17;
const ulong3 kOBJECTID_NEPTUNE = 18;
const ulong3 kOBJECTID_PLUTON = 19;
const ulong3 kOBJECTID_MOON = 100;

// unit = earth diameter
const real3 kDIAMETER_SCALING = 40;
const real3 kDIAMETER_SUN = 2;	// true value: 109
const real3 kDIAMETER_MERCURE = 0.382;
const real3 kDIAMETER_VENUS = 0.948;
const real3 kDIAMETER_EARTH = 1;
const real3 kDIAMETER_MARS = 0.532;
const real3 kDIAMETER_JUPITER = 3;	// true value: 11.194;
const real3 kDIAMETER_SATURNE = 9.454;
const real3 kDIAMETER_URANUS = 4.021;
const real3 kDIAMETER_NEPTUNE = 3.613;
const real3 kDIAMETER_PLUTON = 0.180;
const real3 kDIAMETER_MOON = 0.2725;

// unit = U.A
const real3 kUA_SCALING = 1000;
const real3 kDIST_FROM_SUN_MERCURE = 0.39;
const real3 kDIST_FROM_SUN_VENUS = 0.72;
const real3 kDIST_FROM_SUN_EARTH = 1;
const real3 kDIST_FROM_SUN_MARS = 1.52;
const real3 kDIST_FROM_SUN_JUPITER = 2.5; // true value: 5.20
const real3 kDIST_FROM_SUN_SATURNE = 9.50;
const real3 kDIST_FROM_SUN_URANUS = 19.20;
const real3 kDIST_FROM_SUN_NEPTUNE = 30;
const real3 kDIST_FROM_SUN_PLUTON = 39.50;
const real3 kDIST_FROM_EARTH_MOON = 0.08; // true value: 0.00257


// unit = earth day
const real3 kALPHA_SCALING = 1;;
const real3 kREVOLUTION_SUN = 30;
const real3 kREVOLUTION_MERCURE = 58.60;
const real3 kREVOLUTION_VENUS = 243;
const real3 kREVOLUTION_EARTH = 1;
const real3 kREVOLUTION_MARS = 1.025;
const real3 kREVOLUTION_JUPITER = 0.4125;
const real3 kREVOLUTION_SATURNE = 0.4375;
const real3 kREVOLUTION_URANUS = 0.7292;
const real3 kREVOLUTION_NEPTUNE = 0.8;
const real3 kREVOLUTION_PLUTON = 6.4;


// unit : earth year
const real3 kYEAR_MERCURE = 0.2411;
const real3 kYEAR_VENUS = 0.6156;
const real3 kYEAR_EARTH = 1;
const real3 kYEAR_MARS = 1.8;
const real3 kYEAR_JUPITER = 11.9;
const real3 kYEAR_SATURNE = 29.50;
const real3 kYEAR_URANUS = 84;
const real3 kYEAR_NEPTUNE = 164.8;
const real3 kYEAR_PLUTON = 247.7;

const real3 kROTATION_MOON = 0.2; // true value: 0.0767



bool AppSolarSystem::Init()
{
	if (!Application3D::Init())
		return false;
	
	Light *cameraLight = NULL;

	// init the camera
//	Camera *camera = fScene.CreateCamera( Coord3D ( 0, 0, -3500), Rotation3D( kPI4 / 3, 0, 0));
	Camera *camera = fScene.CreateCamera( Coord3D ( 0, 500, -3200)/*, Rotation3D( kPI4 / 3, 0, 0)*/);
//	Camera *camera = fScene.CreateCamera( Coord3D ( 0, 4000, 0), Rotation3D( kPI2, 0, 0));
	if (camera != NULL)
	{
		// init the screen world

		fCameraID = camera->GetID();

		camera->GetScreenWorld().SetScreenPos( 0, 0);
		camera->GetScreenWorld().SetScreenSize( 1280, 760);
		camera->GetScreenWorld().SetZ( 700);
		camera->GetScreenWorld().InvertYAxis( true);

		cameraLight = fScene.CreateLight( Coord3D ( 0, 500, -3200));
		if (cameraLight != NULL)
		{
			cameraLight->SetCameraBinding( camera->GetID());
			cameraLight->SetIntensity( 25);
		}
	}

	Light *sunLight = fScene.CreateLight( Coord3D( 0, 0, 0));
	if (sunLight != NULL)
	{
		sunLight->SetIntensity( 100);
	}

	Light *lightForSun = fScene.CreateLight( Coord3D( 0, 0, -2000));
	if (lightForSun != NULL)
	{
		lightForSun->SetIntensity( 100);
	}

	Object3D *sun = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_SUN * kDIAMETER_SCALING, kHigh);
	if (sun)
	{
		sun->SetColor( Color( 0xFF, 0xFF, 0xFF));
		fScene.GetRootObject()->AddChild( kOBJECTID_SUN, sun);

		if (sunLight != NULL)
			fScene.SetObjectLighted( *sunLight, sun, false);

		if (cameraLight != NULL)
			fScene.SetObjectLighted( *cameraLight, sun, false);
	}

	Object3D *mercure = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_MERCURE * kDIAMETER_SCALING, kHigh);
	if (mercure)
	{
		mercure->SetColor( Color( 0xD0, 0x0, 0xBF));
		mercure->SetPosBy( kDIST_FROM_SUN_MERCURE * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_MERCURE, mercure);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, mercure, false);

		ArrayOfCoord3D orbit;
		Math::GetCoordsForCirclePerpendicularToYAxis( orbit, kDIST_FROM_SUN_MERCURE * kUA_SCALING, 360);
		fOrbits[kOBJECTID_MERCURE] = orbit;
	}

	Object3D *venus = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_VENUS * kDIAMETER_SCALING, kHigh);
	if (venus)
	{
		venus->SetColor( Color( 0x00, 0xC8, 0x4B));
		venus->SetPosBy( kDIST_FROM_SUN_VENUS * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_VENUS, venus);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, venus, false);
	}

	Object3D *earth = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_EARTH * kDIAMETER_SCALING, kHigh);
	if (earth)
	{
		earth->SetColor( Color( 0x41, 0x3D, 0xA5));
		earth->SetPosBy( kDIST_FROM_SUN_EARTH * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_EARTH, earth);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, earth, false);
	}

	Object3D *moon = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_MOON * kDIAMETER_SCALING, kHigh);
	if (moon)
	{
		moon->SetColor( Color( 0xAA, 0xAA, 0xAA));
		moon->SetPosBy( (kDIST_FROM_SUN_EARTH + kDIST_FROM_EARTH_MOON) * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_MOON, moon);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, moon, false);
	}

	Object3D *mars = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_MARS * kDIAMETER_SCALING, kHigh);
	if (mars)
	{
		mars->SetColor( Color( 0xED, 0x6E, 0x3F));
		mars->SetPosBy( kDIST_FROM_SUN_MARS * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_MARS, mars);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, mars, false);
	}

	Object3D *jupiter = Engine3D::Get()->GetModeler()->CreateSphere( NULL, kDIAMETER_JUPITER * kDIAMETER_SCALING, kHigh);
	if (jupiter)
	{
		jupiter->SetColor( Color( 0xD7, 0xA7, 0x7A));
		jupiter->SetPosBy( kDIST_FROM_SUN_JUPITER * kUA_SCALING, 0, 0);
		fScene.GetRootObject()->AddChild( kOBJECTID_JUPITER, jupiter);

		if (lightForSun != NULL)
			fScene.SetObjectLighted( *lightForSun, jupiter, false);
	}

	fScene.UpdateViewCoords();
	fScene.UpdateLightness();

	return true;
}


void AppSolarSystem::SetDrawingSettings( ulong3 inDrawingSettings)
{
	if ((inDrawingSettings & kDrawFilled) != 0)
	{
		SetScreenBackColor( Color( 0x0, 0x0, 0x0));
	}
	else
	{
		SetScreenBackColor( Color( 0x30, 0x30, 0x30));
	}

	fScene.SetDrawingSettings( inDrawingSettings);
}


void AppSolarSystem::OnExpose( GraphicContext *inGC)
{
	slong3 width = 0, height = 0;
	Engine3D::Get()->GetScreenSize( width, height);

	Coord2D topLeft( 0, 0), bottomRight( width, height);
	inGC->FillRect( topLeft, bottomRight, fScreenBackColor);

/*
	Camera *camera = fScene.GetCamera( fCameraID);
	if (camera != NULL)
	{
		for (std::map< ulong3 , ArrayOfCoord3D >::iterator orbitIter = fOrbits.begin() ; orbitIter != fOrbits.end() ; orbitIter++)
		{
			ArrayOfCoord3D cameraCoords = orbitIter->second;
			World3D::sRootWorld3D.Transform( cameraCoords, *camera);

			ArrayOfCoord2D screenCoords;
			screenCoords.resize( cameraCoords.size());

			camera->GetScreenWorld().Transform( cameraCoords, *camera, screenCoords);
			inGC->DrawPixels( screenCoords, Color( 0xBB, 0xBB, 0xBB));
		}
	}
*/

	fScene.Draw( inGC);
}


void AppSolarSystem::_Run()
{
	World3D center = World3D::sRootWorld3D;

	Object3D *obj = fScene.GetRootObject();
	if (obj != NULL)
	{
		Object3D *sun = obj->GetChild( kOBJECTID_SUN);
		if (sun != NULL)
		{
			center.SetPos( sun->GetPos());
			sun->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_SUN) * kALPHA_SCALING), 0);
		}

		Object3D *mercure = obj->GetChild( kOBJECTID_MERCURE);
		if (mercure != NULL)
		{
			center.SetPos( mercure->GetPos());
			mercure->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_MERCURE) * kALPHA_SCALING), 0);

			center.SetPos( World3D::sRootWorld3D.GetPos());
			mercure->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_MERCURE) * kALPHA_SCALING), 0);
		}

		Object3D *venus = obj->GetChild( kOBJECTID_VENUS);
		if (venus != NULL)
		{
			center.SetPos( venus->GetPos());
			venus->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_VENUS) * kALPHA_SCALING), 0);

			center.SetPos( World3D::sRootWorld3D.GetPos());
			venus->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_VENUS) * kALPHA_SCALING), 0);
		}

		Object3D *earth = obj->GetChild( kOBJECTID_EARTH);
		if (earth != NULL)
		{
			Object3D *moon = obj->GetChild( kOBJECTID_MOON);
			if (moon != NULL)
			{
				center.SetPos( earth->GetPos());
				moon->RotateBy( center, 0, Math::DegreeToRadian( (1 / kROTATION_MOON) * kALPHA_SCALING), 0);

				center.SetPos( World3D::sRootWorld3D.GetPos());
				moon->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_EARTH) * kALPHA_SCALING), 0);
			}

			center.SetPos( earth->GetPos());
			earth->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_EARTH) * kALPHA_SCALING), 0);

			center.SetPos( World3D::sRootWorld3D.GetPos());
			earth->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_EARTH) * kALPHA_SCALING), 0);
		}

		Object3D *mars = obj->GetChild( kOBJECTID_MARS);
		if (mars != NULL)
		{
			center.SetPos( mars->GetPos());
			mars->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_MARS) * kALPHA_SCALING), 0);

			center.SetPos( World3D::sRootWorld3D.GetPos());
			mars->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_MARS) * kALPHA_SCALING), 0);
		}

		Object3D *jupiter = obj->GetChild( kOBJECTID_JUPITER);
		if (jupiter != NULL)
		{
			center.SetPos( jupiter->GetPos());
			jupiter->RotateBy( center, 0, Math::DegreeToRadian( (1 / kREVOLUTION_JUPITER) * kALPHA_SCALING), 0);

			center.SetPos( World3D::sRootWorld3D.GetPos());
			jupiter->RotateBy( center, 0, Math::DegreeToRadian( (1 / kYEAR_JUPITER) * kALPHA_SCALING), 0);
		}
	}
}

#endif



} // namespace KHEOPS
