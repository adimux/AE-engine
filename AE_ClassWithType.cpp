#include "AE_ClassWithType.h"

using namespace std;

namespace AE
{
	bool ClassWithType::isType(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
			
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return true;	
		}
		
		return false;	
	}

	bool ClassWithType::operator==(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
		
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return true;	
		}
		
		return false;
	}

	bool ClassWithType::operator!=(Type type_of_spr)
	{
		vector<Type>::iterator i = m_type.begin();
		
		for(; i != m_type.end(); i++)
		{
			if(*i == type_of_spr)
				return false;
		}
		
		return true;
	}
}
