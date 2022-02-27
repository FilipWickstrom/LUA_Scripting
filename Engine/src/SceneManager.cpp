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
        p->SetActive();

    return p;
}
