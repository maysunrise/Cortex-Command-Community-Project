#include "MultiplayerGameGUI.h"

#include "GUI.h"
#include "AllegroScreen.h"
#include "GUIInputWrapper.h"
#include "GUICollectionBox.h"
#include "GUILabel.h"
#include "GUIButton.h"
#include "GUIListBox.h"
#include <ConsoleMan.h>
#include <Networking.h>

using namespace RTE;

MultiplayerGameGUI::MultiplayerGameGUI(AllegroScreen* guiScreen, GUIInputWrapper* guiInput) {
	m_GUIControlManager = std::make_unique<GUIControlManager>();
	m_GUIControlManager->Create(guiScreen, guiInput, "Base.rte/GUIs/Skins/Menus", "MainMenuSubMenuSkin.ini");
	m_GUIControlManager->Load("Base.rte/GUIs/MultiplayerGameGUI.ini");

	m_BackToMainButton = dynamic_cast<GUIButton*>(m_GUIControlManager->GetControl("ButtonBackToMainMenu"));
	m_HostButton = dynamic_cast<GUIButton*>(m_GUIControlManager->GetControl("HostButton"));
	m_ConnectButton = dynamic_cast<GUIButton*>(m_GUIControlManager->GetControl("ConnectButton"));

	//GUICollectionBox* rootBox = dynamic_cast<GUICollectionBox*>(m_GUIControlManager->GetControl("base"));
}

bool MultiplayerGameGUI::HandleInputEvents() {
	m_GUIControlManager->Update();
	GUIEvent guiEvent;
	while (m_GUIControlManager->GetEvent(&guiEvent)) {
		if (guiEvent.GetType() == GUIEvent::Command) {
			if (guiEvent.GetControl() == m_BackToMainButton) {
				g_ConsoleMan.PrintString("MP: Exit back to menu");
				return true;
			} else if (guiEvent.GetControl() == m_HostButton) {
				Host();
				return false;
			} else if (guiEvent.GetControl() == m_HostButton) {
				Connect();
				return false;
			}
		}
	}
	return false;
}
void MultiplayerGameGUI::Host() {
	g_ConsoleMan.PrintString("Starting host");
	StartGame(0);
}
void MultiplayerGameGUI::Connect() {
	g_ConsoleMan.PrintString("Starting client");
	StartGame(1);
}

void MultiplayerGameGUI::StartGame(int mode) {
	g_GUISound.ConfirmSound()->Play();
	g_Networking.StartGame(mode);
}

void MultiplayerGameGUI::Draw() const {
	m_GUIControlManager->Draw();
}