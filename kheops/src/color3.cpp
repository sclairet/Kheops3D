

#include "core3.h"
#include "color3.h"



namespace KHEOPS
{



Color::Color()
{
    fRed = 0xFF;
    fGreen = 0xFF;
    fBlue = 0xFF;

	fHSLIsDirty = true;
	fHue = 0;
	fSaturation = 0;
	fLightness = 0;
}


Color::Color( ubyte3 inRed, ubyte3 inGreen, ubyte3 inBlue, ubyte3 inAlpha)
{
    fRed = inRed;
    fGreen = inGreen;
    fBlue = inBlue;
    fAlpha = inAlpha;

	fHSLIsDirty = true;
	fHue = 0;
	fSaturation = 0;
	fLightness = 0;
}


Color::Color( const Color &inSource)
{
    fRed = inSource.fRed;
    fGreen = inSource.fGreen;
    fBlue = inSource.fBlue;
    fAlpha = inSource.fAlpha;

	fHSLIsDirty = true;
	fHue = 0;
	fSaturation = 0;
	fLightness = 0;
}


Color::~Color()
{
}


void Color::Set( ubyte3 inRed, ubyte3 inGreen, ubyte3 inBlue, ubyte3 inAlpha)
{
    fRed = inRed;
    fGreen = inGreen;
    fBlue = inBlue;
    fAlpha = inAlpha;

	fHSLIsDirty = true;
}


void Color::ToHSL( real3& outHue, real3& outSaturation, real3& outLightness) const
{
	if (fHSLIsDirty)
	{
		real3 H = 0, S = 0, L = 0;
		
		real3 var_R = ( (real3)fRed / (real3)255 );
		real3 var_G = ( (real3)fGreen / (real3)255 );
		real3 var_B = ( (real3)fBlue / (real3)255 );

		real3 var_Min = std::min( var_R, var_G);
			if  (var_B < var_Min)
				var_Min = var_B;
		real3 var_Max = std::max( var_R, var_G);
		if (var_B > var_Max)
			var_Max = var_B;
		real3 del_Max = var_Max - var_Min;

		L = ( var_Max + var_Min ) / (real3)2;

		if ( del_Max == 0 )
		{
			H = 0;
			S = 0;
		}
		else
		{
			if ( L < 0.5 )
				S = del_Max / ( var_Max + var_Min );
			else
				S = del_Max / ( 2 - var_Max - var_Min );

			real3 del_R = ( ( ( var_Max - var_R ) / (real3)6 ) + ( del_Max / (real3)2 ) ) / del_Max;
			real3 del_G = ( ( ( var_Max - var_G ) / (real3)6 ) + ( del_Max / (real3)2 ) ) / del_Max;
			real3 del_B = ( ( ( var_Max - var_B ) / (real3)6 ) + ( del_Max / (real3)2 ) ) / del_Max;

			if ( var_R == var_Max )
				H = del_B - del_G;
			else if ( var_G == var_Max )
				H = ( (real3)1 / (real3)3 ) + del_R - del_B;
			else if ( var_B == var_Max )
				H = ( (real3)2 / (real3)3 ) + del_G - del_R;

			if ( H < 0 )
				H += 1;
			if ( H > 1 )
				H -= 1;
		}

		fHue = H;
		fSaturation = S;
		fLightness = L;
		fHSLIsDirty = false;
	}

	outHue = fHue;
	outSaturation = fSaturation;
	outLightness = fLightness;
}


real3 Hue_2_RGB( real3 v1, real3 v2, real3 vH )
{
	if ( vH < 0 )
		vH += 1;
	if ( vH > 1 )
		vH -= 1;
	if ( ( (real3)6 * vH ) < 1 )
		return ( v1 + ( v2 - v1 ) * (real3)6 * vH );
	if ( ( (real3)2 * vH ) < 1 )
		return ( v2 );
	if ( ( (real3)3 * vH ) < (real3)2 )
		return ( v1 + ( v2 - v1 ) * ( ( (real3)2 / (real3)3 ) - vH ) * (real3)6 );

	return ( v1 );
}


void Color::FromHSL( const real3& inHue, const real3& inSaturation, const real3& inLightness)
{
	ubyte3 R = 0, G = 0, B = 0;
	real3 H = inHue, S = inSaturation, L = inLightness;

	if ( S == 0.0 )
	{
		R = (ubyte3)(L * 255);
		G = (ubyte3)(L * 255);
		B = (ubyte3)(L * 255);
	}
	else
	{
		real3 var_2 = 0;

		if ( L < 0.5 )
			var_2 = L * ( 1 + S );
		else
			var_2 = ( L + S ) - ( S * L );

		real3 var_1 = (real3)2 * L - var_2;

		

		R = (ubyte3)(255 * Hue_2_RGB( var_1, var_2, H + ( (real3)1 / (real3)3 ) ));
		G = (ubyte3)(255 * Hue_2_RGB( var_1, var_2, H ));
		B = (ubyte3)(255 * Hue_2_RGB( var_1, var_2, H - ( (real3)1 / (real3)3 ) ));
	}

	fRed = R;
	fGreen = G;
	fBlue = B;

	fHSLIsDirty = false;
	fHue = inHue;
	fSaturation = inSaturation;
	fLightness = inLightness;
}


Color& Color::operator=(const Color& inSource)
{
    fRed = inSource.fRed;
    fGreen = inSource.fGreen;
    fBlue = inSource.fBlue;
    fAlpha = inSource.fAlpha;
    return *this;
}



} // namespace KHEOPS