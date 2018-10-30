#include <BWAPI.h>
#define A auto
#define G using
#define N G namespace
#define C goto q;
N BWAPI;
N UnitTypes;
N Filter;
N std;
G U=UnitInterface*;
G V=void;
A&g=BroodwarPtr;
U m=0;
struct ExampleAIModule:AIModule{
V onFrame(){
  A*s=g->self();
  for(U u:g->getAllUnits()) {
    A t=u->getType();
    int
    iF=u->getPlayer()==s,
    iW=t.isWorker(),
    iC=t.isResourceDepot(),
    ag=t.maxGroundHits(),
    aa=t.maxAirHits();
    if(iF){
      if(iC){u->train(Terran_SCV);C}
      if(U v=u->getClosestUnit(IsEnemy,256)){
        iW||u->getGroundWeaponCooldown()<3?u->getTarget()!=v?u->attack(v):0:0;
        C
      }      
    }
    (m=m&&m->exists()?m:t.isMineralField()?u:0)&&iW&&iF&&u->isGatheringMinerals()||u->gather(m);
    q:;
  }
}
};
