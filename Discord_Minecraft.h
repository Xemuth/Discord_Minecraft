#ifndef _Discord_Minecraft_Discord_Minecraft_h_
#define _Discord_Minecraft_Discord_Minecraft_h_
#include <SmartUppBot/SmartBotUpp.h>

using namespace Upp;
class Discord_Minecraft: public DiscordModule{
	private:
	
		void launchCommande(ValueMap payload);
		
	public:
		
		Discord_Minecraft(Upp::String _name, Upp::String _prefix);
		
		void Event(ValueMap payload);
	
	
};
#endif
