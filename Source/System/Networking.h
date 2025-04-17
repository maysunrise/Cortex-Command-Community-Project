#pragma once
#include <NetworkServer.h>
#include <NetworkClient.h>

#undef GetClassName

#define g_Networking Networking::Instance()

namespace RTE {
	class Networking : public Singleton<Networking> {
	public:
		Networking();

		void StartGame(int mode);
		void Update();
		void Destroy();
		Scene* GetSceneByName(const std::string name);
		Activity* GetActivityByName(const std::string name);
	private:
		NetworkServer* p_Server;
		NetworkClient* p_Client;
		bool IsHost;

		// Disallow the use of some implicit methods.
		Networking(const Networking& reference) = delete;
		Networking& operator=(const Networking& rhs) = delete;
	};
}