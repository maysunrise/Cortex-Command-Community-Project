#pragma once
#include <enet.h>

namespace RTE {

	class NetworkClient {
	public:
		void Connect(std::string ip, int port);
		void Update();
		void UpdateRecieved(int delay = 0);
		void Destroy();
	private:
		ENetHost* p_EnetClient;
		ENetPeer* p_EnetPeer;
		bool Connected;
		void Log(std::string strToPrint);
	};
} // namespace RTE