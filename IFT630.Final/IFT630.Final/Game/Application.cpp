#include "Application.h"
#include "Game/States/GameState.h"
#include "Game/States/PauseState.h"
#include <SFML/Window/Event.hpp>

const sf::Time Application::TimePerFrame = sf::seconds(1.f / 60.f);

Application::Application()
	: m_window{ sf::VideoMode{ 1024, 768 }, "Quickshot", sf::Style::Close }
	, m_stateStack{ State::Context{ m_window, m_textures, m_fonts } }
	, m_updateGame{ true }
	, m_statisticsText{}
	, m_statisticsUpdateTime{}
	, m_statisticsNumFrames{ 0 }
{
	m_window.setVerticalSyncEnabled(true);
	m_window.setKeyRepeatEnabled(false);
	//m_window.setMouseCursorGrabbed(true);

	m_fonts.load(FontsID::Main, "Resources/OpenSans-Light.ttf");

	m_textures.load(TexturesID::ButtonNormal, "Resources/Textures/ButtonNormal.png");
	m_textures.load(TexturesID::ButtonSelected, "Resources/Textures/ButtonSelected.png");
	m_textures.load(TexturesID::ButtonPressed, "Resources/Textures/ButtonPressed.png");

	m_statisticsText.setFont(m_fonts.get(FontsID::Main));
	m_statisticsText.setPosition(5.f, 5.f);
	m_statisticsText.setCharacterSize(10);

	registerStates();
	m_stateStack.pushState(StatesID::Game);
}

void Application::run()
{
	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;

	while (m_window.isOpen())
	{
		sf::Time elapsedTime = clock.restart();
		timeSinceLastUpdate += elapsedTime;

		while (timeSinceLastUpdate > TimePerFrame)
		{
			timeSinceLastUpdate -= TimePerFrame;
			processInput();

			if (m_updateGame)
			{
				update(TimePerFrame);
			}
			
			if (m_stateStack.isEmpty())
			{
				m_window.close();
			}
		}

		updateStatistics(elapsedTime);
		render();
	}
}

void Application::processInput()
{
	sf::Event event;

	while (m_window.pollEvent(event))
	{
		m_stateStack.handleEvent(event);

		switch (event.type)
		{
		case sf::Event::GainedFocus:
			m_updateGame = true;
			break;
		case sf::Event::LostFocus:
			m_updateGame = false;
			break;
		case sf::Event::Closed:
			m_window.close();
			break;
		}
	}
}

void Application::update(sf::Time dt)
{
	m_stateStack.update(dt);
}

void Application::render()
{
	m_window.clear(sf::Color(35, 35, 35));
	m_stateStack.draw();

	m_window.setView(m_window.getDefaultView());
	m_window.draw(m_statisticsText);

	m_window.display();
}

void Application::updateStatistics(sf::Time dt)
{
	m_statisticsUpdateTime += dt;
	m_statisticsNumFrames += 1;

	if (m_statisticsUpdateTime >= sf::seconds(1.0f))
	{
		m_statisticsText.setString("FPS: " + std::to_string(m_statisticsNumFrames));
		m_statisticsUpdateTime -= sf::seconds(1.0f);
		m_statisticsNumFrames = 0;
	}
}

void Application::registerStates()
{
	m_stateStack.registerState<GameState>(StatesID::Game);
	m_stateStack.registerState<PauseState>(StatesID::Pause);
}