#ifndef AE_LOGGER_TTF_CLASS
#define AE_LOGGER_TTF_CLASS
#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include "AEBasic.h"
#include "AELogger.h"
#include "AEDefines.h"
#include "AETypes.h"

namespace AE
{
	class LoggerTTF : public Logger
	{
		public:
			/** Constructeur */
			LoggerTTF(const std::string &chemin_police, int taille_police=16, IRect boite_ecriture=IRect() );
			
			void setBoiteEcriture(IRect new_boite_ecriture=IRect() );
			void draw(Surface);
			
			void clear();
			
			~LoggerTTF();
		
		private:
			/** Ecrit dans le Log file */
			virtual void Write(const std::string &message);
			
			std::vector<std::string> m_buffer;
			Uint32 m_last_message;
			
			bool m_last_was_endline;
			
			/** Le rectangle où on écrit (l'écriture ne doit pas dépasser celui-ci) */
			IRect m_boite_ecriture;
			/** La police avec laquelle on écrit */
			TTF_Font *m_police;
	};
}

#endif
