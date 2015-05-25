#ifndef AE_VECTOR2D_CLASS
#define AE_VECTOR2D_CLASS

#include <iostream>
#include <cmath>
#include "AETypes.h"

namespace AE
{
	template<class T>
	class Vector2D
	{
		public:
			Vector2D(T _x = (T)0, T _y = (T)0) : x(_x), y(_y)
			{
			}

			template<class Y>
			Vector2D(Vector2D<Y> &to_copy) : x(to_copy.x), y(to_copy.y)
			{
			}
		
			~Vector2D()
			{
			}
			
			template<class Y>
			Decimal ScalarProd(Vector2D<Y> &vect)
			{
				return x * vect.x + y * vect.y;
			}
			
/*			template<class Y>
			Decimal operator.(Vector2D<Y> &vect) // Produit scalaire aussi
			{
				return x * vect.x + y * vect.y;
			}*/
			
/*			template<class Y>
			Vector2D VectorialProd(Vector2D<Y> &vect)
			{
				return Vector2D(x, );
			}*/
			
			template<class Y>
			Decimal Distance(Vector2D<Y> &B)
			{
				return sqrt( (x - B.x) * (x - B.x)+(y - B.y) * (y - B.y) );
			}
			
			Decimal Distance()
			{
				return sqrt( x*x + y*y );	
			}
			
			template<class Y>
			Vector2D InSameLine(Vector2D<Y> &C, Decimal distance, bool relative_distance=true) // Cette fonction trouve le point B appartennant à la droite
			// (AC) (A est cette coordonnée - cet objet -, et C est celui dans les arguments de la fonction)
			{
				Vector2D B; // Le vecteur qu'on recherche est B qui appartient à la droite AC
				
				Decimal AC = Distance(C);
			
				if(AC == 0) // Si la distance est 0 donc les deux points sont les mêmes...
					return C; // ...et par conséquent on renvoie l'un deux
					
				if(relative_distance)
				{
					B.x = (Decimal)(C.x - x) * distance + x;
					B.y = (Decimal)(C.y - y) * distance + y;
				}
				else
				{
					B.x = (Decimal)(C.x - x) * (distance/AC) + x;
					B.y = (Decimal)(C.y - y) * (distance/AC) + y;	
				}
			
				return B;
			}
		
			void Normalize()
			{
				Decimal longueur_vector = sqrt( x*x + y*y );
			
				x /= longueur_vector;
				y /= longueur_vector;
			}
			
			template<class Y>
			void operator=(Vector2D<Y> &to_copy)
			{
				x = to_copy.x;
				y = to_copy.y;
			}
			
			template<class Y>
			Vector2D operator+(Vector2D<Y> &vector)
			{
				Vector2D resultat(x+vector.x, y+vector.y);
			}
			
			template<class Y>
			Vector2D operator-(Vector2D<Y> &vector)
			{
				Vector2D resultat(x-vector.x, y-vector.y);
			}
			
			template<class Y>
			void operator-=(Vector2D<Y> &vector)
			{
				x -= vector.x;
				y -= vector.y;
			}
			
			template<class Y>
			void operator+=(Vector2D<Y> &vector)
			{
				x += vector.x;
				y += vector.y;
			}
			
			Vector2D operator/(T nbr)
			{
				return Vector2D(x/nbr, y/nbr);
			}
		
			Vector2D operator*(T nbr)
			{
				return Vector2D(x*nbr, y*nbr);
			}
		
			void operator/=(T nbr)
			{
				x /= nbr;
				y /= nbr;
			}
		
			void operator*=(T nbr)
			{
				x *= nbr;
				y *= nbr;
			}
			
			template<class Y>
			bool operator==(Vector2D<Y> &vect)
			{
				return (vect.x == x && vect.y == y);
			}
			
			template<class Y>
			bool operator!=(Vector2D<Y> &vect)
			{
				return (vect.x != x || vect.y != y);
			}
			
			/*template<class V>
			Vector2D<V> operator V ()
			{
				return Vector2D<V>(x, y);
			}*/
	
			T x;
			T y;
	};
}

#endif
