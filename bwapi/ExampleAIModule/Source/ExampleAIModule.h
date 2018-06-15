#include <BWAPI.h>
#define UN using namespace
UN BWAPI;UN Filter;UN std;using ss=string;using U=Unit;using b=bool;using i=int;using V=void;auto&g=BroodwarPtr;
struct ExampleAIModule:AIModule{V onStart(){}V onFrame(){auto s=g->self();g->drawTextScreen(0,0,"Frame:%d",g->getFrameCount());}V onUnitShow(U u){}V onUnitHide(U u){}V onUnitCreate(U u){}V onUnitDestroy(U u){}V onUnitMorph(U u){}V onUnitRenegade(U u){}V onUnitComplete(U u){}};
