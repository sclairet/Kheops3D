

#ifndef __APP_PRIMITIVE__
#define __APP_PRIMITIVE__


namespace KHEOPS
{



class AppBase : public Application3D
{
public:

	typedef enum
	{
		eTestID	= 0,
		eCubeID,
		eCylinderID,
		eHollowedCenterCylinderID,
		eRoundedCylinderID,
		eHollowedCylinderID,
		eConeID,
		eSphereID,
		eSpintopID,
		eToreID,
		eRingID,
		ePyramidID,
		eFirstPrimitive = eTestID,
		eLastPrimitive = ePyramidID,

	};

    AppBase();
    virtual ~AppBase();

	virtual	bool					Init();

			void					SelectPrimitive( ulong3 inPrimitiveID);

	virtual	void					SetDrawingSettings( ulong3 inDrawingSettings);

	virtual	void					SetObjectAnimationEnabled( bool inSet);
	virtual	bool					GetObjectAnimationEnabled() const;

	virtual	void					OnExpose( GraphicContext *inGC);

	virtual	void					DoKeyDown( EKey inKey, ulong3 inRepeatCount);

	virtual	void					DoMouseMove( const Coord2D& inCursorPos);

protected:

	virtual	void					_Run();
	virtual	void					_DoBeginCaptureMouse();
	virtual	void					_DoEndCaptureMouse();

	virtual	Object3D*				_GetObject()			{ return NULL; }			

			MapOfObject3D			fPrimitives;
			Coord2D					fCursorPos;
			bool					fShowMouseTarget;
			bool					fObjectAnimationEnabled;
			
            Camera					*fLeftCamera;
			Camera					*fTopRightCamera;
			Camera					*fBottomRightCamera;

			Light					*fLeftCameraLight;
	
			slong3					fAlpha_x;
            slong3					fAlpha_y;
            slong3					fAlpha_z;
};



// ============================================================================



class AppPrimitive_test : public AppBase
{
public:
	AppPrimitive_test();
	virtual ~AppPrimitive_test();

	virtual	bool		Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fObject;	}

private:
			Object3D	*fObject;
};



// ============================================================================



class AppPrimitive_cube : public AppBase
{
public:
	AppPrimitive_cube();
	virtual ~AppPrimitive_cube();

	virtual	bool		Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCube;	}

private:
			Object3D	*fCube;
};



// ============================================================================



class AppPrimitive_cylinder : public AppBase
{
public:
	AppPrimitive_cylinder();
	virtual ~AppPrimitive_cylinder();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCylinder;	}

private:
			Object3D	*fCylinder;
};



// ============================================================================



class AppPrimitive_hollowedCenterCylinder : public AppBase
{
public:
	AppPrimitive_hollowedCenterCylinder();
	virtual ~AppPrimitive_hollowedCenterCylinder();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCylinder;	}

private:
			Object3D	*fCylinder;
};



// ============================================================================



class AppPrimitive_roundedCylinder : public AppBase
{
public:
	AppPrimitive_roundedCylinder();
	virtual ~AppPrimitive_roundedCylinder();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCylinder;	}

private:
			Object3D	*fCylinder;
};



// ============================================================================



class AppPrimitive_hollowedCylinder : public AppBase
{
public:
	AppPrimitive_hollowedCylinder();
	virtual ~AppPrimitive_hollowedCylinder();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCylinder;	}

private:
			Object3D	*fCylinder;
};



// ============================================================================



class AppPrimitive_cone : public AppBase
{
public:
	AppPrimitive_cone();
	virtual ~AppPrimitive_cone();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fCone;	}

private:
			Object3D	*fCone;
};



// ============================================================================



class AppPrimitive_sphere : public AppBase
{
public:
	AppPrimitive_sphere();
	virtual ~AppPrimitive_sphere();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fSphere;	}

private:
			Object3D	*fSphere;
};



// ============================================================================



class AppPrimitive_spintop : public AppBase
{
public:
	AppPrimitive_spintop();
	virtual ~AppPrimitive_spintop();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fSpintop;	}

private:
			Object3D	*fSpintop;
};



// ============================================================================



class AppPrimitive_tore : public AppBase
{
public:
	AppPrimitive_tore();
	virtual ~AppPrimitive_tore();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fTore;	}

private:
			Object3D	*fTore;
};



// ============================================================================



class AppPrimitive_ring : public AppBase
{
public:
	AppPrimitive_ring();
	virtual ~AppPrimitive_ring();

	virtual	bool					Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fRing;	}

private:
			Object3D	*fRing;
};



// ============================================================================



class AppPrimitive_pyramid : public AppBase
{
public:
	AppPrimitive_pyramid();
	virtual ~AppPrimitive_pyramid();

	virtual	bool		Init();

protected:
	virtual	Object3D*	_GetObject()		{ return fPyramid;	}

private:
			Object3D	*fPyramid;
};



// ============================================================================

#if 0

class AppPrimitive_mug : public AppBase
{
public:
	AppPrimitive_mug();
	virtual ~AppPrimitive_mug();

	virtual	bool					Init();
};



class AppPrimitive_mix : public Application3D
{
public:

    AppPrimitive_mix();
    virtual ~AppPrimitive_mix();

	virtual	bool					Init();

	virtual	void					SetDrawingSettings( ulong3 inDrawingSettings);

	virtual	void					OnExpose( GraphicContext *inGC);

protected:

	virtual	void					_Run();

private:
            slong3					fAlpha_x;
            slong3					fAlpha_y;
            slong3					fAlpha_z;
};

#endif



}

#endif
