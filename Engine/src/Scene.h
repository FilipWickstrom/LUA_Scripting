#pragma once
#include "Model.h"
#include "CppToLua.h"

class Scene
{
private:
	static unsigned int s_GUI_ID;

protected:
	std::unordered_map<unsigned int, Model> m_models;
	irr::scene::ICameraSceneNode* m_defaultCamera;

public:
	Scene();
	virtual ~Scene();

	virtual void Load() = 0;
	virtual void Clean() = 0;
	virtual void Update() = 0;

	// Models
	unsigned int AddModel(std::string& file);
	void RemoveModel(unsigned int id);
	const irr::scene::ICameraSceneNode* GetCamera() const;

	void UpdatePosition(unsigned int id, const irr::core::vector3df& pos);

	// Camera
	bool RemoveCamera();


	/*
		GUI
	*/
	unsigned int AddText(const std::string& text, const std::string& font,
						irr::core::vector2di pos, irr::core::vector2di size);
	unsigned int AddButton(const std::string& text, const std::string& font,
						irr::core::vector2di pos, irr::core::vector2di size);

	void RemoveGUI(unsigned int id);
	bool IsButtonPressed(unsigned int id);
};