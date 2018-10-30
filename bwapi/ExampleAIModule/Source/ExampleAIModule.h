#include <BWAPI.h>
#define A auto
#define G using
#define N G namespace
N BWAPI;
N std;
G U=UnitInterface*;
G V=void;
A&g=BroodwarPtr;
U m=0;
class ExampleAIModule:AIModule{
V onFrame(){
  A*s=g->self();
  m=m&&m->exists()?m:0;
  for(U u:g->getAllUnits()) {
    int f=u->getPlayer()==s;
    A t=u->getType();
    m=m?m:t.isMineralField()?u:0;
    m&&f&&!u->isGatheringMinerals()&&u->gather(m);
  }
}
};
