#include<BWAPI.h>
#define A auto
#define C continue;
#define G using
#define N G namespace
#define PP Position
#define TP TilePosition
#define UP(x) x->getPosition()
N BWAPI;
N UnitTypes;
N Filter;
N std;
G U=UnitInterface*;
G V=void;
A&g=BroodwarPtr;
U m,b;
PP d;
TP bd;
int i,t,cW,cF,cP,cB,cT,cE,lW,lF,lP,lB,lT,lE;
struct ExampleAIModule:AIModule{
V onFrame(){
  g->setLocalSpeed(lF<12?0:1);
  g->drawTextScreen(0,0,"%dW %dF %dP %dB %dT %dE",lW,lF,lP,lB,lT,lE);
  if(++i%6>0)return;
  g->setLatCom(cW=cF=cB=cT=cE=0);
  A*s=g->self();
  A ou=s->getUnits();
  A sl=s->getStartLocation();
  A ms=20+s->minerals(),su=0,sc=0+g->isVisible(TP(d));
  for(A u:ou){A t=u->getType();su+=t.supplyProvided()-t.supplyRequired();};
  A&st=g->getStartLocations();
  d=sc&&!lE?PP(st[++t%st.size()]):d;  
  bd=bd==TP()?sl:bd;
  b=b&&b->exists()?b:g->getClosestUnit(PP(bd),IsOwned&&IsWorker);
  A B=[&](UnitType x){
    A r=(ms-=x.mineralPrice())>0;
    if(r){
      su+=x.supplyProvided();      
      if(b){
        bd=g->getBuildLocation(x,TP(sl),100);
        g->isVisible(bd)?b->build(x,bd):b->move(PP(bd));
      }
    }
    return r;
  };
  A T=[&](UnitType x, UnitType y) {
    A p=x.mineralPrice();
    if(ms>p) {
      A u=find_if(ou.begin(),ou.end(),[&](A z){return z->isIdle()&&z->getType()==y;});
      if(u!=ou.end()&&(*u)->train(x)){
        g->drawTextScreen(29,29,"X");
        ms-=p;
        su-=x.supplyRequired();
        return 1;
      };      
    }
    return 0;
  };
  while(ms>0){
    if(((lP<1&&lW>7)||su<2+4*lB)&&B(Protoss_Pylon))C
    if(T(Protoss_Zealot,Protoss_Gateway))C
    if(lW<22&&T(Protoss_Probe,Protoss_Nexus))C
    if(lB<lT*5&&B(Protoss_Gateway))C
    break;
  }
  for(U u:g->getAllUnits()) {
    A p=u->getPlayer();
    A t=u->getType();
    int
    cs=100,
    e=u->exists(),
    v=u->isVisible(),
    iW=t.isWorker(),
    iP=t==Protoss_Pylon,
    iB=t==Protoss_Gateway,
    iT=t.isResourceDepot(),
    iE=p->isEnemy(s),
    ag=!!t.maxGroundHits(),
    aa=!!t.maxAirHits();
    A iF=ag&&!iW;
    m=m&&e?m:t.isMineralField()?u:0;
    cE+=iE*e;
    d=iE&&!sc&&v?UP(u):d;
    if(p==s){
      iW?++cW:cF+=ag;
      cT+=iT;
      cP+=iP;
      cB+=iB;
      if(iF)for(U n:u->getUnitsInRadius(300,CanAttack)){
        A nt=n->getType();
        cs+=(n->getPlayer()==s?1:-1)*nt.mineralPrice()/(1+nt.isTwoUnitsInOneEgg())/(1+5*nt.isWorker());
      }
      if(cs<0&&UP(u).getDistance(PP(sl))>300&&u->move(PP(sl)))C
      U v=(v=u->getClosestUnit(IsEnemy&&CanAttack&&!IsCloaked,iW?99:1e3))?v:u->getClosestUnit(IsEnemy,iW?0:1e3);
      if(ag&&v){u->isAttacking()||u->attack(UP(v));C}
      iW?u->isIdle()&&u->gather(m):ag?u->attack(d):0;
    }
  }
  lW=cW;lF=cF;lP=cP;lB=cB;lT=cT;lE=cE;
}
};
