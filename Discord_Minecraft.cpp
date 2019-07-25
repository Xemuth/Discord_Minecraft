#include <Core/Core.h>
#include "Discord_Minecraft.h"
using namespace Upp;

void Discord_Minecraft::launchCommande(ValueMap payload){
	ptrBot->CreateMessage(ChannelLastMessage, "Felix est un camé !!");
}
	
Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix){
	name = _name;
	prefix = _prefix;

	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("test"))this->launchCommande(e);});
}

void Discord_Minecraft::EventsMessageCreated(ValueMap payload){
	for(auto &e : EventsMapMessageCreated){
		e(payload);
	}
}