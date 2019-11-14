#ifndef _Discord_Minecraft_Discord_Minecraft_h_
#define _Discord_Minecraft_Discord_Minecraft_h_
#include <SmartUppBot/SmartBotUpp.h>
#include <RconManager/RconManager.h>
#include <EasyConfiguration/EasyConfiguration.h>
using namespace Upp;
class Discord_Minecraft: public DiscordModule{
	private:
		void PrepareEvent();
		//Commands
		void LaunchCommande(ValueMap& payload);
		void ClearWeather(ValueMap& payload);
		void SaySomething(ValueMap& payload);
		void Help(ValueMap& payload);
		virtual String Credit(ValueMap& json,bool sendCredit = true);
	
		//***************
		
		
		EasyConfiguration rconConfig;
		RconManager myRcon;
		
		bool RconLoaded = false;
		bool RconValide =false;
		bool RconAuthentified = false;
		
		
		void PrepareRcon();
		bool testConnexion();
		
	public:
		
		
		
		
		
		Discord_Minecraft(Upp::String _name,Upp::String _prefix,String RconConfigPath="");
		Discord_Minecraft(Upp::String _name,Upp::Vector<String> _prefix,String RconConfigPath=""); // Ici nous passons un vector de prefix si nous avons du multi prefix
		void EventsMessageCreated(ValueMap payload);
};
#endif
