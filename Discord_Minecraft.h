#ifndef _Discord_Minecraft_Discord_Minecraft_h_
#define _Discord_Minecraft_Discord_Minecraft_h_
#include <SmartUppBot/SmartBotUpp.h>
#include <RconManager/RconManager.h>
#include <EasyConfiguration/EasyConfiguration.h>
using namespace Upp;
class Discord_Minecraft: public DiscordModule{
	private:
		void launchCommande(ValueMap payload);
		void clearWeather(ValueMap payload);
		void saySomething(ValueMap payload);
		bool testConnexion();
		
		EasyConfiguration rconConfig;
		RconManager myRcon;
		
		bool RconLoaded = false;
		bool RconValide =false;
		bool RconAuthentified = false;
	public:
		
		void Help(ValueMap payload);
		virtual String Credit(ValueMap json,bool sendCredit = true);
		
		Discord_Minecraft(Upp::String _name,Upp::String _prefix,String RconConfigPath="");
		void EventsMessageCreated(ValueMap payload);
};
#endif
