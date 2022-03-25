#pragma once
#include "Scene.h"
#include "EnemyManager.h"

class GameScene : public Scene
{
private:
	// Lua manager for all enemies.
	irr::scene::ICameraSceneNode* m_gameCamera;
	EnemyManager m_enemyManager;

public:
	GameScene();
	~GameScene();

	// Specific functions for this scene
	void AddBasicEnemy(float x, float y);


	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};
