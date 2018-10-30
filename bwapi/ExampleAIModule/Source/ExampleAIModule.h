#include <BWAPI.h>
#define A auto
#define G using
#define N G namespace
#define C goto q;
#define B(x,y) if(ms>y-20){u->build(x,g->getBuildLocation(x,u->getTilePosition()));ms-=y;su+=16;C}
N BWAPI;
N UnitTypes;
N Filter;
N std;
G U=UnitInterface*;
G V=void;
A&g=BroodwarPtr;
U m=0;
int i=0;
struct ExampleAIModule:AIModule{
V onFrame(){
  if(++i%3)return;
  g->setLocalSpeed(0);
  g->setLatCom(0);
  A*s=g->self();
  A ms=s->minerals(),su=s->supplyTotal()-s->supplyUsed();
  for(U u:g->getAllUnits()) {
    A t=u->getType();
    int
    iF=u->getPlayer()==s,
    iW=t.isWorker(),
    iB=t==Terran_Barracks,
    iC=t.isResourceDepot(),
    ag=t.maxGroundHits(),
    aa=t.maxAirHits();
    if(iF){
      if(iC){u->train(Terran_SCV);C}
      if(iB){u->train(Terran_Marine);C}
      if(U v=u->getClosestUnit(IsEnemy,256)){
        iW||u->getGroundWeaponCooldown()<3?u->isAttacking()?0:u->attack(v):0;C
      }
      if(iW){
        if(su<4)B(Terran_Supply_Depot,100)
        B(Terran_Barracks,150)
      }
    }
    (m=m&&m->exists()?m:t.isMineralField()?u:0)&&iW?iF&&u->isGatheringMinerals()||u->gather(m):u->attack(Position(s->getStartLocation()));
    q:;
  }
}
};
