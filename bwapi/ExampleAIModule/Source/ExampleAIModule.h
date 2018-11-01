#include<BWAPI.h>
#include<cmath>
#define A auto
#define C continue;
#define G using
#define N G namespace
#define PP Position
#define TP TilePosition
#define UP(u) u->getPosition()
#define MP(t) t.mineralPrice()
#define GT(u) u->getType()
#define I(u) u->getID()
#define R(u) !k[I(u)]
#define K(u) k[I(u)]=1
#define Z(t) Protoss_##t
N BWAPI;N UnitTypes;N Filter;N std;
G I=int;G U=Unit;G UT=UnitType;
U m,b,c;
PP d;
TP bd;
I i,t,cW,cP,cB,cE,lW,lP,lB,lE;
A&g=BroodwarPtr;
struct ExampleAIModule:AIModule{void onFrame(){
g->setLatCom(cW=cP=cB=cE=0);
if(++i%6>0)return;  
g->setLocalSpeed(lE>0);
A*s=g->self();
A ou=s->getUnits();
A sl=s->getStartLocation();
I k[99999]={},ms=45+s->minerals(),su=0,sc=0+g->isVisible(TP(d));
for(A u:ou)su+=GT(u).supplyProvided()-GT(u).supplyRequired();
A&st=g->getStartLocations();
d=(sc&&!lE||d==PP())?PP(st[(++t)%st.size()])+(i<1e5?PP():PP(i%994-497,(i*su)%994-497)):d;
bd=bd==TP()?sl:bd;
b=b&&b->exists()?b:g->getClosestUnit(PP(bd),IsOwned&&IsWorker);
c=c?c:b->getClosestUnit(IsWorker);
A B=[&](UT x){
A r=(ms-=MP(x))>0;
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
A T=[&](UT x, UT y) {
I r=ms>MP(x)&&su>0;
if(r) {
  A u=find_if(ou.begin(),ou.end(),[&](A z){return z->isIdle()&&GT(z)==y;});
  if(r=u!=ou.end()&&R((*u))&&(*u)->train(x)){
    K((*u));
    ms-=MP(x);
    su-=x.supplyRequired();
  };
}
return r;
};
while(ms>0){
if(lW>7&&lP<1&&B(Z(Pylon)))C
if(lW>8&&lP>0&&lB<2&&B(Z(Gateway)))C
if(T(Z(Zealot),Z(Gateway)))C
if(lW<22&&T(Z(Probe),Z(Nexus)))C
if(su<2+4*lB&&B(Z(Pylon)))C
if(ms>250&&lB<5&&B(Z(Gateway)))C
break;
}
for(U u:g->getAllUnits()) {
A p=u->getPlayer();
A t=GT(u);
U tr=u->getTarget();
A up=UP(u);
I ag=!!t.maxGroundHits(),
hp=u->getHitPoints(),
sp=u->getShields(),
iW=t.isWorker(),
rw=1;
I iF=ag&&(!iW||(u==c&&lB>1)),cs=(iW?20.:100.)*hp/(1.+t.maxHitPoints());
m=m&&m->exists()?m:t.isMineralField()?u:m;
cE+=p->isEnemy(s);
if(p==s){
  cW+=iW;cP+=t==Z(Pylon);cB+=t==Z(Gateway);
  if(!R(u))C
  if(iF)for(U n:u->getUnitsInRadius(512,CanAttack)){
    A q=GT(n);A r=GT(n).groundWeapon().maxRange();
    rw=rw&&r<32;
    cs+=(n->getPlayer()==s?1.:-1)
    *u->isCompleted()
    *(u->getDistance(n)-r<320)
    *(q.gasPrice()+MP(q)+(q==Zerg_Sunken_Colony?150:0))/(1+q.isTwoUnitsInOneEgg())/(1+5*q.isWorker())    
    *n->getHitPoints()/(1.+q.maxHitPoints());
  }
  if((cs<0||(rw&&hp+sp<16))&&up.getDistance(PP(sl))>224&&u->move(PP(sl)))C    
#define TR u->getClosestUnit(IsEnemy&&!IsCloaked&&!IsFlying
  U v=(v=TR&&CanAttack,iF?1e3:99))?v:TR,iW?0:1e3);
  if(ag&&v){tr==v||(u->isAttacking()&&tr&&tr->isAttacking())||u->attack(UP(v));C}
  iF?u->attack(d):u->isGatheringMinerals()||u->gather(m);
}
}
lW=cW;lP=cP;lB=cB;lE=cE;
}
};
