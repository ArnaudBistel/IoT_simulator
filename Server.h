#ifndef DEF_SERVER
#define DEF_SERVER

#include <string>
#include <iostream>
#include <fstream>
#include <chrono>
#include <ctime>
#include <sstream>

#include "SensorType.h"

class Server{

	public:
  	// ----- forme canonique de Coplien -----
  	Server	();
		Server	(Server const& server_p);
		Server	(int nbrOfSensors, bool consolActivation, bool logActivation);
		Server	(int nbrOfSensors);
		virtual ~Server();
		Server& operator=(const Server &server_p);


		// ---------- autres methodes -----------
		bool operator==(Server &server_p);

	private:
		// ------------- attributs --------------
		unsigned int 	nbrOfSensors;
		bool 					consolActivation;
		bool 					logActivation;


		// ------------- methodes ---------------
		void clonage (const Server &server_p);
		void setActivations();

		template <typename T> void dataRcv(T dataSens_p, SensorType type) const;

		// ------- methodes d'affichage ---------
		std::string toString() const;
		void printSettings() const;

		void consoleWrite() const ;
		void consoleWrite(std::ostream& stream) const;
		template <typename T> void consoleWrite(T dataSens_p, SensorType type) const;

		void fileWrite() const;
		void fileWrite(std::ofstream& stream) const;
		template <typename T> void fileWrite(T dataSens_p, SensorType type) const;


		// -------------- Friends ---------------
		friend class Scheduler;
		friend std::ostream& operator<<(std::ostream& stream, Server const& server_p);
		friend std::ofstream& operator<<(std::ofstream& stream, Server const& server_p);
};


// -------- méthodes non-membres --------
inline std::ostream& operator<<(std::ostream& stream, Server const& server_p);
std::ofstream& operator<<(std::ofstream& stream, Server const& server_p);


// -------- templates méthodes ----------
template <typename T> void Server::consoleWrite(T dataSens_p, SensorType type) const
{
  if (this->consolActivation)
  {
		auto end = std::chrono::system_clock::now();
		std::time_t end_time = std::chrono::system_clock::to_time_t(end);
		std::cout << std::ctime(&end_time) << "\t" ;

		std::cout << type << " : "  << dataSens_p << std::endl;
  }
}



template <typename T> void Server::fileWrite(T dataSens_p, SensorType type)const
{
	std::string file;
  if (this->logActivation)
  {
		switch (type)
		{
			case SensorType::Temperature :
			{
				file = ("./files/temperatures.txt");
				break;
			}
			case SensorType::Humidity :
			{
				file = ("./files/humidity.txt");
				break;
			}
			case SensorType::Light :
			{
				file = ("./files/light.txt");
				break;
			}
			case SensorType::Sound :
			{
				file = ("./files/sound.txt");
				break;
			}
			default:
				file = ("./files/log.txt");
		}

    std::ofstream stream(file.std::string::c_str(), std::ios::app);

    if (stream) {
				auto end = std::chrono::system_clock::now();
				std::time_t end_time = std::chrono::system_clock::to_time_t(end);
				stream << std::ctime(&end_time) << "\t" ;
				
				stream << type << " : "  << dataSens_p << std::endl;
				stream.close();
    } else {
      	std::cout << "fileWrite: error.";
    }
  }
}

#endif
