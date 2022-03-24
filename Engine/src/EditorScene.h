#pragma once
#include "Scene.h"

class EditorScene : public Scene
{
private:
	//UI


public:
	EditorScene() = default;
	~EditorScene() = default;

	// Inherited via Scene
	virtual void Load() override;
	virtual void Clean() override;
	virtual void Update() override;
};