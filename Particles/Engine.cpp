#include "Engine.h"
#include <iostream>

using namespace std;

Engine::Engine() {
	m_Window.create(sf::VideoMode(1920, 1080), "Particles");
}

void Engine::run()
{
	Clock clock;
	cout << "Starting Particle unit tests..." << endl;
    	Particle p(m_Window, 4, { (int)m_Window.getSize().x / 2, (int)m_Window.getSize().y / 2 });
    	p.unitTests();
    	cout << "Unit tests complete.  Starting engine..." << endl;
    	while (m_Window.isOpen())
    	{
        	Time dt = clock.restart();
        	float dtAsSeconds = dt.asSeconds();
        	input();
        	update(dtAsSeconds);
        	draw();
    	}
}

void Engine::input()
{
	sf::Event event;
    while (m_Window.pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            m_Window.close();
        }
        else if (event.type == sf::Event::MouseButtonPressed)
        {
            if (event.mouseButton.button == sf::Mouse::Left)
            {
                // Add new particle at mouse position
                for (int i = 0; i < 5; i++) {
                    int rnd = rand() % 51 + 20;
                    m_particles.emplace_back(m_Window, rnd, sf::Mouse::getPosition(m_Window));
                }
            }
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Escape)
            {
                m_Window.close();
            }
        }
    }
}

void Engine::update(float dtAsSeconds)
{
	for (auto& particle : m_particles)
    	{
		particle.update(dtAsSeconds);
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
