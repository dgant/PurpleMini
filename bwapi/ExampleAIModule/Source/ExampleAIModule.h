#include<BWAPI.h>
#include<cmath>
#include<set>
#define N using namespace
N BWAPI;N UnitTypes;N Filter;N std;
auto&g = BroodwarPtr;
constexpr int mapSize = 256 * 256;
int buildable[mapSize] = { 0 };
int walkable[mapSize] = { 0 };
int regions[mapSize] = { -1 };
int mapW, mapH;
int frame = -1;
int xyi(int x, int y) { return x + y * mapW; }
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
		for (int x = 0; x < mapW; ++x) {
			for (int y = 0; y < mapH; ++y) {
				buildable[xyi(x, y)] = g->isBuildable(x, y);
				walkable[xyi(x, y)] =
					g->isWalkable(x * 4, y * 4)
					* g->isWalkable(x * 4 + 3, y * 4);
			}
		}
		for (auto u : g->getNeutralUnits()) {
			for (int x = u->getLeft(); x <= u->getRight() && ! u->isFlying(); x += 8) {
				for (int y = u->getTop(); y <= u->getBottom(); y += 8) {
					int i = xyi(x/32, y/32);
					walkable[i] = (buildable[i] = 0);
				}
			}
		}
	}
	for (auto u : g->getNeutralUnits()) {
		g->drawBoxMap(u->getLeft(), u->getTop(), u->getRight(), u->getBottom(), Colors::Grey);
	}
	for (int x = 0; x < mapW; ++x) {
		g->drawLineMap(32 * x, 0, 32 * x, mapH - 1, Colors::Black);
		g->drawLineMap(0, 32 * x, mapW - 1, 32 * x, Colors::Black);
		for (int y = 0; y < mapH; ++y) {
			if (buildable[xyi(x, y)]) {
				g->drawCircleMap(32 * x + 16, 32 * y + 16, 15, Colors::Purple);
			}
			if (walkable[xyi(x, y)]) {
				g->drawCircleMap(32 * x + 16, 32 * y + 16, 12, Colors::Green);
			}
		}
	}
}};
