// 08/02/2008


#ifndef __TYPES3__
#define __TYPES3__



namespace KHEOPS
{



// ============================================================================
// types definitions

typedef unsigned long   ulong3;
typedef long            slong3;

typedef unsigned short  uword3;
typedef short           sword3;

typedef unsigned char   ubyte3;
typedef char            sbyte3;

typedef float			real3;



// ============================================================================
// constants definitions


const ulong3 kDefault    = 0;
const ulong3 kLow        = 1;
const ulong3 kMedium     = 2;
const ulong3 kHigh       = 3;



const real3 kVirtualScreenWidth		= 1600;
const real3 kVirtualScreenHeight	= 900;



typedef enum
{
	ePrecisionUndefined = 0,
	eLowPrecision,
	eMediumPrecision,
	eHighPrecision,
	eVeryHighPrecision,
	eDefaultPrecision
};
typedef ulong3 EPrecision;



typedef enum
{
	eSolidColoringPattern = 0,
	eCheckerboardColoringPattern
};
typedef ulong3 EColoringPattern;



// drawing settings
const ulong3 kDrawSegment				= 0;
const ulong3 kDrawFilled				= 1;
const ulong3 kDrawShapeNormalVector		= 2;
const ulong3 kDrawRootWorld				= 4;



const real3 kPI     = (real3)3.1415926535897932384626433832795028841971693993751;
const real3 kPI2    = (real3)1.5707963267948966192313216916397514420985846996876;
const real3 kPI4    = (real3)0.78539816339744830961566084581987572104929234984378;


typedef enum
{
	eInterval_0_2PI = 1,	// [0 , 2Pi[
	eInterval_mPI_PI		// ]-Pi , Pi]
};
typedef ulong3 EArgumentInterval;


typedef enum
{
	eUndefinedAxis = 0,
	eXAxis,
	eYAxis,
	eZAxis,
	eFirstAxis = eXAxis,
	eLastAxis = eZAxis

};
typedef ulong3 EAxis;



typedef enum
{
	eUndefinedBase = 0,	//	used in rotation around:
	eBaseYoZ,			//	- X Axis
	eBaseZoY,			//	- X Axis
	eBaseZoX,			//	- Y Axis
	eBaseXoZ,			//	- Y Axis
	eBaseXoY,			//	- Z Axis
	eBaseYoX			//	- Z Axis

};
typedef ulong3 EBase;



typedef enum
{
	eUndefinedRotationDirection = 0,
	eAnticlockwiseRotation,
	eClockwiseRotation
};
typedef ulong3 ERotationDirection;



// Key code

typedef enum
{
	eUndefinedKey = 0,
	eKeyLeft,
	eKeyUp,
	eKeyRight,
	eKeyDown,
	eKeyHome,
	eKeyEnd,
	eKeyPageUp,
	eKeyPageDown,
	eKeySpace,
	eKeyMultiply,
	eKeyAdd,
	eKeySubstract,
	eKeyDivide

};
typedef slong3 EKey;



// Key modifiers
const ulong3 kShiftKey	= 0x00000001;
const ulong3 kCtrlKey	= 0x00000002;
const ulong3 kAltKey	= 0x00000004;

typedef ulong3	KeyModifiers;



} // namespace KHEOPS



#endif // __TYPES3__
