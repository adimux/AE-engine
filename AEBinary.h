#ifndef AE_FLAG_CLASS
#define AE_FLAG_CLASS

#include <iostream>

namespace AE
{
	/*typedef enum Endianess
	{
		Little_endian,
		Big_endian,
		Middle_endian
	} BitsOrder;

	typedef enum Bits_Order
	{
		Big_head,
		Little_head
	} Bits_Order;*/

	union TestEndian
	{
		unsigned long total;

		struct
		{
			unsigned char octet1;
			unsigned char octet2;
			unsigned char octet3;
			unsigned char octet4;
		} octets;
	};
	
	class Architecture
	{
		public:
			static void Init();
		/*	*------------------------------------------------------*
			| Fonctions pour savoir l'architecture de l'ordinateur |
			*------------------------------------------------------*  */
			static int BitOrder();
			static int ByteOrder();
			
		private:
			static int s_BitOrder;
			static int s_ByteOrder;
			
		public:
			static int Little_endian;
			static int Big_endian;
			static int Middle_endian;
			
			static int Big_head;
			static int Little_head;	
	};
	
	class BinUtils
	{
		public:			
		/*	*--------------------------------------------------------------*
			| Fonctions de Conversion Binaire->Décimal et Décimal->Binaire |
			*--------------------------------------------------------------*  */
			template<class T>
			static T toDecimal(std::string &binaire, int length=-1)
			{
				if(length == -1)
					length = binaire.length();
					
				int i = 0;
				T resultat = 0; // Le résultat
		
				for(i = 0; i < length; i++)
				{
					if(binaire[i] == '0')
						resultat = resultat * 2 + 0;
					else if(binaire[i] == '1')
						resultat = resultat * 2 + 1;
				}
		
				return resultat;
			}
			
			template<class T>
			static T toDecimal(char* binaire, int length=-1)
			{
				if(length == -1)
					length = strlen(binaire);
				
				int i = 0;
				T resultat = 0; // Le résultat
		
				for(i = 0; i < length; i++)
				{
					if(binaire[i] == '0')
						resultat = resultat * 2 + 0;
					else if(binaire[i] == '1')
						resultat = resultat * 2 + 1;
				}
		
				return resultat;
			}
			
			template<class T>
			static char* toBinary(T decimal)
			{
				char *binaire = new char[ sizeof(T) * 8 + 1 ];
				binaire[ sizeof(T) * 8 ] = '\0';
				
				for(int i = 0; i < sizeof(T) * 8; i++)
				{
					
				}
			}
			/*static int toInt(string binaire, int length=-1);
			static int toInt(char *binaire, int length=-1);
		
			static short toShort(string binaire, int length=-1);
			static short toShort(char *binaire, int length=-1);
		
			static char toChar(string binaire, int length=-1);
			static char toChar(char *binaire, int length=-1);*/
			
			/* ------------------------------------------------ */
			/*  Fonctions de reversement des bits et des bytes  */
			/* ------------------------------------------------ */
			
			/** Cette fonction inverse l'ordre des bits des int, short, char etc... */
			template<class T>
			static T BitReverse(const T in)
			{
				T out = 0;
				int n = 0;
	
				while(1)
				{
					out |= in&0x01; // Copie du bit de poids faible   
					n++; // Compter les bits copiés   
		
					if(n >= sizeof(T)*CHAR_BIT ) // Si tous les bits sont traités...
						break; // ...arrêter
		
					in >>= 1; // Vider vers la droite (préparer le suivant)...   
					out <<= 1; // ...pour remplir vers la gauche (préparer la place)   
				}
		
				return out;
			}
			
			/** Celle-ci inverse l'ordre des bytes dans les int, short, long etc... */
			template<class T>
			T ByteReverse(const T in)
			{
				T out;
				
				const char *pin = (const char*) &in;
				char *pout = (char*)(&out+1)-1;
				
				int i;
	
				for(i = sizeof(T); i > 0 ; --i)
				{
					*pout-- = *pin++;
				}
	
				return out;
			}
	};
	
	class Binary
	{
		public:
			Binary(void);
			
			template<class T>
			Binary(T);
			
			Binary(char*);
			Binary(std::string &);
			
			template<class T>
			operator T()
			{
				return (T)BinUtils::toDecimal(m_binary.c_str() );
			}
			
			template<class T>
			T toDecimal()
			{
				return (T)BinUtils::toDecimal(m_binary.c_str() );
			}
			
			char *getBinary();
			
		private:
			std::string m_binary;
	};
}

#endif
