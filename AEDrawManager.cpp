#include "AEDrawManager.h"

using namespace std;
using namespace boost;

namespace AE
{
	DrawManager::DrawManager()
	{
	}
	
	DrawManager::~DrawManager()
	{
	}

	DrawManager& DrawManager::push( SprPtr to_add, int n_couche )
	{
		if(m_couches_sprites.size() < n_couche+1)
			m_couches_sprites.resize(n_couche+1);
		
		m_couches_sprites[n_couche].push_back(to_add);
		
		return *this;
	}
	
	DrawManager& DrawManager::push( int n_couche, void *to_add, ...)
	{
		if(m_couches_sprites.size() < n_couche+1)
			m_couches_sprites.resize(n_couche+1);
		
		va_list liste_sprites;
		va_start(liste_sprites, to_add);
		
		SprPtr* sprite;
		sprite = (SprPtr*) va_arg(liste_sprites, void*);
		
		while(sprite != NULL )
		{
			m_couches_sprites[n_couche].push_back( *sprite );
			
			sprite = (SprPtr*) va_arg(liste_sprites, void*);
		}
		
		return *this;
	}
	
	/*DrawManager& DrawManager::operator<<( SprPtr to_add, int n_couche)
	{
		if(m_couches_sprites.size() < n_couche+1)
			m_couches_sprites.resize(n_couche+1);
		
		m_couches_sprites[n_couche].push_back(to_add);
		
		return *this;
	}*/

	void DrawManager::popSprite( SprPtr to_remove )
	{
		if( !m_couches_sprites.empty() )
		{
			vector< vector<SprPtr> >::iterator couche;
			vector<SprPtr>::iterator sprite;
			
			for(int n_couche = 0; n_couche < m_couches_sprites.size(); n_couche++)
			{
				sprite = find( m_couches_sprites[n_couche].begin(), m_couches_sprites[n_couche].end(), to_remove); // On recherche dans chaque couche le sprite que l'utilisateur veut supprimer		
				
				if(sprite != m_couches_sprites[n_couche].end() )
					m_couches_sprites[n_couche].erase(sprite); // On enlève le sprite (to_remove) de la liste
			}
		}
	}
	
	void DrawManager::popSprite(int n_couche, int n_sprite)
	{
		if( !m_couches_sprites.empty() && n_couche < m_couches_sprites.size() )
		{
			if( n_sprite < m_couches_sprites[n_couche].size() )
				m_couches_sprites[n_couche].erase( m_couches_sprites[n_couche].begin() + n_sprite );
		}
	}

	void DrawManager::popCouche()
	{
		if(!m_couches_sprites.empty() )
			m_couches_sprites.pop_back(); // On enlève la dernière couche de Sprites
	}
	
	void DrawManager::popCouche(int n_couche)
	{
		if(!m_couches_sprites.empty() && n_couche < m_couches_sprites.size() )
			m_couches_sprites.erase( m_couches_sprites.begin() + n_couche ); // On enlève la couche de sprite numéro n_couche
	}

	void DrawManager::clear()
	{
		m_couches_sprites.clear();	
	}

	SprPtr DrawManager::getSprite(int n_couche, int n_sprite)
	{
		if(n_couche < m_couches_sprites.size() )
		{
			if(n_sprite < m_couches_sprites[n_couche].size() )
				return m_couches_sprites[n_couche][n_sprite];
			else
				return SprPtr( (Spr*)NULL ); // On retourne NULL car cette couche-là n'a pas autant de sprites que n_sprite :D
		}
		else
			return SprPtr( (Spr*)NULL ); // On retourne un pointeur NULL car le numéro de couche dépasse celui de la longueur de m_couches_sprites
	}
	
	vector<SprPtr> DrawManager::getCouche(int n_couche)
	{
		if(n_couche < m_couches_sprites.size() )
			return m_couches_sprites[n_couche];
		else
			return vector<SprPtr>(0);
	}
	
	/*SprPtr DrawManager::operator>>(int i)
	{
		if(i < m_couches_sprites.size() )
			return m_couches_sprites[i];
		else
			return SprPtr( (Spr*)NULL ); // On retourne un pointeur NULL car i dépasse la taille du vector m_sprites
	}*/

	void DrawManager::draw(Surface ou_dessiner)
	{
		if( !m_couches_sprites.empty() )
		{
			int i = 0;
			
			vector< vector<SprPtr> >::iterator couche = m_couches_sprites.begin();
	
			while(couche != m_couches_sprites.end() )
			{
				if( !m_couches_sprites[i].empty() )
				{
					vector<SprPtr>::iterator sprite = m_couches_sprites[i].begin();
				
					while(sprite != m_couches_sprites[i].end() )
					{
						(*sprite)->draw(ou_dessiner);
						sprite++;
					}
				}
				
				couche++;
				i++;
			}
		}
	}
}
