

#ifndef __APP_SOLAR_SYSTEM__
#define __APP_SOLAR_SYSTEM__


namespace KHEOPS
{


#if 0

class AppSolarSystem : public Application3D
{
public:

    AppSolarSystem();
    virtual ~AppSolarSystem();

	virtual	bool					Init();

	virtual	void					SetDrawingSettings( ulong3 inDrawingSettings);

	virtual	void					OnExpose( GraphicContext *inGC);

protected:

	virtual	void					_Run();

private:
			std::map< ulong3 , ArrayOfCoord3D >		fOrbits;
			slong3									fCameraID;
};

#endif


}

#endif
