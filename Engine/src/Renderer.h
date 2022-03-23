#pragma once

class Renderer
{
private:
	SceneHandler m_sceneHandler;

private:
	void Update();
	void Render();

public:
	Renderer();
	~Renderer();
	void Run();

};