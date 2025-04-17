#pragma once
#include <enet.h>

namespace RTE {

	class NetworkServer {
	public:
		void Create(enet_uint32 port);
		void UpdateRecieved();
		void Update();
		void Destroy();
	private:
		ENetHost* p_EnetServer;
		void Log(std::string strToPrint);
	};
} // namespace RTE