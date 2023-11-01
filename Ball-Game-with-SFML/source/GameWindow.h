#include "stdafx.h"
#include "PlayerPaddle.h"
#include "GameObjectManager.h"
#include "Ball.h"
#include "AIPaddle.h"

#pragma once

class Game
{
	public:
		const static int SCREEN_WIDTH = 1024;
		const static int SCREEN_HEIGHT = 768;

	     static void Start();
		 static sf::RenderWindow& GetWindow();
		 const static sf::Event& GetInput();
		 const static GameObjectManager& GetGameObjectManager();
		 
	
	private:
	     static bool IsExiting();
	     static void GameLoop();
		 static void ShowSplashScreen();
		 static void ShowMenu();
	     //用枚举类型来代替常量表示游戏状态
		 enum GameState 
		{
			Uninitialized, ShowingSplash, Paused,
		    ShowingMenu, Playing, Exiting
		};
		static GameState _gameState;
	    static sf::RenderWindow _mainWindow;
		static GameObjectManager _gameObjectManager;
};


