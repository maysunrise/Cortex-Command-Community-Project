#define ENET_IMPLEMENTATION

#include "Networking.h"
#include <ConsoleMan.h>
#include <PresetMan.h>
#include <LuaMan.h>
#include <MetaMan.h>
#include <enet.h>
#include <thread>
#include <MenuMan.h>
#include <MetaGameGUI.h>

using namespace RTE;

RTE::Networking::Networking() {
}

void Networking::StartGame(int mode) {
	int enetStatus = enet_initialize();
	if (enetStatus != 0) {
		g_ConsoleMan.PrintString("An error occurred while initializing ENet. Status - " + enetStatus);
		return;
	}

	if (g_MetaMan.GameInProgress()) {
		g_MetaMan.EndGame();
	}
	g_LuaMan.FileCloseAll();

	Activity* pActivity = GetActivityByName("Test Activity");
	Scene* pScene = GetSceneByName("Tutorial Bunker");
	if (pActivity == nullptr) {
		g_ConsoleMan.PrintString("Networking: activity is NULL");
		return;
	}
	if (pScene == nullptr) {
		g_ConsoleMan.PrintString("Networking: scene is NULL");
		return;
	}
	//pActivity->ClearPlayers(false);
	//pActivity->AddPlayer(1, true, 1, 10000);

	if (g_ActivityMan.ActivityRunning()) {
		g_ActivityMan.EndActivity();
	}

	// Prepare the scene
	g_SceneMan.SetSceneToLoad(pScene, true, true);

	//g_ActivityMan.SetRestartActivity();
	// Start the game
	g_ActivityMan.StartActivity(pActivity);

	g_MetaMan.SetSuspend(false);

	g_MenuMan.ForceResumeGame();

	if (mode == 0) { // Host
		IsHost = true;
		p_Server = new NetworkServer();
		p_Server->Create(7777);
		
		std::thread serverThread([this]() {
			while (p_Server) {
				p_Server->UpdateRecieved();
			}
		});
		serverThread.detach();
		
		// Since the host is also a player, we create a client
		p_Client = new NetworkClient();
		p_Client->Connect("127.0.0.1", 7777);
	} else { // Client
		IsHost = false;
		p_Client = new NetworkClient();
		p_Client->Connect("127.0.0.1", 7777);
	}
}

void Networking::Update() {
	if (p_Server) {
		p_Server->Update();
	}
	if (p_Client) {
		p_Client->Update();
	}
	//g_ConsoleMan.PrintString("Server active: " + m_Server->IsActive());
}

void Networking::Destroy() {
	enet_deinitialize();
	if (p_Server) {
		delete p_Server;
	}
	if (p_Client) {
		delete p_Client;
	}
	if (g_MetaMan.GameInProgress()) {
		g_MetaMan.EndGame();
	}
	if (g_ActivityMan.ActivityRunning()) {
		g_ActivityMan.EndActivity();
	}
}

Scene* Networking::GetSceneByName(const std::string name) {
	std::list<Entity*> presetList;
	g_PresetMan.GetAllOfType(presetList, "Scene");
	for (std::list<Entity*>::iterator itr = presetList.begin(); itr != presetList.end(); ++itr) {
		Scene* pScene = dynamic_cast<Scene*>(*itr);
		if (pScene) {
			if (pScene->GetPresetName() == name) {
				return pScene;
			}
		}
	}
	g_ConsoleMan.PrintString("Networking: Scene with name " + name + " not found!");
	return nullptr;
}

Activity* Networking::GetActivityByName(const std::string name) {
	std::list<Entity*> presetList;
	g_PresetMan.GetAllOfType(presetList, "Activity");
	for (std::list<Entity*>::iterator itr = presetList.begin(); itr != presetList.end(); ++itr) {
		Activity* pActivity = dynamic_cast<Activity*>(*itr);
		if (pActivity) {
			//g_ConsoleMan.PrintString("Networking: Activity: " + pActivity->GetPresetName());
			if (pActivity->GetPresetName() == name) {
				return pActivity;
			}
		}
	}
	g_ConsoleMan.PrintString("Networking: Activity with name " + name + " not found!");
	return nullptr;
}