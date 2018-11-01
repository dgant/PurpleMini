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
U m,b,c;
PP d;
TP bd;
I i,t,cW,cP,cB,cE,lW,lP,lB,lE;
struct ExampleAIModule:AIModule{
void onFrame(){
  g->setLatCom(cW=cP=cB=cE=0);
  if(++i%6>0)return;  
  g->setLocalSpeed(lB>1);
  I k[99999]={};  
  A*s=g->self();
  A ou=s->getUnits();
  A sl=s->getStartLocation();
  A ms=45+s->minerals(),su=0,sc=0+g->isVisible(TP(d));
  for(A u:ou){A t=u->getType();su+=t.supplyProvided()-t.supplyRequired();};
  A&st=g->getStartLocations();
  d=sc&&!lE?PP(st[++t%st.size()])+(i<1e5?PP():PP(i%994-497,(i*su)%994-497)):d;
  g->drawCircleMap(d,99,Colors::Red);
  bd=bd==TP()?sl:bd;
  b=b&&b->exists()?b:g->getClosestUnit(PP(bd),IsOwned&&IsWorker);
  c=c?c:b->getClosestUnit(IsWorker);
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
    ag=!!t.maxGroundHits(),
    e=u->exists(),
    v=u->isVisible(),
    iW=t.isWorker(),
    iP=t==Protoss_Pylon,
    iB=t==Protoss_Gateway,
    iE=p->isEnemy(s);
    I iF=ag&&(!iW||(u==c&&lB>1));
    m=m&&m->exists()?m:t.isMineralField()&&u->exists()?u:m;
    iE&&e?++cE:0;
    d=iE&&!sc&&v&&!u->isCloaked()&&!u->isFlying()?UP(u):d;
    if(p==s){
      cW+=iW;
      cP+=iP;
      cB+=iB;
      if(!R(u))C
      if(iF)for(U n:u->getUnitsInRadius(300,CanAttack)){A nt=n->getType();cs+=(n->getPlayer()==s?1:-1)*(nt.gasPrice()+nt.mineralPrice())/(1+nt.isTwoUnitsInOneEgg())/(1+5*nt.isWorker());}
      if(cs<0&&UP(u).getDistance(PP(sl))>300&&u->move(PP(sl)))C
#define TR u->getClosestUnit(IsEnemy&&!IsCloaked&&!IsFlying
      U v=(v=TR&&CanAttack,iW?99:1e3))?v:TR,iW?0:1e3);
      if(ag&&v){u->isAttacking()||u->attack(UP(v));C}
      iF?u->attack(d):u->isGatheringMinerals()||u->gather(m);
    }
  }
  lW=cW;lP=cP;lB=cB;lE=cE;
}
};
