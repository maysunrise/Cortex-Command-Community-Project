#pragma once
#include <enet.h>

namespace RTE {

	class NetworkServer {
	public:
		void Create(enet_uint32 port);
		void UpdateRecieved();
		void Update();
		void Destroy();
		void ProcessEvents();
	private:
		ENetHost* p_EnetServer;
		std::queue<ENetEvent> m_NetEvents;
		void Log(std::string strToPrint);
	};
} // namespace RTE