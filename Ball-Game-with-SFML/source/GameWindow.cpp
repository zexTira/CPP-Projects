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

	//设置窗口参数
	_mainWindow.create(sf::VideoMode(1024, 768, 32), "BallGame");

	//添加玩家弹板并设置其位置
	PlayerPaddle* player1 = new PlayerPaddle();
	player1->Load("images/paddle.png");
	player1->SetPosition((1024 / 2) - 45, 700);

	//添加敌人AI
	AIPaddle* player2 = new AIPaddle();
	player2->SetPosition((SCREEN_WIDTH / 2), 40);

	//添加弹球
	GameBall* ball = new GameBall();
	ball->SetPosition((SCREEN_WIDTH / 2), (SCREEN_HEIGHT / 2) - 15);

	_gameObjectManager.Add("Paddle1", player1);
	_gameObjectManager.Add("Paddle2", player2);
	_gameObjectManager.Add("Ball", ball);

	_gameState = Game::ShowingSplash;

	//游戏循环，当游戏状态为Exiting则退出游戏
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

	//从消息队列里面拿出消息
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
			//用黑色填充游戏画面
			_mainWindow.clear(sf::Color(0, 0, 0));

			//把玩家添加到舞台上去
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

//创建一个Event类型变量，从系统消息队列里面取出消息并放到该变量里然后返回
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

//此处要手动声明静态变量，不然编译器会报错
Game::GameState Game::_gameState = Uninitialized;
sf::RenderWindow Game::_mainWindow;
GameObjectManager Game::_gameObjectManager;