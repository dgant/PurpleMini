#include <BWAPI.h>
#define VV void
#define UN using namespace
UN BWAPI;UN Filter;UN std;using ss=string;using u=Unit;using b=bool;using ui=unsigned;using i=int;auto &g=BroodwarPtr;struct ExampleAIModule:AIModule{VV onStart(){}VV onEnd(b w){}VV onFrame(){g->drawTextScreen(0,0,"Frame:%d",g->getFrameCount());}VV onSendText(ss t){}VV onReceiveText(Player p, Player t){}VV onPlayerLeft(Player p){}VV onNukeDetect(Position t){}VV onUnitDiscover(u u){}VV onUnitEvade(u u){}VV onUnitShow(u u){}VV onUnitHide(u u){}VV onUnitCreate(u u){}VV onUnitDestroy(u u){}VV onUnitMorph(u u){}VV onUnitRenegade(ui u){}VV onSaveGame(ss){}VV onUnitComplete(u u){}};
