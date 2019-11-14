#include <Core/Core.h>
#include "Discord_Minecraft.h"

using namespace Upp;

void Discord_Minecraft::PrepareEvent(){
	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("commande"))LaunchCommande();});
	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("say"))SaySomething();});
	EventsMapMessageCreated.Add([&](ValueMap e){if(NameOfFunction.IsEqual("clearweather"))ClearWeather();});
}

void Discord_Minecraft::PrepareRcon(){
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
}


//!mc commande(commande:ExempleCommande)
void Discord_Minecraft::LaunchCommande(){
	if(testConnexion()){
		String commande = "";
		if(MessageArgs.Find("commande") && MessageArgs.Get("commande").GetTypeName().IsEqual("String"))commande = MessageArgs.Get("commande").Get<String>();
		
		if(commande.GetCount() != 0){
			if(	AuthorId.IsEqual("131865910121201664") || AuthorId.IsEqual("131915014419382272")){
				myRcon.SendCommand(commande);
				BotPtr->CreateMessage(ChannelLastMessage, "Commande envoyée");
			}else{
				BotPtr->CreateMessage(ChannelLastMessage, "Vous n'avez pas les droits !");
			}
		}else{
			BotPtr->CreateMessage(ChannelLastMessage, "Veuillez mettre une commande !");
		}
	}
}
//!mc clearWeather
void Discord_Minecraft::ClearWeather(){
	if(testConnexion()){
		String command ="weather clear";
		myRcon.SendCommand(command);
		BotPtr->CreateMessage(ChannelLastMessage, "Commande envoyée");
	}
}	
//!mc say(message:Hello World !)
void Discord_Minecraft::SaySomething(){
	if(testConnexion()){
		String toSay = "";
		if(MessageArgs.Find("message") && MessageArgs.Get("message").GetTypeName().IsEqual("String"))toSay = MessageArgs.Get("message").Get<String>();
		if(toSay.GetCount() != 0){
			String command ="say " + toSay;
			myRcon.SendCommand(command);
			BotPtr->CreateMessage(ChannelLastMessage, "Commande envoyée");
		}else{
			BotPtr->CreateMessage(ChannelLastMessage, "Veuillez mettre un message !");
		}
	}
}

Discord_Minecraft::Discord_Minecraft(Upp::String _name, Upp::String _prefix , String RconConfigPath): rconConfig(RconConfigPath) ,myRcon(rconConfig.GetValue<String>("addr"),rconConfig.GetValue<int>("port"),rconConfig.GetValue<String>("password"),rconConfig.GetValue<String>("serviceName")){
	name = _name;
	AddPrefix(_prefix);
	PrepareRcon();
	PrepareEvent();
}

Discord_Minecraft::Discord_Minecraft(Upp::String _name,Upp::Vector<String> _prefix,String RconConfigPath): rconConfig(RconConfigPath) ,myRcon(rconConfig.GetValue<String>("addr"),rconConfig.GetValue<int>("port"),rconConfig.GetValue<String>("password"),rconConfig.GetValue<String>("serviceName")){
	name = _name;
	AddPrefix(_prefix);
	PrepareRcon();
	PrepareEvent();
}



bool Discord_Minecraft::testConnexion(){
	if(RconLoaded){
		if(RconValide){
			if(RconAuthentified){
				return true;
			}else{
				BotPtr->CreateMessage(ChannelLastMessage, "Impossible de s'authentifier sur le serveur. Vérifier le fichier de configuration !");
				return false;
			}
		}else{
			BotPtr->CreateMessage(ChannelLastMessage, "Impossible d'établir la connexion avec le serveur. Vérifier le fichier de configuration !");
			return false;
		}
	}else{
		BotPtr->CreateMessage(ChannelLastMessage, "Impossible de faire d'envoyer des commandes. Fichier de configuration invalide !");
		return false;
	}
	return true;
}

String Discord_Minecraft::Credit(ValueMap json,bool sendCredit){
	String credit =  "----Minecraft Module have been made By Clément Hamon---\n";
	credit << "-----------https://github.com/Xemuth-----------\n";
	credit << "Minecraft module is used to do minecraft command over Discord\nLike cleaning the weather or speak to the server\nAll this by using RCON communication\n";
	credit << "https://github.com/Xemuth/RconManager\nhttps://github.com/Xemuth/Discord_Minecraft";
	if(sendCredit) BotPtr->CreateMessage(ChannelLastMessage,"```"+credit +"```");
	return credit;
}

void Discord_Minecraft::Help(ValueMap payload){
	Upp::String help;
	
	help << "```";
	help << "Commandes module discord Minecraft No "  << 1  << "/" << 1 << "\n";
	help << "!mc Commande(Commande:tp Xemuth Salty_Diviper)" <<" -> Execute la command passé en paramètre sur le serveur, vous devez être l'élu. Ses arguments sont 'commande'\n\n";
	help << "!mc Say(Message:Hello world from SmartUppBot !)"<<" -> Ecrit un message global sur le serveur minecraft.Ses arguments sont 'commande'\n\n";
	help << "!mc ClearWeather"<<" -> Clean la météo du serveur. Cette fonction ne possède pas d'arguments\n\n";
	help << "!mc Credit" <<" -> Affiche les crédit du module minecraft. Cette fonction ne possède pas d'arguments\n\n";
	help <<"```";
	
	
	BotPtr->CreateMessage(this->ChannelLastMessage, help);
}

void Discord_Minecraft::EventsMessageCreated(ValueMap payload){
	for(auto &e : EventsMapMessageCreated){
		e(payload);
	}
}