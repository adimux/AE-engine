/**
* \file AESprite.h
* \brief Des classes pour gérer les sprites qui sont considérés comme une ou plusieurs images (animation) ayant une position et ne peuvent s'afficher que dans le surfaces
* \author Adam Cherti
* \version 0.1
* \date 29 Octobre 2010
*
* Sprites
*/
#ifndef AE_SPRITE_CLASS
#define AE_SPRITE_CLASS

#include <iostream>
#include <boost/shared_ptr.hpp>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "AETypes.h"
#include "AEBasic.h"
#include "AELogger.h"
#include "AELoggerFile.h"
#include "AEObject.h"
#include "AESpriteBrain.h"
#include "AE_ClassWithType.h"

class SpriteBrain;

namespace AE
{
	class Object;
	class CollisionEvents;
	
	struct SurfDeleter
	{
		void operator()(Surface surf)
        { 
        	surf.free();
        }	
	};
	
	/** Classe abstraite qui "décrit" ce qu'est initialement un Sprite */
	class Spr : public ClassWithType
	{
		public:
			Spr(Rect<Decimal> initial_position=Rect<Decimal>() );
			virtual ~Spr();
			
			/*bool isType(Type); // Pour savoir de quelle type de sprite s'agit-il
			bool operator==(Type); // Pour savoir de quelle type de sprite s'agit-il
			bool operator!=(Type);*/
			
			/** Pour avancer */
			virtual void avancer(DVector2D &vector);
			/** On peut connecter le sprite avec un SpriteBrain qui permet d'affecter à un sprite un "cerveau" (par exemple, s'il y a collision, le sprite change d'état et de position, exemple : mort d'un personnage) */
			virtual void connect( boost::shared_ptr<SpriteBrain> &brain );
			virtual void disconnect();
			
			virtual boost::shared_ptr<SpriteBrain> &connectedWith();
			
			/** Quand il y a une collision entre une des formes connectée à ce Sprite et une autre forme connectée à un sprite différent, cette fonction est
			appellée (en cas d'évènement de collision) et cette fonction prend en paramètre une
			classe de type CollisionEvents qui indique les circonstances de la collision */
			//virtual void thereIsCollision(boost::shared_ptr<Object>, DRect);
			
			virtual DVector2D &getPos();
			virtual void setPosition(DVector2D &);
			virtual void setPosition(DVector2D);
			
			virtual int width();
			virtual int height();
			
			/** Dessine le sprite dans une surface */
			virtual void draw(Surface);
			/** Retourne l'image courante du Sprite (car un sprite peut être composé de plusieurs images -> animation) */
			virtual Surface currentImage();
			
		public:			
			// Déclaration de types de sprites basiques (la classe Spr, Sprite et AnimSprite)
			/** Un sprite quelconque dérivé de la classe Spr */
			static Type Sprite;
			/** Un sprite avec une seule image (peut-être soit de type Sprite ou d'une classe dérivée de cette dernière) */ 
			static Type OneImageSprite;
			/** Un sprite animé (peut-être soit de type AnimSprite ou d'une classe dérivée de cette dernière) */
			static Type AnimatedSprite;
		
		protected:
			/** La vitesse du Sprite */
			DRect m_vitesse;
			/** La position du Sprite */
			DVector2D m_position;
			/** Le temps passé depuis le début de l'application jusqu'au dernier mouvement fait par le sprite */
			Uint32 m_last_mouvement;
//			/** Tableaux d'objets connectées à ce Sprites (ces objets sont par exemple des boites AABB, triangles etc. et ces objets
//			* servent dans les tests de collision */
			/** Le cerveau du sprite est celui qui agit en conséquences des évènements qui ont encourus au sprite (si c'est un personnage et qu'il y a eu collision avec un monstre, le personnage doit mourir par exemple) */
			boost::shared_ptr<SpriteBrain> m_brain;
	};
	
	/** Classe dérivée de Spr, c'est un Sprite se composant d'une et unique image */
	class Sprite : public Spr
	{
		public:
			Sprite(std::string img_to_load, Rect<Decimal> initial_position=Rect<Decimal>() );
			Sprite(SDL_Surface *img, Rect<Decimal> initial_position=Rect<Decimal>() );
			Sprite(const Sprite &);
			~Sprite();
			
			int width();
			int height();
			
			void draw(Surface);
			void free();
			
			void load(std::string chemin);
			void load(SDL_Surface *img);
			
			Surface currentImage();
			
		protected:
			boost::shared_ptr<Surface> m_image;
	};
	
	/**
		Classe dérivée de Spr, un Sprite se composant de plusieurs images (animation)
	*/
	class AnimSprite : public Spr
	{
		
	};
	
	typedef boost::shared_ptr<Sprite> SpritePtr;
	typedef boost::shared_ptr<Spr> SprPtr;
	typedef boost::shared_ptr<AnimSprite> SprAnim;
}

#endif
