#pragma once

#include "SFML\Window.hpp"
#include "SFML\Graphics.hpp"
#include <list>

class MainMenu
{
	public:
		enum MenuResult { Nothing, Exit, Play };

		//�ýṹ�����洢���ε����������Բ�����Ϣ
		struct MenuItem
		{
			public:
			    //�����洢��������Χ�ĵ��ģ�����,һ���������������ֵ�������γ�һ��������
				sf::Rect<int> rect;
			    MenuResult action;
		};
	    
		MenuResult Show(sf::RenderWindow & window);

	private:
		MenuResult GetMenuResponse(sf::RenderWindow & window);
		MenuResult HandleClick(int x, int y);

		//�����洢������������
		std::list<MenuItem> _menuItems;
};
