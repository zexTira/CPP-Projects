#include "StdAfx.h"
#include "SplashScreen.h"

void SplashScreen::Show(sf::RenderWindow & renderWindow)
{
    //����texture��������ȡͼƬ
	sf::Texture image;
	if (image.loadFromFile("images/SplashScreen.png") != true)
		return;     
		    
	//����sprite�������洢ͼƬ
	sf::Sprite sprite(image);
	//���ͼƬ�ɹ�����������ʾ����Ϸ������
	renderWindow.draw(sprite);
	renderWindow.display();

	sf::Event event;
	while (true)
	{
		//����һpartһ������renderWindow������������궯���¼�
		while (renderWindow.pollEvent(event))
		{
			if (event.type == sf::Event::EventType::KeyPressed || event.type == sf::Event::EventType::MouseButtonPressed || event.type == sf::Event::EventType::Closed)
				return;
		}
	}
}