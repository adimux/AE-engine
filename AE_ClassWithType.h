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
			/** Vous vous demandez sûrement pourquoi la type se stocke-t-il dans un tableau de int.
			* Quand une classe est dérivée de celle-ci, le type de la classe fille est reconnaissable par ce vector.
			* Exemple : Une classe "Personnage" est dérivée de ClassWithType, ce vector sera par exemple {1}
			* (si 1 est l'identifiant qu'on a choisi pour désigner la classe Personnage). Une autre classe dérivée de Personnage qu'on appellera 
			* "Magicien" aura le vector m_type par ex {1, 4} (4 est l'identifiant qu'on a donné à la classe Magicien
			* En gros, m_type est comme l'arbre généalogique de chaque objet pour savoir qui est sa mère (classe mère), sa grand-mère,
			* son arrière grand-mère (qui sont toutes des classes bien sûr :D) s*/
			std::vector< Type > m_type;	
	};
}

#endif
