#include "stdafx.h"
#include "GameWindow.h"
#include "SplashScreen.h"
#include "MainMenu.h"
#include "PlayerPaddle.h"
#include "VisibleGameObject.h"

void Game::Start(void)
{
	if (_gameState != Uninitialized)
		return;

	//���ô��ڲ���
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "BallGame");

	//�����ҵ��岢������λ��
	PlayerPaddle* player1 = new PlayerPaddle();
	player1->Load("images/paddle.png");
	player1->SetPosition((1024 / 2) - 45, 700);

	//��ӵ���AI
	AIPaddle* player2 = new AIPaddle();
	player2->SetPosition((SCREEN_WIDTH / 2), 40);

	//��ӵ���
	GameBall* ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	_gameObjectManager.Add("Paddle1", player1);
	_gameObjectManager.Add("Paddle2", player2);
	_gameObjectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	//��Ϸѭ��������Ϸ״̬ΪExiting���˳���Ϸ
	while (!IsExiting())
		GameLoop();
	_mainWindow.close();
}

bool Game::IsExiting()
{
	if (_gameState == Game::Exiting)
		return true;
	else
		return false;
}

void Game::GameLoop()
{
	sf::Event currentEvent;

	//����Ϣ���������ó���Ϣ
	_mainWindow.pollEvent(currentEvent);

	switch (_gameState)
	{
		case Game::ShowingSplash:
		{
			ShowSplashScreen();
			break;
		}
	    case Game::ShowingMenu:
		{
			ShowMenu();
			break;
		}
		case Game::Playing:
		{
			//�ú�ɫ�����Ϸ����
			_mainWindow.clear(sf::Color(0, 0, 0));

			//�������ӵ���̨��ȥ
			_gameObjectManager.UpdateAll();
			_gameObjectManager.DrawAll(_mainWindow);

			_mainWindow.display();

			if (currentEvent.type == sf::Event::Closed)
				_gameState = Game::Exiting;
			if (currentEvent.type == sf::Event::KeyPressed)
			{
				if (currentEvent.key.code == sf::Keyboard::Escape) 
					ShowMenu();
			}
			break;
		}
	}
}

void Game::ShowSplashScreen()
{
	SplashScreen splashScreen;
	splashScreen.Show(_mainWindow);
	_gameState = Game::ShowingMenu;
}

void Game::ShowMenu()
{
	MainMenu mainMenu;
	MainMenu::MenuResult result = mainMenu.Show(_mainWindow);
	switch (result)
	{
		case MainMenu::Exit:
		_gameState = Exiting;
		break;
	    case MainMenu::Play:
		_gameState = Playing;
		break;
	}
}

sf::RenderWindow& Game::GetWindow()
{
	return _mainWindow;
}

//����һ��Event���ͱ�������ϵͳ��Ϣ��������ȡ����Ϣ���ŵ��ñ�����Ȼ�󷵻�
const sf::Event& Game::GetInput()
{
	sf::Event currentEvent;
	_mainWindow.pollEvent(currentEvent);
	return currentEvent;
}

const GameObjectManager& Game::GetGameObjectManager()
{
	return Game::_gameObjectManager;
}

//�˴�Ҫ�ֶ�������̬��������Ȼ�������ᱨ��
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;