
// 03/06/2008


#ifndef __MOTION3__
#define __MOTION3__


namespace KHEOPS
{



// ============================================================================
// needed declarations
class Object3D;



// ============================================================================


class ITimeable
{
public:

    ITimeable();
    virtual ~ITimeable();




private:


};



// sequence à repeter n fois toutes les s secondes
// stack de sequence lineaire
//

// ============================================================================
// Motion3D base class declaration


class Motion3D
{
public:

    Motion3D();
    virtual ~Motion3D();

            void                            AddObject( Object3D *inObject);

protected:

            ArrayPtrOfObject3D				fObjects;
};



// ============================================================================



class Motion3D_rotation : public Motion3D
{
    Motion3D_rotation();
    Motion3D_rotation( const World3D& inCenter, const Rotation3D& inRotation);
    virtual ~Motion3D_rotation();

			const World3D&          GetCenter() const                           { return fCenter; }
			const Rotation3D&       GetRotation() const                         { return fRotation; }

    virtual void                    SetCenter( const World3D& inCenter)         { fCenter = inCenter; }
    virtual void                    SetRotation( const Rotation3D& inRotation)  { fRotation = inRotation; }

protected:

            World3D                 fCenter;
            Rotation3D              fRotation;
};








} // namespace KHEOPS


#endif // __MOTION3__
