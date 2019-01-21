

#include "core3.h"
#include <assert.h>
#include <math.h>
#include <algorithm>
#include "objects3.h"
#include "objects3_behaviour.h"
#include "modeler3.h"


namespace KHEOPS
{



Object3D_behaviour::Object3D_behaviour()
: fObject(NULL)
{
}


Object3D_behaviour::~Object3D_behaviour()
{
}


void Object3D_behaviour::SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor)
{
	if (inPattern == eSolidColoringPattern)
	{
		ArrayPtrOfShape3D *shapes = _GetObjectShapes();
		if (shapes != NULL)
		{
			for (ArrayPtrOfShape3D_iter iter = shapes->begin() ; iter != shapes->end() ; ++iter)
			{
				if (*iter != NULL)
					(*iter)->SetColor( inFirstColor);
			}
		}
	}
	else
	{
		assert(false);
	}
}


void Object3D_behaviour::_SetObject( Object3D *inObject)
{
	fObject = inObject;
}


Object3D* Object3D_behaviour::_GetObject() const
{
	return fObject;
}


ArrayOfCoord3D* Object3D_behaviour::_GetObjectCoords() const
{
	if (fObject != NULL)
		return &fObject->fCoords;

	return NULL;
}


ArrayPtrOfShape3D* Object3D_behaviour::_GetObjectShapes() const
{
	if (fObject != NULL)
		return &fObject->fShapes;

	return NULL;
}



// ============================================================================



ObjRect3D::ObjRect3D()
{
}


ObjRect3D::~ObjRect3D()
{
}


void ObjRect3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


void ObjRect3D::SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor)
{
	if (inPattern == eCheckerboardColoringPattern)
	{
		ArrayPtrOfShape3D *shapes = _GetObjectShapes();
		if (shapes != NULL)
		{
			ulong3 wShapesCount = fCoordsCountPerWidth-1, hShapesCount = fCoordsCountPerHeight-1;
			ulong3 shapeOffset[2] = { 0, wShapesCount*hShapesCount};

			for (ubyte3 offsetIter = 0 ; offsetIter < 2 ; ++offsetIter)
			{
				bool beginFirstColor = true;
				for (ulong3 hIndex = 0 ; hIndex < hShapesCount ; ++hIndex)
				{
					bool useFirstColor = beginFirstColor;
					for (ulong3 wIndex = 0 ; wIndex < wShapesCount ; ++wIndex)
					{
						Shape3D *shape = (*shapes)[wIndex + hIndex*hShapesCount + shapeOffset[offsetIter]];
						if (shape != NULL)
						{
							shape->SetColor( (useFirstColor) ? inFirstColor : inSecondColor);
							useFirstColor = !useFirstColor;
						}
					}
					
					beginFirstColor = !beginFirstColor;
				}
			}
		}
	}
	else
	{
		Object3D_behaviour::SetColor( inPattern, inFirstColor, inSecondColor);
	}
}


Object3D* ObjRect3D::CreateRect( real3 inWidth, ulong3 inWidthSegmentsCount, real3 inHeight, ulong3 inHeightSegmentsCount, EBase inBase)
{
	Object3D *obj = NULL;

	ObjRect3D *rect = new ObjRect3D();
	if (rect != NULL)
	{
		obj = new Object3D( rect);
		if (obj != NULL)
		{
			rect->_SetObject( obj);

			rect->fCoordsCountPerWidth = inWidthSegmentsCount+1;
			rect->fCoordsCountPerHeight = inHeightSegmentsCount+1;
			
			ArrayOfCoord3D *coords = rect->_GetObjectCoords();
			ArrayPtrOfShape3D *shapes = rect->_GetObjectShapes();

			if (coords != NULL && shapes != NULL)
			{
				real3 wDelta = inWidth/inWidthSegmentsCount, hDelta = inHeight/inHeightSegmentsCount;

				coords->push_back( Coord3D( inWidth/2, 0, inHeight/2)); // center

				for (ulong3 hPos = 0 ; hPos <= inHeightSegmentsCount ; ++hPos)
				{
					for (ulong3 wPos = 0 ; wPos <= inWidthSegmentsCount ; ++wPos)
					{
						if (inBase == eBaseXoZ)
						{
							coords->push_back( Coord3D( wPos*wDelta, 0, hPos*hDelta));
						}
						else
						{
							assert(false);
						}
					}
				}


				Vector3D vNormal[2] = { Vector3D( 0, 1, 0), Vector3D( 0, -1, 0) };

				for (ubyte3 normalIter = 0 ; normalIter < 2 ; ++normalIter)
				{
					for (ulong3 hIndex = 0 ; hIndex < rect->fCoordsCountPerHeight-1 ; ++hIndex)
					{
						for (ulong3 wIndex = 1 ; wIndex < rect->fCoordsCountPerWidth ; ++wIndex)
						{
							Shape3D *shape = Shape3D::CreateRect(	wIndex+(hIndex*rect->fCoordsCountPerWidth),
																	wIndex+(hIndex*rect->fCoordsCountPerWidth)+1,
																	wIndex+((hIndex+1)*rect->fCoordsCountPerWidth)+1,
																	wIndex+((hIndex+1)*rect->fCoordsCountPerWidth),
																	&vNormal[normalIter]);
							if (shape != NULL)
							{
								shapes->push_back( shape);
							}
						}
					}
				}
			}
		}
		else
		{
			delete rect;
		}
	}

	return obj;
}



// ============================================================================



ObjCubic3D::ObjCubic3D()
: Object3D_behaviour()
{
}


ObjCubic3D::~ObjCubic3D()
{
}


void ObjCubic3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


Object3D* ObjCubic3D::CreateCube( real3 inSize)
{
	return CreateBox( inSize, inSize, inSize);
}


Object3D* ObjCubic3D::CreateBox( real3 inWidth, real3 inHeight, real3 inDepth)
{
	Object3D *obj = NULL;

	ObjCubic3D *box = new ObjCubic3D();
	if (box != NULL)
	{
		obj = new Object3D( box);
		if (obj != NULL)
		{
			box->_SetObject( obj);
			
			ArrayOfCoord3D *coords = box->_GetObjectCoords();
			ArrayPtrOfShape3D *shapes = box->_GetObjectShapes();

			if (coords != NULL && shapes != NULL)
			{
				coords->resize( 9);

				(*coords)[0].SetCoordsTo( 0, 0, 0);	// center
				(*coords)[1].SetCoordsTo( inWidth/2, inHeight/2, inDepth/2);
				(*coords)[2].SetCoordsTo( -inWidth/2, inHeight/2, inDepth/2);
				(*coords)[3].SetCoordsTo( -inWidth/2, -inHeight/2, inDepth/2);
				(*coords)[4].SetCoordsTo( inWidth/2, -inHeight/2, inDepth/2);
				(*coords)[5].SetCoordsTo( inWidth/2, inHeight/2, -inDepth/2);
				(*coords)[6].SetCoordsTo( -inWidth/2, inHeight/2, -inDepth/2);
				(*coords)[7].SetCoordsTo( -inWidth/2, -inHeight/2, -inDepth/2);
				(*coords)[8].SetCoordsTo( inWidth/2, -inHeight/2, -inDepth/2);

				shapes->resize( 6, NULL);

				(*shapes)[0] = Shape3D::CreateRect( 1, 2, 3, 4, &Vector3D( 0, 0, 1));	// front face
				(*shapes)[1] = Shape3D::CreateRect( 6, 5, 8, 7, &Vector3D( 0, 0, -1));	// back face
				(*shapes)[2] = Shape3D::CreateRect( 5, 6, 2, 1, &Vector3D( 0, 1, 0));	// top face
				(*shapes)[3] = Shape3D::CreateRect( 4, 3, 7, 8, &Vector3D( 0, -1, 0));	// bottom face
				(*shapes)[4] = Shape3D::CreateRect( 5, 1, 4, 8, &Vector3D( 1, 0, 0));	// right face
				(*shapes)[5] = Shape3D::CreateRect( 2, 6, 7, 3, &Vector3D( -1, 0, 0));	// left face
			}
		}
		else
		{
			delete box;
		}
	}

	return obj;
}



// ============================================================================



ObjCylindric3D::ObjCylindric3D()
: fThickness(0), fCoordsCountPerCircle(0)
{
}


ObjCylindric3D::~ObjCylindric3D()
{
}


void ObjCylindric3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


Object3D* ObjCylindric3D::CreateCylinderPerpendicularToYAxis( real3 inDiameter, real3 inMiddleDiameter, real3 inHeight, EPrecision inPrecision)
{
	ObjCylindric3D *cylinder = _Instantiate();
	if (cylinder != NULL)
	{
		cylinder->_CreateCylinderPerpendicularToYAxis( inDiameter, inMiddleDiameter, inHeight, inPrecision);
		return cylinder->_GetObject();
	}

	return NULL;
}


Object3D* ObjCylindric3D::CreateStraightCylinderPerpendicularToYAxis( real3 inBottomDiameter, real3 inTopDiameter, real3 inHeight, EPrecision inPrecision)
{
	ObjCylindric3D *cylinder = _Instantiate();
	if (cylinder != NULL)
	{
		cylinder->_CreateStraightCylinderPerpendicularToYAxis( inBottomDiameter, inTopDiameter, inHeight, inPrecision);
		return cylinder->_GetObject();
	}

	return NULL;
}


Object3D* ObjCylindric3D::CreateHollowedCenterStraightCylinderPerpendicularToYAxis( real3 inInternalBottomDiameter, real3 inExternalBottomDiameter, real3 inInternalTopDiameter, real3 inExternalTopDiameter, real3 inHeight, EPrecision inPrecision)
{
	ObjCylindric3D *cylinder = _Instantiate();
	if (cylinder != NULL)
	{
		cylinder->_CreateHollowedCenterStraightCylinderPerpendicularToYAxis( inInternalBottomDiameter, inExternalBottomDiameter, inInternalTopDiameter, inExternalTopDiameter, inHeight, inPrecision);
		return cylinder->_GetObject();
	}

	return NULL;
}


ObjCylindric3D* ObjCylindric3D::_Instantiate()
{
	ObjCylindric3D *cylinder = new ObjCylindric3D();
	if (cylinder != NULL)
	{
		Object3D *obj = new Object3D( cylinder);
		if (obj != NULL)
		{
			cylinder->_SetObject( obj);
		}
		else
		{
			delete cylinder;
			cylinder = NULL;
		}
	}

	return cylinder;
}


void ObjCylindric3D::_BuildCylinderPerpendicularToYAxis( const ArrayOfCoord3D& inSideCoords)
{
	assert(inSideCoords.size() > 1);

	if (inSideCoords.size() > 1)
	{
		ArrayOfCoord3D *coords = _GetObjectCoords();
		ArrayPtrOfShape3D *shapes = _GetObjectShapes();

		if (coords != NULL && shapes != NULL)
		{
			coords->push_back( Coord3D( 0, 0, 0));	// center

			std::vector<ArrayOfIndex> indexes;
			for (ulong3 pos = 0 ; pos < inSideCoords.size() ; ++pos)
			{
				ArrayOfCoord3D circleCoords;
				Math::GetCoordsForCirclePerpendicularToYAxis( circleCoords, inSideCoords[pos].GetZ(), fCoordsCountPerCircle, eBaseXoZ);
				Math::TranslateBy( circleCoords, 0, inSideCoords[pos].GetY(), 0);
				
				coords->push_back( Coord3D( 0, inSideCoords[pos].GetY(), 0));	// circle center
				coords->insert( coords->end(), circleCoords.begin(), circleCoords.end()); //	circle coords
				
				ArrayOfIndex circleIndexes;
				FillIndexesArray( circleIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
				circleIndexes.push_back(circleIndexes.front());
				indexes.push_back(circleIndexes);
			}

			// append bottom disc shapes
			std::vector<ArrayOfIndex> bottomDiscShapesIndexes;
			Modeler3D::GetTriangularShapesIndexes( 1, indexes.front(), bottomDiscShapesIndexes);
			
			for (std::vector<ArrayOfIndex>::iterator iter = bottomDiscShapesIndexes.begin() ; iter != bottomDiscShapesIndexes.end() ; ++iter)
			{
				shapes->push_back( Shape3D::Create( *iter, &Vector3D( 0, -1, 0)));
			}

			std::vector<ArrayOfIndex> topDiscShapesIndexes;
			Modeler3D::GetTriangularShapesIndexes( coords->size()-fCoordsCountPerCircle-1, indexes.back(), topDiscShapesIndexes);

			// append top disc shapes
			for (std::vector<ArrayOfIndex>::iterator iter = topDiscShapesIndexes.begin() ; iter != topDiscShapesIndexes.end() ; ++iter)
			{
				shapes->push_back( Shape3D::Create( *iter, &Vector3D( 0, 1, 0)));
			}

			// append the side rectangular shapes
			for (ulong3 indexesPos = 0 ; indexesPos < indexes.size() - 1 ; ++indexesPos)
			{
				for (ulong3 pos = 0 ; pos < indexes[indexesPos].size() - 1 ; ++pos)
				{
					Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[indexes[indexesPos][pos+1]],(*coords)[indexes[indexesPos+1][pos+1]]),
																	Vector3D( (*coords)[indexes[indexesPos][pos+1]],(*coords)[indexes[indexesPos][pos]]),
																	false);
					normal.Normalize();
					Shape3D *shape = Shape3D::CreateRect( indexes[indexesPos+1][pos], indexes[indexesPos+1][pos+1], indexes[indexesPos][pos+1], indexes[indexesPos][pos], &normal);
					if (shape != NULL)
					{
						shapes->push_back( shape);
					}
				}
			}
		}
	}
}


void ObjCylindric3D::_CreateCylinderPerpendicularToYAxis( real3 inDiameter, real3 inMiddleDiameter, real3 inHeight, EPrecision inPrecision)
{
	fThickness = inHeight;
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	// calcul de la fleche (sagitta or versine)
	real3 sagitta = abs((inDiameter - inMiddleDiameter) / 2);
	real3 chord = inHeight;
	// calcul du rayon
	real3 radius = (4*pow(sagitta,2) + pow(chord,2)) / (8*sagitta);
	// calcul de l'argument
	real3 arg = acos((radius-sagitta)/radius);

	ArrayOfCoord3D arcCoords;
	Math::GetCoordsForArcPerpendicularToXAxis( arcCoords, -arg, arg, radius, fCoordsCountPerCircle/2 + 1, eBaseZoY);
	Math::TranslateBy( arcCoords, 0, 0, -arcCoords.front().GetZ());

	if (inMiddleDiameter < inDiameter)
		Math::RotateBy( arcCoords,0, kPI, 0);

	Math::TranslateBy( arcCoords, 0, 0, inDiameter/2);

	_BuildCylinderPerpendicularToYAxis( arcCoords);
}


void ObjCylindric3D::_CreateStraightCylinderPerpendicularToYAxis( real3 inBottomDiameter, real3 inTopDiameter, real3 inHeight, EPrecision inPrecision)
{
	fThickness = inHeight;
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D sideCoords;
	sideCoords.push_back( Coord3D( 0, - inHeight/2, inBottomDiameter/2));
	sideCoords.push_back( Coord3D( 0, inHeight/2, inTopDiameter/2));

	_BuildCylinderPerpendicularToYAxis( sideCoords);
}


void ObjCylindric3D::_CreateHollowedCenterStraightCylinderPerpendicularToYAxis( real3 inInternalBottomDiameter, real3 inExternalBottomDiameter, real3 inInternalTopDiameter, real3 inExternalTopDiameter, real3 inHeight, EPrecision inPrecision)
{
	fThickness = inHeight;
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D *coords = _GetObjectCoords();
	ArrayPtrOfShape3D *shapes = _GetObjectShapes();

	if (coords != NULL && shapes != NULL)
	{
		ArrayOfCoord3D intTopCoords, extTopCoords, intBottomCoords, extBottomCoords;
		ArrayOfIndex intTopIndexes, extTopIndexes, intBottomIndexes, extBottomIndexes;

		coords->push_back( Coord3D( 0, 0, 0));	// center

		// create bottom circles
		Math::GetCoordsForCirclePerpendicularToYAxis( intBottomCoords, inInternalBottomDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);
		Math::GetCoordsForCirclePerpendicularToYAxis( extBottomCoords, inExternalBottomDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);
		Math::SetPosBy( intBottomCoords, 0, - inHeight / 2, 0);
		Math::SetPosBy( extBottomCoords, 0, - inHeight / 2, 0);

		// create top circles
		Math::GetCoordsForCirclePerpendicularToYAxis( intTopCoords, inInternalTopDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);
		Math::GetCoordsForCirclePerpendicularToYAxis( extTopCoords, inExternalTopDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);
		Math::SetPosBy( intTopCoords, 0, inHeight / 2, 0);
		Math::SetPosBy( extTopCoords, 0, inHeight / 2, 0);

		coords->push_back( Coord3D( 0, - inHeight / 2, 0));	// bottom circles center

		coords->insert( coords->end(), extBottomCoords.begin(), extBottomCoords.end());
		FillIndexesArray( extBottomIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
		extBottomIndexes.push_back( extBottomIndexes.front());

		coords->insert( coords->end(), intBottomCoords.begin(), intBottomCoords.end());
		FillIndexesArray( intBottomIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
		intBottomIndexes.push_back( intBottomIndexes.front());

		coords->push_back( Coord3D( 0, inHeight / 2, 0));	// top circles center

		coords->insert( coords->end(), extTopCoords.begin(), extTopCoords.end());
		FillIndexesArray( extTopIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
		extTopIndexes.push_back( extTopIndexes.front());

		coords->insert( coords->end(), intTopCoords.begin(), intTopCoords.end());
		FillIndexesArray( intTopIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
		intTopIndexes.push_back( intTopIndexes.front());

		// append bottom shapes
		for (ulong3 pos = 0 ; pos < intBottomIndexes.size() - 1 ; ++pos)
		{
			Shape3D *shape = Shape3D::CreateRect( intBottomIndexes[pos], intBottomIndexes[pos+1], extBottomIndexes[pos+1], extBottomIndexes[pos], &Vector3D( 0, -1, 0));
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}

		// append top shapes
		for (ulong3 pos = 0 ; pos < intTopIndexes.size() - 1 ; ++pos)
		{
			Shape3D *shape = Shape3D::CreateRect( intTopIndexes[pos], intTopIndexes[pos+1], extTopIndexes[pos+1], extTopIndexes[pos], &Vector3D( 0, 1, 0));
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}

		// append external side shapes
		for (size_t pos = 0 ; pos < extBottomIndexes.size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[extBottomIndexes[pos+1]],(*coords)[extTopIndexes[pos+1]]),
															Vector3D( (*coords)[extBottomIndexes[pos+1]],(*coords)[extBottomIndexes[pos]]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateRect( extTopIndexes[pos], extTopIndexes[pos+1], extBottomIndexes[pos+1], extBottomIndexes[pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}

		// append internal side shapes
		for (size_t pos = 0 ; pos < intBottomIndexes.size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[intBottomIndexes[pos]],(*coords)[intTopIndexes[pos]]),
															Vector3D( (*coords)[intBottomIndexes[pos]],(*coords)[intBottomIndexes[pos+1]]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateRect( intTopIndexes[pos], intTopIndexes[pos+1], intBottomIndexes[pos+1], intBottomIndexes[pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}
	}
}



// ============================================================================



ObjConic3D::ObjConic3D()
: fHeight(0), fCoordsCountPerCircle(0)
{
}


ObjConic3D::~ObjConic3D()
{
}


void ObjConic3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


Object3D* ObjConic3D::CreateConePerpendicularToYAxis( real3 inBottomDiameter, real3 inHeight, EPrecision inPrecision)
{
	Object3D *obj = NULL;

	ObjConic3D *cone = new ObjConic3D();
	if (cone != NULL)
	{
		obj = new Object3D( cone);
		if (obj != NULL)
		{
			cone->_SetObject( obj);
			cone->_CreateConePerpendicularToYAxis( inBottomDiameter, inHeight, inPrecision);
		}
		else
		{
			delete cone;
		}
	}

	return obj;
}


void ObjConic3D::_CreateConePerpendicularToYAxis( real3 inBottomDiameter, real3 inHeight, EPrecision inPrecision)
{
	fHeight = inHeight;
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D *coords = _GetObjectCoords();
	ArrayPtrOfShape3D *shapes = _GetObjectShapes();

	if (coords != NULL && shapes != NULL)
	{
		ulong3 bottomDiscCenterIndex = 1;
		ulong3 bottomDiscFirstIndex = 2;
		ulong3 apexIndex = bottomDiscFirstIndex + fCoordsCountPerCircle;
		ArrayOfCoord3D circleCoords;

		coords->push_back( Coord3D( 0, 0, 0));	// center

		// build bottom disc coords
		coords->push_back( Coord3D( 0, - inHeight / 2, 0));	// bottom disc center
		Math::GetCoordsForCirclePerpendicularToYAxis( circleCoords, inBottomDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);
		Math::TranslateBy( circleCoords, 0, - inHeight / 2, 0);
		coords->insert( coords->end(), circleCoords.begin(), circleCoords.end());
		
		// build bottom disc shape indexes
		ArrayOfIndex bottomDiscIndexes;
		FillIndexesArray( bottomDiscIndexes, bottomDiscFirstIndex, fCoordsCountPerCircle);
		std::vector<ArrayOfIndex> bottomDiscShapesIndexes;
		Modeler3D::GetTriangularShapesIndexes( bottomDiscCenterIndex, bottomDiscIndexes, bottomDiscShapesIndexes);

		// append bottom disc shapes
		for (std::vector<ArrayOfIndex>::iterator iter = bottomDiscShapesIndexes.begin() ; iter != bottomDiscShapesIndexes.end() ; ++iter)
		{
			shapes->push_back( Shape3D::Create( *iter, &Vector3D( 0, -1, 0)));
		}

		coords->push_back( Coord3D( 0, inHeight / 2, 0));	// apex coord

		// append the side shapes
		bottomDiscIndexes.push_back( bottomDiscIndexes.front());

		for (size_t pos = 0 ; pos < bottomDiscIndexes.size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[bottomDiscIndexes[pos+1]],(*coords)[apexIndex]),
															Vector3D( (*coords)[bottomDiscIndexes[pos+1]],(*coords)[bottomDiscIndexes[pos]]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateTriangle( apexIndex, bottomDiscIndexes[pos+1], bottomDiscIndexes[pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}
	}
}



// ============================================================================



ObjSpheric3D::ObjSpheric3D()
: fCoordsCountPerCircle(0)
{
}


ObjSpheric3D::~ObjSpheric3D()
{
}


void ObjSpheric3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


void ObjSpheric3D::SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor)
{
	if (inPattern == eCheckerboardColoringPattern)
	{
		ArrayPtrOfShape3D *shapes = _GetObjectShapes();
		if (shapes != NULL)
		{
			bool beginFirstColor = true;
			for (ulong3 latIter = 0 ; latIter < fCoordsCountPerCircle/2 ; ++latIter)
			{
				bool useFirstColor = beginFirstColor;
				for (ulong3 longIter = 0 ; longIter < fCoordsCountPerCircle ; ++longIter)
				{
					Shape3D *shape = (*shapes)[longIter + latIter*fCoordsCountPerCircle];
					if (shape != NULL)
					{
						shape->SetColor( (useFirstColor) ? inFirstColor : inSecondColor);
						useFirstColor = !useFirstColor;
					}
				}
				beginFirstColor = !beginFirstColor;
			}
		}
	}
	else
	{
		Object3D_behaviour::SetColor( inPattern, inFirstColor, inSecondColor);
	}
}


Object3D* ObjSpheric3D::CreateSphere( real3 inDiameter, EPrecision inPrecision)
{
	ObjSpheric3D *sphere = _Instantiate();
	if (sphere != NULL)
	{
		sphere->_CreateSphere( inDiameter, inPrecision);
		return sphere->_GetObject();
	}

	return NULL;
}


Object3D* ObjSpheric3D::CreateSpintop( real3 inDiameter, EPrecision inPrecision)
{
	ObjSpheric3D *spintop = _Instantiate();
	if (spintop != NULL)
	{
		spintop->_CreateSpintop( inDiameter, inPrecision);
		return spintop->_GetObject();
	}

	return NULL;
}


ObjSpheric3D* ObjSpheric3D::_Instantiate()
{
	ObjSpheric3D *sphere = new ObjSpheric3D();
	if (sphere != NULL)
	{
		Object3D *obj = new Object3D( sphere);
		if (obj != NULL)
		{
			sphere->_SetObject( obj);
		}
		else
		{
			delete sphere;
		}
	}

	return sphere;
}


void ObjSpheric3D::_BuildSphere( const ArrayOfCoord3D& inSideCoords)
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	ArrayPtrOfShape3D *shapes = _GetObjectShapes();

	if (coords != NULL && shapes != NULL)
	{
		coords->push_back( Coord3D( 0, 0, 0));	// center

		coords->push_back( inSideCoords.front());	// base coords

		std::vector<ArrayOfIndex> indexes;
		for (ulong3 pos = 1 ; pos <= inSideCoords.size() - 2 ; ++pos)
		{
			ArrayOfCoord3D circleCoords;
			Math::GetCoordsForCirclePerpendicularToYAxis( circleCoords, inSideCoords[pos].GetZ(), fCoordsCountPerCircle, eBaseXoZ);
			Math::TranslateBy( circleCoords, 0, inSideCoords[pos].GetY(), 0);
			
			coords->push_back( Coord3D( 0, inSideCoords[pos].GetY(), 0));	// circle center
			coords->insert( coords->end(), circleCoords.begin(), circleCoords.end()); //	circle coords
			
			ArrayOfIndex circleIndexes;
			FillIndexesArray( circleIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
			circleIndexes.push_back(circleIndexes.front());
			indexes.push_back(circleIndexes);
		}

		coords->push_back( inSideCoords.back());	// apex coords

		// append the bottom triangular shapes
		for (ulong3 pos = 0 ; pos < indexes[0].size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[indexes[0][pos+1]],(*coords)[indexes[0][pos]]),
															Vector3D( (*coords)[indexes[0][pos+1]],(*coords)[1]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateTriangle( 1, indexes[0][pos+1], indexes[0][pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}

		// append the side rectangular shapes
		for (ulong3 indexesPos = 0 ; indexesPos < indexes.size() - 1 ; ++indexesPos)
		{
			for (ulong3 pos = 0 ; pos < indexes[indexesPos].size() - 1 ; ++pos)
			{
				Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[indexes[indexesPos][pos+1]],(*coords)[indexes[indexesPos+1][pos+1]]),
																Vector3D( (*coords)[indexes[indexesPos][pos+1]],(*coords)[indexes[indexesPos][pos]]),
																false);
				normal.Normalize();
				Shape3D *shape = Shape3D::CreateRect( indexes[indexesPos+1][pos], indexes[indexesPos+1][pos+1], indexes[indexesPos][pos+1], indexes[indexesPos][pos], &normal);
				if (shape != NULL)
				{
					shapes->push_back( shape);
				}
			}
		}


		// append the top triangular shapes
		ulong3 apexIndex = coords->size() - 1;
		for (ulong3 pos = 0 ; pos < indexes.back().size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[indexes.back()[pos+1]],(*coords)[apexIndex]),
															Vector3D( (*coords)[indexes.back()[pos+1]],(*coords)[indexes.back()[pos]]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateTriangle( apexIndex, indexes.back()[pos+1], indexes.back()[pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}
	}
}


void ObjSpheric3D::_CreateSphere( real3 inDiameter, EPrecision inPrecision)
{
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D arcCoords;
	Math::GetCoordsForArcPerpendicularToXAxis( arcCoords, -kPI/2, kPI/2, inDiameter / 2, fCoordsCountPerCircle/2 + 1, eBaseZoY);

	_BuildSphere( arcCoords);
}


void ObjSpheric3D::_CreateSpintop( real3 inDiameter, EPrecision inPrecision)
{
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D astroidCoords, circleCoords;

	Math::GetCoordsForArcPerpendicularToXAxis( circleCoords, -kPI/2, kPI/2, inDiameter / 2, fCoordsCountPerCircle/2 + 1, eBaseZoY);
	Math::GetCoordsForAstroidArcPerpendicularToXAxis( astroidCoords, -kPI/2, kPI/2, inDiameter / 2, fCoordsCountPerCircle/2 + 1, eBaseZoY);

	real3 astroidPercent = 0.75, circlePercent = 0.25;
	for (ulong3 pos = 0 ; pos < circleCoords.size() ; ++pos)
	{
		circleCoords[pos].SetX( astroidCoords[pos].GetX()*astroidPercent + circleCoords[pos].GetX()*circlePercent);
		circleCoords[pos].SetY( astroidCoords[pos].GetY()*astroidPercent + circleCoords[pos].GetY()*circlePercent);
		circleCoords[pos].SetZ( astroidCoords[pos].GetZ()*astroidPercent + circleCoords[pos].GetZ()*circlePercent);
	}

	_BuildSphere( circleCoords);
}



// ============================================================================



ObjToric3D::ObjToric3D()
: fCoordsCountPerCircle(0)
{
}


ObjToric3D::~ObjToric3D()
{
}


void ObjToric3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


Object3D* ObjToric3D::CreateTorePerpendicularToYAxis( real3 inInternalDiameter, real3 inExternalDiameter, EPrecision inPrecision)
{
	Object3D *obj = NULL;

	ObjToric3D *tore = new ObjToric3D();
	if (tore != NULL)
	{
		obj = new Object3D( tore);
		if (obj != NULL)
		{
			tore->_SetObject( obj);
			tore->_CreateTorePerpendicularToYAxis( inInternalDiameter, inExternalDiameter, inPrecision);
		}
		else
		{
			delete tore;
		}
	}

	return obj;
}


void ObjToric3D::_CreateTorePerpendicularToYAxis( real3 inInternalDiameter, real3 inExternalDiameter, EPrecision inPrecision)
{
	fCoordsCountPerCircle = Modeler3D::GetCoordsCountPerCircle( inPrecision);

	ArrayOfCoord3D *coords = _GetObjectCoords();
	ArrayPtrOfShape3D *shapes = _GetObjectShapes();

	if (coords != NULL && shapes != NULL)
	{
		coords->push_back( Coord3D( 0, 0, 0));	// center

		// build temporary circle
		ArrayOfCoord3D internalCircleCoords, temporaryCircleCoords;
		std::vector<ArrayOfIndex> temporaryCircleIndexes;
		ArrayOfVector3D normalVectors;

		real3 internalCircleDiameter = inInternalDiameter + ((inExternalDiameter - inInternalDiameter) / 2);
		real3 temporaryCircleDiameter = inExternalDiameter - inInternalDiameter;

		Math::GetCoordsForCirclePerpendicularToYAxis( internalCircleCoords, internalCircleDiameter / 2, fCoordsCountPerCircle, eBaseXoZ);

		real3 alpha = 0, delta = (kPI * 2) / fCoordsCountPerCircle;
		for (ArrayOfCoord3D_iter coordsIter = internalCircleCoords.begin() ; coordsIter != internalCircleCoords.end() ; ++coordsIter)
		{
			Math::GetCoordsForCirclePerpendicularToZAxis( temporaryCircleCoords, temporaryCircleDiameter / 2, fCoordsCountPerCircle, eBaseXoY);
			
			PolarCoord polarCoord;
			Math::GetPolarCoordsFromYAxis( *coordsIter, polarCoord, eBaseXoZ);
			Math::RotateBy( temporaryCircleCoords, 0, polarCoord.fArgument, 0, World3D::sRootWorld3D.IsDirect());
			Math::SetPosBy( temporaryCircleCoords, (*coordsIter).GetX(), (*coordsIter).GetY(), (*coordsIter).GetZ());

			coords->push_back( *coordsIter);	// circle center
			coords->insert( coords->end(), temporaryCircleCoords.begin(), temporaryCircleCoords.end()); //	circle coords
			
			ArrayOfIndex circleIndexes;
			FillIndexesArray( circleIndexes, coords->size() - fCoordsCountPerCircle, fCoordsCountPerCircle);
			circleIndexes.push_back(circleIndexes.front());
			temporaryCircleIndexes.push_back(circleIndexes);
		}

		temporaryCircleIndexes.push_back( temporaryCircleIndexes.front());

		for (std::vector<ArrayOfIndex>::iterator circleIter = temporaryCircleIndexes.begin() ; circleIter != temporaryCircleIndexes.end() - 1 ; ++circleIter)
		{
			for (ulong3 pos = 0 ; pos < (*circleIter).size() - 1 ; ++pos)
			{
				Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[(*circleIter)[pos+1]],(*coords)[(*(circleIter+1))[pos+1]]),
																Vector3D( (*coords)[(*circleIter)[pos+1]],(*coords)[(*circleIter)[pos]]),
																false);
				normal.Normalize();
				Shape3D *shape = Shape3D::CreateRect( (*(circleIter+1))[pos], (*(circleIter+1))[pos+1], (*circleIter)[pos+1], (*circleIter)[pos], &normal);
				if (shape != NULL)
				{
					shapes->push_back( shape);
				}
			}
		}
	}
}



// ============================================================================



ObjPyramidal3D::ObjPyramidal3D()
{
}


ObjPyramidal3D::~ObjPyramidal3D()
{
}


void ObjPyramidal3D::GetCenter( Coord3D& outCenter) const
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	if (coords != NULL)
	{
		outCenter = (*coords)[0];
	}
}


Object3D* ObjPyramidal3D::CreateTriangularPyramidPerpendicularToYAxis( real3 inSize)
{
	Object3D *obj = NULL;

	ObjPyramidal3D *pyramid = new ObjPyramidal3D();
	if (pyramid != NULL)
	{
		obj = new Object3D( pyramid);
		if (obj != NULL)
		{
			pyramid->_SetObject( obj);
			pyramid->_CreateTriangularPyramidPerpendicularToYAxis( inSize);
		}
		else
		{
			delete pyramid;
		}
	}

	return obj;
}


void ObjPyramidal3D::_CreateTriangularPyramidPerpendicularToYAxis( real3 inSize)
{
	ArrayOfCoord3D *coords = _GetObjectCoords();
	ArrayPtrOfShape3D *shapes = _GetObjectShapes();

	if (coords != NULL && shapes != NULL)
	{
		coords->push_back( Coord3D( 0, 0, 0));	// center

		// inSize = longueur d'une arrete
		// calcul du rayon du cercle circonscrit
		real3 radius = inSize * sqrt((real3)3) / 3;
		
		Coord3D coord( 0, 0, radius);
		coords->push_back( coord);

		Math::RotateBy( coord, 0, 2*kPI/3, 0);
		coords->push_back( coord);

		coord.SetCoordsTo( 0, 0, radius);
		Math::RotateBy( coord, 0, 4*kPI/3, 0);
		coords->push_back( coord);

		// calcul de la hauteur
		real3 height = inSize*sqrt((real3)2/(real3)3);
		
		coords->push_back( Coord3D( 0, height, 0)); // apex

		// append the bottom shape
		Shape3D *shape = Shape3D::CreateTriangle( 1, 2, 3, &Vector3D( 0, -1, 0));
		if (shape != NULL)
			shapes->push_back( shape);

		// append the side shapes
		ArrayOfIndex indexes;
		FillIndexesArray( indexes, 1, 3);
		indexes.push_back( indexes.front());
		
		ulong3 apexIndex = 4;
		for (size_t pos = 0 ; pos < indexes.size() - 1 ; ++pos)
		{
			Vector3D normal = Vector3D::CalcCrossProduct(	Vector3D( (*coords)[indexes[pos+1]],(*coords)[apexIndex]),
															Vector3D( (*coords)[indexes[pos+1]],(*coords)[indexes[pos]]),
															false);
			normal.Normalize();
			Shape3D *shape = Shape3D::CreateTriangle( apexIndex, indexes[pos+1], indexes[pos], &normal);
			if (shape != NULL)
			{
				shapes->push_back( shape);
			}
		}

		// center the pyramid on its gravity center
		Coord3D gravityCenter;
		ArrayOfCoord3D pyramidCoords;
		pyramidCoords.insert( pyramidCoords.end(), coords->begin()+1, coords->end());

		if (Math::GetBarycentre( pyramidCoords, gravityCenter))
		{
			for (ArrayOfCoord3D_iter coordIter = coords->begin()+1 ; coordIter != coords->end() ; ++coordIter)
				(*coordIter).SetCoordsBy( 0, -gravityCenter.GetY(), 0);
		}
	}
}



// ============================================================================

} // namespace KHEOPS