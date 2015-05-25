#include "AEEvent.h"

using namespace std;
using namespace boost;

namespace AE
{
	MouseEvents::MouseEvents() : right(false), left(false), middle(false), wheel_down(false), wheel_up(false)
	{
	}
	
	

	Event::Event() : m_keys_pressed( new bool[SDLK_LAST] ), m_there_is_event(false), m_type_event(-1)
	{
		memset(m_keys_pressed, false, SDLK_LAST); // On remplit m_keys_pressed de falses (bien sûr, puisque aucune touche n'a été pressée, non :D ? )
	}
	
	Event::Event(const Event &a_copier) : m_type_event(-1)
	{
		m_event = a_copier.m_event;
		m_there_is_event = a_copier.m_there_is_event;
		
		m_keys_pressed = new bool[SDLK_LAST];
		memcpy(m_keys_pressed, a_copier.m_keys_pressed, SDLK_LAST);
		
		m_mouse_events = a_copier.m_mouse_events;
	}
	
	Event::~Event()
	{
		
	}
	
	bool Event::poll()
	{
		m_there_is_event = SDL_PollEvent( &m_event );
		/*if( mouseButtonDown(SDL_BUTTON_RIGHT) )
			m_mouse_button_right_pressed = true;
		else if( mouseButtonDown(SDL_BUTTON_LEFT) )
			m_mouse_button_left_pressed = true;
		
		if( mouseButtonUp(SDL_BUTTON_RIGHT) )
			m_mouse_button_right_pressed = false;
		if( mouseButtonDown(SDL_BUTTON_LEFT) )
			m_mouse_button_left_pressed = false;*/
			
		majVars();
		
		return m_there_is_event;
	}
	
	void Event::majVars()
	{
		if(m_there_is_event) // S'il y a eu un event
		{
			m_type_event = m_event.type;
			
			if(m_type_event == SDL_KEYDOWN)
				m_keys_pressed[m_event.key.keysym.sym] = true; // On rend la touche event.key.keysym.sym enfoncée
			else if(m_type_event == SDL_KEYUP)
				m_keys_pressed[m_event.key.keysym.sym] = false; // L'utilisateur a lâché la touche, donc elle n'est plus pressée
		
			if(m_type_event == SDL_MOUSEBUTTONDOWN || m_type_event == SDL_MOUSEBUTTONUP)
			{
				bool affect;
		
				if(m_type_event == SDL_MOUSEBUTTONDOWN)
				{
					affect = true;
				}
				if(m_type_event == SDL_MOUSEBUTTONUP)
				{
					affect = false;
				}
		
				switch(m_event.button.button)
				{
					case SDL_BUTTON_RIGHT:
						m_mouse_events.right = affect;
					break;
				
					case SDL_BUTTON_LEFT:
						m_mouse_events.left = affect;
					break;
				
					case SDL_BUTTON_MIDDLE:
						m_mouse_events.middle = affect;
					break;
				
					case SDL_BUTTON_WHEELUP:
						m_mouse_events.wheel_up = affect;
					break;
				
					case SDL_BUTTON_WHEELDOWN:
						m_mouse_events.wheel_down = affect;
					break;
				};
				
				m_mouse_events.button_position.x = m_event.button.x;
				m_mouse_events.button_position.y = m_event.button.y;
			}
			
			if(m_type_event == SDL_MOUSEMOTION)
			{
				m_mouse_events.motion_position.x = m_event.motion.x;
				m_mouse_events.motion_position.y = m_event.motion.y;
				
				SDL_GetRelativeMouseState( &m_mouse_events.relative_position.x, &m_mouse_events.relative_position.y);
			}
		}
	}
	
	bool Event::wait()
	{
		if( SDL_WaitEvent( &m_event ) == 0) // Aucune erreur
		{
			m_there_is_event = true; // Il y a eu un évènement car SDL_WaitEvent attend jusqu'à ce qu'un event se passe
			
			return true;
		}
		else
			return false;
	}
	
	int Event::type() // Retourne le type d'évènement
	{
		return m_type_event;	
	}
	
	bool Event::keyPressed(int keysym)
	{
		if(keysym >= 0 && keysym <= SDLK_LAST)
			return m_keys_pressed[keysym];
		else
			return false;
	}
	
	bool Event::keyUp(int keysym)
	{
		if(!m_there_is_event)
			return false;
		
		if(m_type_event == SDL_KEYUP)
			return (m_event.key.keysym.sym == keysym);
		else
			return false;
	}
	
	bool Event::keyDown(int keysym)
	{
		if(!m_there_is_event)
			return false;
		
		if(m_type_event == SDL_KEYDOWN)
			return (m_event.key.keysym.sym == keysym);
		else
			return false;
	}
	
	bool Event::mouseButtonDown(int button)
	{
		if(!m_there_is_event)
			return false;
		
		if(m_type_event == SDL_MOUSEBUTTONDOWN)
			return m_event.button.button == button;
		else
			return false;
	}
	
	bool Event::mouseButtonUp(int button)
	{
		if(!m_there_is_event)
			return false;
		
		if(m_type_event == SDL_MOUSEBUTTONUP)
			return m_event.button.button == button;
		else
			return false;
	}
	
	bool Event::mouseButtonPressed(int button)
	{
		if(button == SDL_BUTTON_RIGHT)
			return m_mouse_events.right;
		else if(button == SDL_BUTTON_LEFT)
			return m_mouse_events.left;
		else if(button == SDL_BUTTON_MIDDLE)
			return m_mouse_events.middle;
		else if(button == SDL_BUTTON_WHEELDOWN)
			return m_mouse_events.wheel_down;
		else if(button == SDL_BUTTON_WHEELUP)
			return m_mouse_events.wheel_up;
		else
			return false;
	}
	
	IVector2D Event::mouseButtonPosition()
	{
		return m_mouse_events.button_position;
	}
	
	bool Event::mouseMotion()
	{
		if(m_there_is_event)
			return (m_type_event == SDL_MOUSEMOTION);
		else
			return false;
	}
	
	IVector2D Event::mouseMotionPosition()
	{
		return m_mouse_events.motion_position;
	}
	
	IVector2D Event::mouseRelativePosition()
	{
		return m_mouse_events.relative_position;
	}
	
	void Event::operator=(Event &a_copier)
	{
		m_event = a_copier.m_event;
		m_there_is_event = a_copier.m_there_is_event;
		
		m_keys_pressed = new bool[SDLK_LAST];
		memcpy(m_keys_pressed, a_copier.m_keys_pressed, SDLK_LAST);
		
		m_mouse_events = a_copier.m_mouse_events;
	}
}
