#pragma once

class Renderer
{
private:
	std::thread  m_conThread;

private:
	void Update();
	void Render();

public:
	Renderer();
	~Renderer();
	void Run();

};