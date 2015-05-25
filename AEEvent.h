#ifndef AE_EVENT_CLASS
#define AE_EVENT_CLASS

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "AEBasic.h"
#include "AETypes.h"

namespace AE
{
	struct MouseEvents
	{
		public:
			MouseEvents();
	
			bool right;
			bool left;
			bool middle;
			bool wheel_down;
			bool wheel_up;
			
			Vector2D<int> button_position;
			Vector2D<int> motion_position;
			Vector2D<int> relative_position;
	};

	class Event
	{
		public:
			Event();
			
			Event(const Event &);
			
			~Event();
			
			/** Met � jour les events (s'il n'y a pas eu d'�v�nement, cela retourne false) */
			bool poll();
			/** Attend jusqu'� ce qu'un �v�nement se passe (renvoie true si la capture d'events s'est bien pass�e sinon false) */
			bool wait();
			
			/** Renvoie le type d'event */			
			int type();
			
			/** Si l'utilisateur a enlev� son doigt de la touche keysym */
			bool keyUp(int keysym);
			/** Si l'utilisateur a press� la touche keysym */
			bool keyDown(int keysym);
			/** Si une touche du clavier est actuellement press�e */
			bool keyPressed(int keysym);
			
			/** Clic de souris */
			bool mouseButtonDown(int button);
			/** Rel�chement du bouton de la souris */
			bool mouseButtonUp(int button);
			/** Un bouton de la souris est press� ou non */
			bool mouseButtonPressed(int button);
			/** Nouvelle position de la souris apr�s clic */
			IVector2D mouseButtonPosition();
			
			/** Mouvement de la souris */
			bool mouseMotion();
			/** Nouvelle position de la souris apr�s l'avoir mouv�e */
			IVector2D mouseMotionPosition();
			/** Position relative de la souris par rapport au dernier mouvement de la souris */
			IVector2D mouseRelativePosition();
			
			/** Coordonn�es du clic de la souris */
			IVector2D mouseButtonCoord();
			
			void operator=(Event &);
			
		protected:
			void majVars();
			
			
			/** Les events */
			SDL_Event m_event;
			int m_type_event;
			
			/**  Bool�en indiquant s'il y a eu un �v�nement ou non au dernier pollevent ou waitevent */
			bool m_there_is_event;
			
			/** Tableau de bool�ens indiquant l'�tat press�e ou non de chaque keysym (SDLK_a, SDLK_ESCAPE, etc...) */
			bool *m_keys_pressed;
			
			MouseEvents m_mouse_events;
	};	
}

#endif
