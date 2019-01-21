
// 07/10/2011

#pragma once


#ifndef __ARCH__
#define __ARCH__



#include "resource.h"


const long  kAPP_INDEX_CUBE = 0;
const long  kAPP_INDEX_PRIMITIVE1_CUBE = 1;
const long  kAPP_INDEX_PRIMITIVE1_CYLINDER = 2;
const long  kAPP_INDEX_PRIMITIVE1_SPHERE = 3;
const long  kAPP_INDEX_PRIMITIVE1_SPHERE2 = 4;



// ============================================================================



class ArchApplication : public KHEOPS::Engine3D_delegate
{
public:

    ArchApplication( HINSTANCE inInstance, HWND inHwnd);
    virtual ~ArchApplication();

	static	ArchApplication*		Get() { return sApplication; }
    static  bool					Init( HINSTANCE inInstance, HWND inHwnd);
    static  void					DeInit();

			void					BeforeRun();
			void					AfterRun();

			void					SetIsRunning( bool inSet);
			bool					GetIsRunning() const;

			void					SetCurrentApplication3DIndex( long inIndex);
			long					GetCurrentApplication3DIndex() const;
			KHEOPS::Application3D*	GetCurrentApplication3D() const;

			void					SetDrawingSettings( KHEOPS::ulong3 inDrawingSettings);
			KHEOPS::ulong3			GetDrawingSettings() const;

			LRESULT					DrawHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT					KeyHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			LRESULT					MouseHandler( HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

			// Inherited from Engine3D_delegate
			virtual	void			GetScreenSize( KHEOPS::slong3& outWidth, KHEOPS::slong3& outHeight);
			virtual	void			GetCursorPosition( KHEOPS::Coord2D& outPos);
			virtual void			SetCursorPosition( const KHEOPS::Coord2D& inPos);
			virtual void			GetResourcesFolderPath( std::wstring& outPath);

private:
			void					_TimerHander( UINT_PTR inTimerID);

	static	VOID CALLBACK			_TimerProc( HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime);

    static	ArchApplication			*sApplication;
	static  bool					sInited;
			UINT_PTR				fTimerID;
			HWND					fHwnd;
			HINSTANCE				fInstance;
			bool					fIsRunning;

			std::map< long, KHEOPS::Application3D*>		fApplications3D;
			long										fCurrentApplication3DIndex;
			KHEOPS::ulong3								fDrawingSettings;
};



#endif