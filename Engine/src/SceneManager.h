#pragma once
#include "Scene.h"

//Fix a better place for it
enum class EScene
{
	None,
	Menu,
	Game,
	Editor
};

class SceneHandler
{
private:
	std::unique_ptr<Scene>	m_currentScene;
	EScene					m_currentSceneType;

public:
	SceneHandler();
	~SceneHandler();

	Scene* GetScene();
	void UpdateScene();
	void SetScene(const EScene& scene);
	const EScene& GetSceneType() const;
};

/*
	Use this to get access to the scenemanager from anywhere.
*/
class SceneAccess
{
private:
	SceneAccess() = default;
	~SceneAccess() = default;

	SceneHandler* m_sceneHandler = nullptr;
	static auto& Get();

public:
	static void SetSceneHandler(SceneHandler* handler);
	static SceneHandler* GetSceneHandler();

};
