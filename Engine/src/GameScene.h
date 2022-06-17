#pragma once
#include "Scene.h"

class GameScene : public Scene
{
private:

public:
	GameScene() = default;
	~GameScene() = default;

	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};
