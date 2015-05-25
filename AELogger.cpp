/**
* \file ILogger.cpp
* \brief ILogger est une classe abstraite. C'est un gestionnaire de log
* \author Adam Cherti
* \version 0.1
* \date 9 Octobre 2010
*
* Gestionnaire de Log
*/
#include "AELogger.h"

using namespace std;

// ------------------ //
// Begin Namespace AE //
// ------------------ //
namespace AE
{
	Logger* Logger::m_instance = NULL;
	char Logger::endline = '\n';

	Logger::~Logger()
	{
		delete m_instance;
	}
	
	const Logger* Logger::getLogger()
	{
		return m_instance;	
	}

	void Logger::SetLogger(Logger *logger)
	{
		m_instance = logger;	
	}
	
	void Logger::Log(const char* format, ...)
	{
    	// Formatage du message dans une chaîne de caractères
	    char resultat[512];
    	va_list params;
	    va_start(params, format);
    	vsprintf(resultat, format, params); // vsprintf retourne le résultat dans une variable donnée (ici resultat)
	    va_end(params);
    
    	m_instance->Write(resultat);
	}
	
	string Logger::date()
	{
		char dateStr [9];
		_strdate(dateStr);
		
		return string(dateStr);
	}

	string Logger::time()
	{
		char timeStr [9];
		_strtime(timeStr);
		
		return string(timeStr);
	}

	Logger& Logger::Log()
	{
		return *m_instance;	
	}
}
//-------------------- //
// END OF namespace AE //
// ------------------- //
