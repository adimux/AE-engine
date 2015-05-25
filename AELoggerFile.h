#ifndef AE_LOGGERFILE_CLASS
#define AE_LOGGERFILE_CLASS

/**
* \file LoggerFile.h
* \brief LoggerFile hérite de ILogger. LoggerFile écrit dans des fichiers
* \author Adam Cherti
* \version 0.1
* \date 9 Octobre 2010
*
* Log dans un fichier
*/

#include <iostream>
#include <fstream>
#include "AELogger.h"
#include "AEDefines.h"

namespace AE
{
	class LoggerFile : public Logger
	{
		public:
			/** Constructeur */
			LoggerFile(const std::string &filename = "Output.log");
			~LoggerFile();
		
		private:
			/** Ecrit dans le Log file */
			virtual void Write(const std::string &message);
		
			/** Log file */
			std::ofstream m_file;
	};
}

#endif
