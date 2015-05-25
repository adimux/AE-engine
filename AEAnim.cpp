#include "AEAnim.h"

using namespace std;
using namespace boost;

namespace AE
{
	Anim::Anim() : m_delai_anim(0), m_current_image_index(0), m_last_time(0), m_started(true), m_clip( shared_ptr<Clip>(new Clip() ) )
	{
	}

	Anim::Anim(int delai_anim, shared_ptr<Clip> clip) : m_delai_anim(delai_anim), m_started(true), m_current_image_index(0), m_last_time(SDL_GetTicks() ), m_clip( clip )
	{
	}

	Anim::Anim(const Anim &a_copier) : m_clip(a_copier.m_clip), m_started(a_copier.m_started), m_delai_anim(a_copier.m_delai_anim), m_current_image_index(a_copier.m_current_image_index), m_last_time(a_copier.m_last_time)
	{
	}

	Anim::~Anim()
	{
	
	}

	void Anim::operator=(Anim a_copier)
	{
		m_clip = a_copier.m_clip; // On copie le pointeur du clip, attention au confusions
		m_started = a_copier.m_started;
		m_delai_anim = a_copier.m_delai_anim;
		m_current_image_index = a_copier.m_current_image_index;
		m_last_time = a_copier.m_last_time;
	}

	void Anim::start()
	{
		if(m_started == true)
			return;
	
		m_current_image_index = 0;
		m_last_time = SDL_GetTicks();
	}

	void Anim::stop()
	{
		m_started = false;
	}

	void Anim::restart()
	{
		stop();
		start();
	}

	Surface Anim::current_image() // Une fonction retournant un pointeur SDL_Surface vers l'image courante qui doit être affichée
	{
		if(m_started == false || m_clip->get_nbr_sprites() <= 0) // Si l'animation n'est pas "started" ou si il y a 0 images sur le clip
			return Surface(); // On retourne une surface vide
	
		Uint32 time_past = SDL_GetTicks() - m_last_time; // On calcule le temps passé depuis le dernier changement de current_image
	
		if(time_past < m_delai_anim) // Si le temps passé est moins que le délai d'animation, on lui retourne la même image
		{
			Surface to_return;
			to_return = m_clip->get( m_current_image_index );

			return to_return;
		}
	
		// Sinon, on fait avancer l'index en fonction de time_past et on retourne la surface qui doit être affichée
	
		int to_add = (int) ( (float)time_past / (float)m_delai_anim );
	
		m_last_time = SDL_GetTicks();

		m_current_image_index += to_add;

		if(m_current_image_index >= m_clip->get_nbr_sprites() )
		{
			m_current_image_index %= m_clip->get_nbr_sprites();
		}

		return m_clip->get( m_current_image_index );
	}

	void Anim::setDelaiAnim(const int delai_anim)
	{
		m_delai_anim = delai_anim;
	}
}
