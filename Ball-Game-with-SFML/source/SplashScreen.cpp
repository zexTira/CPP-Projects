#include "StdAfx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    //创建texture对象来读取图片
	sf::Texture image;
	if (image.loadFromFile("images/SplashScreen.png") != true)
		return;     
		    
	//创建sprite对象来存储图片
	sf::Sprite sprite(image);
	//如果图片成功创建则将其显示到游戏窗口里
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		//跟上一part一样，用renderWindow对象来监听鼠标动作事件
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
				return;
		}
	}
}