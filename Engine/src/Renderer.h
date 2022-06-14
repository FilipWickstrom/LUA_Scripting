#pragma once

class Renderer
{
private:
	SceneHandler m_sceneHandler;
	std::thread  m_conThread;

private:
	bool Update();
	void Render();

public:
	Renderer();
	~Renderer();
	void Run();

};