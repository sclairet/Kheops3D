
#ifndef __ENGINE3__
#define __ENGINE3__


namespace KHEOPS
{



class Modeler3D;


class Engine3D_delegate
{
public:
	virtual	void				GetScreenSize( slong3& outWidth, slong3& outHeight) = 0;
	virtual	void				GetCursorPosition( Coord2D& outPos) = 0;
	virtual	void				SetCursorPosition( const Coord2D& inPos) = 0;
	virtual	void				GetResourcesFolderPath( std::wstring& outPath) = 0;
};



class Engine3D
{
public:
			Engine3D( Engine3D_delegate *inDelegate);
	virtual ~Engine3D();

	static	Engine3D*			Get()	{ return sInstance; }
	static	bool				Init( Engine3D_delegate *inDelegate);
	static	void				DeInit();

			Engine3D_delegate*	GetDelegate() const;

			void				GetVirtualScreenSize( real3& outWidth, real3& outHeight) const;
			void				GetScreenSize( slong3& outWidth, slong3& outHeight) const;
			void				GetCursorPosition( Coord2D& outPos);
			void				SetCursorPosition( const Coord2D& inPos);
			void				GetResourcesFolderPath( std::wstring& outPath);

			Modeler3D*			GetModeler() const						{ return fModeler; }

private:
			void				_Test();

	static	Engine3D			*sInstance;
			Engine3D_delegate	*fDelegate;
			Modeler3D			*fModeler;
};



}


#endif