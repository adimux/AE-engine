/**
* \file AEDrawManager.h
* \brief DrawManager est une classe qui a une liste de sprites contenus dans std::vector. Cette classe affiche tous les sprites en m�me temps au moment o� on appelle la fonction draw
* \author Adam Cherti
* \version 0.1
* \date 29 Octobre 2010
*
* Classe qui manage les sprites dessin
*/
#ifndef AE_DRAWMANAGER_CLASS
#define AE_DRAWMANAGER_CLASS

#include <iostream>
#include <boost/shared_ptr.hpp>
#include "AEBasic.h"
#include "AESprite.h"

namespace AE
{
	class DrawManager
	{
		public:
			DrawManager();
			~DrawManager();
			
			/** Ajouter un sprite dans la couche voulue */
			DrawManager& push( SprPtr, int n_couche);
			/** Ajoute plusieurs sprites dans la couche n_couche */
			DrawManager& push( int n_couche, void *, ...);
			/** Ajoute plusieurs sprites contenus dans un std::vector dans la couche n_couche */
			DrawManager& push( int n_couche, std::vector<SprPtr> );
			
			/** Cherche dans toutes les couches le pointeur de Sprite indiqu� pour pouvoir le supprimer */
			void popSprite( SprPtr );
			/** Enl�ve le sprite n_sprite de la couche n_couche */
			void popSprite( int n_couche, int n_sprite);
			
			/** Retourne la couche de sprites num�ro n_couche */
			std::vector<SprPtr> getCouche(int n_couche);
			/** Supprime la derni�re couche de sprites */
			void popCouche();
			/** Supprime la couche num�ro n_couche de sprites */
			void popCouche(int n_couche);
			
			void clear();
			
			/** Pour get un sprite num�ro n de la couche x */
			SprPtr getSprite(int n_couche, int n_sprite);
			
			/** Dessine tout les Sprites dans une surface */
			void draw(Surface);
			
		
		protected:
			/** Un tableau 2D de sprites car parfois, on veut dessiner un sprite avant l'autre. Ou m�me plusieurs sprites avant d'autres sprites.
			* On parle ici de couches de sprites, c'est pourquoi c'est un tableau 2D
			* PS : La premi�re couche qui va est dessin�e est la couche num�ro 0 */
			std::vector< std::vector<SprPtr> > m_couches_sprites;
	};	
}

#endif
