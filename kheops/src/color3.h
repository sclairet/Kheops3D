
#ifndef __COLOR3__
#define __COLOR3__



namespace KHEOPS
{



/*	============================================================================

	HSL
	- Hue (teinte): 0 - 1
	- Saturation (saturation): 0 - 1
	- Lightness (luminance): 0 - 1

	============================================================================*/



class Color
{
public:

    Color();
    Color( ubyte3 inRed, ubyte3 inGreen, ubyte3 inBlue, ubyte3 inAlpha = 0xFF);
    Color( const Color &inSource);
    virtual ~Color();

            void            Set( ubyte3 inRed, ubyte3 inGreen, ubyte3 inBlue, ubyte3 inAlpha = 0xFF);

			const ubyte3&   GetRed() const          { return fRed; }
			const ubyte3&   GetGreen() const        { return fGreen; }
			const ubyte3&   GetBlue() const         { return fBlue; }
			const ubyte3&   GetAlpha() const        { return fAlpha; }

			ubyte3&         GetRed()                { return fRed; }
			ubyte3&         GetGreen()              { return fGreen; }
			ubyte3&         GetBlue()               { return fBlue; }
			ubyte3&         GetAlpha()              { return fAlpha; }

			void			ToHSL( real3& outHue, real3& outSaturation, real3& outLightness) const;
			void			FromHSL( const real3& inHue, const real3& inSaturation, const real3& inLightness); 

            Color&          operator=(const Color& inSource);

private:

            ubyte3          fRed;
            ubyte3          fGreen;
            ubyte3          fBlue;
            ubyte3          fAlpha;

			// HSL
	mutable	bool			fHSLIsDirty;
	mutable	real3			fHue;
	mutable	real3			fSaturation;
	mutable	real3			fLightness;
};



} // namespace KHEOPS



#endif