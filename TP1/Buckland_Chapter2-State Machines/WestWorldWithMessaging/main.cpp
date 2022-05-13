#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"
#include <thread>


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //seed random number generator
  srand((unsigned) time(NULL));

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);

  auto f_bob = [](Miner* Bob) {
      for (int i = 0; i < 30; ++i) {
          Bob->Update();
          Sleep(800);
      }
  };

  auto f_elsa = [](MinersWife* Elsa) {
      for (int i = 0; i < 30; ++i) {
          Elsa->Update();
          Sleep(800);
      }
  };

  auto f_message = []() {
      for (int i = 0; i < 30; ++i) {
          Dispatch->DispatchDelayedMessages();
          Sleep(800);
      }
  };

  std::thread t_bob(f_bob, Bob);

  Sleep(100);

  std::thread t_elsa(f_elsa, Elsa);

  Sleep(100);

  std::thread t_message(f_message);

  //run Bob and Elsa through a few Update calls
  //for (int i=0; i<30; ++i)
  //{ 
  //  

  //  

  //  
  //  Bob->Update();
  //  Elsa->Update();

  //  

  //  //dispatch any delayed messages
  //  Dispatch->DispatchDelayedMessages();

  //  Sleep(800);
  //}

  t_bob.join();
  t_elsa.join();
  t_message.join();

  //tidy up
  delete Bob;
  delete Elsa;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






