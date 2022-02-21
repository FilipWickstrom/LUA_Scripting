#pragma once
#include "Includer.h"

class Game
{
private:

	SceneManager m_sceneManager;
	Scene* m_currentScene;

	// Put any update events here.
	void Update();

public:

	Game();
	~Game() = default;

	// This handles update events and drawing commands.
	void Run();
};