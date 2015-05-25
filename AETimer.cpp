#include "AETimer.h"

namespace AE
{
	Timer::Timer() : m_last_time(0), m_started(false)
	{
	}

	Timer::~Timer()
	{	
	}

	void Timer::start()
	{
		m_started = true;
		m_last_time = SDL_GetTicks();	
	}

	void Timer::stop()
	{
		m_started = false;
		m_last_time = 0;
	}

	void Timer::restart()
	{
		stop();
		start();	
	}

	int Timer::elapsed_time()
	{
		if(m_started)
			return SDL_GetTicks() - m_last_time;
		else
			return 0;	
	}
}
