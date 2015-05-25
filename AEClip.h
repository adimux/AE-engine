#ifndef AE_CLIP_CLASS
#define AE_CLIP_CLASS

#include <iostream>
#include <vector>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "AEBasic.h"

namespace AE
{
	class Clip
	{
		public:
			Clip();
			Clip(const Clip &a_copier);
			Clip(Surface *img, ...);
			Clip(char *chemin_img, ...);
			Clip(std::string chemin_feuille_sprites, int largeur_sprite, int hauteur_sprite, RGB transparent_color=RGB(255, 0, 255) );
			~Clip();
		
			int get_nbr_sprites();
			bool empty();
		
			Surface to_feuille_sprites(Rect<int> = Rect<int>(), int depth=32);
		
			void operator=(Clip a_copier);
			bool operator<<(Surface to_add);
			bool operator<<(std::string to_add );

			Surface get(const int number);
			Surface operator[](const int number);
	
		protected:
			std::vector<Surface> m_clip; // Tableaux d'objets Surface des images du clip
	};
}

#endif
