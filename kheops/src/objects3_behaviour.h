


#ifndef __OBJECTS3_BEHAVIOUR__
#define __OBJECTS3_BEHAVIOUR__




namespace KHEOPS
{



class Object3D_behaviour
{
public:
	Object3D_behaviour();
	virtual ~Object3D_behaviour();

	virtual	void				GetCenter( Coord3D& outCenter) const = 0;
	virtual	void				SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor);

#if 0
	virtual	real3				GetWidth() const = 0;
	virtual	real3				GetHeight() const = 0;
	virtual	real3				GetDepth() const = 0;

	virtual	void				SetWidth( real3 inWidth) = 0;
	virtual	void				SetHeight( real3 inHeight) = 0;
	virtual	void				setDepth( real3 inDepth) = 0;
#endif

protected:
			void				_SetObject( Object3D *inObject);
			Object3D*			_GetObject() const;

			ArrayOfCoord3D*		_GetObjectCoords() const;
			ArrayPtrOfShape3D*	_GetObjectShapes() const;

private:
			Object3D			*fObject;
};



// ============================================================================



class ObjRect3D : public Object3D_behaviour
{
public:
	ObjRect3D();
	virtual ~ObjRect3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;
	virtual	void				SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor);

	static	Object3D*			CreateRect( real3 inWidth, ulong3 inWidthSegmentsCount, real3 inHeight, ulong3 inHeightSegmentsCount, EBase inBase);

private:
			ulong3				fCoordsCountPerWidth;
			ulong3				fCoordsCountPerHeight;
};



// ============================================================================



class ObjCubic3D : public Object3D_behaviour
{
public:
	ObjCubic3D();
	virtual ~ObjCubic3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;

	static	Object3D*			CreateCube( real3 inSize);
	static	Object3D*			CreateBox( real3 inWidth, real3 inHeight, real3 inDepth);
};



// ============================================================================



class ObjCylindric3D : public Object3D_behaviour
{
public:
	ObjCylindric3D();
	virtual ~ObjCylindric3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;

	static	Object3D*			CreateCylinderPerpendicularToYAxis( real3 inDiameter, real3 inMiddleDiameter, real3 inHeight, EPrecision inPrecision = eDefaultPrecision);
	static	Object3D*			CreateStraightCylinderPerpendicularToYAxis( real3 inBottomDiameter, real3 inTopDiameter, real3 inHeight, EPrecision inPrecision = eDefaultPrecision);
	static	Object3D*			CreateHollowedCenterStraightCylinderPerpendicularToYAxis( real3 inInternalBottomDiameter, real3 inExternalBottomDiameter, real3 inInternalTopDiameter, real3 inExternalTopDiameter, real3 inHeight, EPrecision inPrecision = eDefaultPrecision);

private:

	static	ObjCylindric3D*		_Instantiate();

			void				_BuildCylinderPerpendicularToYAxis( const ArrayOfCoord3D& inSideCoords);

			void				_CreateCylinderPerpendicularToYAxis( real3 inDiameter, real3 inMiddleDiameter, real3 inHeight, EPrecision inPrecision);
			void				_CreateStraightCylinderPerpendicularToYAxis( real3 inBottomDiameter, real3 inTopDiameter, real3 inHeight, EPrecision inPrecision);
			void				_CreateHollowedCenterStraightCylinderPerpendicularToYAxis( real3 inInternalBottomDiameter, real3 inExternalBottomDiameter, real3 inInternalTopDiameter, real3 inExternalTopDiameter, real3 inHeight, EPrecision inPrecision);
			
			real3				fThickness;
			ulong3				fCoordsCountPerCircle;
};



// ============================================================================



class ObjConic3D : public Object3D_behaviour
{
public:
	ObjConic3D();
	virtual ~ObjConic3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;

	static	Object3D*			CreateConePerpendicularToYAxis( real3 inBottomDiameter, real3 inHeight, EPrecision inPrecision = eDefaultPrecision);

private:
			void				_CreateConePerpendicularToYAxis( real3 inBottomDiameter, real3 inHeight, EPrecision inPrecision);

			real3				fHeight;
			ulong3				fCoordsCountPerCircle;
};



// ============================================================================



class ObjSpheric3D : public Object3D_behaviour
{
public:
	ObjSpheric3D();
	virtual ~ObjSpheric3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;
	virtual	void				SetColor( EColoringPattern inPattern, const Color& inFirstColor, const Color &inSecondColor);

	static	Object3D*			CreateSphere( real3 inDiameter, EPrecision inPrecision = eDefaultPrecision);
	static	Object3D*			CreateSpintop( real3 inDiameter, EPrecision inPrecision = eDefaultPrecision);

private:
	static	ObjSpheric3D*		_Instantiate();
			
			void				_BuildSphere( const ArrayOfCoord3D& inSideCoords);

			void				_CreateSphere( real3 inDiameter, EPrecision inPrecision);
			void				_CreateSpintop( real3 inDiameter, EPrecision inPrecision);

			ulong3				fCoordsCountPerCircle;
};



// ============================================================================



class ObjToric3D : public Object3D_behaviour
{
public:
	ObjToric3D();
	virtual ~ObjToric3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;

	static	Object3D*			CreateTorePerpendicularToYAxis( real3 inInternalDiameter, real3 inExternalDiameter, EPrecision inPrecision = eDefaultPrecision);

private:
			void				_CreateTorePerpendicularToYAxis( real3 inInternalDiameter, real3 inExternalDiameter, EPrecision inPrecision);

			ulong3				fCoordsCountPerCircle;
};



// ============================================================================



class ObjPyramidal3D : public Object3D_behaviour
{
public:
	ObjPyramidal3D();
	virtual ~ObjPyramidal3D();

	virtual	void				GetCenter( Coord3D& outCenter) const;

	static	Object3D*			CreateTriangularPyramidPerpendicularToYAxis( real3 inSize);

private:
			void				_CreateTriangularPyramidPerpendicularToYAxis( real3 inSize);
};



// ============================================================================



} // namespace KHEOPS


#endif