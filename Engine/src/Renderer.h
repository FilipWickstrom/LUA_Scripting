#pragma once

class Renderer
{
private:
	std::thread  m_conThread;
	SceneHandler m_sceneHandler;

private:
	bool Update();
	void Render();

public:
	Renderer();
	~Renderer();
	void Run();

};