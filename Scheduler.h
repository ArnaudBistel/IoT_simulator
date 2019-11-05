#ifndef DEF_SCHEDULER
#define DEF_SCHEDULER

#include <iostream>
#include <ctime>
#include <vector>
#include <iterator>
#include <chrono>
#include <thread>

#include "SensorPrototype.h"
#include "Server.h"
#include "Temperature.h"
#include "Light.h"
#include "Humidity.h"
#include "Sound.h"
#include "Sensor.h"


class Scheduler
{
  public:
      // ----- forme canonique de Coplien -----
      Scheduler();
      Scheduler(Scheduler const& scheduler_p);
      virtual ~Scheduler();
      Scheduler& operator= (Scheduler const& scheduler_p);

    private:
      // ------------- attributs --------------
  		  Server *server;
  		  std::vector <SensorPrototype*> sensors;
  		  std::vector <int> print_times;
        int runTime;


        // ---------- autres methodes -----------
        void init();
        void register_print_times();
        void setRunDuration();
        int askPrintTime(SensorType type);
        int integerInput(int default_val);
        void start();
        void stop();
	      void clonage(const Scheduler& scheduler_p);
};

#endif
