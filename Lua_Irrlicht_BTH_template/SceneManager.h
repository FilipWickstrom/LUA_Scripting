#pragma once
#include "Scene.h"
#include <unordered_map>
#include <string>

class SceneManager
{
private:

	std::unordered_map<std::string, Scene> m_scenes;
	SceneManager();
	~SceneManager();

public:

	static auto& Get();
	static void AddScene(const std::string& sceneName);
	static Scene& GetScene(const std::string& sceneName);

};