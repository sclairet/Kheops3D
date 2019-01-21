
#ifndef __MODELER3__
#define __MODELER3__



namespace KHEOPS
{


class Object3D;


class Modeler3D
{
public:

	Modeler3D();
	virtual ~Modeler3D();

			Object3D*			CreateFromFile( Object3D *inParent, const wchar_t *inPath, ulong3 inSize);

			// Low level primitives

			// Returns the indexes of all triangular shapes which exist between a dot and a circle.
			// If the dot matches the circle center, it returns the indexes of triangular shapes of a disc.
	static	void				GetTriangularShapesIndexes( size_t inDot, const ArrayOfIndex& inCircleIndexes, std::vector<ArrayOfIndex>& outShapesIndexes);

			// Returns the indexes of all rectangular shapes which exist between two circle.
            // The circles MUST have the same indexes count.
	static	bool				GetRectangularShapesIndexes( const ArrayOfIndex& inFirstCircleIndexes,  const ArrayOfIndex& inSecondCircleIndexes, std::vector<ArrayOfIndex>& outShapesIndexes);

			void				FillIndexesArray( std::vector<size_t>& inIndexes, size_t inFirstIndex, size_t inCount);

	static	void				ResolveShapeNormalVector( Shape3D *inShape, const ArrayOfCoord3D& inCoords);
	static	void				ResolveShapeNormalVector( Shape3D *inShape, const ArrayOfVector3D& inNormalVectors);

			// Utilities
	static	ulong3				GetCoordsCountPerCircle( EPrecision inPrecision);

private:
			bool				_OBJFILE_ReadVerticeLine( const char *inBuffer, Coord3D& outVertice);
			bool				_OBJFILE_ReadNormalVectorLine( const char *inBuffer, Vector3D& outNormalVector);
			bool				_OBJFILE_ReadFaceLine( const char *inBuffer, std::vector<size_t>& outVerticeIndexes, std::vector<size_t>& outNormalIndexes);
			bool				_OBJFILE_ReadFaceBlock( const char *inBuffer, size_t& outVerticeIndex, size_t& outTextureIndex, size_t& outNormalIndex);



			void				_ResolveShapeNormalVector( Shape3D *inShape, const ArrayOfCoord3D& inCoords);
};



} // namespace KHEOPS



#endif