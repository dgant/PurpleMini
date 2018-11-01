#include<BWAPI.h>
#define A auto
#define C continue;
#define G using
#define N G namespace
#define PP Position
#define TP TilePosition
#define UP(u) u->getPosition()
#define R(u) !k[u->getID()]
#define K(u) k[u->getID()]=1
N BWAPI;
N UnitTypes;
N Filter;
N std;
G I=int;G U=UnitInterface*;
A&g=BroodwarPtr;
U m,b;
PP d;
TP bd;
I i,t,cW,cF,cP,cB,cE,lW,lF,lP,lB,lE;
struct ExampleAIModule:AIModule{
void onFrame(){
  g->setLatCom(cW=cF=cB=cE=0);
  g->drawTextScreen(0,0,"%dW %dF %dP %dB %dT %dE",lW,lF,lP,lB,lE);
  if(++i%6>0)return;  
  g->setLocalSpeed(lW<8?0:1);
  I k[99999]={};  
  A*s=g->self();
  A ou=s->getUnits();
  A sl=s->getStartLocation();
  A ms=45+s->minerals(),su=0,sc=0+g->isVisible(TP(d));
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
        R(b)?(g->isVisible(bd)&&ms>45)?b->build(x,bd):b->move(PP(bd)):0;
        K(b);
      }
    }
    return r;
  };
  A T=[&](UnitType x, UnitType y) {
    A p=x.mineralPrice();
    if(ms>p&&su>0) {
      A u=find_if(ou.begin(),ou.end(),[&](A z){return z->isIdle()&&z->getType()==y;});
      if(u!=ou.end()&&R((*u))&&(*u)->train(x)){
        K((*u));
        ms-=p;
        su-=x.supplyRequired();
        return 1;
      };      
    }
    return 0;
  };
  while(ms>0){
    if(lW>7&&lP<1&&B(Protoss_Pylon))C
    if(lW>8&&lP>0&&lB<2&&B(Protoss_Gateway))C
    if(T(Protoss_Zealot,Protoss_Gateway))C
    if(lW<22&&T(Protoss_Probe,Protoss_Nexus))C
    if(su<2+4*lB&&B(Protoss_Pylon))C
    if(ms>250&&lB<5&&B(Protoss_Gateway))C
    break;
  }
  for(U u:g->getAllUnits()) {
    A p=u->getPlayer();
    A t=u->getType();
    I cs=100,
    e=u->exists(),
    v=u->isVisible(),
    iW=t.isWorker(),
    iP=t==Protoss_Pylon,
    iB=t==Protoss_Gateway,
    iE=p->isEnemy(s),
    ag=!!t.maxGroundHits(),
    aa=!!t.maxAirHits();
    A iF=ag&&!iW;
    m=m&&e?m:t.isMineralField()?u:0;
    cE+=iE*e;
    d=iE&&!sc&&v&&!u->isCloaked()&&!u->isFlying()?UP(u):d;
    if(p==s){
      iW?++cW:cF+=ag;
      cP+=iP;
      cB+=iB;
      if(!R(u))C
      if(iF)for(U n:u->getUnitsInRadius(300,CanAttack)){A nt=n->getType();cs+=(n->getPlayer()==s?1:-1)*nt.mineralPrice()/(1+nt.isTwoUnitsInOneEgg())/(1+5*nt.isWorker());}
      if(cs<0&&UP(u).getDistance(PP(sl))>300&&u->move(PP(sl)))C
      U v=(v=u->getClosestUnit(IsEnemy&&CanAttack&&!IsCloaked,iW?99:1e3))?v:u->getClosestUnit(IsEnemy,iW?0:1e3);
      if(ag&&v){u->isAttacking()||u->attack(UP(v));C}
      iW?u->isIdle()&&u->gather(m):ag?u->attack(d):0;
    }
  }
  lW=cW;lF=cF;lP=cP;lB=cB;lE=cE;
}
};
