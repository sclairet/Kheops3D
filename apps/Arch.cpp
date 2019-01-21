// Arch.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include <windows.h>
#include <windowsx.h>
#include "kheops.h"
#include "application3.h"
#include "app_primitive.h"
#include "app_demos.h"
#include "app_solar_system.h"
#include "win_graphics3.h"
#include "win_tools3.h"
#include <math.h>
#include <string>
#include "Arch.h"

using namespace KHEOPS;

#define MAX_LOADSTRING 100

// Global Variables:
HINSTANCE hInst;								// current instance
TCHAR szTitle[MAX_LOADSTRING];					// The title bar text
TCHAR szWindowClass[MAX_LOADSTRING];			// the main window class name

// Forward declarations of functions included in this code module:
ATOM				MyRegisterClass(HINSTANCE hInstance);
BOOL				InitInstance(HINSTANCE, int);
LRESULT CALLBACK	WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK	About(HWND, UINT, WPARAM, LPARAM);


const long kAppBaseID = 1;


int APIENTRY _tWinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPTSTR    lpCmdLine,
                     int       nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

 	// TODO: Place code here.
	MSG msg;

	// Initialize global strings
	LoadString(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
	LoadString(hInstance, IDC_ARCH, szWindowClass, MAX_LOADSTRING);
	MyRegisterClass(hInstance);

	// Perform application initialization:
	if (!InitInstance (hInstance, nCmdShow))
	{
		return FALSE;
	}

	HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_ARCH));
	
	ArchApplication::Get()->BeforeRun();

	// Main message loop:
	while (GetMessage(&msg, NULL, 0, 0))
	{
		if (!TranslateAccelerator(msg.hwnd, hAccelTable, &msg))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
	}

	ArchApplication::Get()->AfterRun();

	return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
//  COMMENTS:
//
//    This function and its usage are only necessary if you want this code
//    to be compatible with Win32 systems prior to the 'RegisterClassEx'
//    function that was added to Windows 95. It is important to call this function
//    so that the application will get 'well formed' small icons associated
//    with it.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style			= CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc	= WndProc;
	wcex.cbClsExtra		= 0;
	wcex.cbWndExtra		= 0;
	wcex.hInstance		= hInstance;
	wcex.hIcon			= LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ARCH));
	wcex.hCursor		= LoadCursor(NULL, IDC_ARROW);
	wcex.hbrBackground	= (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName	= MAKEINTRESOURCE(IDC_ARCH);
	wcex.lpszClassName	= szWindowClass;
	wcex.hIconSm		= LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_SMALL));

	return RegisterClassEx(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   HWND hWnd;

   hInst = hInstance; // Store instance handle in our global variable

   hWnd = CreateWindow(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, NULL, NULL, hInstance, NULL);

   if (!hWnd)
   {
      return FALSE;
   }

	if (!ArchApplication::Init( hInstance, hWnd))
	{
		return FALSE;
	}

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND	- process the application menu
//  WM_PAINT	- Paint the main window
//  WM_DESTROY	- post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	int wmId, wmEvent;

	switch (message)
	{
	case WM_COMMAND:
		wmId    = LOWORD(wParam);
		wmEvent = HIWORD(wParam);
		// Parse the menu selections:
		switch (wmId)
		{
		case IDM_ABOUT:
			DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
			break;
		case IDM_EXIT:
			DestroyWindow(hWnd);
			break;

		case ID_APPLICATIONS_CUBE:
		case ID_APPLICATIONS_PRIMITIVEMUG:
		case ID_APPLICATIONS_PRIMITIVEMIX:
		case ID_APPLICATIONS_SOLARSYSTEM:
			break;

		case ID_APPLICATIONS_PRIMITIVECUBE:
		case ID_APPLICATIONS_PRIMITIVEPYRAMID:
		case ID_APPLICATIONS_PRIMITIVECYLINDER:
		case ID_PRIMITIVES_HOLLOWCYLINDER:
		case ID_PRIMITIVES_ROUNDEDCYLINDER:
		case ID_PRIMITIVES_HOLLOWEDCYLINDER:
		case ID_APPLICATIONS_PRIMITIVESPHERE:
		case ID_PRIMITIVES_SPINTOP:
		case ID_APPLICATIONS_PRIMITIVETORE:
		case ID_APPLICATIONS_PRIMITIVERING:
		case ID_APPLICATIONS_PRIMITIVECONE:
		case ID_APPLICATIONS_TEST:
			{
				if (ArchApplication::Get() != NULL)
				{
					if (ArchApplication::Get()->GetCurrentApplication3DIndex() != kAppBaseID)
						ArchApplication::Get()->SetCurrentApplication3DIndex( kAppBaseID);

					AppBase *appBase = dynamic_cast<AppBase*>(ArchApplication::Get()->GetCurrentApplication3D());
					if (appBase != NULL)
					{
						switch (wmId)
						{
						case ID_APPLICATIONS_PRIMITIVECUBE:
							appBase->SelectPrimitive( AppBase::eCubeID);
							break;
						case ID_APPLICATIONS_PRIMITIVEPYRAMID:
							appBase->SelectPrimitive( AppBase::ePyramidID);
							break;
						case ID_APPLICATIONS_PRIMITIVECYLINDER:
							appBase->SelectPrimitive( AppBase::eCylinderID);
							break;
						case ID_PRIMITIVES_HOLLOWCYLINDER:
							appBase->SelectPrimitive( AppBase::eHollowedCenterCylinderID);
							break;
						case ID_PRIMITIVES_ROUNDEDCYLINDER:
							appBase->SelectPrimitive( AppBase::eRoundedCylinderID);
							break;
						case ID_PRIMITIVES_HOLLOWEDCYLINDER:
							appBase->SelectPrimitive( AppBase::eHollowedCylinderID);
							break;
						case ID_APPLICATIONS_PRIMITIVESPHERE:
							appBase->SelectPrimitive( AppBase::eSphereID);
							break;
						case ID_PRIMITIVES_SPINTOP:
							appBase->SelectPrimitive( AppBase::eSpintopID);
							break;
						case ID_APPLICATIONS_PRIMITIVETORE:
							appBase->SelectPrimitive( AppBase::eToreID);
							break;
						case ID_APPLICATIONS_PRIMITIVERING:
							appBase->SelectPrimitive( AppBase::eRingID);
							break;
						case ID_APPLICATIONS_PRIMITIVECONE:
							appBase->SelectPrimitive( AppBase::eConeID);
							break;
						case ID_APPLICATIONS_TEST:
							appBase->SelectPrimitive( AppBase::eTestID);
							break;
						}
					}
				}
			}
			break;

		case ID_DEMO_CHESSBOARD:
			if (ArchApplication::Get() != NULL)
			{
				ArchApplication::Get()->SetCurrentApplication3DIndex( wmId);
			}
			break;

		case ID_SETTINGS_DRAWSEGMENT:
			{
				ArchApplication::Get()->SetDrawingSettings( kDrawSegment);
			}
			break;

		case ID_SETTINGS_DRAWNORMAL:
			{
				KHEOPS::ulong3 settings = ArchApplication::Get()->GetDrawingSettings();

				if ((settings & KHEOPS::kDrawShapeNormalVector) == 0)
					settings |= KHEOPS::kDrawShapeNormalVector;
				else
					settings &= ~KHEOPS::kDrawShapeNormalVector;

				ArchApplication::Get()->SetDrawingSettings( settings);
			}
			break;

		case ID_SETTINGS_DRAWFILLED:
			{
				ArchApplication::Get()->SetDrawingSettings( kDrawFilled);
			}
			break;

		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
		}
		break;
	case WM_PAINT:
		if (ArchApplication::Get() != NULL)
		{
			ArchApplication::Get()->DrawHandler( hWnd, message, wParam, lParam);
		}
		break;

	case WM_KEYDOWN:
		{
			if (ArchApplication::Get() != NULL)
			{
				ArchApplication::Get()->KeyHandler( hWnd, message, wParam, lParam);
			}
		}
		break;

	case WM_LBUTTONDOWN:
	case WM_LBUTTONUP:
	case WM_MOUSEMOVE:
		{
			if (ArchApplication::Get() != NULL)
			{
				ArchApplication::Get()->MouseHandler( hWnd, message, wParam, lParam);
			}
		}
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}
	return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
	UNREFERENCED_PARAMETER(lParam);
	switch (message)
	{
	case WM_INITDIALOG:
		return (INT_PTR)TRUE;

	case WM_COMMAND:
		if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
		{
			EndDialog(hDlg, LOWORD(wParam));
			return (INT_PTR)TRUE;
		}
		break;
	}
	return (INT_PTR)FALSE;
}



ArchApplication *ArchApplication::sApplication = NULL;
bool ArchApplication::sInited = false;

ArchApplication::ArchApplication( HINSTANCE inInstance, HWND inHwnd)
: fTimerID(0),
fInstance(inInstance),
fHwnd( inHwnd),
fCurrentApplication3DIndex(-1),
fIsRunning(false),
fDrawingSettings(KHEOPS::kDrawSegment)
{
}


ArchApplication::~ArchApplication()
{
}


bool ArchApplication::Init( HINSTANCE inInstance, HWND inHwnd)
{
	bool result = false;

	if (sApplication == NULL)
	{
		sApplication = new ArchApplication( inInstance, inHwnd);
		sInited = (sApplication != NULL);
		KHEOPS::Engine3D::Init( sApplication);
		result = true;
	}

	return  result;
}


void ArchApplication::DeInit()
{
	KHEOPS::Engine3D::DeInit();
	delete sApplication;
	sApplication = NULL;
	sInited = false;
}


void ArchApplication::BeforeRun()
{
	fApplications3D[kAppBaseID] = NULL;
	fApplications3D[ID_APPLICATIONS_CUBE] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVECUBE] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVEPYRAMID] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVECYLINDER] = NULL;
	fApplications3D[ID_PRIMITIVES_HOLLOWCYLINDER] = NULL;
	fApplications3D[ID_PRIMITIVES_ROUNDEDCYLINDER] = NULL;
	fApplications3D[ID_PRIMITIVES_HOLLOWEDCYLINDER] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVECONE] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVESPHERE] = NULL;
	fApplications3D[ID_PRIMITIVES_SPINTOP] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVETORE] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVERING] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVEMUG] = NULL;
	fApplications3D[ID_APPLICATIONS_PRIMITIVEMIX] = NULL;
	fApplications3D[ID_APPLICATIONS_SOLARSYSTEM] = NULL;
	fApplications3D[ID_APPLICATIONS_TEST] = NULL;
	fApplications3D[ID_DEMO_CHESSBOARD] = NULL;

	AppBase *appBase = new AppBase();
	if (appBase != NULL)
	{
		appBase->Init();
		appBase->SelectPrimitive( AppBase::eCubeID);
		fApplications3D[kAppBaseID] = appBase;
	}

#if 0

	AppPrimitive_test *tester = new AppPrimitive_test();
	if (tester != NULL)
	{
		tester->Init();
		fApplications3D[ID_APPLICATIONS_TEST] = tester;
	}

	AppPrimitive_cube *primCube = new AppPrimitive_cube();
	if (primCube != NULL)
	{
		primCube->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVECUBE] = primCube;
	}

	AppPrimitive_pyramid *primPyramid = new AppPrimitive_pyramid();
	if (primPyramid != NULL)
	{
		primPyramid->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVEPYRAMID] = primPyramid;
	}

	AppPrimitive_cylinder *primCylinder = new AppPrimitive_cylinder();
	if (primCylinder != NULL)
	{
		primCylinder->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVECYLINDER] = primCylinder;
	}

	AppPrimitive_hollowedCenterCylinder *primHollowedCenterCylinder = new AppPrimitive_hollowedCenterCylinder();
	if (primHollowedCenterCylinder != NULL)
	{
		primHollowedCenterCylinder->Init();
		fApplications3D[ID_PRIMITIVES_HOLLOWCYLINDER] = primHollowedCenterCylinder;
	}

	AppPrimitive_roundedCylinder *primRoundedCylinder = new AppPrimitive_roundedCylinder();
	if (primRoundedCylinder != NULL)
	{
		primRoundedCylinder->Init();
		fApplications3D[ID_PRIMITIVES_ROUNDEDCYLINDER] = primRoundedCylinder;
	}

	AppPrimitive_hollowedCylinder *primHollowedCylinder = new AppPrimitive_hollowedCylinder();
	if (primHollowedCylinder != NULL)
	{
		primHollowedCylinder->Init();
		fApplications3D[ID_PRIMITIVES_HOLLOWEDCYLINDER] = primHollowedCylinder;
	}

	AppPrimitive_cone *primCone = new AppPrimitive_cone();
	if (primCone != NULL)
	{
		primCone->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVECONE] = primCone;
	}

	AppPrimitive_sphere *primSphere = new AppPrimitive_sphere();
	if (primSphere != NULL)
	{
		primSphere->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVESPHERE] = primSphere;
	}

	AppPrimitive_spintop *primSpintop = new AppPrimitive_spintop();
	if (primSpintop != NULL)
	{
		primSpintop->Init();
		fApplications3D[ID_PRIMITIVES_SPINTOP] = primSpintop;
	}

	AppPrimitive_tore *primTore = new AppPrimitive_tore();
	if (primTore != NULL)
	{
		primTore->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVETORE] = primTore;
	}

	AppPrimitive_ring *primRing = new AppPrimitive_ring();
	if (primRing != NULL)
	{
		primRing->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVERING] = primRing;
	}

#endif

	AppDemo_chessboard *chessboard = new AppDemo_chessboard();
	if (chessboard != NULL)
	{
		chessboard->Init();
		fApplications3D[ID_DEMO_CHESSBOARD] = chessboard;
	}


#if 0

	AppPrimitive_mug *primMug = new AppPrimitive_mug();
	if (primMug != NULL)
	{
		primMug->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVEMUG] = primMug;
	}

	AppPrimitive_mix *primMix = new AppPrimitive_mix();
	if (primMix != NULL)
	{
		primMix->Init();
		fApplications3D[ID_APPLICATIONS_PRIMITIVEMIX] = primMix;

		KHEOPS::ulong3 coordsCount = primMix->GetScene().GetRootObject()->GetCoordsCount();
		printf( "coords count = %i\n", coordsCount);

		KHEOPS::ulong3 shapesCount = primMix->GetScene().GetRootObject()->GetShapesCount();
		printf( "shapes count = %i\n", shapesCount);
	}

	AppSolarSystem *solarSystem = new AppSolarSystem();
	if (solarSystem != NULL)
	{
		solarSystem->Init();
		fApplications3D[ID_APPLICATIONS_SOLARSYSTEM] = solarSystem;

		KHEOPS::ulong3 coordsCount = solarSystem->GetScene().GetRootObject()->GetCoordsCount();
		printf( "coords count = %i\n", coordsCount);

		KHEOPS::ulong3 shapesCount = solarSystem->GetScene().GetRootObject()->GetShapesCount();
		printf( "shapes count = %i\n", shapesCount);
	}
#endif

	fTimerID = ::SetTimer( NULL, 0, 1000/25, ArchApplication::_TimerProc);

	SetDrawingSettings( kDrawFilled);

	SetCurrentApplication3DIndex( kAppBaseID);

}


void ArchApplication::AfterRun()
{
	if (fTimerID != 0)
	{
		BOOL ok = ::KillTimer( NULL, fTimerID);
		if (ok)
			fTimerID = 0;
	}

	for (std::map< long, KHEOPS::Application3D*>::iterator iter = fApplications3D.begin() ; iter != fApplications3D.end() ; ++iter)
	{
		delete iter->second;
	}
}


void ArchApplication::SetIsRunning( bool inSet)
{
	fIsRunning = inSet;
}


bool ArchApplication::GetIsRunning() const
{
	return fIsRunning;
}


void ArchApplication::SetCurrentApplication3DIndex( long inIndex)
{
	fCurrentApplication3DIndex = inIndex;
	::InvalidateRect( fHwnd, NULL, false);
}


long ArchApplication::GetCurrentApplication3DIndex() const
{
	return fCurrentApplication3DIndex;
}


KHEOPS::Application3D* ArchApplication::GetCurrentApplication3D() const
{
	std::map< long, KHEOPS::Application3D*>::const_iterator found = fApplications3D.find(fCurrentApplication3DIndex);
	if (found != fApplications3D.end())
		return  found->second;

	return NULL;
}


void ArchApplication::SetDrawingSettings( KHEOPS::ulong3 inDrawingSettings)
{
	fDrawingSettings = inDrawingSettings;

	for (std::map< long, KHEOPS::Application3D*>::iterator iter = fApplications3D.begin() ; iter != fApplications3D.end() ; ++iter)
	{
		if (iter->second != NULL)
			iter->second->SetDrawingSettings( fDrawingSettings);
	}

	::InvalidateRect( fHwnd, NULL, false);
}


KHEOPS::ulong3 ArchApplication::GetDrawingSettings() const
{
	return fDrawingSettings;
}


LRESULT ArchApplication::DrawHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;

	HDC hdc = BeginPaint( hWnd, &ps);

	RECT clientRect;
	::GetClientRect( fHwnd, &clientRect);

	HDC offscreenDC = ::CreateCompatibleDC( hdc);
	if (offscreenDC != NULL)
	{
		HBITMAP bmp = ::CreateCompatibleBitmap( hdc, clientRect.right - clientRect.left, clientRect.bottom - clientRect.top);
		if (bmp != NULL)
		{
			::SelectObject( offscreenDC, bmp);
		
		#if 0
			HBRUSH hBrush = ::CreateSolidBrush( RGB( 0x30, 0x30, 0x30));
			if (hBrush != NULL)
			{
				::FillRect( offscreenDC, &clientRect, hBrush);
				::DeleteObject( hBrush);
				hBrush = NULL;
			}
		#endif

			Application3D *curApp = GetCurrentApplication3D();
			if (curApp != NULL)
			{
				WinGraphics3D *gc = new WinGraphics3D( hWnd, offscreenDC);
				if  (gc != NULL)
				{
					RECT clientRect;
					real3 virtualWidth = 0, virtualHeight = 0;
					
					::GetClientRect( fHwnd, &clientRect);
					Engine3D::Get()->GetVirtualScreenSize( virtualWidth, virtualHeight);
					gc->SetScreenScaling( ((real3)(clientRect.right-clientRect.left))/virtualWidth, ((real3)(clientRect.bottom-clientRect.top))/virtualHeight);
			
					curApp->OnExpose( gc);
					delete gc;
					gc = NULL;
				}
			}
		}

		BOOL done = ::BitBlt(	hdc,
								clientRect.left,
								clientRect.top,
								clientRect.right - clientRect.left,
								clientRect.bottom - clientRect.top,
								offscreenDC,
								0,
								0,
								SRCCOPY );

		::DeleteObject( bmp);
		bmp = NULL;
	}

	::DeleteDC( offscreenDC);
	offscreenDC = NULL;

	EndPaint(hWnd, &ps);

	return 0;
}


LRESULT ArchApplication::KeyHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Application3D *curApp = GetCurrentApplication3D();
	if (curApp != NULL)
	{
		curApp->DoKeyDown( KHEOPS::VirtualKeyCodeToKheopsKey( wParam), 0);
	}
	return 0;
}


LRESULT ArchApplication::MouseHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	Application3D *curApp = GetCurrentApplication3D();

	switch (message)
	{
	case WM_LBUTTONDOWN:
		{
			HWND capture = ::GetCapture();
			if (capture == NULL)
			{
				::SetCapture( fHwnd);
				::ShowCursor( FALSE);
				if (curApp != NULL)
				{
					curApp->DoBeginCaptureMouse();
				}
			}
		}
		break;

	case WM_LBUTTONUP:
		{
			HWND capture = ::GetCapture();
			if (capture == fHwnd)
			{
				::ReleaseCapture();
				::ShowCursor( TRUE);
				if (curApp != NULL)
				{
					curApp->DoEndCaptureMouse();
				}
			}
		}
		break;

	case WM_MOUSEMOVE:
		{
			HWND capture = ::GetCapture();
			if (capture == fHwnd)
			{
				if (curApp != NULL)
				{
					curApp->DoMouseMove( Coord2D( GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam)));
				}
			}
		}
		break;

	default:
		break;
	}

	return 0;
}


void ArchApplication::GetScreenSize( KHEOPS::slong3& outWidth, KHEOPS::slong3& outHeight)
{
	RECT clientRect;
	::GetClientRect( fHwnd, &clientRect);
	outWidth = clientRect.right - clientRect.left;
	outHeight = clientRect.bottom - clientRect.top;
}


void ArchApplication::GetCursorPosition( KHEOPS::Coord2D& outPos)
{
	POINT pos = {0,0};
	if (::GetCursorPos( &pos) == TRUE)
	{
		if (::ScreenToClient( fHwnd, &pos) == TRUE)
		{
			outPos.SetCoordsTo( pos.x, pos.y);
		}
	}
}


void ArchApplication::SetCursorPosition( const KHEOPS::Coord2D& inPos)
{
	POINT pos = {inPos.GetX(),inPos.GetY()};
	if (::ClientToScreen( fHwnd, &pos) == TRUE)
	{
		::SetCursorPos( pos.x, pos.y);
	}
}


void ArchApplication::GetResourcesFolderPath( std::wstring& outPath)
{
	wchar_t buffer[1024];
	HMODULE hModule = ::GetModuleHandleW( NULL);
	size_t len = ::GetModuleFileNameW( hModule, buffer, 1024);

	outPath.append( buffer);
	size_t found = outPath.rfind( L'\\');
	if (found != -1)
	{
		outPath.resize( found + 1);
		outPath.append( L"resources\\");
	}
}


void ArchApplication::_TimerHander( UINT_PTR inTimerID)
{
	if (inTimerID == fTimerID)
	{
		Application3D *curApp = GetCurrentApplication3D();
		if (curApp != NULL)
		{
			curApp->Run();
		}

		::InvalidateRect( fHwnd, NULL, false);
	}
}


VOID ArchApplication::_TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime)
{
	ArchApplication::Get()->_TimerHander( idEvent);
}

