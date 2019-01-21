
#include "core3.h"
#include "modeler3.h"
#include "engine3.h"



namespace KHEOPS
{



Engine3D* Engine3D::sInstance = NULL;

Engine3D::Engine3D( Engine3D_delegate *inDelegate)
: fDelegate( inDelegate)
{
	fModeler = new Modeler3D();
}


Engine3D::~Engine3D()
{
	delete fModeler;
}


bool Engine3D::Init( Engine3D_delegate *inDelegate)
{
	if (sInstance == NULL)
	{
		sInstance = new Engine3D( inDelegate);
		if (sInstance != NULL)
		{
			sInstance->_Test();
		}
	}
	return true;
}


void Engine3D::DeInit()
{
	delete sInstance;
	sInstance = NULL;
}


Engine3D_delegate* Engine3D::GetDelegate() const
{
	return fDelegate;
}


void Engine3D::GetVirtualScreenSize( real3& outWidth, real3& outHeight) const
{
	outWidth = kVirtualScreenWidth;
	outHeight = kVirtualScreenHeight;
}


void Engine3D::GetScreenSize( slong3& outWidth, slong3& outHeight) const
{
	outWidth = 0;
	outHeight = 0;

	if (fDelegate != NULL)
		fDelegate->GetScreenSize( outWidth, outHeight);
}


void Engine3D::GetCursorPosition( Coord2D& outPos)
{
	if (fDelegate != NULL)
		fDelegate->GetCursorPosition( outPos);
}


void Engine3D::SetCursorPosition( const Coord2D& inPos)
{
	if (fDelegate != NULL)
		fDelegate->SetCursorPosition( inPos);
}


void Engine3D::GetResourcesFolderPath( std::wstring& outPath)
{
	outPath.clear();

	if  (fDelegate != NULL)
		fDelegate->GetResourcesFolderPath( outPath);

}


void Engine3D::_Test()
{
	Vector3D res1 = Vector3D::CalcCrossProduct( Vector3D( 1, 6, -2), Vector3D(3, -1, 5), true);
	Vector3D res2 = Vector3D::CalcCrossProduct( Vector3D( 1, 6, 2), Vector3D(3, -1, -5), false);
}


}