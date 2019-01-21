// 08/02/2008

#include "core3.h"
#include <assert.h>
#include <algorithm>
#include "shapes3.h"



namespace KHEOPS
{



// ============================================================================



Segment Segment::sNullSegment;


bool Segment::operator<( const Segment& inSource) const
{
    if (fFrom < inSource.fFrom)
        return true;
    else if (fFrom > inSource.fFrom)
        return false;
    else
        return (fTo < inSource.fTo);
}


bool Segment::operator==(const Segment& inSource) const
{
    return ((fFrom == inSource.fFrom) && (fTo == inSource.fTo));
}


Segment& Segment::operator=( const Segment& inSource)
{
    fFrom = inSource.fFrom;
    fTo = inSource.fTo;
    return *this;
}




Shape3DLightInfo::Shape3DLightInfo()
{
}


Shape3DLightInfo::Shape3DLightInfo( const Shape3DLightInfo& inInfo)
{
	fNormalVector = inInfo.fNormalVector;
	fLightness = inInfo.fLightness;
}


Shape3DLightInfo::~Shape3DLightInfo()
{
}


void Shape3DLightInfo::SetLightness( const real3& inLightness)
{
	fLightness = inLightness;
}


const real3& Shape3DLightInfo::GetLightness() const
{
	return fLightness;
}


void Shape3DLightInfo::SetNormalVector( const Vector3D& inNormalVector)
{
	fNormalVector = inNormalVector;
}


const Vector3D& Shape3DLightInfo::GetNormalVector() const
{
	return fNormalVector;
}


Shape3DLightInfo& Shape3DLightInfo::operator=( const Shape3DLightInfo& inInfo)
{
	fNormalVector = inInfo.fNormalVector;
	fLightness = inInfo.fLightness;
	return *this;
}




Shape3DCameraInfo::Shape3DCameraInfo()
: fVisible(false)
{
}


Shape3DCameraInfo::Shape3DCameraInfo( const Shape3DCameraInfo& inInfo)
{
	fNormalVector = inInfo.fNormalVector;
	fVisible = inInfo.fVisible;
}


Shape3DCameraInfo::~Shape3DCameraInfo()
{
}


void Shape3DCameraInfo::SetVisible( const bool& inVisible)
{
	fVisible = inVisible;
}


const bool& Shape3DCameraInfo::IsVisible()  const
{
	return fVisible;
}


void Shape3DCameraInfo::SetNormalVector( const Vector3D& inNormalVector)
{
	fNormalVector = inNormalVector;
}


const Vector3D& Shape3DCameraInfo::GetNormalVector() const
{
	return fNormalVector;
}


Shape3DCameraInfo& Shape3DCameraInfo::operator=( const Shape3DCameraInfo& inInfo)
{
	fNormalVector = inInfo.fNormalVector;
	fVisible = inInfo.fVisible;
	return *this;
}



// ============================================================================
// 3d shapes classes definition



Shape3D::Shape3D()
{
    fVisible = true;
    fColor = NULL;
}


Shape3D::Shape3D( const ArrayOfIndex& inIndexes)
{
    fVisible = true;
    fColor = NULL;
	fIndexes.insert( fIndexes.end(), inIndexes.begin(), inIndexes.end());
}


Shape3D::~Shape3D()
{
    fIndexes.clear();
    delete fColor;
    fColor = NULL;
}


void Shape3D::SetColor( const Color& inColor)
{
    if (fColor == NULL)
        fColor = new Color();

    fColor->Set( inColor.GetRed(), inColor.GetGreen(), inColor.GetBlue(), inColor.GetAlpha());
}


void Shape3D::GetSegments( ArrayOfSegment& outSegments) const
{
    size_t count = fIndexes.size();
	std::vector<size_t> toIndexes;
    toIndexes.resize( count, 0);

    // fIndexes contains From coord indexes, build To coord indexes array
    for( size_t pos = 0 ; pos < count ; ++pos )
    {
        toIndexes[pos] = fIndexes[pos];
    }
    std::rotate( toIndexes.begin(), toIndexes.begin()+1, toIndexes.end());

    // build the segment array
    outSegments.resize( count);
    for( size_t pos = 0 ; pos < count ; ++pos )
    {
        outSegments[pos].SetIndexes( fIndexes[pos], toIndexes[pos]);
    }
}


void Shape3D::SetNormalVector( const Vector3D&  inNormalVector)
{
	fNormalVector = inNormalVector;
}


const Vector3D& Shape3D::GetNormalVector() const
{
	return fNormalVector;
}


void Shape3D::SetNormalVectorByCamera( const Camera& inCamera, const Vector3D&  inNormalVector)
{
	MapOfCameraInfo_iter found = fCameraInfos.find( inCamera.GetID());
	if (found != fCameraInfos.end())
	{
		found->second.SetNormalVector( inNormalVector);
	}
	else
	{
		Shape3DCameraInfo info;
		info.SetNormalVector( inNormalVector);
		fCameraInfos[inCamera.GetID()] = info;
	}
}


bool Shape3D::GetNormalVectorByCamera( const Camera& inCamera, Vector3D& outNormalVector) const
{
	MapOfCameraInfo_citer found = fCameraInfos.find( inCamera.GetID());
	if (found != fCameraInfos.end())
	{
		outNormalVector = found->second.GetNormalVector();
		return true;
	}
	return false;
}


void Shape3D::SetVisibleByCamera( const Camera& inCamera, bool inVisible)
{
	MapOfCameraInfo_iter found = fCameraInfos.find( inCamera.GetID());
	if (found != fCameraInfos.end())
	{
		found->second.SetVisible( inVisible);
	}
	else
	{
		Shape3DCameraInfo info;
		info.SetVisible( inVisible);
		fCameraInfos[inCamera.GetID()] = info;
	}
}


bool Shape3D::IsVisibleByCamera( const Camera& inCamera) const
{
	if (!fVisible)
		return false;

	MapOfCameraInfo_citer found = fCameraInfos.find( inCamera.GetID());
	if (found != fCameraInfos.end())
	{
		return found->second.IsVisible();
	}
	return true;
}


void Shape3D::SetNormalVectorByLight( const Light& inLight, const Vector3D&  inNormalVector)
{
	MapOfLightInfo_iter found = fLightInfos.find( inLight.GetID());
	if (found != fLightInfos.end())
	{
		found->second.SetNormalVector( inNormalVector);
	}
	else
	{
		Shape3DLightInfo info;
		info.SetNormalVector( inNormalVector);
		fLightInfos[inLight.GetID()] = info;
	}
}


bool Shape3D::GetNormalVectorByLight( const Light& inLight, Vector3D& outNormalVector) const
{
	MapOfLightInfo_citer found = fLightInfos.find( inLight.GetID());
	if (found != fLightInfos.end())
	{
		outNormalVector = found->second.GetNormalVector();
		return true;
	}
	return false;
}


void Shape3D::SetLightnessByLight( const Light& inLight, real3 inLightness)
{
	MapOfLightInfo_iter found = fLightInfos.find( inLight.GetID());
	if (found != fLightInfos.end())
	{
		found->second.SetLightness( inLightness);
	}
	else
	{
		Shape3DLightInfo info;
		info.SetLightness( inLightness);
		fLightInfos[inLight.GetID()] = info;
	}
}


bool Shape3D::GetLightnessByLight( const Light& inLight, real3& outLightness) const
{
	MapOfLightInfo_citer found = fLightInfos.find( inLight.GetID());
	if (found != fLightInfos.end())
	{
		outLightness = found->second.GetLightness();
		return true;
	}
	return false;
}


bool Shape3D::GetNormalVector( const ArrayOfCoord3D& inCoords, Vector3D& outVector) const
{
	bool ok = false;

    if (fIndexes.size() >= 3)
    {
        size_t id0 = fIndexes[0], id1 = fIndexes[1], id2 = fIndexes[2];
        if ((id0 < inCoords.size()) && (id1 < inCoords.size()) && (id0 < inCoords.size()))
		{
            Vector3D vp0( inCoords[id0].GetX(), inCoords[id0].GetY(), inCoords[id0].GetZ());
            Vector3D vp1( inCoords[id1].GetX(), inCoords[id1].GetY(), inCoords[id1].GetZ());
            Vector3D vp2( inCoords[id2].GetX(), inCoords[id2].GetY(), inCoords[id2].GetZ());

            outVector =  (vp2 - vp1) ^ (vp0 - vp1);     // produit vectoriel

			ok = true;
        }
    }
    return ok;
}


const Vector3D Shape3D::GetNormalVector( const ArrayPtrOfCoord3D& inCoords) const
{
    Vector3D result;

    if (fIndexes.size() >= 3)
    {
        size_t id0 = fIndexes[0], id1 = fIndexes[1], id2 = fIndexes[2];
        bool ok = (id0 < inCoords.size()) && (id1 < inCoords.size()) && (id0 < inCoords.size());
        if (ok)
            ok = (inCoords[id0] != NULL) && (inCoords[id1] != NULL) && (inCoords[id2] != NULL);

        if (ok)
        {
            Vector3D vp0( inCoords[id0]->GetX(), inCoords[id0]->GetY(), inCoords[id0]->GetZ());
            Vector3D vp1( inCoords[id1]->GetX(), inCoords[id1]->GetY(), inCoords[id1]->GetZ());
            Vector3D vp2( inCoords[id2]->GetX(), inCoords[id2]->GetY(), inCoords[id2]->GetZ());

            result =  (vp2 - vp1) ^ (vp0 - vp1);     // produit vectoriel
        }
        assert(ok);
    }
    return result;
}


bool Shape3D::GetGravityCenter( const ArrayOfCoord3D& inCoords, Coord3D& outCoord) const
{
    // le centre de gravite n'est autre que le barycentre du polygon dans lequel tous les poids valent 1
    bool result = false;

    if (fIndexes.size() >= 2)
    {
        size_t count = fIndexes.size(), total_count = 0;
        real3 total_x = 0, total_y = 0, total_z = 0;

        for( size_t pos = 0 ; pos < count ; ++pos )
        {
            if (fIndexes[pos] < inCoords.size())
            {
                total_x += inCoords[fIndexes[pos]].GetX();
                total_y += inCoords[fIndexes[pos]].GetY();
                total_z += inCoords[fIndexes[pos]].GetZ();
                ++total_count;
            }
        }
        assert(count == total_count);
        outCoord.SetX( total_x / total_count);
        outCoord.SetY( total_y / total_count);
        outCoord.SetZ( total_z / total_count);

		result = true;

    }
    return result;
}


const Coord3D Shape3D::GetGravityCenter( const ArrayPtrOfCoord3D& inCoords) const
{
    // le centre de gravite n'est autre que le barycentre du polygon dans lequel tous les poids valent 1
    Coord3D result;

    if (fIndexes.size() >= 2)
    {
        size_t count = fIndexes.size(), total_count = 0;
        real3 total_x = 0, total_y = 0, total_z = 0;

        for( size_t pos = 0 ; pos < count ; ++pos )
        {
            if (fIndexes[pos] < inCoords.size())
            {
                const Coord3D *coord = inCoords[fIndexes[pos]];
                if (coord != NULL)
                {
                    total_x += coord->GetX();
                    total_y += coord->GetY();
                    total_z += coord->GetZ();
                    ++total_count;
                }
            }
        }
        assert(count == total_count);
        result.SetX( total_x / total_count);
        result.SetY( total_y / total_count);
        result.SetZ( total_z / total_count);

    }
    return result;
}


Shape3D* Shape3D::Create( const ArrayOfIndex& inIndexes, Vector3D *inNormal)
{
	Shape3D *shape = new Shape3D( inIndexes);
	if  (shape != NULL)
	{
		if (inNormal != NULL)
			shape->fNormalVector = *inNormal;
	}
	return shape;
}


Shape3D* Shape3D::CreateTriangle( size_t inTop, size_t inLeft, size_t inRight, Vector3D *inNormal)
{
	Shape3D *shape = new Shape3D();
	if  (shape != NULL)
	{
		shape->fIndexes.push_back( inTop);
		shape->fIndexes.push_back( inLeft);
		shape->fIndexes.push_back( inRight);

		if (inNormal != NULL)
			shape->fNormalVector = *inNormal;
	}
	return shape;
}


Shape3D* Shape3D::CreateRect( size_t inTopRight, size_t inTopLeft, size_t inBottomLeft, size_t inBottomRight, Vector3D *inNormal)
{
	Shape3D *shape = new Shape3D();
	if  (shape != NULL)
	{
		shape->fIndexes.push_back( inTopRight);
		shape->fIndexes.push_back( inTopLeft);
		shape->fIndexes.push_back( inBottomLeft);
		shape->fIndexes.push_back( inBottomRight);

		if (inNormal != NULL)
			shape->fNormalVector = *inNormal;
	}
	return shape;
}


Shape3D* Shape3D::CreateCircle( size_t inFromCoord, ulong3 inCoordsCount, Vector3D *inNormal)
{
	Shape3D *shape = new Shape3D();
	if  (shape != NULL)
	{
		shape->fIndexes.resize( inCoordsCount, 0);
		for ( size_t pos = 0 ; pos < inCoordsCount ; ++pos)
		{
			shape->fIndexes[pos] = inFromCoord;
			++inFromCoord;
		}

		if (inNormal != NULL)
			shape->fNormalVector = *inNormal;
	}
	return shape;
}


bool Shape3D::GetRectangularShapes( const Shape3D& inFrom,  const Shape3D& inTo, ArrayPtrOfShape3D& outShapes)
{
    bool result = false;

	for (ArrayPtrOfShape3D_iter iter = outShapes.begin() ; iter != outShapes.end() ; ++iter)
	{
		delete *iter;
		*iter = NULL;
	}

    ArrayOfSegment s1_segs, s2_segs;
    inFrom.GetSegments( s1_segs);
    inTo.GetSegments( s2_segs);

    if (s1_segs.size() == s2_segs.size())
    {
        for ( size_t pos = 0 ; pos < s1_segs.size() ; ++pos )
        {
            outShapes.push_back( new Shape3D_rect( s1_segs[pos].GetTo(), s1_segs[pos].GetFrom(), s2_segs[pos].GetFrom(), s2_segs[pos].GetTo()));
        }
        result = true;
    }
    else
    {
        assert(false);
    }

    s1_segs.clear();
    s2_segs.clear();

    return result;
}


bool Shape3D::GetTriangulareShapes( size_t inFrom, const Shape3D& inTo, ArrayPtrOfShape3D& outShapes)
{
	for (ArrayPtrOfShape3D_iter iter = outShapes.begin() ; iter != outShapes.end() ; ++iter)
	{
		delete *iter;
		*iter = NULL;
	}

    ArrayOfSegment segments;
    inTo.GetSegments( segments);

    for ( size_t pos = 0 ; pos < segments.size() ; ++pos )
    {
        outShapes.push_back( new Shape3D_triangle( inFrom, segments[pos].GetFrom(), segments[pos].GetTo()));
    }

    segments.clear();

    return true;
}



// ============================================================================



Shape3D_triangle::Shape3D_triangle( size_t inTop, size_t inLeft, size_t inRight)
{
    fIndexes.push_back( inTop);
    fIndexes.push_back( inLeft);
    fIndexes.push_back( inRight);
}


Shape3D_triangle::~Shape3D_triangle()
{
}



// ============================================================================



Shape3D_rect::Shape3D_rect( size_t inTopRight, size_t inTopLeft, size_t inBottomLeft, size_t inBottomRight)
{
    fIndexes.push_back( inTopRight);
    fIndexes.push_back( inTopLeft);
    fIndexes.push_back( inBottomLeft);
    fIndexes.push_back( inBottomRight);
}


Shape3D_rect::~Shape3D_rect()
{
}



// ============================================================================



Shape3D_circle::Shape3D_circle( size_t inFromCoord, ulong3 inCoordsCount)
{
    fIndexes.resize( inCoordsCount, 0);
    for ( size_t pos = 0 ; pos < inCoordsCount ; ++pos)
    {
        fIndexes[pos] = inFromCoord;
        ++inFromCoord;
    }

}


Shape3D_circle::~Shape3D_circle()
{
}



} // namespace KHEOPS
