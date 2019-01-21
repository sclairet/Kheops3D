
#include "core3.h"
#include <math.h>
#include <algorithm>
#include <assert.h>
#include "objects3.h"
#include "modeler3.h"


namespace KHEOPS
{



Modeler3D::Modeler3D()
{
}


Modeler3D::~Modeler3D()
{
}


Object3D* Modeler3D::CreateFromFile( Object3D *inParent, const wchar_t *inPath, ulong3 inSize)
{
	Object3D *obj = NULL;

	FILE *file = ::_wfopen( inPath, L"r");
	if (file != NULL)
	{
		bool ok = true;
		char buffer[1024];

		ArrayOfCoord3D coords;
		ArrayOfVector3D nVectors;
		std::vector< std::vector<size_t> > shapeCoordIndexes;
		std::vector< std::vector<size_t> > shapeNormalIndexes;

		while ((::fgets( buffer, 1024, file) != NULL) && ok)
		{
			size_t len = ::strlen( buffer);
			if (len > 1)
			{
				if (buffer[0] == 'v')
				{
					if (buffer[1] == 'n')
					{
						// it's a normal vector
						Vector3D nVector;
						ok = _OBJFILE_ReadNormalVectorLine( buffer, nVector);
						if (ok)
							nVectors.push_back( nVector);
					}
					else
					{
						// it's a coord (vertice)
						Coord3D coord;
						ok = _OBJFILE_ReadVerticeLine( buffer,  coord);
						if (ok)
						{
							coord.SetCoordsTo( coord.GetX() * inSize, coord.GetY() * inSize, coord.GetZ() * inSize);
							coords.push_back( coord);
						}
					}
				}
				else if (buffer[0] == 'f')
				{
					// it's a face
					std::vector<size_t> coordIndexes, normalIndexes;
					ok = _OBJFILE_ReadFaceLine( buffer, coordIndexes, normalIndexes);
					if (ok)
					{
						shapeCoordIndexes.push_back( coordIndexes);
						shapeNormalIndexes.push_back( normalIndexes);
					}
				}
			}
		}

		::fclose( file);
		file = NULL;

		if (ok)
		{
			obj = new Object3D();
			if (obj != NULL)
			{
				obj->fCoords = coords;
				size_t shapesCount = shapeCoordIndexes.size();
				for (size_t pos = 0 ; pos < shapesCount ; ++pos)
				{
					Shape3D *shape = Shape3D::CreateTriangle( shapeCoordIndexes[pos][0], shapeCoordIndexes[pos][1], shapeCoordIndexes[pos][2]);
					if (shape != NULL)
					{
						Vector3D normal;
						for (std::vector<size_t>::iterator nvIter = shapeNormalIndexes[pos].begin() ; nvIter != shapeNormalIndexes[pos].end() ; ++nvIter)
						{
							normal = normal + nVectors[*nvIter];
						}
						normal.Normalize();
						shape->SetNormalVector( normal);

						obj->fShapes.push_back( shape);
					}

				}
			}
		}
	}

	return  obj;
}


void Modeler3D::GetTriangularShapesIndexes( size_t inDot, const ArrayOfIndex& inCircleIndexes, std::vector<ArrayOfIndex>& outShapesIndexes)
{
	size_t pos = 0;
	outShapesIndexes.resize( inCircleIndexes.size());

	for (ArrayOfIndex_citer iter = inCircleIndexes.begin() ; iter < inCircleIndexes.end() - 1 ; ++iter)
	{
		outShapesIndexes[pos].push_back( inDot);
		outShapesIndexes[pos].push_back( *iter);
		outShapesIndexes[pos].push_back( *(iter + 1));
		++pos;
	}

	outShapesIndexes[pos].push_back( inDot);
	outShapesIndexes[pos].push_back( inCircleIndexes.back());
	outShapesIndexes[pos].push_back( inCircleIndexes.front());
}


bool Modeler3D::GetRectangularShapesIndexes( const ArrayOfIndex& inFirstCircleIndexes,  const ArrayOfIndex& inSecondCircleIndexes, std::vector<ArrayOfIndex>& outShapesIndexes)
{
	if (inFirstCircleIndexes.size() != inSecondCircleIndexes.size())
	{
		assert(false);
		return false;
	}
	
	size_t pos = 0;
	outShapesIndexes.resize( inFirstCircleIndexes.size());

	ArrayOfIndex_citer firstIter = inFirstCircleIndexes.begin();
	ArrayOfIndex_citer secondIter = inSecondCircleIndexes.begin();

	while (firstIter != inFirstCircleIndexes.end() -1)
	{
		outShapesIndexes[pos].push_back( *firstIter);
		outShapesIndexes[pos].push_back( *(firstIter + 1));
		outShapesIndexes[pos].push_back( *(secondIter + 1));
		outShapesIndexes[pos].push_back( *secondIter);
		++firstIter;
		++secondIter;
		++pos;
	}

	outShapesIndexes[pos].push_back( inFirstCircleIndexes.back());
	outShapesIndexes[pos].push_back( inFirstCircleIndexes.front());
	outShapesIndexes[pos].push_back( inSecondCircleIndexes.front());
	outShapesIndexes[pos].push_back( inSecondCircleIndexes.back());

	return true;
}


void Modeler3D::FillIndexesArray( std::vector<size_t>& inIndexes, size_t inFirstIndex, size_t inCount)
{
	inIndexes.resize( inCount);
	size_t pos = 0;
	while (pos < inCount)
	{
		inIndexes[pos] = inFirstIndex;
		++inFirstIndex;
		++pos;
	}
}


void Modeler3D::ResolveShapeNormalVector( Shape3D *inShape, const ArrayOfCoord3D& inCoords)
{
	std::vector<Vector3D> vectors;
	
	for (std::vector<size_t>::const_iterator iterInd = inShape->GetIndexes().begin() ; iterInd != inShape->GetIndexes().end() ; ++ iterInd)
	{
		vectors.push_back( Vector3D( inCoords[*iterInd].GetX(), inCoords[*iterInd].GetY(), inCoords[*iterInd].GetZ()));
	}

	Vector3D vn;

	for (std::vector<Vector3D>::iterator iterVct = vectors.begin() ; iterVct != vectors.end() ; ++iterVct)
	{
		vn = vn + *iterVct;
	}

	vn.Normalize();
	inShape->SetNormalVector( vn);
}


void Modeler3D::ResolveShapeNormalVector( Shape3D *inShape, const ArrayOfVector3D& inNormalVectors)
{
	Vector3D vn;

	for (std::vector<size_t>::const_iterator iterInd = inShape->GetIndexes().begin() ; iterInd != inShape->GetIndexes().end() ; ++ iterInd)
	{
		vn = vn + inNormalVectors[*iterInd];
	}

	vn.Normalize();
	inShape->SetNormalVector( vn);
}


ulong3 Modeler3D::GetCoordsCountPerCircle( EPrecision inPrecision)
{
    ulong3 count = 0;

    switch (inPrecision)
    {
    case eLowPrecision:
        count = 12;
        break;

    case eMediumPrecision:
        count = 24;
        break;

    case eHighPrecision:
		count = 36;
        break;

    case eVeryHighPrecision:
		count = 72;
        break;

	default:
        count = 24;
        break;
    }
    return count;
}


bool Modeler3D::_OBJFILE_ReadVerticeLine( const char *inBuffer, Coord3D& outCoord)
{
	bool ok = false;

	std::vector<double> coords;
	const char *ptr = inBuffer + 1;	// skip 'v' character
	char coordBuffer[1024];
	coordBuffer[0] = '\0';

	while (coords.size() < 3)
	{
		if (*ptr == '\0')	// end of line
		{
			if (coordBuffer[0] != '\0')
				coords.push_back( ::atof( coordBuffer));
			break;
		}
		else if  (*ptr == ' ')
		{
			if (coordBuffer[0] != '\0')
			{
				coords.push_back( ::atof( coordBuffer));
				coordBuffer[0] = '\0';
			}
		}
		else
		{
			size_t len = ::strlen( coordBuffer);
			coordBuffer[len] = *ptr;
			coordBuffer[len + 1] = '\0';
		}
		++ptr;
	}

	if (coords.size() == 3)
	{
		outCoord.SetCoordsTo( (real3)coords[0], (real3)coords[1], (real3)coords[2]);
		ok = true;
	}

	return ok;
}


bool Modeler3D::_OBJFILE_ReadNormalVectorLine( const char *inBuffer, Vector3D& outNormalVector)
{
	bool ok = false;

	std::vector<double> coords;
	const char *ptr = inBuffer + 2;	// skip 'vn' characters
	char coordBuffer[1024];
	coordBuffer[0] = '\0';

	while (coords.size() < 3)
	{
		if (*ptr == '\0')	// end of line
		{
			if (coordBuffer[0] != '\0')
				coords.push_back( ::atof( coordBuffer));
			break;
		}
		else if  (*ptr == ' ')
		{
			if (coordBuffer[0] != '\0')
			{
				coords.push_back( ::atof( coordBuffer));
				coordBuffer[0] = '\0';
			}
		}
		else
		{
			size_t len = ::strlen( coordBuffer);
			coordBuffer[len] = *ptr;
			coordBuffer[len + 1] = '\0';
		}
		++ptr;
	}

	if (coords.size() == 3)
	{
		outNormalVector.SetVx( (real3)coords[0]);
		outNormalVector.SetVy( (real3)coords[1]);
		outNormalVector.SetVz( (real3)coords[2]);
		ok = true;
	}

	return ok;
}


bool Modeler3D::_OBJFILE_ReadFaceLine( const char *inBuffer, std::vector<size_t>& outVerticeIndexes, std::vector<size_t>& outNormalIndexes)
{
	bool ok = true;

	const char *ptr = inBuffer + 1;	// skip 'f' character
	char blockBuffer[1024];
	blockBuffer[0] = '\0';

	while (ok)
	{
		if (*ptr == '\0')	// end of line
		{
			size_t len = ::strlen( blockBuffer);
			if (len > 0)
			{
				blockBuffer[len + 1] = '\0';
				size_t verticeIndex = 0, textureIndex = 0, normalIndex = 0;
				ok = _OBJFILE_ReadFaceBlock( blockBuffer, verticeIndex, textureIndex, normalIndex);
				if (ok)
				{
					outVerticeIndexes.push_back( verticeIndex);
					outNormalIndexes.push_back( normalIndex);
				}
			}
			break;
		}
		if  (*ptr == ' ')
		{
			size_t len = ::strlen( blockBuffer);
			if (len > 0)
			{
				blockBuffer[len + 1] = '\0';
				size_t verticeIndex = 0, textureIndex = 0, normalIndex = 0;
				ok = _OBJFILE_ReadFaceBlock( blockBuffer, verticeIndex, textureIndex, normalIndex);
				if (ok)
				{
					outVerticeIndexes.push_back( verticeIndex);
					outNormalIndexes.push_back( normalIndex);
				}
				blockBuffer[0] = '\0';
			}
		}
		else
		{
			size_t len = ::strlen( blockBuffer);
			blockBuffer[len] = *ptr;
			blockBuffer[len + 1] = '\0';
		}
		++ptr;
	}

	return ok;
}


bool Modeler3D::_OBJFILE_ReadFaceBlock( const char *inBuffer, size_t& outVerticeIndex, size_t& outTextureIndex, size_t& outNormalIndex)
{
	bool ok = false;

	std::vector<size_t> indexes;
	const char *ptr = inBuffer;
	char indexBuffer[1024];
	indexBuffer[0] = '\0';

	while (indexes.size() < 3)
	{
		if (*ptr == '\0')	// end of block
		{
			indexes.push_back( ::atoi( indexBuffer));
			break;
		}
		else if  (*ptr == '/')
		{
			indexes.push_back( ::atoi( indexBuffer));
			indexBuffer[0] = '\0';
		}
		else
		{
			size_t len = ::strlen( indexBuffer);
			indexBuffer[len] = *ptr;
			indexBuffer[len + 1] = '\0';
		}
		++ptr;
	}

	if (indexes.size() == 3)
	{
		outVerticeIndex = indexes[0] - 1;
		outTextureIndex = indexes[1] - 1;
		outNormalIndex = indexes[2] - 1;
		ok = true;
	}

	return ok;
}



} // namespace KHEOPS