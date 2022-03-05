#include "PCH.h"
#include "SceneManager.h"

SceneManager::SceneManager()
{
    AddScene();
}

SceneManager::~SceneManager()
{

}

void SceneManager::AddScene()
{
    m_scenes.push_back(Scene());
}

Scene* SceneManager::GetScene(const size_t& scene_pos)
{
    Scene* p = nullptr;
    p = &m_scenes[scene_pos];
    
    // Set this to the active scene.
    if (p)
    {
        m_currentScene = scene_pos;
        p->SetActive();
    }

    return p;
}

Scene* SceneManager::GetCurrentScene()
{
    return &m_scenes[m_currentScene];
}

auto& SceneAccess::Get()
{
    static SceneAccess instance;
    return instance;
}

void SceneAccess::SetSceneManager(SceneManager* man)
{
    SceneAccess::Get().m_sceneManager = man;
}

SceneManager* SceneAccess::GetSceneManager()
{
    return SceneAccess::Get().m_sceneManager;
}
