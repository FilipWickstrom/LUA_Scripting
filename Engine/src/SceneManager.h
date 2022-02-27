#pragma once
#include "Scene.h"

class SceneManager
{
private:

	std::vector<Scene> m_scenes;

public:

	SceneManager();
	~SceneManager();

	void AddScene();

	/*
		Use this if you want to switch to another scene.
		The game will now actively use this scenes camera
		and models.
	*/
	Scene* GetScene(const size_t& scene_pos);
};