#pragma once
#include "Sprite.h"

class SceneHandler
{
private:
	std::string m_currentScene;

	//Unique ID
	unsigned int m_spriteUID;
	unsigned int m_guiUID;

	std::unordered_map<unsigned int, std::unique_ptr<Sprite>> m_sprites;
	std::unordered_map<unsigned int, irr::gui::IGUIStaticText*> m_texts;

	irr::scene::ICameraSceneNode* m_camera;

private:
	//Singleton standard
	SceneHandler();
	~SceneHandler();
	SceneHandler(SceneHandler const&) = delete;
	SceneHandler(SceneHandler const&&) = delete;
	SceneHandler& operator=(SceneHandler const&) = delete;
	SceneHandler& operator=(SceneHandler const&&) = delete;
	static auto& Get();

	//Help functions to make the code cleaner
	void ResetScene();
	bool LoadScene(const std::string& file);

public:
	/*
		Adjust the scene
	*/
	static void LoadStartScene();
	static void ChangeScene(const std::string& file);
	static void UpdateScene();

	/*
		Sprites
	*/
	static unsigned int AddSprite(const std::string& file);
	static void RemoveSprite(const unsigned int& id);
	static void ChangeSprite(const unsigned int& id, const std::string& file);
	static void SetSpriteVisible(const unsigned int& id, const bool& isVisible);
	static void SetSpritePosition(const unsigned int& id, const irr::core::vector3df& pos);
	static void SetSpriteScale(const unsigned int& id, const irr::core::vector3df& scl);
	static void SetSpriteRotation(const unsigned int& id, const irr::core::vector3df& rot);

	/*
		Camera
	*/
	static void AddCamera();
	static void SetCameraPosition(const irr::core::vector3df& pos);
	static void SetCameraTarget(const irr::core::vector3df& tar);
	static void SetCameraFOV(const float& fov);

	/*
		GUI
	*/
	static unsigned int AddText(const std::string& text, const std::string& font,
								irr::core::vector2di pos, irr::core::vector2di size);
	static void SetTextAlignment(const unsigned int& id, const irr::gui::EGUI_ALIGNMENT& alignment);
	static void UpdateText(unsigned int& id, const std::string& text);
	static unsigned int AddButton(const std::string& text, const std::string& font,
								 irr::core::vector2di pos, irr::core::vector2di size);

	static void RemoveGUI(unsigned int id);
	static bool IsButtonPressed(unsigned int id);

	static irr::core::line3df GetRayFromScreenCoords(irr::core::vector2di screenCoords);

};