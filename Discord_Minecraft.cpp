#include <Core/Core.h>
#include "Discord_Minecraft.h"

using namespace Upp;

void Discord_Minecraft::launchCommande(ValueMap payload){
	if(testConnexion()){
		if(	AuthorId.IsEqual("131865910121201664") || AuthorId.IsEqual("131915014419382272")){
			String command ="";
			for(String& e : MessageArgs){
				command += e  ;
			}
			myRcon.SendCommand(command);
			ptrBot->CreateMessage(ChannelLastMessage, "Commande envoyée");
		}else{
			ptrBot->CreateMessage(ChannelLastMessage, "Vous n'avez pas les droits !");
		}
	}
}

void Discord_Minecraft::clearWeather(ValueMap payload){
	if(testConnexion()){
		String command ="weather clear";
		myRcon.SendCommand(command);
		ptrBot->CreateMessage(ChannelLastMessage, "Commande envoyée");
	}
}
void Discord_Minecraft::saySomething(ValueMap payload){
	if(testConnexion()){
		String command ="say ";
		for(String& e : MessageArgs){
			command += e  ;
		}
		myRcon.SendCommand(command);
		ptrBot->CreateMessage(ChannelLastMessage, "Commande envoyée");
	}
}
	
Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix,String RconConfigPath) : rconConfig(RconConfigPath) ,myRcon(rconConfig.GetValue<String>("addr"),rconConfig.GetValue<int>("port"),rconConfig.GetValue<String>("password"),rconConfig.GetValue<String>("serviceName")){
	name = _name;
	prefix = _prefix;
	if(rconConfig.GetValue<String>("addr").GetCount() > 0 && rconConfig.GetValue<int>("port") > 0 && rconConfig.GetValue<String>("password").GetCount() > 0 ){
		RconLoaded =true;
		if(myRcon.TestConnexion()){
			RconValide=true;
			if(myRcon.TestLoggin()){
				RconAuthentified=true;
			}else{
				LOG("Discord_Minecraft : Rcon authentification failled. All Rcon function will be disable");
			}
		}else{
			LOG("Discord_Minecraft : Rcon connection can't be established. All Rcon function will be disable");
		}
	}else{
		LOG("Discord_Minecraft : Error occured in loading of rconLogs. All Rcon function will be disable");
	}
	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("command"))this->launchCommande(e);});
}

bool Discord_Minecraft::testConnexion(){
	if(RconLoaded){
		if(RconValide){
			if(RconAuthentified){
				return true;
			}else{
				ptrBot->CreateMessage(ChannelLastMessage, "Impossible de s'authentifier sur le serveur. Vérifier le fichier de configuration !");
				return false;
			}
		}else{
			ptrBot->CreateMessage(ChannelLastMessage, "Impossible d'établir la connexion avec le serveur. Vérifier le fichier de configuration !");
			return false;
		}
	}else{
		ptrBot->CreateMessage(ChannelLastMessage, "Impossible de faire d'envoyer des commandes. Fichier de configuration invalide !");
		return false;
	}
	return true;
}

void Discord_Minecraft::EventsMessageCreated(ValueMap payload){
	for(auto &e : EventsMapMessageCreated){
		e(payload);
	}
}