#ifndef AE_ABSTRACT_CLASSWITHTYPE
#define AE_ABSTRACT_CLASSWITHTYPE

#include <iostream>
#include <vector>
#include "AETypes.h"

namespace AE
{
	class ClassWithType
	{
		public:
			virtual bool isType(Type);
			virtual bool operator==(Type);
			virtual bool operator!=(Type);
		
		protected:
			/** Vous vous demandez s�rement pourquoi la type se stocke-t-il dans un tableau de int.
			* Quand une classe est d�riv�e de celle-ci, le type de la classe fille est reconnaissable par ce vector.
			* Exemple : Une classe "Personnage" est d�riv�e de ClassWithType, ce vector sera par exemple {1}
			* (si 1 est l'identifiant qu'on a choisi pour d�signer la classe Personnage). Une autre classe d�riv�e de Personnage qu'on appellera 
			* "Magicien" aura le vector m_type par ex {1, 4} (4 est l'identifiant qu'on a donn� � la classe Magicien
			* En gros, m_type est comme l'arbre g�n�alogique de chaque objet pour savoir qui est sa m�re (classe m�re), sa grand-m�re,
			* son arri�re grand-m�re (qui sont toutes des classes bien s�r :D) s*/
			std::vector< Type > m_type;	
	};
}

#endif
