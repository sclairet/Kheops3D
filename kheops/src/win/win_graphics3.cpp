
// 06/10/2011

#include "core3.h"
#include <assert.h>
#include <windows.h>
#include "win_graphics3.h"



namespace KHEOPS
{



WinGraphics3D::WinGraphics3D( HWND inHwnd, HDC inHDC)
: fHwnd( inHwnd), fHDC( inHDC), fXAxisScaling(1), fYAxisScaling(1)
{
}


WinGraphics3D::~WinGraphics3D()
{
}


void WinGraphics3D::SetScreenScaling( real3 inXAxisScaling, real3 inYAxisScaling)
{
	fXAxisScaling = inXAxisScaling;
	fYAxisScaling = inYAxisScaling;
}


void WinGraphics3D::DrawSegment( const Coord2D& inFrom, const Coord2D& inTo, const Color& inColor) const
{
    if (fHDC != NULL)
    {
		COLORREF colorRef = RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue());

		HPEN hPen = ::CreatePen( PS_SOLID, 1, colorRef);
		if (hPen != NULL)
		{
			HGDIOBJ previousObj = ::SelectObject( fHDC, hPen);

			::MoveToEx( fHDC, (int)inFrom.GetX()*fXAxisScaling, (int)inFrom.GetY()*fYAxisScaling, NULL);
			::LineTo( fHDC, (int)inTo.GetX()*fXAxisScaling, (int)inTo.GetY()*fYAxisScaling);

			::SelectObject( fHDC, previousObj);

			::DeleteObject( hPen);
			hPen = NULL;
		}
    }
}


void WinGraphics3D::DrawSegments( const ArrayOfSegment& inSegments, const ArrayOfCoord2D& inCoords, const Color& inColor) const
{
    if (fHDC != NULL)
    {
		COLORREF colorRef = RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue());

		HPEN hPen = ::CreatePen( PS_SOLID, 1, colorRef);
		if (hPen != NULL)
		{
			HGDIOBJ previousObj = ::SelectObject( fHDC, hPen);

			for( ArrayOfSegment_citer iter = inSegments.begin() ; iter != inSegments.end() ; ++iter )
			{
				size_t fromCoord = (*iter).GetFrom();
				size_t toCoord = (*iter).GetTo();

				if ( (fromCoord >= 0) && (fromCoord < inCoords.size()) && (toCoord >= 0) && (toCoord < inCoords.size()) )
				{
					::MoveToEx( fHDC, (int)inCoords[fromCoord].GetX()*fXAxisScaling, (int)inCoords[fromCoord].GetY()*fYAxisScaling, NULL);
					::LineTo( fHDC, (int)inCoords[toCoord].GetX()*fXAxisScaling, (int)inCoords[toCoord].GetY()*fYAxisScaling);
				}
				else
				{
					assert(false);
				}
			}

			::SelectObject( fHDC, previousObj);

			::DeleteObject( hPen);
			hPen = NULL;
		}
    }
}


void WinGraphics3D::DrawPixel( const Coord2D& inPos, const Color& inColor) const
{
	if (fHDC != NULL)
	{
		::SetPixel( fHDC, (int)inPos.GetX()*fXAxisScaling, (int)inPos.GetY()*fYAxisScaling, RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue()));
	}
}


void WinGraphics3D::DrawPixels( const ArrayOfCoord2D& inCoords, const Color& inColor) const
{
	if (fHDC != NULL)
	{
		COLORREF colorRef = RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue());

		for (ArrayOfCoord2D_citer iter = inCoords.begin() ; iter != inCoords.end() ; ++iter)
		{
			::SetPixel( fHDC, (int)(*iter).GetX()*fXAxisScaling, (int)(*iter).GetY()*fYAxisScaling, colorRef);
		}
	}
}


void WinGraphics3D::FillRect( const Coord2D& inTopLeft, const Coord2D&  inBottomRight, const Color& inColor) const
{
    if (fHDC != NULL)
    {
		COLORREF colorRef = RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue());

		HBRUSH hBrush = ::CreateSolidBrush( colorRef);
		if (hBrush != NULL)
		{
			RECT rect = { (int)inTopLeft.GetX()*fXAxisScaling, (int)inTopLeft.GetY()*fYAxisScaling, (int)inBottomRight.GetX()*fXAxisScaling, (int)inBottomRight.GetY()*fYAxisScaling };
			::FillRect( fHDC, &rect, hBrush);
			::DeleteObject( hBrush);
			hBrush = NULL;
		}
	}
}


void WinGraphics3D::FillPolygon( const vector<size_t>& inIndexes, const ArrayOfCoord2D& inCoords, const Color& inColor) const
{
    if (fHDC != NULL)
    {
		COLORREF colorRef = RGB( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue());

		HPEN hPen = ::CreatePen( PS_SOLID, 1, colorRef);
		if (hPen != NULL)
		{
			HGDIOBJ previousPen = ::SelectObject( fHDC, hPen);

			HBRUSH hBrush = ::CreateSolidBrush( colorRef);
			if (hBrush != NULL)
			{
				HGDIOBJ previousBrush = ::SelectObject( fHDC, hBrush);

				POINT *lpPoints = (POINT*)::malloc( inIndexes.size() * sizeof(POINT));
				int pos = 0;

				for (std::vector<size_t>::const_iterator indexIter = inIndexes.begin() ; indexIter != inIndexes.end() ; ++indexIter)
				{
					assert((*indexIter) >= 0 && (*indexIter) < inCoords.size());

					if ((*indexIter) >= 0 && (*indexIter) < inCoords.size())
					{
						(*(lpPoints + pos)).x = (LONG) inCoords[*indexIter].GetX()*fXAxisScaling;
						(*(lpPoints + pos)).y = (LONG) inCoords[*indexIter].GetY()*fYAxisScaling;
					}
					++pos;
				}
				
				BOOL ok = ::Polygon( fHDC, lpPoints, inIndexes.size());

				::free( (void*)lpPoints);
				lpPoints = NULL;

				::SelectObject( fHDC, previousBrush);

				::DeleteObject( hBrush);
				hBrush = NULL;
			}

			::SelectObject( fHDC, previousPen);

			::DeleteObject( hPen);
			hPen = NULL;
		}
	}
}



} // namespace KHEOPS
