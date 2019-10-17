#ifndef _Discord_Minecraft_Discord_Minecraft_h_
#define _Discord_Minecraft_Discord_Minecraft_h_
#include <SmartUppBot/SmartBotUpp.h>
#include <RconManager/RconManager.h>
using namespace Upp;
class Discord_Minecraft: public DiscordModule{
	private:
	
		void launchCommande(ValueMap payload);
		RconManager myRcon;
	public:
		
		Discord_Minecraft(Upp::String _name, Upp::String _prefix);
		
		void EventsMessageCreated(ValueMap payload);
	
	
};
#endif
