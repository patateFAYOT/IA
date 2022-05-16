#include <fstream>
#include <time.h>
#include <thread>
#include "Locations.h"
#include "Miner.h"
#include "Drunk.h"
#include "MinersWife.h"
#include "EntityManager.h"
#include "MessageDispatcher.h"
#include "misc/ConsoleUtils.h"
#include "EntityNames.h"


std::ofstream os;

int main()
{
//define this to send output to a text file (see locations.h)
#ifdef TEXTOUTPUT
  os.open("output.txt");
#endif

  //create a miner
  Miner* Bob = new Miner(ent_Miner_Bob);

  //create his wife
  MinersWife* Elsa = new MinersWife(ent_Elsa);

  //create a drunk
  Drunk* Drunkard = new Drunk(ent_Roger);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Drunkard);
  //seed random number generator
  srand((unsigned) time(NULL));

  //threads
  auto FunctionBob = [](Miner* Bob)
  {
      for (int i = 0; i < 30; ++i) {
          Bob->Update();
          Sleep(800);
      }
  };

  auto FunctionElsa = [](MinersWife* Elsa)
  {
      for (int i = 0; i < 30; ++i) {
          Elsa->Update();
          Sleep(800);
      }
  };

  auto FunctionDrunkard = [](Drunk* Drunkard)
  {
      for (int i = 0; i < 30; ++i) {
          Drunkard->Update();
          Sleep(800);
      }
  };

  auto FunctionMessage = []()
  {
      for (int i = 0; i < 30; ++i) {
          Dispatch->DispatchDelayedMessages();
          Sleep(800);
      }
  };

  std::thread ThreadDrunkard(FunctionDrunkard, Drunkard);
  Sleep(100);
  std::thread ThreadBob(FunctionBob, Bob);
  Sleep(100);
  std::thread ThreadElsa(FunctionElsa, Elsa);
  Sleep(100);
  std::thread ThreadMessage(FunctionMessage);

  ThreadDrunkard.join();
  ThreadBob.join();
  ThreadElsa.join();
  ThreadMessage.join();


  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






