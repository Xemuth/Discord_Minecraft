#include <Core/Core.h>
#include "Discord_Minecraft.h"
using namespace Upp;

void Discord_Minecraft::launchCommande(ValueMap payload){
	Cout() << "Event déclanché ! #Minecraft" <<"\n";
}
	
Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix){
	name = _name;
	prefix = _prefix;

	Events.Add([&](ValueMap e){this->launchCommande(e);});
}

void Discord_Minecraft::Event(ValueMap payload){
	for(auto &e : Events){
		e(payload);
	}
}