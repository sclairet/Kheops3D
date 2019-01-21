
#ifndef __SPOT3__
#define __SPOT3__



namespace KHEOPS
{



class Light : public World3D
{
typedef World3D inherited;

public:
	
	// first light ID is 1
    Light( slong3 inID);
    Light( slong3 inID, const Coord3D& inPos);
    virtual ~Light();

			void				SetID( slong3 inID)			{ fID = inID; }
			slong3              GetID() const               { return fID; }

			void				SetCameraBinding( slong3 inCameraID)	{ fCameraBinding = inCameraID; }
			slong3				GetCameraBinding() const				{ return fCameraBinding; }
			bool				HasCameraBinding() const				{ return fCameraBinding > 0; }

			void				SetIntensity( slong3 inIntensity);
			slong3				GetIntensity() const;

protected:
            slong3              fID;
			slong3				fIntensity;	// 0 - 100
			slong3				fCameraBinding;
};



typedef std::map< slong3, Light* >                    MapPtrOfLight;
typedef std::map< slong3, Light* >::iterator          MapPtrOfLight_iter;
typedef std::map< slong3, Light* >::const_iterator    MapPtrOfLight_citer;



} // namespace KHEOPS



#endif
