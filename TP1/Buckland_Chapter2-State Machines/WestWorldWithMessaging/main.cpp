#include <fstream>
#include <time.h>

#include "Locations.h"
#include "Miner.h"
#include "MinersWife.h"
#include "Drunk.h"
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

  //create a drunk
  Drunk* Drunkard = new Drunk(ent_Drunkard);

  //register them with the entity manager
  EntityMgr->RegisterEntity(Bob);
  EntityMgr->RegisterEntity(Elsa);
  EntityMgr->RegisterEntity(Drunkard);

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

  //run Bob and Elsa through a few Update calls
  /*
  for (int i=0; i<30; ++i)
  {
    Drunkard->Update();
    Bob->Update();
    Elsa->Update();

    //dispatch any delayed messages
    Dispatch->DispatchDelayedMessages();

    Sleep(800);
  }
  */

  //tidy up
  delete Bob;
  delete Elsa;
  delete Drunkard;

  //wait for a keypress before exiting
  PressAnyKeyToContinue();


  return 0;
}






