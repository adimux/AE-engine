#include "AELoggerTTF.h"

using namespace std;

namespace AE
{
	LoggerTTF::LoggerTTF(const std::string &chemin_police, int taille_police, IRect boite_ecriture)
	{
		m_police = TTF_OpenFont(chemin_police.c_str(), taille_police);
		m_last_message = 0;
		m_boite_ecriture = boite_ecriture;
	}
	
	LoggerTTF::~LoggerTTF()
	{
		if(m_police != NULL)
		{
			TTF_CloseFont(m_police);	
		}
	}
	
	void LoggerTTF::setBoiteEcriture(IRect new_boite_ecriture)
	{
		m_boite_ecriture = new_boite_ecriture;
	}
	
	void LoggerTTF::draw(Surface ecran)
	{
		if(m_buffer.empty() )
			return;
		
		if(SDL_GetTicks() - m_last_message >= 3000)
		{
			m_buffer.erase( m_buffer.begin() );
			
			m_last_message = SDL_GetTicks();
		}
		
		if(m_police)
		{
			SDL_Color noir = {0, 0, 0};
			
			vector<string>::iterator message = m_buffer.begin();
			IRect boite = m_boite_ecriture;
		
			for(; message != m_buffer.end(); message++)
			{
				SDL_Surface *text = TTF_RenderText_Blended(m_police, message->c_str(), noir);
				
				if(text)
				{
					boite.y += text->h;
					boite.h -= text->h;
					
					ApplySurface(text, ecran.getSurface(), IRect(), boite );
				}
			}
		}
	}
	
	void LoggerTTF::clear()
	{
		m_buffer.clear();	
	}
	
	void LoggerTTF::Write(const std::string &message)
	{
		if(message == "\n")
			m_last_was_endline = true;
		else
		{
			if(m_last_was_endline)
				m_buffer.insert(m_buffer.begin(), message);
			else
			{
				if(!m_buffer.empty() )
				{
					vector<string>::iterator last = m_buffer.begin();
					
					last->operator+=(message);
				}
				else
					m_buffer.insert(m_buffer.begin(), message);
			}
			m_last_was_endline = false;
		}
	}
}
