#pragma once
#include "Scene.h"

class SceneManager
{
private:

	std::vector<Scene> m_scenes;
	size_t m_currentScene = 0;

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

	Scene* GetCurrentScene();
};

/*
	Use this to get access to the scenemanager from anywhere.
*/
class SceneAccess
{
private:

	SceneAccess() = default;
	~SceneAccess() = default;

	SceneManager* m_sceneManager = nullptr;

public:

	static auto& Get();

	static void SetSceneManager(SceneManager* man);
	static SceneManager* GetSceneManager();

};