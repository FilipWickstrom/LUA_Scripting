#pragma once
#include "Sprite.h"
#include "CppToLua.h"


class Graphics;

class Scene
{
private:
	static unsigned int s_Sprite_ID;
	static unsigned int s_GUI_ID;

protected:
	std::unordered_map<unsigned int, std::unique_ptr<Sprite>> m_sprites;
	std::unordered_map<unsigned int, irr::gui::IGUIStaticText*> m_texts;
	irr::scene::ICameraSceneNode* m_camera;

public:
	Scene();
	virtual ~Scene();

	virtual void Load() = 0;
	virtual void Clean() = 0;
	virtual void Update() = 0;

	/*
		Sprites
	*/
	unsigned int AddSprite(	const std::string& file);
	void RemoveSprite(		const unsigned int& id);
	void ChangeSprite(	    const unsigned int& id, const std::string& file);
	void SetSpriteVisible(  const unsigned int& id, const bool& isVisible);
	void SetSpritePosition(	const unsigned int& id, const irr::core::vector3df& pos);
	void SetSpriteScale(	const unsigned int& id, const irr::core::vector3df& scl);
	void SetSpriteRotation(	const unsigned int& id, const irr::core::vector3df& rot);

	/*
		Camera
	*/
	void AddCamera();
	void SetCameraPosition(const irr::core::vector3df& pos);
	void SetCameraTarget(const irr::core::vector3df& tar);
	void SetCameraFOV(const float& fov);

	/*
		GUI
	*/
	unsigned int AddText(const std::string& text, const std::string& font,
						irr::core::vector2di pos, irr::core::vector2di size);
	void SetTextAlignment(const unsigned int& id, const irr::gui::EGUI_ALIGNMENT& alignment);

	void UpdateText(unsigned int& id, const std::string& text);
	unsigned int AddButton(const std::string& text, const std::string& font,
						irr::core::vector2di pos, irr::core::vector2di size);

	void RemoveGUI(unsigned int id);
	bool IsButtonPressed(unsigned int id);

	irr::core::line3df GetRayFromScreenCoords(irr::core::vector2di screenCoords);
};