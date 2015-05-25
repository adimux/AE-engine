#include "AESprite.h"

using namespace std;
using namespace boost;

namespace AE
{
	Type Spr::Sprite = 0;
	Type Spr::OneImageSprite = 1;
	Type Spr::AnimatedSprite = 2;
	
	/* ---------------- */
	/*    Classe Spr    */
	/* ---------------- */
	Spr::Spr(Rect<Decimal> initial_position ) : m_position(initial_position), m_last_mouvement(0)
	{
		m_type.push_back(Spr::Sprite);
	}
	
	Spr::~Spr()
	{
	}
	
	/*bool Spr::isType(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
		
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return true;	
		}
		
		return false;
	}
	
	bool Spr::operator==(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
		
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return true;	
		}
		
		return false;
	}
	
	bool Spr::operator!=(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
		
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return false;
		}
		
		return true;
	}*/
	
	void Spr::avancer(DVector2D &v)
	{
		if(m_brain == NULL) // Si ce sprite n'a pas de "cerveau", il peut avancer. Mais s'il en a, c'est le cerveau qui doit faire avancer le sprite.
		{
			m_position.x += v.x;
			m_position.y += v.y;
		
			m_vitesse = v;
		
			m_last_mouvement = SDL_GetTicks();
		}
//		std::vector< shared_ptr<Object> >::iterator object = m_objects.begin();
		
//		while(object != m_objects.end() )
//		{
//			(*object)->setPos(m_position); // On déplace aussi les objets connectés au sprite ils sont "connectés" à lui !
			
//			object++;	
//		}
	}
	
/*	void Spr::connect(ObjectPtr object)
	{
		m_objects.push_back(object);
		
		object->connected_with = SprPtr( this );
		
		object->setPos(m_position);
	}*/
	void Spr::connect(shared_ptr<SpriteBrain> & brain)
	{
		if(m_brain != NULL)
			m_brain->disconnect();
			
		m_brain = brain;	
	}
	
	/*void Spr::disconnect( ObjectPtr object)
	{
		for(int i = 0; i < m_objects.size(); i++)
		{
			if(m_objects[i] == object)
			{
				m_objects[i]->connected_with.reset( (Spr*)NULL );
				m_objects.erase( m_objects.begin() + i);
			}
		}
	}*/
	void Spr::disconnect()
	{
		if(m_brain != NULL)
			m_brain->disconnect();
	}
	
	SpriteBrainPtr &Spr::connectedWith()
	{
		return m_brain;	
	}
	
/*	void Spr::thereIsCollision(boost::shared_ptr<Object> object, DRect recul)
	{
		m_position.x += recul.x;
		m_position.y += recul.y;
	}*/
	
	DVector2D &Spr::getPos()
	{
		return m_position;
	}
	
	void Spr::setPosition(DVector2D &new_pos)
	{
		m_vitesse = DRect(new_pos.x - m_position.x, new_pos.x - m_position.x);
		m_position = new_pos;
	}
	
	void Spr::setPosition(DVector2D new_pos)
	{
		m_vitesse = DRect(new_pos.x - m_position.x, new_pos.x - m_position.x);
		m_position = new_pos;
	}
	
	int Spr::width()
	{
	}
	
	int Spr::height()
	{
	}
	
	void Spr::draw(Surface ou_dessiner)
	{
		currentImage().apply(ou_dessiner, Rect<Decimal>(), m_position);
	}
	
	Surface Spr::currentImage()
	{
		return Surface();	
	}	
	
	
	/* ---------------- */
	/*  Classe Sprite  */
	/* ---------------- */
	Sprite::Sprite(std::string img_to_load, Rect<Decimal> initial_position) : Spr::Spr(initial_position)
	, m_image( SurfacePtr( new Surface(img_to_load), SurfaceDeleter() ) )
	{
		m_type.push_back(Spr::OneImageSprite);
	}
	
	Sprite::Sprite(const Sprite &sprite)
	{
		m_type = sprite.m_type;
		m_image = sprite.m_image;
	}
	
	Sprite::Sprite(SDL_Surface *img, Rect<Decimal> initial_position) : Spr::Spr(initial_position)
	, m_image( SurfacePtr( new Surface(img), SurfaceDeleter() ) )
	{
		m_type.push_back(Spr::OneImageSprite);
	}
	
	Sprite::~Sprite()
	{
		m_image.reset();
	}
	
	int Sprite::width()
	{
		if(m_image != NULL)
			return m_image->width();	
	}
	
	int Sprite::height()
	{
		if(m_image != NULL)
			return m_image->height();
	}
	
	void Sprite::draw(Surface ou_dessiner)
	{
		if(m_image != NULL)
		{
			m_image->apply(ou_dessiner, Rect<Decimal>(), m_position);
		}	
	}
	
	void Sprite::free()
	{
		m_image.reset();
	}
	
	void Sprite::load(string chemin)
	{
		m_image.reset( new Surface(chemin) );
	}
	
	void Sprite::load(SDL_Surface *img)
	{
		free();
		
		m_image.reset( new Surface(img) );
	}
	
	Surface Sprite::currentImage()
	{
		if(m_image != NULL)	
		{
			return *m_image;
		}
		else
			return Surface();
	}
}
