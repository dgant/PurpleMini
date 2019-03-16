#include<BWAPI.h>
#include<cmath>
<<<<<<< HEAD
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
#define Z(t) Protoss_##t
N BWAPI;N UnitTypes;N Filter;N std;G I=int;G U=Unit;G UT=UnitType;vector<U>mi;U m,b,c;PP d;TP bd;I i,t,cW,cP,cB,cE,lW,lP,lB,lE;A&g=BroodwarPtr;
struct ExampleAIModule:AIModule{void onFrame(){
g->setLatCom(cW=cP=cB=cE=0);
if(++i%6!=2)R;
A*s=g->self();
A ou=s->getUnits();
A sl=s->getStartLocation();
I k[99999]={},ms=45+s->minerals(),su=0,sc=0+g->isVisible(TP(d));
U n=g->getClosestUnit(PP(sl),IsResourceDepot);
A np=n?UP(n):PP(sl);
if(!mi.size())for(U u:g->getUnitsInRadius(PP(sl),320,IsMineralField))mi.push_back(u);
std::sort(mi.begin(),mi.end(),[&](U x,U y){R np.getDistance(UP(x))<np.getDistance(UP(y));});
for(A u:ou)su+=GT(u).supplyProvided()-GT(u).supplyRequired();
A&st=g->getStartLocations();
d=(sc&&!lE||d==PP())?PP(st[(++t)%st.size()])+(i<1e5?PP():PP(i%994-497,(i*su)%994-497)):d;
bd=bd==TP()?sl:bd;
b=b&&b->exists()?b:g->getClosestUnit(PP(bd),IsOwned&&IsWorker);
c=c?c:b->getClosestUnit(IsWorker);
A B=[&](UT x){A r=(ms-=MP(x))>0;if(r){su+=x.supplyProvided();if(b){bd=g->getBuildLocation(x,TP(sl),100);J(b)?(g->isVisible(bd)&&ms>45)?b->build(x,bd):b->move(PP(bd)):0;K(b);}}R r;};
A T=[&](UT x,UT y){I r=ms>MP(x)&&su>0;if(r){A u=find_if(ou.begin(),ou.end(),[&](A z){R z->isIdle()&&GT(z)==y;});if(r=u!=ou.end()&&J((*u))&&(*u)->train(x)){K((*u));ms-=MP(x);su-=x.supplyRequired();};}R r;};
while(ms>0){
if(lW>7&&lP<1&&B(Z(Pylon)))C
if(lW>8&&lP>0&&lB<2&&B(Z(Gateway)))C
if(T(Z(Zealot),Z(Gateway)))C
if(lW<22&&T(Z(Probe),Z(Nexus)))C
if(su<2+4*lB&&B(Z(Pylon)))C
if(ms>250&&lB<5&&B(Z(Gateway)))C
break;
}
for(U u:g->getAllUnits()){
A p=u->getPlayer();
A t=GT(u);
A up=UP(u);
U tr=u->getOrderTarget();
tr=tr?tr:u->getTarget();
I ag=!!t.maxGroundHits(),
hp=u->getHitPoints(),
iW=t.isWorker(),
rw=1;
I iF=ag&&(!iW||(u==c&&lB>1)),cs=(iW?5.:100.)*hp/(1.+t.maxHitPoints());
m=m&&m->exists()?m:t.isMineralField()?u:m;
cE+=p->isEnemy(s);
if(p==s){
cW+=iW;cP+=t==Z(Pylon);cB+=t==Z(Gateway);
if(!J(u))C
if(iF)for(U n:u->getUnitsInRadius(512,CanAttack)){
A q=GT(n);A r=GT(n).groundWeapon().maxRange();
rw=rw&&r<32;
cs+=(n->getPlayer()==s?1.:-1)
*u->isCompleted()
*(u->getDistance(n)-r<320)
*(q.gasPrice()+MP(q)+(q==Zerg_Sunken_Colony?150:0))/(1+q.isTwoUnitsInOneEgg())/(1+10*q.isWorker())   
*n->getHitPoints()/(1.+q.maxHitPoints());
}
if((cs<0||(rw&&hp+u->getShields()<16))&&up.getDistance(PP(sl))>224&&u->move(PP(sl)))C
#define TR u->getClosestUnit(IsEnemy&&!IsCloaked&&!IsFlying
U v=(v=TR&&CanAttack,iF?1e3:99))?v:TR,iW?0:1e3);
if(ag&&v){tr==v||(u->isAttacking()&&tr&&tr->canAttack())||u->attack(UP(v));C}
iF?u->attack(d):u->isGatheringMinerals()||u->gather(mi.size()?mi[0]:m);
if(mi.size())mi.erase(mi.begin());
}}
lW=cW;lP=cP;lB=cB;lE=cE;
=======
#include<set>
#define N using namespace
N BWAPI;N UnitTypes;N Filter;N std;
auto&g = BroodwarPtr;
constexpr int mapSize = 256 * 256;
int buildable[mapSize] = { 0 };
int walkable[mapSize] = { 0 };
int regions[mapSize] = { 0 };
int unoccupied[mapSize];
int mapW, mapH;
int frame = -1;
int xyi(int x, int y) { return x + y * mapW; }
void paint(int x, int y, int color) {
	int i = xyi(x, y);
	if (x >= 0 && y >= 0 && x < mapW && y < mapH && regions[i] < 1 && walkable[i]) {
		regions[i] = color;
		paint(x - 1, y, color);
		paint(x + 1, y, color);
		paint(x, y - 1, color);
		paint(x, y + 1, color);
	}
}
struct ExampleAIModule:AIModule{void onFrame(){
	// Paint map regions by walkability
	mapW = g->mapWidth();
	mapH = g->mapHeight();
	++frame;
	if (frame == 0) {
		g->setLatCom(0);
		// TODO: Delete these
		g->setLocalSpeed(1);
		g->enableFlag(Flag::UserInput);
		// Terrain pathability
		for (int x = 0; x < mapW; ++x) {
			for (int y = 0; y < mapH; ++y) {
				buildable[xyi(x, y)] = g->isBuildable(x, y);
				walkable[xyi(x, y)] =
					g->isWalkable(x * 4, y * 4)
					* g->isWalkable(x * 4 + 3, y * 4); // Can't check complete tiles due to Plasma ramps
			}
		}
		// Neutral unit pathability
		for (auto u : g->getNeutralUnits()) {
			// TODO: Reused with occupied, below
			for (int x = u->getLeft(); x <= u->getRight() && ! u->isFlying(); x += 8) {
				for (int y = u->getTop(); y <= u->getBottom(); y += 8) {
					int i = xyi(x/32, y/32);
					walkable[i] = buildable[i] = 0;
				}
			}
		}
		// Paint regions
		for (int x = 0; x < mapW; ++x) {
			for (int y = 0; y < mapH; ++y) {
				paint(x, y, xyi(x, y) + 1);
			}
		}

	}

	// Populate buildable tiles
	memset(&unoccupied, 1, mapSize);
	for (auto u : g->getAllUnits()) {
		for (int x = u->getLeft(); x <= u->getRight() && !u->isFlying(); x += 8) {
			for (int y = u->getTop(); y <= u->getBottom(); y += 8) {
				unoccupied[xyi(x / 32, y / 32)] = 0;
			}
		}
	}

	// TODO: Delete these drawing functions
	if (true) {
		for (auto u : g->getNeutralUnits()) {
			g->drawBoxMap(u->getLeft(), u->getTop(), u->getRight(), u->getBottom(), Colors::Grey);
		}
		for (int x = 0; x < mapW; ++x) {
			for (int y = 0; y < mapH; ++y) {
				if (buildable[xyi(x, y)] && unoccupied[xyi(x, y)]) {
					g->drawCircleMap(32 * x + 16, 32 * y + 16, 15, Colors::Purple);
				}
				if (walkable[xyi(x, y)]) {
					g->drawCircleMap(32 * x + 16, 32 * y + 16, 12, Colors::Green);
				}
				g->drawTextMap(32 * x, 32 * y, "%d", regions[xyi(x, y)]);
			}
		}
	}
>>>>>>> aitt-2-terran
}};
