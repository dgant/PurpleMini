#include<BWAPI.h>
#include<cmath>
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
}};
