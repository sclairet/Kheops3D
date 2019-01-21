

#include "core3.h"
#include <assert.h>
#include <math.h>
#include "objects3.h"
#include "objects3_behaviour.h"
#include "modeler3.h"
#include "renderer3.h"
#include "scene3.h"
#include "application3.h"
#include "app_demos.h"



namespace KHEOPS
{



AppDemo::AppDemo()
{
    fShowMouseTarget = false;
	fObjectAnimationEnabled = false;
	
	fAlpha_x = 0;
    fAlpha_y = 45;
    fAlpha_z = 90;

	fCamera = NULL;
	fCameraLight = NULL;
}


AppDemo::~AppDemo()
{
}


bool AppDemo::Init()
{
	if (!Application3D::Init())
		return false;

	// init the camera
    fCamera = fScene.CreateCamera( Coord3D ( 0, 200, -1000));
	if (fCamera != NULL)
	{
		// init the screen world
		fCamera->GetScreenWorld().SetScreenPos( 0, 0);
		fCamera->GetScreenWorld().SetScreenSize( 1280, 760);
		fCamera->GetScreenWorld().SetZ( 700);
		fCamera->GetScreenWorld().InvertYAxis( true);

		fCameraLight = fScene.CreateLight( Coord3D ( 0.0, 0.0, -1000));
		if (fCameraLight != NULL)
		{
			fCameraLight->SetCameraBinding( fCamera->GetID());
			fCameraLight->SetIntensity( 30);
		}
	}

	Light *light = fScene.CreateLight( Coord3D( 250, 500, 250));
	if (light != NULL)
		light->SetIntensity( 100);

	return true;
}


void AppDemo::SetDrawingSettings( ulong3 inDrawingSettings)
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


void AppDemo::SetObjectAnimationEnabled( bool inSet)
{
	fObjectAnimationEnabled = inSet;
}


bool AppDemo::GetObjectAnimationEnabled() const
{
	return fObjectAnimationEnabled;
}


void AppDemo::OnExpose( GraphicContext *inGC)
{
	slong3 width = 0, height = 0;
	Engine3D::Get()->GetScreenSize( width, height);

	Coord2D topLeft( 0, 0), bottomRight( width, height);
	inGC->FillRect( topLeft, bottomRight, fScreenBackColor);

	fScene.Draw( inGC);

	if (fShowMouseTarget)
	{
		if (fCamera != NULL)
		{
			slong3 screenHeight, screenWidth;
			fCamera->GetScreenWorld().GetScreenSize( screenWidth, screenHeight);
			inGC->DrawSegment( Coord2D( (screenWidth/2)-10, screenHeight/2), Coord2D( (screenWidth/2)+10, screenHeight/2), Color( 0xFF, 0xFF, 0xFF));
			inGC->DrawSegment( Coord2D( (screenWidth/2), (screenHeight/2)-10), Coord2D( (screenWidth/2), (screenHeight/2)+10), Color( 0xFF, 0xFF, 0xFF));
		}
	}
}



const real3 kTranslationStep = 7;
const real3 kRotationStep = 0.001;

void AppDemo::DoKeyDown( EKey inKey, ulong3 inRepeatCount)
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
			if (fCamera != NULL)
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
					
				fCamera->Transform( vTranslation, World3D::sRootWorld3D);
				vTranslation.SetModule( kTranslationStep);
				
				Coord3D pos = fCamera->GetPos();
				Math::TranslateBy( pos, vTranslation);
				fCamera->SetPos( pos);
				
				if (fCameraLight != NULL)
				{
					pos = fCameraLight->GetPos();
					Math::TranslateBy( pos, vTranslation);
					fCameraLight->SetPos( pos);
				}
			}
		}
		break;

	default:
		break;
	}
}


void AppDemo::_Run()
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

		Object3D *obj = _GetObject();
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
		if (fCamera != NULL)
		{
			Coord2D previousPos = fCursorPos, cursorPos;
			Engine3D::Get()->GetCursorPosition( cursorPos);
			Engine3D::Get()->SetCursorPosition( fCursorPos);
		
			real3 deltaX = cursorPos.GetX() - fCursorPos.GetX();
			real3 deltaY = fCursorPos.GetY() - cursorPos.GetY();

			if (deltaX != 0 || deltaY != 0)
			{
				Vector3D vOrientation( deltaX*kRotationStep, deltaY*kRotationStep, 1);
				fCamera->Transform( vOrientation, World3D::sRootWorld3D);
				fCamera->SetAxisOrientation( eZAxis, vOrientation);
			}
		}
	}
}


void AppDemo::_DoBeginCaptureMouse()
{
	Engine3D::Get()->GetCursorPosition( fCursorPos);
	fShowMouseTarget = true;
}


void AppDemo::_DoEndCaptureMouse()
{
	fShowMouseTarget = false;
}



// ============================================================================



AppDemo_chessboard::AppDemo_chessboard()
: fObj(NULL)
{
}


AppDemo_chessboard::~AppDemo_chessboard()
{
}


bool AppDemo_chessboard::Init()
{
	if (!AppDemo::Init())
		return  false;

	Object3D *chessboard = ObjRect3D::CreateRect( 1000, 10, 1000, 10, eBaseXoZ);
	if (chessboard)
	{
		chessboard->SetColor( eCheckerboardColoringPattern, Color( 0xFF, 0xFF, 0xFF), Color( 0, 0, 0));
		chessboard->SetPosBy( -500, 0, -500);
		fScene.GetRootObject()->AddChild( chessboard);
	}

	fObj = ObjSpheric3D::CreateSpintop( 100, eVeryHighPrecision);
	if (fObj != NULL)
	{
		fObj->SetColor( Color( 0xBB, 0xBB, 0xBB));
		chessboard->SetPosBy( 250, -100, 250);
		fScene.GetRootObject()->AddChild( fObj);
	}

	fScene.UpdateViewCoords();
	fScene.UpdateLightness();

	return  true;
}







} // namespace KHEOPS
