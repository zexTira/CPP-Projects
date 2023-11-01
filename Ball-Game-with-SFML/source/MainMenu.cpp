#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow & window)
{
	sf::Texture image;
	image.loadFromFile("images/MainMenu.png");
	sf::Sprite sprite(image);

	//设置鼠标点击矩形区域范围
	
	//play的点击范围
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.width = 380;
	playButton.rect.height = 1023;
	playButton.action = Play;
	
	//Exit的点击范围
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 0;
	exitButton.rect.height = 1023;
	exitButton.rect.width = 560;
	exitButton.action = Exit;
	
	//把点击范围放进容器里面
	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
	
	window.draw(sprite);
	window.display();
	
	return GetMenuResponse(window);
}

//判断鼠标点击位置是否在矩形区域里面从而返回状态参数
MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	//迭代器遍历list容器里面存放的点击区域以供判断
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.width > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.height > x)
			return (*it).action;
	}

		return Nothing;
}

//根据鼠标动作来做出相应的响应
MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow & window)
{
	sf::Event menuEvent;

	//这里的42！=43可以理解为true
	while (42 != 43)
	{
		while (window.pollEvent(menuEvent))
		{
			if (menuEvent.type == sf::Event::MouseButtonPressed)
				return HandleClick(menuEvent.mouseButton.x, menuEvent.mouseButton.y);
			if (menuEvent.type == sf::Event::Closed)
				return Exit;
		
	    }
    }
}