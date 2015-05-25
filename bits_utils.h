#ifndef AE_BITS_UTILS_H
#define AE_BITS_UTILS_H

#include <iostream>
#include "AELogger.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdlib.h>
#include <limits.h>
#include <stdint.h>
#include <math.h>

namespace AE
{
	typedef unsigned int Uint;
	typedef unsigned char Uchar;
	typedef unsigned short Ushort;

	typedef enum ENDIANESS
	{
		Little_endian,
		Big_endian,
		Middle_endian
	} ENDIANESS;

	typedef enum ORDRE_BITS
	{
		Big_head,
		Little_head
	} ORDRE_BITS;

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

	static ENDIANESS BitOrder;
	static ENDIANESS ByteOrder;

	ENDIANESS bit_order();
	ENDIANESS byte_order();

	#define BIT_ORDER BitOrder

	void PrintBinary(int x, int d);
	void initBitsUtils();

	Uchar BitReverseUchar(const Uchar in);
	int ByteReverseInt(const int in);
	int BitReverseInt(const int in);

	int bin_to_dec(char *binaire, int taille);

	int puissance(int nombre, int nombre_de_fois);

	Uchar extract_bits_from_byte(Uchar octet, Uchar pos, Uchar nb_bits);

	int extract_bits(Uchar *buffer, Uint pos, Uchar nb_bits);
}

#endif
