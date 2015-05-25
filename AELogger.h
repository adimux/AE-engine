/**
* \file ILogger.h
* \brief Logger est une classe abstraite. C'est un gestionnaire de log
* \author Adam Cherti
* \version 0.1
* \date 9 Octobre 2010
*
* Gestionnaire de Log
*/
#ifndef AE_ILOGGER_CLASS
#define AE_ILOGGER_CLASS

#include <iostream>
#include <cstdarg>
#include <sstream>
#include "AEDll.h"

namespace AE
{
	class Logger
	{
		public:
			/** Destructeur */
			virtual ~Logger();
			
			static const Logger* getLogger();

			/** Change l'instance du logger */
		    static void SetLogger(Logger* logger);

		    /** Log un message (façon C) */
		    static void Log(const char* format, ...);
		    
		    /** Retourne la date d'aujourd'hui */
		    static std::string date();
		    /** Retourne l'heure actuelle */
		    static std::string time();

		    /** Log un message (façon C++) */
	    	static Logger& Log();
	    	template <class T>
			Logger& operator <<(const T& toLog);
	
	
			static char endline;
		private:
		    /** Inscrit un message - à redéfinir dans les classes dérivées */
	    	virtual void Write(const std::string& message) = 0;

	    	/** Pointeur sur le logger actuel */
    		static Logger* m_instance;
	};

	template <class T>
	Logger& Logger::operator <<(const T& toLog)
	{
	    std::ostringstream stream;
		stream << toLog;
		Write( stream.str() );

		// On n'oublie pas de toujours renvoyer notre instance, pour pouvoir chaîner les appels à <<
		return Log();
	}
} // namespace AE

#endif
