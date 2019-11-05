#include "Scheduler.h"


/////////////////////////////////////////
// ----- forme canonique de Coplien -----
/////////////////////////////////////////

Scheduler::Scheduler(): server(), sensors(), print_times(), runTime()
{
  this->init();
  this->start();
}

Scheduler::Scheduler(Scheduler const& scheduler_p) : sensors(scheduler_p.sensors), server(scheduler_p.server), print_times(scheduler_p.print_times), runTime(scheduler_p.runTime)
{
  this->server->nbrOfSensors = this->sensors.size();
}


Scheduler::~Scheduler()
{
  /*
  for (std::vector<SensorPrototype*>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it)
  {
    delete *it;
  }*/
}


Scheduler& Scheduler::operator= (Scheduler const& scheduler_p)
{
  if (this != &scheduler_p) {
    this->clonage (scheduler_p);
  }
  return *this;
}



/////////////////////////////////////////
// ---------- autres methodes -----------
/////////////////////////////////////////


// --------------- PRIVATE --------------

void Scheduler::init()
{
  this->sensors.push_back( static_cast<SensorPrototype*> (new Temperature()) );
  this->sensors.push_back( static_cast<SensorPrototype*> (new Humidity()) );
  this->sensors.push_back( static_cast<SensorPrototype*> (new Light() ));
  this->sensors.push_back( static_cast<SensorPrototype*> (new Sound()) );

  this->register_print_times();
  this->setRunDuration();

  this->server = new Server (sensors.size());

  std::cout << "Scheduler initialized successfully" << std::endl;
  std::cout << sensors.size() << " sensors running..." << std::endl;
}


void Scheduler::register_print_times()
{
	int j = 0;
    for (std::vector<SensorPrototype*>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it)
    {
  		switch (j)
  		{

        case (int)SensorType::Temperature :
        {
            int print_time = this->askPrintTime(SensorType::Temperature);
            this->print_times.push_back(print_time);
            break;
        }

        case (int)SensorType::Humidity :
        {
            int print_time = this->askPrintTime(SensorType::Humidity);
            this->print_times.push_back(print_time);
            break;
        }

        case (int)SensorType::Light :
        {
            int print_time = this->askPrintTime(SensorType::Light);
            this->print_times.push_back(print_time);
            break;
        }

        case (int)SensorType::Sound :
        {
            int print_time = this->askPrintTime(SensorType::Sound);
            this->print_times.push_back(print_time);
            break;
        }

        default:
        {
          break;
        }
  		}
		++j;
  }
}


void Scheduler::setRunDuration()
{
  std::cout << std::endl;
  std::cout << "How long do you want to run the app ?"  << std::endl;
  std::cout << "Default 60 seconds."                    << std::endl;
  std::cout << "Your choice in seconds ?\t";

  this->runTime = (this->integerInput(60));

  std::cout << std::endl;
}


int Scheduler::askPrintTime(SensorType type)
{
    std::cout << std::endl;
    std::cout << "Time gap between each print for " << type << " ?" << std::endl;
    std::cout << "Default 5 seconds."                               << std::endl;
    std::cout << "Your choice in seconds ?\t";

    int ret (this->integerInput(5));

    std::cout << std::endl;
    return ret;
}


int Scheduler::integerInput(int default_val)
{
  int ret(default_val);
  std::cin >> ret;

  // vérifie que l'utilsiateur entre bien un integer
  while(std::cin.fail()) {
      std::cout << "Error" << std::endl;
      std::cin.clear();
      std::cin.ignore(256,'\n');
      std::cin >> ret;
  }
  return ret;
}



void Scheduler::start()
{
  std::cout << "\nBegin transmission." << std::endl;


  // linux version
  struct timespec begin, now;
  clock_gettime(CLOCK_MONOTONIC, &begin);
  int elapsed_secs = 0;
  std::cout << "-----------------------------------" << std::endl;

  while (true && (elapsed_secs < this->runTime))
  {
  // linux version
  std::this_thread::sleep_for(std::chrono::seconds(1));
  clock_gettime(CLOCK_MONOTONIC, &now);
  elapsed_secs = (now.tv_sec - begin.tv_sec);
  elapsed_secs += (int)(now.tv_nsec - begin.tv_nsec) / 1000000000.0;


  // windows version
  /*clock_t begin = clock();
  int elapsed_secs = 0;

  while (true && (elapsed_secs < this->runTime))
  {

  std::this_thread::sleep_for(std::chrono::seconds(1));

  clock_t now = clock();
  elapsed_secs = int(now - begin) / CLOCKS_PER_SEC;
  */

	int j = 0;
  for (std::vector<SensorPrototype*>::iterator it = this->sensors.begin(); it != this->sensors.end(); ++it)
  {
  		switch (j)
  		{

        case (int)SensorType::Temperature :
        {
          if ( elapsed_secs%print_times[ (int)SensorType::Temperature ] == 0)
          {
            Temperature* temp =  static_cast<Temperature*> (*it);
		        this->server->dataRcv((float)temp->sendData(), SensorType::Temperature);
            temp->generateNewVal();
          }
          break;
        }

        case (int)SensorType::Humidity :
        {
          if ( elapsed_secs%print_times[ (int)SensorType::Humidity ] == 0)
          {
            Humidity* hum =  static_cast<Humidity*> (*it);
		        this->server->dataRcv((float)hum->sendData(), SensorType::Humidity);
            hum->generateNewVal();
          }
          break;
        }

        case (int)SensorType::Light :
        {
          if ( elapsed_secs%print_times[ (int)SensorType::Light ] == 0)
          {
            Light* light =  static_cast<Light*> (*it);
		        this->server->dataRcv((bool)light->sendData(), SensorType::Light);
            light->generateNewVal();
          }
          break;
        }

        case  (int)SensorType::Sound :
        {
          if ( elapsed_secs%print_times[ (int)SensorType::Sound ] == 0)
          {
            Sound* sound =  static_cast<Sound*> (*it);
		        this->server->dataRcv((int)sound->sendData(), SensorType::Sound);
            sound->generateNewVal();
          }
          break;
        }

        default:
        {
          break;
        }
  		}

		++j;
    }

    std::cout << "-----------------------------------" << std::endl;
   }

   this->stop();
}




void Scheduler::stop()
{
  std::cout << "End of transmission.\n";

  std::cout << std::endl << std::endl;
  std::cout << "*************************************************" << std::endl;
  std::cout << "******************** SEE YOU! *******************" << std::endl;
  std::cout << "*************************************************" << std::endl;
}



void Scheduler::clonage ( const Scheduler& scheduler_p)
{
    this->sensors       = scheduler_p.sensors;
    this->server        = scheduler_p.server;
    this->print_times   = scheduler_p.print_times;
    this->runTime       = scheduler_p.runTime;
	  return;
}
