#include "Application.hpp"
#include "TestWorld.hpp"
#include <string.h>
#include <stdio.h>

Application *Application::m_App = nullptr;

Application *Application::getSingleton()
{
	if (m_App == nullptr)
		m_App = new Application();
	return m_App;
}

void Application::initialize()
{
	videoMode.width = 1280;
	videoMode.height = 720;
	videoMode.bitsPerPixel = 32;
	
	dt = 1.0f / 60.0f;
	timeNow = gameClock.getElapsedTime().asSeconds();
	timeFrame = 0.0f;
	timeActual = 0.0f;
	accumulator = 0.0f;
	
	enableVSync = false;
	doForceFPS = true;
	forceFPS = 60;
}

void Application::release()
{
	popAllWorlds();
	delete m_App;
}

void Application::pushWorld(GameWorld *world)
{
	this->world.push(world);
}

void Application::popWorld()
{
	GameWorld *world = cont_worlds.top();
	cont_worlds.pop();
	delete world;
}

void Application::popAllWorlds()
{
	for (int i = 0; i < cont_worlds.size(); ++i)
	{
		GameWorld *world = cont_worlds.top();
		cont_worlds.pop();
		delete world;
	}
}

bool Application::parseArguments(int argc, char **argv)
{
	for (int i = 1; i < argc; i++)
	{
		if ((strcmp("-fps", argv[i]) == 0) || (strcmp(argv[i], "--force-fps") == 0))
		{
			if (strcmp(argv[i + 1], "off") == 0)
			{
				printf("Setting doForceFPS to false\n");
				doForceFPS = false;
			}
			else
			{
				printf("Setting FPS lock to %s\n", argv[i + 1]);
				doForceFPS = true;
				forceFPS = atoi(argv[i + 1]);
			}
			enableVSync = false;
		}
		else if ((strcmp(argv[i], "-vsync") == 0) || (strcmp(argv[i], "--enable-vsync") == 0))
		{
			doForceFPS = false;
			enableVSync = true;
		}
		else
		{
			if (argv[i][0] == '-')
				printf("Warning: Unrecognized command line argument \"%s\"\n", argv[i]);
		}
	}
	return true;
}

int Application::run(int argc, char **argv)
{
	if (!parseArguments(argc, argv)) return 0;
	
	rwin.create(videoMode, "Smooth Movement Test", !sf::Style::Resize | sf::Style::Close);
	
	if (doForceFPS) rwin.setFramerateLimit(forceFPS);
	if (enableVSync) rwin.setVerticalSyncEnabled(true);
	
	pushWorld(new TestWorld());
	
	while (rwin.isOpen())
	{
		sf::Event event;
		while (rwin.pollEvent(event))
		{
			world.top()->input(event);
			switch (event.type)
			{
				case sf::Event::Closed:
					rwin.close();
				break;
			}
		}
		
		timeNow = gameClock.getElapsedTime().asSeconds();
		timeFrame = timeNow - timeActual;
		
		if (timeFrame > 0.25f)
			timeFrame = 0.25f;
		
		timeActual = timeNow;
		accumulator += timeFrame;
		
		while (accumulator >= dt)
		{
			world.top()->update(dt);
			accumulator -= dt;
		}
		
		const float interpolation = accumulator / dt;
		
		rwin.clear(sf::Color(120, 120, 120));
		world.top()->draw(rwin, interpolation);
		rwin.display();
	}
	release();
	return 0;
}
