#pragma once

class Graphics
{
private:
	struct window 
	{
		std::string name;
		unsigned int width;
		unsigned int height;
		bool fullscreen;
		bool vsync;
		irr::video::E_DRIVER_TYPE driverType;
	} m_window;

	// General Irrlicht Devices
	irr::IrrlichtDevice* m_device;
	irr::video::IVideoDriver* m_driver;
	irr::scene::ISceneManager* m_sceneManager;
	irr::gui::IGUIEnvironment* m_guiEnvironment;

	// Memory Management - not in use?
	std::unordered_map<std::string, irr::scene::ISceneNode*> m_nodes;

	// Delta time
	double m_dt;

private:
	Graphics();
	~Graphics();
	static auto& Get();

	void LoadOptionsLUA(const std::string& luafile);

public:

	static irr::IrrlichtDevice* GetDevice();
	static irr::video::IVideoDriver* GetDriver();
	static irr::scene::ISceneManager* GetSceneManager();
	static irr::gui::IGUIEnvironment* GetGUIEnvironment();

	static double& GetDeltaTime();
	static unsigned int& GetWindowWidth();
	static unsigned int& GetWindowHeight();
	static void UpdateWindowCaption();
};