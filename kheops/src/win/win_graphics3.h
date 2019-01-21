
// 06/10/2011

#ifndef __WIN_GRAPHICS3__
#define __WIN_GRAPHICS3__



namespace KHEOPS
{



class WinGraphics3D : public GraphicContext
{
public:

    WinGraphics3D( HWND inHwnd, HDC inHDC);
    virtual ~WinGraphics3D();

			void			SetScreenScaling( real3 inXAxisScaling, real3 inYAxisScaling);

    virtual void            DrawSegment( const Coord2D& inFrom, const Coord2D& inTo, const Color& inColor) const;

	virtual void            DrawSegments( const ArrayOfSegment& inSegments, const ArrayOfCoord2D& inCoords, const Color& inColor) const;

	virtual	void			DrawPixel( const Coord2D& inPos, const Color& inColor) const;

	virtual	void			DrawPixels( const ArrayOfCoord2D& inCoords, const Color& inColor) const;

	virtual	void			FillRect( const Coord2D& inTopLeft, const Coord2D&  inBottomRight, const Color& inColor) const;

	virtual void            FillPolygon( const vector<size_t>& inIndexes, const ArrayOfCoord2D& inCoords, const Color& inColor) const;

protected:
            HWND			fHwnd;
            HDC				fHDC;
			real3			fXAxisScaling;
			real3			fYAxisScaling;
};



} // namespace KHEOPS



#endif