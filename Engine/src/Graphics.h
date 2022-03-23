#pragma once

constexpr unsigned int window_width = 1440;
constexpr unsigned int window_height = 900;

class Graphics
{
private:

	// General Devices
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_sceneManager;
	irr::gui::IGUIEnvironment* m_guiEnvironment;

	// Memory Management - not in use?
	std::unordered_map<std::string, irr::scene::ISceneNode*> m_nodes;

	// Delta time
	double dt;

private:
	Graphics();
	~Graphics();
	static auto& Get();

public:

	static irr::IrrlichtDevice* GetDevice();
	static irr::video::IVideoDriver* GetDriver();
	static irr::scene::ISceneManager* GetSceneManager();
	static irr::gui::IGUIEnvironment* GetGUIEnvironment();

	static double& GetDeltaTime();
};