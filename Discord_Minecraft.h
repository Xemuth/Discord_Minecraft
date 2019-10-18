#ifndef _Discord_Minecraft_Discord_Minecraft_h_
#define _Discord_Minecraft_Discord_Minecraft_h_
#include <SmartUppBot/SmartBotUpp.h>
#include <RconManager/RconManager.h>
#include <EasyConfiguration/EasyConfiguration.h>
using namespace Upp;
class Discord_Minecraft: public DiscordModule{
	private:
		EasyConfiguration rconConfig;
	
		void launchCommande(ValueMap payload);
		RconManager myRcon;
		bool RconLoaded = false;
		bool RconValide =false;
		bool RconAuthentified = false;
	public:
		
		Discord_Minecraft(Upp::String _name, Upp::String _prefix,String RconConfigPath="");
		
		void EventsMessageCreated(ValueMap payload);
	
	
};
#endif
