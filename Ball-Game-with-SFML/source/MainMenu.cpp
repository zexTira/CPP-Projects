#include "stdafx.h"
#include "MainMenu.h"


MainMenu::MenuResult MainMenu::Show(sf::RenderWindow & window)
{
	sf::Texture image;
	image.loadFromFile("images/MainMenu.png");
	sf::Sprite sprite(image);

	//�����������������Χ
	
	//play�ĵ����Χ
	MenuItem playButton;
	playButton.rect.top = 145;
	playButton.rect.left = 0;
	playButton.rect.width = 380;
	playButton.rect.height = 1023;
	playButton.action = Play;
	
	//Exit�ĵ����Χ
	MenuItem exitButton;
	exitButton.rect.top = 383;
	exitButton.rect.left = 0;
	exitButton.rect.height = 1023;
	exitButton.rect.width = 560;
	exitButton.action = Exit;
	
	//�ѵ����Χ�Ž���������
	_menuItems.push_back(playButton);
	_menuItems.push_back(exitButton);
	
	window.draw(sprite);
	window.display();
	
	return GetMenuResponse(window);
}

//�ж������λ���Ƿ��ھ�����������Ӷ�����״̬����
MainMenu::MenuResult MainMenu::HandleClick(int x, int y)
{
	//����������list���������ŵĵ�������Թ��ж�
	std::list<MenuItem>::iterator it;

	for (it = _menuItems.begin(); it != _menuItems.end(); it++)
	{
		sf::Rect<int> menuItemRect = (*it).rect;
		if (menuItemRect.width > y && menuItemRect.top < y && menuItemRect.left < x && menuItemRect.height > x)
			return (*it).action;
	}

		return Nothing;
}

//������궯����������Ӧ����Ӧ
MainMenu::MenuResult  MainMenu::GetMenuResponse(sf::RenderWindow & window)
{
	sf::Event menuEvent;

	//�����42��=43�������Ϊtrue
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