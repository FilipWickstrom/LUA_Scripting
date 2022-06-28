#pragma once

class Renderer
{
private:
	std::thread  m_conThread;

public:
	Renderer();
	~Renderer();
	void Run();

};