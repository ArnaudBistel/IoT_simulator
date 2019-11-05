#include "Server.h"

/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Server::Server(): nbrOfSensors(), consolActivation(true), logActivation(true)
{
  this->setActivations();
  this->printSettings();
}


Server::Server(Server const& server_p){
  clonage (server_p);
  return;
}


Server::Server(int nbrOfSensors, bool consolActivation, bool logActivation)
{
  this->nbrOfSensors      = nbrOfSensors;
  this->consolActivation  = consolActivation;
  this->logActivation     = logActivation;

  this->printSettings();
}


Server::Server(int nbrOfSensors) : nbrOfSensors(nbrOfSensors), consolActivation(true), logActivation(true)
{
  this->setActivations();
  this->printSettings();
}


Server::~Server(){}


Server& Server::operator=(const Server &server_p)
{
    if (this == &server_p) return *this;

    this->clonage (server_p);
    return *this;
}



// --------------------------------------
// ---------- autres methodes -----------
// --------------------------------------


// +++++++++++++++ PUBLIC +++++++++++++++

bool Server::operator==(Server& server_p)
{
    if (this->nbrOfSensors      == server_p.nbrOfSensors      &&
        this-> consolActivation == server_p.consolActivation  &&
        this->logActivation     == server_p.logActivation )
        return true;

    return false;
}



// -------------- PRIVATE ---------------

void Server::clonage (const Server &server_p)
{
    this->nbrOfSensors      = server_p.nbrOfSensors;
    this->consolActivation  = server_p.consolActivation;
    this->logActivation     = server_p.logActivation;
    return;
}


void Server::setActivations()
{
  int print_val;

  std::cout << std::endl;
  std::cout << "Print data into console (1), logs (2), both (3)?" << std::endl;
  std::cout << "Default prints in both console and logs."         << std::endl;
  std::cout << "Your choice (1, 2, 3) ?\t";

  std::cin >> print_val;
  std::cout << std::endl;

  switch (print_val)
  {
    case 1:
      this->logActivation     = false;
      break;

    case 2:
      this-> consolActivation = false;
      break;

    default:
      break;
  }
}


template <typename T> void Server::dataRcv(T dataSens_p, SensorType type) const
{
  if (this->logActivation)
  {
    this->fileWrite(dataSens_p, type);
  }

  if(this->consolActivation)
  {
    this->consoleWrite(dataSens_p, type);
  }
}
template void Server::dataRcv<int>(int, SensorType) const;
template void Server::dataRcv<float>(float, SensorType) const;
template void Server::dataRcv<bool>(bool, SensorType) const;




std::string Server::toString() const
{
  std::ostringstream ss;
  ss << (*this);
  return ss.str();
}


void Server::printSettings() const
{
    if (this->logActivation)
    {
      this->fileWrite();
    }

    if(this->consolActivation)
    {
      this->consoleWrite();
    }
}

// --------------------------------------
// ----- Affichage dans la console ------
// --------------------------------------

void Server::consoleWrite() const{
  if (this->consolActivation)
  {
    std::cout << this->toString();
  }
}


void Server::consoleWrite(std::ostream& stream) const
{
  if (this->consolActivation)
  {
    stream << this->toString();
  }
}



// --------------------------------------
// ------- Ecriture dans les logs -------
// --------------------------------------

void Server::fileWrite() const{
  if (this->logActivation)
  {
    std::string const file("./files/server.txt");
    std::ofstream stream(file.std::string::c_str(), std::ios::app);

    if (stream) {
      stream    << this->toString();
    }

    else {
      std::cout << "fileWrite: error.";
    }
  }
}


void Server::fileWrite(std::ofstream& stream) const{
  if (this->logActivation)
  {
    stream << this->toString();
  }
}



// --------------------------------------
// -- Surcharge des operateurs externes -
// --------------------------------------

std::ostream& operator<< (std::ostream& stream, Server const& server){
    stream << "Server initialized successfully" 	<< std::endl;
    stream << "Nb sensors : \t"       << server.nbrOfSensors     << "\t";
    stream << "Console display : \t"  << server.consolActivation << "\t";
    stream << "Log display : \t"      << server.logActivation    << "\t";
    stream << "\n";
    return stream;
}

std::ofstream& operator<< (std::ofstream& stream, Server const& server){
    stream << "Server initialized successfully" 	<< std::endl;
    stream << "Nb sensors : \t" 	    << server.nbrOfSensors     << "\t";
    stream << "Console display : \t"  << server.consolActivation << "\t";
    stream << "Log display : \t" 	    << server.logActivation    << "\t";
    stream << "\n";
    return stream;
}
