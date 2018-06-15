#include <BWAPI.h>
#define UN using namespace
UN BWAPI;UN Filter;UN std;using U=Unit;using V=void;auto&g=BroodwarPtr;struct ExampleAIModule:AIModule{V onStart(){}V onFrame(){g->drawTextScreen(0,0,"Frame:%d",g->getFrameCount());}V onUnitShow(U u){}V onUnitHide(U u){}V onUnitCreate(U u){}V onUnitDestroy(U u){}V onUnitMorph(U u){}V onUnitRenegade(U u){}V onUnitComplete(U u){}};
