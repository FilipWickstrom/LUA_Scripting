#pragma once
#include <irrlicht.h>
#include <unordered_map>

class Graphics
{
private:

	// General Devices
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_sceneManager;
	irr::gui::IGUIEnvironment* m_guiEnvironment;

	// Memory Management
	std::unordered_map<std::string, irr::scene::ISceneNode*> m_nodes;

	Graphics();
	~Graphics();

public:

	static auto& Get();
	static irr::IrrlichtDevice* GetDevice();
	static irr::video::IVideoDriver* GetDriver();
	static irr::scene::ISceneManager* GetSceneManager();
	static irr::gui::IGUIEnvironment* GetGUIEnvironment();

};