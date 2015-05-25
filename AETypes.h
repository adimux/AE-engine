#ifndef AE_TYPES_HEADER
#define AE_TYPES_HEADER

namespace AE
{
	typedef float Decimal;
	typedef int Integer;
	
	typedef unsigned short Type;

	template<class T>
	class Rect;
	template<class T>
	class Vector2D;
	
	// Typedefs pour le type Rect et Vector2D
	typedef Rect<int> IRect;
	typedef Rect<Decimal> DRect;
	typedef Vector2D<int> IVector2D;
	typedef Vector2D<Decimal> DVector2D;
}

#endif
