/**
* \file AEForme.h
* \brief Des classes de formes d'objets (rectangles, cercles, etc...) pour les collisions
* \author Adam Cherti
* \version 0.1
* \date 30 Octobre 2010
*
* Formes d'objets pour les tests collision.
* Les formes sont connect�es � des Sprites (classe abstraite Spr dans le fichier AESprite.h).
* Et quand il y a une collision entre une forme et une autre, la fonction thereIsCollision des deux sprites concern�s est appell�e
*/
#ifndef AE_PHYSICS_OBJECTS_CLASSES
#define AE_PHYSICS_OBJECTS_CLASSES

#include "AEBasic.h"
#include "AESprite.h"
#include "AE_ClassWithType.h"

namespace AE
{
	class Object;
	class OPoint;
	class OAABB;
	class OTriangle;
	class OCircle;
	
	typedef boost::shared_ptr<Object> ObjectPtr;
	
	class Spr;
	
	/** La classe CollisionEvents */
	struct CollisionEvents
	{
		public:
			CollisionEvents();
			CollisionEvents(bool f_there_is_collision, ObjectPtr f_first_object, ObjectPtr f_second_object, DVector2D f_recul_first_object=DVector2D(), DVector2D f_recul_second_object=DVector2D() );
			~CollisionEvents();
			
			/** S'il y a collision ou non */
			bool there_is_collision;

			/** Les deux objets en collision */			
			ObjectPtr first_object;
			ObjectPtr second_object;
			/** Le recul qui doit �tre fait pour que les objets ne soient plus "un dans l'autre" */
			DVector2D recul_first_object;
			DVector2D recul_second_object;
	};
	
	/** La classe Object */
	class Object : public ClassWithType
	{
		public:
			Object(bool is_static=false);
			virtual ~Object();
			
			virtual DRect &getBoundingBox();
			virtual void calculateBoundingBox();
			
			virtual DVector2D& getPos();
			virtual void setPos(DVector2D &);
			virtual void avancer(DVector2D &);
			
			virtual DVector2D& getVitesse();
			
			virtual void setStatic(bool);
			virtual bool isStatic();
			
			/** Fonction de test de collision avec un autre Objet, cela retourne une structure de type CollisionEvents
			* Bien s�r, si on veut que la collision se teste avec une autre classe d�rivant de Object (cr��e par l'utilisateur), il faut surcharger cette fonction (autres arguments) */
			virtual CollisionEvents collisionWith(ObjectPtr &object);

			/** Le sprite auquel l'objet est connect� */
			boost::shared_ptr<Spr> connected_with;
			
		public:
			// Types d'objets
			/** Un objet quelconque (d�riv� de la classe Object) */
			static Type AnyObject;
			/** Un point (soit un OPoint soit une classe d�riv�e de cette derni�re) */
			static Type Point;
			/** Un rectangle AABB (soit un OAABB soit une classe d�riv�e de cette derni�re) */
			static Type AABB;
			/** Un triangle (soit un OTriangle soit une classe d�riv�e de cette derni�re) */
			static Type Triangle;
			/** Un cercle (soit un OCircle soit une classe d�riv�e de cette derni�re) */
			static Type Circle;
		
		protected:
			/** La vitesse de l'objet */
			DVector2D m_vitesse;
			
			/** Ce rect-l� "encandre" l'objet (pour n'importe quelle forme, on peut trouver un rectangle qui "l'encadre", on appelle �a une bouding box)
			* Cela sert � optimiser les collision en utilisant les offsets (des arbres contenant les objets, celui-ci les
			* classe en fonction de leur position pour ne tester la collision d'un objet qu'avec ceux qui sont proches de lui
			* Cela peut servir � d'autres choses comme ne pas calculer la collision d'un objet complexe (un polygone convexe par exemple)
			* si et seulement si leur boites englobantes sont en collision (cela contribue donc � la rapidit�) */
			DRect m_boundingBox;
			
			/** Si l'objet est statique ou non */
			bool m_static;
//			/** La derni�re fois que cet objet a chang� de position (mouvement) */
//			Uint32 m_last_mouvement;
			/** La position de l'objet */
			//DVector2D m_position;
	};
	
	/** La classe Point, qui n'est qu'une simple coordonn�e (un point) */
	class OPoint : public Object
	{
		public:
			OPoint(DVector2D _position_point, bool is_static=false);
			~OPoint();
			
			void avancer(DVector2D &);
			void calculateBoundingBox();
			
			CollisionEvents collisionWith(ObjectPtr &object);
			
			/** La position du point */
			DVector2D position_point;
	};
	
	/** La classe OAABB, la forme rectangle */
	class OAABB : public Object
	{
		public:
			OAABB(DRect _rectangle, bool is_static=false);
			~OAABB();
			
			void avancer(DVector2D &);
			void calculateBoundingBox();
			
			void operator=(OAABB &);
			
			CollisionEvents collisionWith(ObjectPtr &object);
			
			/** x et y du rectangle sont relatifs � la position de l'objet (DVector2D position - voir la classe Object) */
			DRect rectangle;
	};
	
	/** La classe OTriangle, la forme triangle */
	class OTriangle : public Object
	{
		public:
			OTriangle();
			OTriangle(DVector2D _A, DVector2D _B, DVector2D _C, bool is_static=false);
			~OTriangle();
			
			void operator=(OTriangle &);
			
			CollisionEvents collisionWith(ObjectPtr &object);
			
			/** Point A */
			DVector2D A;
			/** Point B */
			DVector2D B;
			/** Point C */
			DVector2D C;
	};
	
	/** La classe OCircle, la forme cercle */
	class OCircle : public Object
	{
		public:
			OCircle(DVector2D f_position, bool is_static, DVector2D f_position_centre, float f_rayon);
			~OCircle();
			
			void operator=(OCircle &);
			
			CollisionEvents collisionWith(ObjectPtr &object);
			
			/** Le rayon du cercle */
			Decimal rayon;
			/** x et y sont des positions relatives � la position DVector2D position - voir la classe Object */
			DVector2D position_centre;
	};
}

#endif
