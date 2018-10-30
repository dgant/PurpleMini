#include<BWAPI.h>
#define A auto
#define C continue;
#define G using
#define N G namespace
#define PP Position
#define UP(x) x->getPosition()
#define B(x,y) if(ms>y-20){u->isConstructing()||u->build(x,g->getBuildLocation(x,u->getTilePosition(),1e3));ms-=y;su+=16;C}
#define T(x,y) if(x&&!u->isTraining()){ms-=50*u->train(y);C}

N BWAPI;
N UnitTypes;
N Filter;
N std;
G U=UnitInterface*;
G V=void;
A&g=BroodwarPtr;
U m;
int i,cW,cF,cB,lW,lF,lB;
struct ExampleAIModule:AIModule{
V onFrame(){
  i==0?g->setLocalSpeed(lF<12?0:1):0;
  if(i++%3>0)return;
  g->setLatCom(cW=cF=cB=0);
  A*s=g->self();
  A ms=s->minerals(),su=s->supplyTotal()-s->supplyUsed();
  A&st=g->getStartLocations();
  PP d(lF>12?st[(i/999)%st.size()]:s->getStartLocation());
  g->drawTextScreen(0, 0, "%d %d %d %d,%d", lW, lF, lB, d.x, d.y);
  for(U u:g->getAllUnits()) {
    A t=u->getType();
    int
    iF=u->getPlayer()==s,
    iW=t.isWorker(),
    iB=t==Terran_Barracks,
    iC=t.isResourceDepot(),
    ag=!!t.maxGroundHits(),
    aa=!!t.maxAirHits();
    m=m&&m->exists()?m:t.isMineralField()?u:0;
    if(iF){
      iW?++cW:cF+=ag;
      cB+=iB;
      T(iB,Terran_Marine);
      if(ag)if(U v=u->getClosestUnit(IsEnemy,iW?99:1e3)){
        iW||u->getGroundWeaponCooldown()<3?u->isAttacking()||u->attack(v):u->move(UP(u)-UP(v));C
      }
      if(iW){
        if(su<3+3*lB&&lB>1)B(Terran_Supply_Depot,100)
        B(Terran_Barracks,150)
      }      
      T(lW<27&&iC&&(lB>1||lW<8),Terran_SCV);
      if(m&&iW){u->isGatheringMinerals()||u->gather(m);C}
      u->attack(d);
    }
  }
  lW=cW;lF=cF;lB=cB;
}
};
