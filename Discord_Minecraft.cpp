#include <Core/Core.h>
#include "Discord_Minecraft.h"
using namespace Upp;

void Discord_Minecraft::launchCommande(ValueMap payload){
	String channel  = payload["d"]["channel_id"];
    String content  = payload["d"]["content"];
    String userName = payload["d"]["author"]["username"];
    String id = payload["d"]["author"]["id"];
    String discriminator = payload["d"]["author"]["discriminator"];
	
	Cout() << "Event Minecraft" <<"\n";
	ptrBot->CreateMessage(channel, "Felix est un camé !!");
}
	
Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix){
	name = _name;
	prefix = _prefix;

	EventsMapMessageCreated.Add([&](ValueMap e){this->launchCommande(e);});
}

void Discord_Minecraft::EventsMessageCreated(ValueMap payload){
	for(auto &e : EventsMapMessageCreated){
		e(payload);
	}
}