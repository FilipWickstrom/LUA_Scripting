#pragma once
#include "Scene.h"

class GameScene : public Scene
{
private:

public:
	GameScene();
	~GameScene();

	void UpdateCamera();

	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};
