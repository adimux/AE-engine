#ifndef AE_BASIC_CLASSES
#define AE_BASIC_CLASSES

#include <iostream>
#include <sstream>
#include <limits>
#include <vector>
#include <fstream>
#include "incLib.h"
#include "AETypes.h"
#include "AELogger.h"
#include "AELoggerFile.h"
#include "AEDll.h"
#include "Vector2D.h"

void lire_matrice(std::vector <std::vector<char> > matrice);

namespace AE
{
	template<class T>
	class Rect : public Vector2D<T>
	{
		public:
			Rect() : x(0), y(0), w(0), h(0)
			{
			}
			
			Rect(T _x, T _y, T _w=0, T _h=0) : x(_x), y(_y), w(_w), h(_h)
			{
			}
			
			template<class S>
			Rect(const Rect<S> &a_copier) : x( (T)a_copier.x ), y( (T)a_copier.y ), w( (T)a_copier.w ), h( (T)a_copier.h )
			{
			}
			
			template<class S>
			Rect(const Vector2D<S> &a_copier) : x( (T)a_copier.x ), y( (T)a_copier.y ), w(0), h(0)
			{
			}
			
			Rect(const SDL_Rect &rect) : x(rect.x), y(rect.y), w(rect.w), h(rect.h)
			{
			}
			
			template<class S>
			void operator=(Rect<S> &a_copier)
			{
				x = (T)a_copier.x;
				y = (T)a_copier.y;
				w = (T)a_copier.w;
				h = (T)a_copier.h;
			}
			
			void operator=(SDL_Rect &a_copier)
			{
				x = a_copier.x;
				y = a_copier.y;
				w = a_copier.w;
				h = a_copier.h;
			}
			
			template<class S>
			Rect operator+(Rect<S> &a_ajouter)
			{
				Rect to_return;
				to_return = *this;
		
				to_return.x += (T)a_ajouter.x;
				to_return.y += (T)a_ajouter.y;
				to_return.w += (T)a_ajouter.w;
				to_return.h += (T)a_ajouter.h;
		
				return to_return;	
			}
			
			template<class S>
			bool operator==(Rect<S> &compare)
			{
				if(x == compare.x && y == compare.y && w == compare.w && h == compare.h)
					return true;
				else
					return false;
			}
			
			template<class S>
			bool operator!=(Rect<S> &compare)
			{
				if(x == compare.x && y == compare.y && w == compare.w && h == compare.h)
					return false;
				else
					return true;
			}
			
			
			Rect operator+(SDL_Rect &a_ajouter)
			{
				Rect to_return;
				to_return = *this;
	
				to_return.x += a_ajouter.x;
				to_return.y += a_ajouter.y;
				to_return.w += a_ajouter.w;
				to_return.h += a_ajouter.h;
	
				return to_return;	
			}
			
			template<class S>
			Rect operator-(Rect<S> &rect)
			{
				Rect to_return;	
				to_return = *this;
				
				to_return.x -= rect.x;
				to_return.y -= rect.y;
				to_return.w -= rect.w;
				to_return.h -= rect.h;
			}
			
			template<class S>
			void operator-=(Rect<S> &rect)
			{
				x -= rect.x;
				y -= rect.y;
				w -= rect.w;
				h -= rect.h;
			}
			
			void afficher()
			{
				Logger::Log() << "Rect - x : " << x << " ; y : " << y << " ; w : " << w << " ; h : " << h << Logger::endline;
			}

			bool zero()
			{
				if(x == 0 && y == 0 && w == 0 && h == 0)
	    			return true;
	    
				return false;	
			}
		
			T w, h;
			T x, y;
	};

	class RGB
	{
		public:
			RGB(int=0, int=0, int=0);

			Uint32 toMapRGB(SDL_PixelFormat *format);
		
			bool operator==(RGB color);
			bool operator!=(RGB color);
		
			int moyenne();
	
			int r, g, b;
	};

	SDL_Surface * LoadImage(std::string chemin_image);
	SDL_Surface * RGB_Surface(Rect<int> dimensions, int depth=32, Uint32 Gmask=0, Uint32 Rmask=0, Uint32 Bmask=0, Uint32 Amask=0);
	SDL_Surface * copySurface(SDL_Surface *);
	
	bool FreeSurface(SDL_Surface *to_free);
	bool RotoZoomSurface(SDL_Surface *src, SDL_Surface *dest, double angle, double zoomx, double zoomy, bool anti_aliasing=false);
	bool ApplySurface(SDL_Surface *source, SDL_Surface *dest, Rect<int> source_rect=Rect<int>(), Rect<int> dest_rect=Rect<int>() );
	bool FillSurface(SDL_Surface *to_fill, RGB=RGB(255, 255, 255), Rect<int> to_fill_rect=Rect<int>() );
	bool SetColorKey( SDL_Surface *, RGB transparent_color );
	bool SaveBMP(SDL_Surface *, std::string chemin);

	Uint32 getPixel(SDL_Surface *surface, Vector2D<int> position);
	void setPixel(SDL_Surface *surface, Vector2D<int> position, Uint32 pixel);

	class Pixel
	{
		public:
			Pixel();
			Pixel(const Pixel &to_copy);
			Pixel(Uint32 pixel, SDL_PixelFormat &format);
			Pixel(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_PixelFormat &format);
		
			Uint32 getPixel();
			void getPixelInfo(Uint8 *r, Uint8 *g, Uint8 *b, Uint8 *a);
		
			void setPixelInfo(Uint8 r, Uint8 g, Uint8 b, Uint8 a, SDL_PixelFormat &format);
			void setPixel(Uint32 pixel);
		
			void setR(Uint8 R);
			void setG(Uint8 G);
			void setB(Uint8 B);
			void setA(Uint8 A);

			Uint8 getR();
			Uint8 getG();
			Uint8 getB();
			Uint8 getA();

		protected:
			Uint32 m_pixel;
			SDL_PixelFormat m_format;
	};
	
	class Surface
	{
		public:
			Surface();
			Surface(const Surface &);
			Surface(const SDL_Surface *);
			Surface(const std::string);
			Surface(Rect<int> dimensions, int depth=32, Uint32 Gmask=0, Uint32 Rmask=0, Uint32 Bmask=0, Uint32 Amask=0);
			~Surface();
			
			SDL_Surface *getSurface(); // Il est fortement déconseillé d'utiliser cette fonction
	
			bool rgb_surface(Rect<int> dimensions, int depth=32, Uint32 Gmask=0, Uint32 Rmask=0, Uint32 Bmask=0, Uint32 Amask=0);
			bool load(std::string);
			bool apply(Surface, Rect<int> = Rect<int>(), Rect<int> = Rect<int>() ) const;
			bool fill(RGB=RGB(255, 255, 255), Rect<int> = Rect<int>() );
			bool setColorKey(RGB transparent_color );
			bool saveBMP(std::string chemin);
			bool flip() const; // const (à la fin de la déclaration de la fonction) Veut dire que cette fonction ne change pas les variables de la classe

			bool lock();
			bool unlock();

			void setPixel(Vector2D<int> position, Pixel &pixel);
			Pixel getPixel(Vector2D<int> position);
		
			void setPixelColor(Vector2D<int> position, RGB color);
			RGB getPixelColor(Vector2D<int> position);
			Uint8 getPixelOneComposant(Vector2D<int> position, char color_number);

			bool free(); // Fait un free de la surface
			
			void *pixels();
			int pitch();

			int width() const;
			int height() const;
			int BitsPerPixel() const;
			SDL_PixelFormat PixelFormat() const;
			SDL_PixelFormat *PixelFormatAddr() const;

			void copySurface(Surface);
			void copySurface(SDL_Surface *);
			bool is_null() const;
		
			bool operator=(Surface); // Ne copie pas la surface mais le pointeur de surface, attention aux confusions
			bool operator=(SDL_Surface *); // IDEM :D

			operator bool();
			bool operator==(bool) const;
			bool operator!=(bool) const;

		protected:
			SDL_Surface *m_surface; // Le pointeur de SDL_Surface
			std::string m_path; // Si c'est une image loadée d'un fichier, le path n'est pas vide
	};

	struct SurfaceDeleter
	{
		void operator()(Surface *&surf);
	};
	
	typedef boost::shared_ptr<Surface> SurfacePtr;
	
	//char **explode(char *str, char separator, int *number_exploded);
	int string_to_int(std::string nombre_str);

	void aller_a_ligne(std::ifstream &fichier, int num_ligne);
}

class MapPos
{
	public:
		MapPos( int L=0, int l=0, int rL=0, int rl=0, float plus_x=0, float plus_y=0);
		MapPos(const MapPos &a_copier);
		MapPos(int L, int l, const AE::Rect<float> a_copier);
		
		void add(float, float);

		void operator=(MapPos a_copier);
		void operator=(AE::Rect<float> a_copier);
		void operator+=(AE::Rect<float> a_ajouter);
		MapPos operator+(AE::Rect<float> a_ajouter);
		
		SDL_Rect* to_SDL_Rect();
		AE::Rect<float> to_Rect();
		int getPlusX();
		int getPlusY();
		
		int m_L, m_l;
		int m_rL, m_rl;
		float m_plus_percent_x, m_plus_percent_y;
};

#endif
