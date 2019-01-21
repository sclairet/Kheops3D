

#ifndef __APPLICATION3__
#define __APPLICATION3__


namespace KHEOPS
{



class Application3D
{
public:

    Application3D();
    virtual ~Application3D();

	virtual	bool					Init();

	virtual	void					SetScreenBackColor( const Color& inColor);
	virtual	void					SetDrawingSettings( ulong3 inDrawingSettings);

	virtual	void					Run();
	virtual	void					OnExpose( GraphicContext *inGC);

	virtual	void					DoKeyDown( EKey inKey, ulong3 inRepeatCount);

	virtual	void					DoBeginCaptureMouse();
	virtual	void					DoEndCaptureMouse();
			bool					GetCaptureMouse() const	{ return fCaptureMouse; }

	virtual	void					DoMouseMove( const Coord2D& inCursorPos);

			const Scene3D&			GetScene() const		{ return fScene; }				

protected:

    virtual void					_BeforeRun();
	virtual	void					_Run();
    virtual void					_AfterRun();
	virtual	void					_DoBeginCaptureMouse();
	virtual	void					_DoEndCaptureMouse();

			Scene3D					fScene;
			Color					fScreenBackColor;
			bool					fCaptureMouse;
};



}

#endif
