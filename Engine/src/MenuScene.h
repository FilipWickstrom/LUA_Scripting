#pragma once
#include "Scene.h"

class MenuScene : public Scene
{
private:
	
public:
	MenuScene() = default;
	~MenuScene() = default;

	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};