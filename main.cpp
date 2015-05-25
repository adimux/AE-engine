#include <iostream>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>
#include <boost/shared_ptr.hpp>
//#include <windows.h>
#include "AE.h"

using namespace std;
using namespace boost;
using namespace AE;

Decimal valeur_absolue(Decimal n)
{
	if(n > 0)
		return n;
	else
		return -n;
}

int main(int argc, char **argv)
{
	TTF_Init();
	
	SDL_Init(SDL_INIT_VIDEO);
	
	Surface ecran = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE );
	
	Logger::SetLogger( new LoggerTTF( string("arial.ttf") ) );
	
	bool continuer = true;
	
	//shared_ptr<Clip> personnage_clip( new Clip("Data/mario1D.gif", "Data/mario2D.gif", "Data/mario3D.gif", "Data/mario4D.gif", "Data/mario5D.gif", "Data/mario6D.gif", "Data/mario7D.gif", NULL) );
	//Anim personnage(100, personnage_clip);
	
	//Surface carre( Rect(0, 0, 100, 100) ); // Un carré 100*100
	//carre.fill( RGB(0, 0, 0) );
	SpritePtr mario( new Sprite( string("data/mario1D.gif") ) );
	SpritePtr fond( new Sprite( string("data/fond.jpg") ) );
	
	DrawManager drawer;
	drawer.push(fond, 0).push(mario, 0);
	mario->setPosition( DVector2D(100, 100) );
	//drawer.push(0, (void*)&fond, (void*)&mario, NULL);
	
	DRect position(0, 100);
	
	Speed mario_speed( DVector2D(0, 0), 2);
	
	Event event;
	
	int fps = 60;
	Timer olel;
	
	mario_speed.start();
	
	Timer temps_ecriture_fps;
	temps_ecriture_fps.start();
	
	while(continuer)
	{
		olel.start();
		// On efface l'écran
		ecran.fill( RGB(255, 255, 255) );
		
		// Gestion des events
		event.poll();
		
		Decimal acc = 0.1;
		Decimal limit = 1;
		
		if( event.keyPressed(SDLK_RIGHT) )
		{
			//Logger::Log() << "RIGHT" << Logger::endline;
			
			if(mario_speed.speed.x < limit && mario_speed.speed.x > -limit)
				mario_speed += DVector2D(acc);
		}
		
		if( event.keyPressed(SDLK_LEFT) )
		{
			//Logger::Log() << "LEFT" << Logger::endline;
			
			if(mario_speed.speed.x < limit && mario_speed.speed.x > -limit)
				mario_speed -= DVector2D(acc);
		}
		
		if( event.keyPressed(SDLK_UP) )
		{
			//Logger::Log() << "UP" << Logger::endline;
			
			if(mario_speed.speed.y < limit && mario_speed.speed.y > -limit)
				mario_speed -= DVector2D(0, acc);
		}
		
		if( event.keyPressed(SDLK_DOWN) )
		{
			//Logger::Log() << "DOWN" << Logger::endline;
			
			if(mario_speed.speed.y < limit && mario_speed.speed.y > -limit)
				mario_speed += DVector2D(0, acc);
		}
		
		
		Decimal no_acc = 0.05;
		
		if( !event.keyPressed(SDLK_DOWN) )
		{
			if( valeur_absolue(mario_speed.speed.y) < no_acc)
			{
				mario_speed.speed.y = 0;
			}
			else if(mario_speed.speed.y > 0)
			{
				mario_speed.speed.y -= no_acc;
			}
		}
		
		if( !event.keyPressed(SDLK_UP) )
		{
			if( valeur_absolue(mario_speed.speed.y) < no_acc)
			{
				mario_speed.speed.y = 0;
			}
			if(mario_speed.speed.y < 0)
			{
				mario_speed.speed.y += no_acc;
			}
		}
		
		/*if( !event.keyPressed(SDLK_DOWN) && !event.keyPressed(SDLK_UP) )
		{
			Decimal no_acc = 0.2;
			
			if( valeur_absolue(mario_speed.speed.y) < no_acc)
			{
				mario_speed.speed.y = 0;
			}
			else
			{
				if(mario_speed.speed.y < 0)
				{
					mario_speed.speed.y += no_acc;
				}
				else if(mario_speed.speed.y > 0)
				{
					mario_speed.speed.y -= no_acc;
				}
			}
		}*/
		
		if( !event.keyPressed(SDLK_RIGHT) )
		{
			if( valeur_absolue(mario_speed.speed.x) < no_acc)
			{
				mario_speed.speed.x = 0;
			}
			else if(mario_speed.speed.x > 0)
			{
				mario_speed.speed.x -= no_acc;
			}
		}
		
		if( !event.keyPressed(SDLK_LEFT) )
		{
			if( valeur_absolue(mario_speed.speed.x) < no_acc)
			{
				mario_speed.speed.x = 0;
			}
			if(mario_speed.speed.x < 0)
			{
				mario_speed.speed.x += no_acc;
			}
		}
		
	/*	if( !event.keyPressed(SDLK_RIGHT) && !event.keyPressed(SDLK_LEFT) )
		{
			Decimal no_acc = 0.2;
			
			if( valeur_absolue(mario_speed.speed.x) < no_acc)
			{
				mario_speed.speed.x = 0;
			}
			else
			{
				if(mario_speed.speed.x < 0)
				{
					mario_speed.speed.x += no_acc;
				}
				else if(mario_speed.speed.x > 0)
				{
					mario_speed.speed.x -= no_acc;
				}
			}
		}*/
		
		/*if( !event.keyPressed(SDLK_DOWN) && !event.keyPressed(SDLK_RIGHT) && !event.keyPressed(SDLK_UP) && !event.keyPressed(SDLK_DOWN) )
		{
			Decimal no_acc = 0.2;
			
			if(mario_speed.speed.x < 0)
			{
				if(mario_speed.speed.x*-1 < no_acc)
					mario_speed.speed.x = 0;
				else 
					mario_speed += DVector2D(no_acc);
			}
			if(mario_speed.speed.x > 0)
			{
				if(mario_speed.speed.x < no_acc)
					mario_speed.speed.x = 0;
				else 
					mario_speed -= DVector2D(no_acc);
			}
			if(mario_speed.speed.y < 0)
			{
				if(mario_speed.speed.y*-1 < no_acc)
					mario_speed.speed.y = 0;
				else
					mario_speed += DVector2D(0, no_acc);
			}
			if(mario_speed.speed.y > 0)
			{
				if(mario_speed.speed.y < no_acc)
					mario_speed.speed.y = 0;
				else
					mario_speed -= DVector2D(0, no_acc);
			}
		}*/
		
		/*if(event.keyUp(SDLK_RIGHT) )
		{
			Logger::Log() << "Relache RIGHT" << Logger::endline;
			mario_speed -= DVector2D(acc);
		}
		
		if(event.keyUp(SDLK_LEFT) )
		{
			Logger::Log() << "Relache LEFT" << Logger::endline;
			mario_speed += DVector2D(acc);
		}
		
		if(event.keyUp(SDLK_UP) )
		{
			Logger::Log() << "Relache UP" << Logger::endline;
			mario_speed += DVector2D(0, acc);
		}
		
		if(event.keyUp(SDLK_DOWN) )
		{
			Logger::Log() << "Relache DOWN" << Logger::endline;
			mario_speed -= DVector2D(0, acc);
		}*/
		
		DVector2D current_speed = mario_speed.current_speed();
		
		mario->avancer(current_speed);
//		if( event.keyPressed(SDLK_RIGHT) )
//			mario->avancer(current_speed);
//		if( event.keyPressed(SDLK_LEFT) )
//			mario->avancer(current_speed);
//		if( event.keyPressed(SDLK_DOWN) )
//			mario->avancer(current_speed);
//		if( event.keyPressed(SDLK_UP) )
//			mario->avancer(current_speed);
		
		/*if( ( event.keyDown(SDLK_RIGHT) || event.keyDown(SDLK_LEFT) || event.keyDown(SDLK_UP) || event.keyDown(SDLK_DOWN) ) &&
		( !event.keyPressed(SDLK_DOWN) && !event.keyPressed(SDLK_RIGHT) && !event.keyPressed(SDLK_UP) && !event.keyPressed(SDLK_DOWN) ) )
		{
			cerr << "start !" << endl;
			mario_speed.restart();
		}
		else
		{
			if(mario_speed.delay > 0.5)
				mario_speed.delay =- 0.01;
		}
		
		
		float current_speed = mario_speed.current_speed();
		
		if( event.keyPressed(SDLK_RIGHT) )
		{
			mario->avancer( DRect(current_speed, 0) );
			//position.x += current_speed;
		}
		if( event.keyPressed(SDLK_LEFT) )
		{
			mario->avancer( DRect(-current_speed, 0) );
			//position.x -= current_speed;
		}
		if( event.keyPressed(SDLK_DOWN) )
		{
			mario->avancer( DRect(0, current_speed) );
			//position.y += current_speed;
		}
		if( event.keyPressed(SDLK_UP) )
		{
			mario->avancer( DRect(0, - current_speed) );
			//position.y -= current_speed;
		}
		if(!event.keyPressed(SDLK_DOWN) && !event.keyPressed(SDLK_RIGHT) && !event.keyPressed(SDLK_UP) && !event.keyPressed(SDLK_DOWN) )
		{
			mario_speed.delay += 0.1;
			if(mario_speed.delay > 1)
				mario_speed.delay = 1;
		}*/
					
		if( event.type() == SDL_QUIT)
			continuer = false;
		if( event.keyDown(SDLK_ESCAPE) )
			continuer = false;
			
		/***** Dessin ******/
		ecran.fill( RGB(0, 0, 0), DRect(0, mario->getPos().y + mario->height(), ecran.width(), 10) );
		drawer.draw(ecran);
		
//		Logger::Log() << "kiki";
		
		( (LoggerTTF*) Logger::getLogger() )->draw(ecran);
		
		ecran.flip();
		
		int timestep = olel.elapsed_time();
		
		if(temps_ecriture_fps.elapsed_time() >= 10)
		{
			( (LoggerTTF*) Logger::getLogger() )->clear();
			Logger::Log() << "Fps : " << 1000.0 / (float)timestep << Logger::endline;
			
			temps_ecriture_fps.restart();
		}
		
		if( timestep < 1000 / fps )
			SDL_Delay(1000 / fps - timestep);
	}
	
	TTF_Quit();
	
	SDL_Quit();
	
	return 0;
}
