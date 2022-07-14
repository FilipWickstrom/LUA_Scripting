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
	const irr::scene::IGeometryCreator* m_geoCreator;
	irr::scene::ISceneCollisionManager* m_collManager;

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
	static const irr::scene::IGeometryCreator* GetGeometryCreator();
	static irr::scene::ISceneCollisionManager* GetCollisionManager();

	static double& GetDeltaTime();
	static unsigned int& GetWindowWidth();
	static unsigned int& GetWindowHeight();
	static void UpdateWindowCaption();
};