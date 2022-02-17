#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>

class SceneManager
{
private:

	std::vector<Scene> m_scenes;

public:

	SceneManager();
	~SceneManager();

	void AddScene();
	Scene* GetScene(const size_t& scene_pos);
};