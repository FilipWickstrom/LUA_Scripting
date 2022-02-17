#include "SceneManager.h"

SceneManager::SceneManager()
{
}

SceneManager::~SceneManager()
{
}

auto& SceneManager::Get()
{
    static SceneManager instance;
    return instance;
}

void SceneManager::AddScene(const std::string& sceneName)
{
    Scene newScene;
    Get().m_scenes.emplace(sceneName, newScene);
}

Scene& SceneManager::GetScene(const std::string& sceneName)
{
    return Get().m_scenes.at(sceneName);
}
