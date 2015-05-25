#ifndef AE_SPEED_CLASS
#define AE_SPEED_CLASS

#include <iostream>
#include "Vector2D.h"
#include "AETimer.h"
#include "AETypes.h"

namespace AE
{
	class Speed : public Timer
	{
		public:
			Speed();
			Speed(DVector2D _speed, Uint32 _delay);
			~Speed();
			
			void operator=(Speed &);
			void operator+=(DVector2D);
			void operator-=(DVector2D);
			DVector2D current_speed();
		
			DVector2D speed;
			Uint32 delay;
	};
}

#endif
