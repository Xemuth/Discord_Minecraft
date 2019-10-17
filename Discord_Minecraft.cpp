#include <Core/Core.h>
#include "Discord_Minecraft.h"

using namespace Upp;

void Discord_Minecraft::launchCommande(ValueMap payload){
	if(	AuthorId.IsEqual("<@131865910121201664>") || AuthorId.IsEqual("<@131915014419382272>")){
		String command =MessageArgs.ToString();
		myRcon.SendCommand(command);
		ptrBot->CreateMessage(ChannelLastMessage, "Commande envoyée");
	}else{
		ptrBot->CreateMessage(ChannelLastMessage, "Vous n'avez pas les droits !");
	}
}
	
Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix){
	name = _name;
	prefix = _prefix;
	
	myRcon(String _host, int _port, String _password ,String _serviceName,int _TBR);


	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("test"))this->launchCommande(e);});
}

void Discord_Minecraft::EventsMessageCreated(ValueMap payload){
	for(auto &e : EventsMapMessageCreated){
		e(payload);
	}
}