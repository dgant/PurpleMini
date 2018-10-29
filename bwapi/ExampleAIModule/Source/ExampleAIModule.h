#include <BWAPI.h>
using namespace BWAPI;
using namespace Filter;
using namespace std;
using U=Unit;
using V=void;
auto&g=BroodwarPtr;
struct ExampleAIModule:AIModule{
	V onStart(){}
	V onFrame(){
		
	}
	V onUnitShow(U u){}
	V onUnitHide(U u){}
	V onUnitCreate(U u){}
	V onUnitDestroy(U u){}
	V onUnitMorph(U u){}
	V onUnitRenegade(U u){}
	V onUnitComplete(U u){}
};
