#include "AESpeed.h"

namespace AE
{
	Speed::Speed() : speed(), delay(0)
	{
	}

	Speed::Speed(DVector2D _speed, Uint32 _delay) : speed(_speed), delay(_delay)
	{
	}

	Speed::~Speed()
	{	
	}

	void Speed::operator=(Speed &a_copier)
	{
		speed = a_copier.speed;
		delay = a_copier.delay;
	}
	
	void Speed::operator+=(DVector2D to_add)
	{
		speed += to_add;	
	}
	
	void Speed::operator-=(DVector2D a_soustraire)
	{
		speed -= a_soustraire;	
	}

	DVector2D Speed::current_speed()
	{
		if(m_started)
		{
			DVector2D current_speed(speed * ( (Decimal)elapsed_time() / (Decimal)delay) );
		
			m_last_time = SDL_GetTicks();	
	
			return current_speed;
		}
		else
			return DVector2D();
	}
}
