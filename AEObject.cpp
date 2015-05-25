#include "AEObject.h"

using namespace std;
using namespace boost;

/*
*--------------------------------*
|-------- Namespace AE  ---------|
*--------------------------------*
*/
namespace AE
{
	/*
	   _____________________________
	 /                              \
	|   La classe CollisionEvents    |
	 \______________________________/
	*/
	CollisionEvents::CollisionEvents() : there_is_collision(false), first_object(  (Object*)NULL ), second_object( (Object*)NULL ), recul_first_object( DVector2D() ), recul_second_object( DVector2D() )
	{
	}
	
	CollisionEvents::CollisionEvents(bool f_there_is_collision, ObjectPtr f_first_object, ObjectPtr f_second_object, DVector2D f_recul_first_object, DVector2D f_recul_second_object)
	{
		there_is_collision = f_there_is_collision;
		first_object = f_first_object;
		second_object = f_second_object;
		recul_first_object = f_recul_first_object;
		recul_second_object = f_recul_second_object;
	}

	CollisionEvents::~CollisionEvents()
	{
	}
	
	/*
	   ___________________
	 /                    \
	|   La classe Object    |
	 \____________________/
	*/
	
	Type Object::AnyObject = 0;
	Type Object::Point = 1;
	Type Object::AABB = 2;
	Type Object::Triangle = 3;
	Type Object::Circle = 4;

	Object::Object(bool is_static) : connected_with( shared_ptr<Spr>( (Spr *) NULL ) ), m_static(is_static), m_boundingBox()
	{
		m_type.push_back(Object::AnyObject);
		
		calculateBoundingBox();
	}
	
	Object::~Object()
	{
	}
	
	DRect &Object::getBoundingBox()
	{
		return m_boundingBox;	
	}
	
	void Object::calculateBoundingBox()
	{
	}
	
	DVector2D &Object::getPos()
	{
		return m_boundingBox;
	}
	
	void Object::setPos(DVector2D &new_pos)
	{
		m_vitesse = DRect(new_pos.x - m_boundingBox.x, new_pos.y - m_boundingBox.y);
		//m_position = new_pos;
		//m_boundingBox += m_vitesse;
		avancer(m_vitesse);
	}
	
	void Object::avancer(DVector2D &to_add)
	{
		m_vitesse = to_add;
		m_boundingBox += to_add;
//		m_position.x += to_add.x;
//		m_position.y += to_add.y;
	}
	
	DVector2D &Object::getVitesse()
	{
		return m_vitesse;
	}
	
	void Object::setStatic(bool is_static)
	{
		m_static = is_static;	
	}
	
	bool Object::isStatic()
	{
		return m_static;
	}
	
	CollisionEvents Object::collisionWith(ObjectPtr &object)
	{
		return CollisionEvents(); // Par défaut, il n'y a aucune collision :p
	}
	
	/*
	   ___________________
	 /                    \
	|   La classe OPoint    |
	 \____________________/
	*/
	
	OPoint::OPoint(DVector2D _position_point, bool is_static) : position_point(_position_point), Object::Object(is_static)
	{
		m_type.push_back(Object::Point);
	}
	
	OPoint::~OPoint()
	{
	}
	
	void OPoint::avancer(DVector2D &v)
	{
		Object::avancer(v);
		
		position_point += v;
	}
	
	void OPoint::calculateBoundingBox()
	{
		m_boundingBox = DRect(position_point);
		m_boundingBox.w = 0;
		m_boundingBox.h = 0;
	}
	
	CollisionEvents OPoint::collisionWith(ObjectPtr &object)
	{
		/*CollisionEvents result(false, ObjectPtr(this), object);
		
		if( object->isType(Object::Point) )
		{
			DRect pos_point_1(m_position.x + pos_relative.x, m_position.y + pos_relative.y);
			DRect pos_point_2(object->getPos().x, object->getPos().y);
			
			if(pos_point_1 == pos_point_2)
			{
				result.there_is_collision = true;
				
				if(m_static)
				{
					if( !object->isStatic() )
					{
						result.recul_second_object = pos_point_2 - pos_point_1;	
					}
				}
				
				else
				{
					if( object->isStatic() )
					{
						result.recul_first_object = DRect(-1, -1);
					}
					else
					{
						result.recul_first_object = DRect(-1, -1);
						result.recul_second_object = DRect(1, 1);	
					}
				}
			}
		}
		else if(object->isType(Object::AABB) )
		{
			DRect pos_point(m_position.x + pos_relative.x, m_position.y + pos_relative.y);
			DRect aabb_rect(object->getPos().x + ( (OAABB*)( object.get() ) )->rectangle.x, object->getPos().y +
			((OAABB*)object.get())->rectangle.y, ((OAABB*)object.get())->rectangle.w, ((OAABB*)object.get())->rectangle.h);
			
			result.there_is_collision = true;
			
			if(m_static)
			{
				if(!object->isStatic() )
				{
					result.recul_second_object -= result.second_object->getVitesse();
				}
			}
			else
			{
				if(object->isStatic() )
				{
					result.recul_first_object -= result.first_object->getVitesse();
				}
				else
				{
					result.recul_first_object -= result.first_object->getVitesse();
					result.recul_second_object -= result.second_object->getVitesse();
				}
			}
		}
		
		return result;*/
	}
	
	/*
	   ___________________
	 /                    \
	|   La classe OAABB    |
	 \____________________/
	*/
	OAABB::OAABB(DRect _rectangle, bool is_static) : rectangle(_rectangle), Object::Object(is_static)
	{
		m_type.push_back(Object::AABB);
	}
	
	OAABB::~OAABB()
	{
	}
	
	void OAABB::avancer(DVector2D &v)
	{
		Object::avancer(v);
		
		rectangle += v;
	}
	
	void OAABB::calculateBoundingBox()
	{
		m_boundingBox = rectangle;
	}
	
	void OAABB::operator=(OAABB &to_copy)
	{
		m_boundingBox = to_copy.m_boundingBox;
		rectangle = to_copy.rectangle;	
	}
	
	CollisionEvents OAABB::collisionWith(ObjectPtr &object)
	{
		/*CollisionEvents collision_info;
		
		if(object->isType(Object::AABB) ) // Si on teste la collision avec une boîte AABB
		{
			shared_ptr<OAABB> aabb_object( (OAABB*)object.get() );
			
			DRect this_aabb = DRect(m_position.x + rectangle.x, m_position.y + rectangle.y, rectangle.w, rectangle.h);
			DRect other_aabb = DRect(aabb_object->getPos().x + aabb_object->rectangle.x, aabb_object->getPos().y + aabb_object->rectangle.y
			, aabb_object->rectangle.w, aabb_object->rectangle.h);
			
			if( !(other_aabb.x >= this_aabb.x + this_aabb.w || other_aabb.x + other_aabb.w <= this_aabb.x
				|| other_aabb.y >= this_aabb.y + this_aabb.h || other_aabb.y + other_aabb.h <= this_aabb.y) ) // Donc il y a collision
			{
				collision_info.there_is_collision = true;
				
				// Passons maitenant au repositionnement des objets pour qu'ils ne soient plus en collision
				
			}
		}
		else if(object->isType(Object::Point) ) // On teste la collision avec un point
		{
			
		}
		
		return collision_info;*/
	}
}
