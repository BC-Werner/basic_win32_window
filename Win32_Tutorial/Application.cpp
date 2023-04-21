#include "Application.h"

Application::Application()
	: m_pWindow(nullptr)
{
	std::cout << "Creating Window" << std::endl;

	if (!m_pWindow)
		m_pWindow = new Window();
}

Application::~Application()
{
	if (m_pWindow)
		delete m_pWindow;
}

void Application::run()
{
	while (running)
	{
		if (!m_pWindow->ProcessMessages())
		{
			std::cout << "Closing Window" << std::endl;
			running = false;
		}

		// Render
		Sleep(10);
	}
}
