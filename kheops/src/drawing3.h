// 08/02/2008


#ifndef __DRAWING3__
#define __DRAWING3__



namespace KHEOPS
{


// ============================================================================
// needed declarations
class Object3D;
class Scene3D;
class Camera;




// ============================================================================
// interface GraphicContext


class GraphicContext
{
public:

    GraphicContext()             { ; }
    virtual ~GraphicContext()    { ; }

    virtual void            DrawSegment( const Coord2D& inFrom, const Coord2D& inTo, const Color& inColor) const = 0;

	virtual void            DrawSegments( const ArrayOfSegment& inSegments, const ArrayOfCoord2D& inCoords, const Color& inColor) const = 0;

	virtual	void			DrawPixel( const Coord2D& inPos, const Color& inColor) const = 0;

	virtual	void			DrawPixels( const ArrayOfCoord2D& inCoords, const Color& inColor) const = 0;

    virtual	void			FillRect( const Coord2D& inTopLeft, const Coord2D&  inBottomRight, const Color& inColor) const = 0;
	
	virtual void            FillPolygon( const vector<size_t>& inIndexes, const ArrayOfCoord2D& inCoords, const Color& inColor) const = 0;
};



} // namespace KHEOPS



#endif // __DRAWING3__
