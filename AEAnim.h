#ifndef AE_ANIM_CLASS
#define AE_ANIM_CLASS

#include <iostream>
#include "incLib.h"
#include "AEBasic.h"
#include "AEClip.h"
#include "AETypes.h"

namespace AE
{
	class Anim
	{
		public:
			Anim();
			Anim(int delai_anim, boost::shared_ptr<Clip> clip);
			Anim(const Anim &a_copier);
			~Anim();
		
			void operator=(Anim a_copier);
		
			void start();
			void stop();
			void restart();
		
			Surface current_image(); // Une fonction retournant un objet de type Surface vers l'image courante qui doit être affichée
		
			void setClip(Clip *clip);
			void setDelaiAnim(const int delai_anim);
		
		protected:
			boost::shared_ptr<Clip> m_clip; // Un smart pointeur vers un clip de sprites
		
			bool m_started;
		
			int m_delai_anim; // Delai en ms entre chaque affichage du sprite du clip
			int m_current_image_index; // L'index courant du clip
			Uint32 m_last_time; // La dernière fois qu'on a changé l'index courant d'image
	};
}

#endif
