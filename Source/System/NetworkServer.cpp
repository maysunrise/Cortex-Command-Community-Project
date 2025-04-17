#define MAX_PLAYERS 4

#include "NetworkServer.h"
#include <ConsoleMan.h>

using namespace RTE;

void NetworkServer::Create(enet_uint32 port) {
	ENetAddress address = {0};
	address.host = ENET_HOST_ANY;
	address.port = port;

	p_EnetServer = enet_host_create(&address, MAX_PLAYERS, 2, 0, 0);

	if (p_EnetServer == NULL) {
		Log("An error occurred while trying to create an ENet server");
		return;
	}
	else {
		Log("Started server!");
	}
}

void NetworkServer::Update() {
	UpdateRecieved();
}

// Processing packets
void NetworkServer::UpdateRecieved() {
	ENetEvent netEvent;
	if (enet_host_service(p_EnetServer, &netEvent, 0) > 0){
		switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				Log("Someone connected!");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				break;
			case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
			case ENET_EVENT_TYPE_DISCONNECT:
				Log("Someone disconnected!");
				break;
		}
	}
}

void NetworkServer::Destroy() {
	enet_host_destroy(p_EnetServer);
}

void NetworkServer::Log(std::string strToPrint) {
	g_ConsoleMan.PrintString("SERVER: " + strToPrint);
}