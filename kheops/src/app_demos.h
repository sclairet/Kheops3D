

#ifndef __DEMOS__
#define __DEMOS__


namespace KHEOPS
{



class AppDemo : public Application3D
{
public:

    AppDemo();
    virtual ~AppDemo();

	virtual	bool					Init();

	virtual	void					SetDrawingSettings( ulong3 inDrawingSettings);

	virtual	void					SetObjectAnimationEnabled( bool inSet);
	virtual	bool					GetObjectAnimationEnabled() const;

	virtual	void					OnExpose( GraphicContext *inGC);

	virtual	void					DoKeyDown( EKey inKey, ulong3 inRepeatCount);

protected:

	virtual	void					_Run();
	virtual	void					_DoBeginCaptureMouse();
	virtual	void					_DoEndCaptureMouse();

	virtual	Object3D*				_GetObject()			{ return NULL; }			

			Coord2D					fCursorPos;
			bool					fShowMouseTarget;
			bool					fObjectAnimationEnabled;
			
            Camera					*fCamera;
			Light					*fCameraLight;
	
			slong3					fAlpha_x;
            slong3					fAlpha_y;
            slong3					fAlpha_z;
};



// ============================================================================



class AppDemo_chessboard : public AppDemo
{
public:
	AppDemo_chessboard();
	virtual ~AppDemo_chessboard();

	virtual	bool		Init();

protected:
	virtual	Object3D*	_GetObject()			{ return fObj; }	

private:
			Object3D	*fObj;
			
};



}

#endif
