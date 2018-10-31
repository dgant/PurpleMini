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
U m;
PP d;
TP bd;
int i,t,cW,cF,cB,cT,cE,lW,lF,lB,lT,lE;
struct ExampleAIModule:AIModule{
V onFrame(){
  g->setLocalSpeed(lF<12?0:1);
  g->drawTextScreen(0, 0, "%dW %dF %dB %dT %dE", lW, lF, lB, lT, lE);
  if(++i%6>0)return;
  g->setLatCom(cW=cF=cB=cT=cE=0);
  A*s=g->self();
  A ou=s->getUnits();
  A sl=s->getStartLocation();
  A ms=20+s->minerals(),su=s->supplyTotal()-s->supplyUsed(),sc=0+g->isVisible(TP(d));
  A&st=g->getStartLocations();
  d=sc&&!lE?PP(st[++t%st.size()]):d;  
  bd=bd==TP()?sl:bd;
  A B=[&](UnitType x){
    if((ms-=x.mineralPrice())>0){
      su+=x.supplyProvided();      
      A c=find_if(ou.begin(),ou.end(),[&](A z){return bd==TP(z->getOrderTargetPosition());});
      U u=(c!=ou.end()?*c:g->getClosestUnit(PP(bd),IsWorker&&IsOwned));
      if(u){
        bd=g->getBuildLocation(x,TP(sl),100);
        g->isVisible(bd)?u->build(x,bd):u->move(PP(bd));
        return 1;
      }
    }
    return 0;
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
    if(lW<22*lT&&(lB>1||lW<8)&&T(Terran_SCV,Terran_Command_Center))C
    if(lW>20*lT&&B(Terran_Command_Center))C
    if(su<3+3*lB&&lB>1&&B(Terran_Supply_Depot))C
    if(T(Terran_Marine,Terran_Barracks))C    
    if(lB<lT*4&&B(Terran_Barracks))C
    break;
  }
  for(U u:g->getAllUnits()) {
    A p=u->getPlayer();
    A t=u->getType();
    int
    e=u->exists(),
    v=u->isVisible(),
    iW=t.isWorker(),
    iB=t==Terran_Barracks,
    iT=t.isResourceDepot(),
    iE=p->isEnemy(s),
    ag=!!t.maxGroundHits(),
    aa=!!t.maxAirHits();
    m=m&&e?m:t.isMineralField()?u:0;
    cE+=iE*e;
    d=iE&&!sc&&v?UP(u):d;
    if(p==s){
      iW?++cW:cF+=ag;
      cT+=iT;
      cB+=iB;
      if(ag)if(U v=u->getClosestUnit(IsEnemy&&CanAttack,iW?99:1e3)){
        u->isAttacking()||u->attack(UP(v));C
        //iW||u->getGroundWeaponCooldown()<6?u->isAttacking()||u->attack(v):u->move(UP(u)-UP(v));C
      }
      iW?u->isIdle()&&u->gather(m):ag?u->attack(d):0;
    }
  }
  lW=cW;lF=cF;lB=cB;lT=cT;lE=cE;
}
};
