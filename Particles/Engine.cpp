#include "Engine.h"
#include <iostream>

using namespace std;

Engine::Engine() {
	m_Window.create(sf::VideoMode(1920, 1080), "Particles");
}

void Engine::run()
{
	Clock clock;
	Particle particle();
	while (m_Window.isOpen())
	{
		clock.restart();
		Time currentSec = clock.getElapsedTime();
		currentSec.asSeconds();
		input();
		update;
		draw;
	}
}

void Engine::input()
{
	RenderTarget target();
	Event event;
	while (m_Window.pollEvent(event))
	{
		if (event.type == Event::Closed || event.type == sf::Keyboard::Scan::Escape	)
		{
			m_Window.close();
		}
		if (event.type == sf::Mouse::Left)
		{
			for (int i = 0; i < 5; i++)
			{
				random_device rd;
				mt19937 gen(rd());
				uniform_int_distribution<> disrt(25, 50);
				m_particles.emplace_back(m_Window, disrt, sf::Mouse::getPosition(m_Window));
			}
		}
	}
}

void Engine::update(float dtAsSeconds)
{
	vector<Particle>::iterator iter;
	for (iter = m_particles.begin(); iter != m_particles.end();)
	{
		if (iter->getTTL() > 0.0)
		{
			iter->update(dtAsSeconds);
			iter++;
		}
		else
		{
			m_particles.erase(iter);
		}
	}
}

void Engine::draw()
{
	m_Window.clear();
	for (int i = 0; i < m_particles.size(); i++)
	{
		m_Window.draw(m_particles[i]);
	}
	m_Window.display();
}