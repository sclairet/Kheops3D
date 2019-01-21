

#include "core3.h"
#include <assert.h>
#include <math.h>
#include "objects3.h"
#include "renderer3.h"
#include "scene3.h"
#include "application3.h"





namespace KHEOPS
{



Application3D::Application3D()
{
	fScreenBackColor.Set( 0x00, 0x00, 0x00, 0x00);
	fCaptureMouse = false;
}


Application3D::~Application3D()
{
}


bool Application3D::Init()
{
	return true;
}


void Application3D::SetScreenBackColor( const Color& inColor)
{
	fScreenBackColor = inColor;
}


void Application3D::SetDrawingSettings( ulong3 inDrawingSettings)
{
	fScene.SetDrawingSettings( inDrawingSettings);
}


void Application3D::Run()
{
	fScene.BeginEdition();

	_Run();

	fScene.EndEdition();
}


void Application3D::OnExpose( GraphicContext *inGC)
{
	slong3 width = 0, height = 0;
	Engine3D::Get()->GetScreenSize( width, height);

	Coord2D topLeft( 0, 0), bottomRight( width, height);
	inGC->FillRect( topLeft, bottomRight, fScreenBackColor);

	fScene.Draw( inGC);
}


void Application3D::DoKeyDown( EKey inKey, ulong3 inRepeatCount)
{
}


void Application3D::DoBeginCaptureMouse()
{
	fCaptureMouse = true;
	_DoBeginCaptureMouse();
}


void Application3D::DoEndCaptureMouse()
{
	fCaptureMouse = false;
	_DoEndCaptureMouse();
}


void Application3D::DoMouseMove( const Coord2D& inCursorPos)
{
}


void Application3D::_BeforeRun()
{
}


void Application3D::_Run()
{
}


void Application3D::_AfterRun()
{
}


void Application3D::_DoBeginCaptureMouse()
{
}


void Application3D::_DoEndCaptureMouse()
{
}



} // namespace KHEOPS
