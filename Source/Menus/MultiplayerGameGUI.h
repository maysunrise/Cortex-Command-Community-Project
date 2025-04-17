#pragma once

#include <vector>
#include <memory>
#include "Controller.h"

struct BITMAP;

namespace RTE {
	class SceneObject;
	class ObjectPickerGUI;
	class PieMenuGUI;
	class GUIControl;
	class GUIScreen;
	class GUIInput;
	class GUIControlManager;
	class GUICollectionBox;
	class GUIComboBox;
	class GUICheckbox;
	class GUITab;
	class GUIListBox;
	class GUITextBox;
	class GUIButton;
	class GUILabel;
	class GUISlider;
	class Entity;
	class Scene;
	class Activity;
	class AllegroScreen;
	class GUIInputWrapper;

	/// Description:
	/// Class history:
	class MultiplayerGameGUI {

		/// Public member variable, method and friend function declarations
	public:
		// Different modes of this editor
		enum GUIMode {
			INACTIVE = 0,
			ACTIVE = 1
		};

		/// Constructor method used to instantiate a MultiplayerGameGUI object in system
		/// memory. Create() should be called before using the object.
		MultiplayerGameGUI(AllegroScreen* guiScreen, GUIInputWrapper* guiInput);

		bool HandleInputEvents();

		void Draw() const;

		/// Protected member variable and method declarations
	protected:
		// Controller which conrols this menu. Not owned
		//Controller* m_pController;

		/// Private member variable and method declarations
	private:
		std::unique_ptr<GUIControlManager> m_GUIControlManager;
		GUIButton* m_BackToMainButton;
		GUIButton* m_HostButton;
		GUIButton* m_ConnectButton;
		// Disallow the use of some implicit methods.
		MultiplayerGameGUI(const MultiplayerGameGUI& reference) = delete;
		MultiplayerGameGUI& operator=(const MultiplayerGameGUI& rhs) = delete;

		void Host();
		void Connect();
		void StartGame(int mode);
	};

} // namespace RTE