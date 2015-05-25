#include "bits_utils.h"

namespace AE
{
	void initBitsUtils()
	{
		BitOrder = bit_order();
		ByteOrder = byte_order();
	}

	ENDIANESS bit_order()
	{
		char test = 1;
	
		if( (test << 1) == 0)
			return Big_endian;
	
		return Little_endian;
	}

	ENDIANESS byte_order()
	{
		/*int test = 1;
		char *en_char = (char*) malloc( sizeof(char)*sizeof(int) );

		memcpy(en_char, &test, sizeof(int) );

		if (en_char[0] != 0)
			return Little_endian;
		else
			return Big_endian;*/
		union TestEndian te;

		te.total = 0xFF;

		if (te.octets.octet1 == 0xFF)
		{
			return Little_endian;
		}
		else
		{
			return Big_endian;
		}
	}

	void PrintBinary(int x, int d)
	{
		char buffer[33];
		int index;
		index = 0;
	
		while(d > 0)
		{
			if (x & 1)
				buffer[index++] = '1';
			else
				buffer[index++]='0';
			
			x >>= 1;
			d--;
		}
	
		while(index > 0)
		{
			if(index % 8 == 0 && index != 0)
				Logger::Log() << " ";
			
//			printf("%c", buffer[--index] );
			Logger::Log() << buffer[--index];
		}
		
		Logger::Log() << Logger::endline;
		
		return;
	}

	Uchar extract_bits_from_byte(Uchar octet, Uchar pos, Uchar nb_bits)
	{
		Uchar resultat;
	
		if(nb_bits + pos > CHAR_BIT)
			nb_bits = CHAR_BIT - pos;

		if(BIT_ORDER == Big_endian)
			octet = BitReverseUchar(octet);
	
		resultat = ( (octet << pos));
		resultat = resultat >> (CHAR_BIT - nb_bits);
	
		if(BIT_ORDER == Big_endian)
			resultat = BitReverseUchar(resultat);
	
		return resultat;
	}

	int puissance(int nombre, int nombre_de_fois)
	{
		int resultat = nombre;
	
		if(nombre_de_fois == 1)
			return resultat;
		if(nombre_de_fois == 0)
			return 1;

		int i;

		for(i = 0; i < nombre_de_fois-1; i++)
			resultat *= nombre;

		return resultat;
	}

	int extract_bits(Uchar *buffer, Uint pos, Uchar nb_bits) // Extrait les bits depuis un buffer en indiquant la position et le nombre de bits (exemple
															 // Un tableau de Uchar dont la taille est 3 [00110111] [01001110] [00001110], on veut extraire 111100 qui est en position 12 et son nombre de bits est 6
	{
		// Nous allons commencer par copier les octets concernant le byte (ensemble de bits) qu'on veut extraire
		int first_octet = pos / (CHAR_BIT * sizeof(char) ); // L'index du premier octet (position)
//cout << endl << "NB_BITS : " << (int)nb_bits << endl;
		int nb_octets = ceil( (float)( ( (int)pos % (int)CHAR_BIT ) + nb_bits) / (float)CHAR_BIT ); // Le nombre d'octets
//cout << "First octet : " << first_octet << " NB octets : " << nb_octets << endl;
	
/*	Uchar *partie = (Uchar*) malloc(sizeof(Uchar) * nb_octets);
	memset(partie, (Uchar)0, nb_octets);

	int i;
//printf("**********\n");
	for(i = 0; i < nb_octets; i++)
	{
		partie[i] = buffer[first_octet+i];
//PrintBinary( partie[i], 8);
//printf("\n");
	}
//printf("**********\n");
	*/
		int resultat = 0;
		int i = 0;

		if(nb_octets > sizeof(int) ) // Si on demande à extraire plus d'octets que la taille du int...
			nb_octets = sizeof(int); // On met nb_octets à la taille d'un int puisque c'est le maximum
	
		memcpy(&resultat, buffer+first_octet, nb_octets);
//printf("*****\n");
//PrintBinary(resultat, 8*4);
//printf("\n*****\n");

//PrintBinary(resultat, 8*4);
		if(ByteOrder == Little_endian)
			resultat = ByteReverseInt(resultat) >> ( sizeof(int) - nb_octets )*CHAR_BIT;

//cout << "FOlel ";PrintBinary(resultat, 8*4);cout << endl;
		resultat = resultat >> (nb_octets*CHAR_BIT - nb_bits - pos%CHAR_BIT);

	
		char *masque = (char*) malloc( sizeof(char)*sizeof(int)*CHAR_BIT+1 );
	
		for(i = 0; i < sizeof(int)*CHAR_BIT; i++)
			masque[i] = '0';
	
		masque[sizeof(int)*CHAR_BIT] = '\0';
		
		for(i = 0; i < sizeof(int)*CHAR_BIT; i++)
		{
			if(i >= sizeof(int)*CHAR_BIT - nb_bits)
				masque[i] = '1';
			else
				masque[i] = '0';
		}
	
		masque[sizeof(int)*CHAR_BIT] = '\0';
		//printf("%s\n\n", masque);
		resultat = resultat & bin_to_dec(masque, sizeof(int)*CHAR_BIT );
		//PrintBinary(resultat, 8*4);

		//if(BIT_ORDER == Big_endian)
		//	resultat = BitReverseInt(resultat);
		
		return resultat;
	}

	int bin_to_dec(char *binaire, int taille) // On donne une chaine de caractères représentant un nombre binaire pour en faire un nombre décimal
	{
		int i = 0;
		int resultat = 0; // Le résultat

		for(i = 0; i < taille; i++)
		{
			if(binaire[i] == '0')
				resultat = resultat * 2 + 0;
			else if(binaire[i] == '1')
				resultat = resultat * 2 + 1;
		}
		
		return resultat;
	}

	//Inverse l'ordre des bits dans un unsigned char
	Uchar BitReverseUchar(Uchar in)
	{
		Uchar out = 0;
		int n = 0;
	
		while(1)
		{
			out|= in&0x01 ; // Copie du bit de poids faible   
			n++;           // Compter les bits copiés   
			
			if(n >= sizeof(Uchar)*CHAR_BIT )    // Si tous les bits sont traités...
				break ;       // ...arrêter
			
			in >>= 1;      // Vider vers la droite (préparer le suivant)...   
			out <<= 1;      // ...pour remplir vers la gauche (préparer la place)   
		}
		
		return out;
	}

	//Inverse l'ordre des octets dans un int
	int ByteReverseInt(const int in)
	{
		int out;
		const char *pin = (const char*) &in;
		char *pout = (char*)(&out+1)-1 ;
		int i;
	
		for( i = sizeof(int); i > 0 ; --i)
		{
			*pout-- = *pin++;
		}
	
		return out;
	}

	//Inverse l'ordre des bits d'un int
	int BitReverseInt(int in)
	{
		int out = 0;
		int n = 0;
	
		while(1)
		{
			out |= in&0x01; // Copie du bit de poids faible   
			n++; // Compter les bits copiés   
		
			if(n >= sizeof(int)*CHAR_BIT ) // Si tous les bits sont traités...
				break; // ...arrêter
		
			in >>= 1; // Vider vers la droite (préparer le suivant)...   
			out <<= 1; // ...pour remplir vers la gauche (préparer la place)   
		}
		
		return out;
	}
	
	//Inverse l'ordre des bits d'un short
	int BitReverseShort(short in)
	{
		short out = 0;
		int n = 0;
	
		while(1)
		{
			out |= in&0x01; // Copie du bit de poids faible   
			n++; // Compter les bits copiés   
		
			if(n >= sizeof(short)*CHAR_BIT ) // Si tous les bits sont traités...
				break; // ...arrêter
		
			in >>= 1; // Vider vers la droite (préparer le suivant)...   
			out <<= 1; // ...pour remplir vers la gauche (préparer la place)   
		}
		
		return out;
	}
}
