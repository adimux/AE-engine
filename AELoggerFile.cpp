/**
* \file LoggerFile.cpp
* \brief LoggerFile hérite de ILogger. LoggerFile écrit dans des fichiers
* \author Adam Cherti
* \version 0.1
* \date 9 Octobre 2010
*
* Log dans un fichier
*/
#include "AELoggerFile.h"

using namespace std;

namespace AE
{
	LoggerFile::LoggerFile(const std::string &filename) : m_file( filename.c_str(), /*ios::in |*/ ios::out | /*ios::app | */ios::trunc)
	{
		m_file << "---------------------------------------------------------------------------------" << endl;
		m_file << "-- AE 2D Engine v" << AE_LIB_VERSION << " - Event Log started the " << date() << " at " << time() << endl;
		m_file << "---------------------------------------------------------------------------------" << endl;
	}
		
	void LoggerFile::Write(const std::string &message)
	{
		if(message.empty() )
			return;
		if(*message.c_str() == endline)
			m_file << endl;
		else
			m_file << message;
	}
	
	LoggerFile::~LoggerFile()
	{
		m_file << "--------------------------------------------------------------------------------" << endl;
		m_file << "-- AE 2D Engine v" << AE_LIB_VERSION << " - Event Log closed the" << date() <<  " at " << time() << endl;
		m_file << "--------------------------------------------------------------------------------" << endl;
		
		m_file.close();	
	}
}
