#pragma once
#include <enet.h>

namespace RTE {

	class NetworkClient {
	public:
		void Connect(std::string ip, int port);
		void Update();
		void UpdateRecieved();
		void Destroy();
	private:
		ENetHost* p_EnetClient;
		ENetPeer* p_EnetPeer;
		void Log(std::string strToPrint);
	};
} // namespace RTE