#ifndef AE_TIMER_CLASS
#define AE_TIMER_CLASS

#include <iostream>
#include <SDL/SDL.h>

namespace AE
{
	/** La classe Timer est une sorte de chronomètre qui calcule le temps écoulé depuis le dernier appel à start en utilisant elapsed_time() */
	class Timer
	{
		public:
			Timer();
			~Timer();
		
			/** Start le timer */
			void start();
			/** Stopper le timer */
			void stop();
			/** Reset du timer */
			void restart();
		
			/** Renvoie le temps écoulé en ms depuis l'appel à la fonction start() */
			int elapsed_time();
	
		protected:
			int m_last_time;
			bool m_started;
	};
}

#endif
