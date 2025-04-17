#include "NetworkClient.h"
#include <ConsoleMan.h>
#include <Networking.h>
#include <thread>

using namespace RTE;

void NetworkClient::Connect(std::string ip, int port) {
	ENetAddress address = {0};
	address.port = port;

	p_EnetClient = enet_host_create(NULL, 1, 2, 0, 0);

	if (p_EnetClient == NULL) {
		Log("An error occurred while trying to create an ENet client host");
		return;
	} else {
		//Log("Started client!");
	}

	enet_address_set_host(&address, ip.c_str());
	p_EnetPeer = enet_host_connect(p_EnetClient, &address, 2, 0);
	UpdateRecieved(1000);
	/*
	ENetEvent netEvent;
	if (enet_host_service(p_EnetClient, &netEvent, 3000) > 0) {
		switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				Log("Connected to the server!");
				break;
		}
	}
	else {
		Log("Can't connect to the server!");
		g_Networking.Destroy();
	}
	*/
}

void NetworkClient::Update() {
	UpdateRecieved();
}

void NetworkClient::UpdateRecieved(int delay) {
	ENetEvent netEvent;
	if (enet_host_service(p_EnetClient, &netEvent, delay) > 0) {
		switch (netEvent.type) {
			case ENET_EVENT_TYPE_CONNECT:
				Connected = true;
				Log("Connected to the server!");
				break;
			case ENET_EVENT_TYPE_RECEIVE:
				break;
			case ENET_EVENT_TYPE_DISCONNECT_TIMEOUT:
			case ENET_EVENT_TYPE_DISCONNECT:
				Log("Can't connect to the server!");
				Connected = false;
				g_Networking.Destroy();
				break;
		}
	}
}

void NetworkClient::Destroy() {
	enet_peer_disconnect(p_EnetPeer, 0);
	enet_peer_reset(p_EnetPeer);
	enet_host_destroy(p_EnetClient);
}

void NetworkClient::Log(std::string strToPrint) {
	g_ConsoleMan.PrintString("CLIENT: " + strToPrint);
}