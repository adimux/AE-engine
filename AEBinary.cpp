#include "AEBinary.h"

namespace AE
{
	int Architecture::Big_endian = 1;
	int Architecture::Little_endian = -1;
	int Architecture::Middle_endian = 0;

	int Architecture::Big_head = 2;
	int Architecture::Little_head = -2;
	
	int Architecture::s_BitOrder = 100; // Le nombre 100 signifie : pas encore vérifié (pour savoir l'architecture de l'ordinateur, il faut appeller la fonctin Architecture::Init() )
	int Architecture::s_ByteOrder = 100;

	void Architecture::Init()
	{
		char test = 1;
	
		if( (test << 1) == 0)
			Architecture::s_BitOrder = Architecture::Big_head;
		else
			Architecture::s_BitOrder = Architecture::Little_head;
	
		union TestEndian te;
	
		te.total = 0xFF;

		if (te.octets.octet1 == 0xFF)
		{
			Architecture::s_ByteOrder = Architecture::Little_endian;
		}
		else
		{
			Architecture::s_ByteOrder = Architecture::Big_endian;
		}
	}

	int Architecture::BitOrder()
	{
		return Architecture::s_BitOrder;
	}

	int Architecture::ByteOrder()
	{
		return Architecture::s_ByteOrder;
	}
	
/*	*-------------------*
	| La classe Binary  |
	*-------------------*	*/
	Binary::Binary(void) : m_binary(NULL)
	{
	}
	
	Binary::Binary(char *binary) : m_binary(binary)
	{
	}
	
	Binary::Binary(std::string &binary) : m_binary(binary)
	{
	}
	
	char* Binary::getBinary()
	{
		return (char*)m_binary.c_str();
	}
}
