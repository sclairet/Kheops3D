
#ifndef __TRANSFORM3__
#define __TRANSFORM3__



namespace KHEOPS
{



class Translation3D
{
public:

    Translation3D();
    Translation3D( real3 inTx, real3 inTy, real3 inTz);
    Translation3D( const Translation3D& inSource);
    virtual ~Translation3D();

			const real3                 GetTx() const           { return fTx; }
			const real3                 GetTy() const           { return fTy; }
			const real3                 GetTz() const           { return fTy; }

			void                        SetTx( real3 inTx)      { fTx = inTx; }
			void                        SetTy( real3 inTy)      { fTy = inTy; }
			void                        SetTz( real3 inTz)      { fTy = inTz; }

			void                        SetTranslationTo( real3 inTx, real3 inTy, real3 inTz)   { fTx = inTx; fTy = inTy; fTy = inTz;}
			void                        SetTranslationBy( real3 inTx, real3 inTy, real3 inTz)   { fTx += inTx; fTy += inTy; fTy += inTz;}

            Translation3D&              operator=( const Translation3D& inSource);

    static  Translation3D               sNullTranslation3D;

protected:

            real3						fTx;
            real3						fTy;
            real3						fTz;
};



// ============================================================================



class Rotation3D
{
public:

    Rotation3D();
    Rotation3D( real3 inRx, real3 inRy, real3 inRz);
    Rotation3D( const Rotation3D& inSource);
    virtual ~Rotation3D();

			const real3&            GetRx() const       { return fRx; }
			const real3&            GetRy() const       { return fRy; }
			const real3&            GetRz() const       { return fRz; }

            void                    SetRx( real3 inRx);
            void                    SetRy( real3 inRy);
            void                    SetRz( real3 inRz);

            Rotation3D&             operator=(const Rotation3D& inSource);
            bool                    operator==(const Rotation3D& inSource);
            bool                    operator!=(const Rotation3D& inSource);

protected:

            void                    _Init( real3 inRx, real3 inRy, real3 inRz);

            real3                   fRx;
            real3                   fRy;
            real3                   fRz;
};



} // namespace KHEOPS



#endif
