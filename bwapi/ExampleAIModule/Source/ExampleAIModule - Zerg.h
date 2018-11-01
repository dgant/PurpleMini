#include<BWAPI.h>
#include<cmath>
#include<set>
#define A auto
#define C continue;
#define G using
#define N G namespace
#define R return
#define PP Position
#define TP TilePosition
#define UP(u) u->getPosition()
#define MP(t) t.mineralPrice()
#define GT(u) u->getType()
#define I(u) u->getID()
#define J(u) !k[I(u)]
#define K(u) k[I(u)]=1
#define Z(t) Zerg_##t
N BWAPI;N UnitTypes;N Filter;N std;G I=int;G U=Unit;G UT=UnitType;vector<U>mi;U m,b=0,c;PP d;TP bd;I i,t,cW,cF,cP,cB,cE,lW,lF,lP,lB,lE,go;A&g=BroodwarPtr;
struct ExampleAIModule:AIModule{void onFrame(){
g->setLocalSpeed(1);
g->setLatCom(cW=cF=cP=cB=cE=0);
if(++i%6!=2)R;
A*s=g->self();A ou=s->getUnits();A sl=s->getStartLocation();I k[99999]={},ms=24+s->minerals(),sc=0+g->isVisible(TP(d));U n=g->getClosestUnit(PP(sl),IsResourceDepot);A np=n?UP(n):PP(sl);go=go||(ms>124&&lB&&lW>3);
if(!mi.size())for(U u:g->getUnitsInRadius(PP(sl),320,IsMineralField))mi.push_back(u);
std::sort(mi.begin(),mi.end(),[&](U x,U y){R np.getDistance(UP(x))<np.getDistance(UP(y));});
A&st=g->getStartLocations();
d=(sc&&!lE||d==PP())?PP(st[(++t)%st.size()])+(i<1e5?PP():PP(i%994-497,(i*i)%994-497)):d;
bd=bd==TP()?sl:bd;
A B=[&](UT x){A r=(ms-=MP(x))>0;if(r){if(b){bd=i%11>0?bd:g->getBuildLocation(x,b?TP(UP(b)):TP(sl),100);J(b)?(g->isVisible(bd)&&ms>24)?b->build(x,bd):b->move(PP(bd)):0;K(b);}}R r;};
A T=[&](UT x,UT y){I r=ms>MP(x);if(r){A u=find_if(ou.begin(),ou.end(),[&](A z){R GT(z)==y;});if(r=u!=ou.end()&&J((*u))&&(*u)->morph(x)){K((*u));ms-=MP(x);};}R r;};
while(ms>0){if(lB<1&&B(Z(Spawning_Pool)))C;if(T(Z(Zergling),Z(Hatchery)))C;if(lW<4&&T(Z(Drone),Z(Larva)))C;break;}
for(U u:g->getAllUnits()){
A p=u->getPlayer();A t=GT(u);A up=UP(u);U tr=u->getOrderTarget();tr=tr?tr:u->getTarget();I ag=!!t.maxGroundHits(),hp=u->getHitPoints(),iW=t.isWorker(),rw=1;
I iF=(ag&&(!iW||(u==c&&lB>0&&lW>3&&go))),cs=(iW?20.:50.)*hp/(1.+t.maxHitPoints());m=m&&m->exists()?m:t.isMineralField()?u:m;cE+=p->isEnemy(s);
if(p==s){b=b&&b->exists()&&b!=c&&!b->getBuildUnit()?b:iW?u:b;c=c&&c!=b?c:iW?u:c;cW+=iW;cF+=ag&&!iW;cP+=t==Z(Overlord);cB+=t==Z(Spawning_Pool);if(!J(u))C
if(iF)for(U n:u->getUnitsInRadius(512,CanAttack)){A q=GT(n);A r=GT(n).groundWeapon().maxRange();rw=rw&&r<32;
cs+=(n->getPlayer()==s?1.:-1)*u->isCompleted()*(u->getDistance(n)-r<320)*(q.gasPrice()+MP(q)+(q==Zerg_Sunken_Colony?150:0))/(1+q.isTwoUnitsInOneEgg())/(1+10*q.isWorker())*n->getHitPoints()/(1.+q.maxHitPoints());}
if((cs<0||(!iW&&u->getGroundWeaponCooldown()&&u->isUnderAttack()))&&up.getDistance(PP(sl))>224&&u->move(PP(sl)))C
#define TR u->getClosestUnit(IsEnemy&&!IsCloaked&&!IsFlying
U v=(v=TR&&(IsWorker||CanAttack),iF?1e4:99))?v:TR,iF?1e4:0);
if(ag&&v){tr==v||(u->isAttacking()&&tr&&tr->canAttack())||u->attack(UP(v));C}
if(u->isFlying()){u->move(lE?PP(sl):d);C}
iF?u->attack(d):u->isGatheringMinerals()||u->gather(mi.size()?mi[0]:m);
if(mi.size())mi.erase(mi.begin());
}}
lW=cW;lF=cF;lP=cP;lB=cB;lE=cE;
}};
