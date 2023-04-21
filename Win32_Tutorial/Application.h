#pragma once
#include <iostream>

#include "Window.h"

class Application
{
public:
	Application();
	~Application();

	void run();

private:
	Window* m_pWindow;
	bool running = true;

};

