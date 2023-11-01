#include "VisibleGameObject.h"

#pragma once

class GameObjectManager
{
    public:
        GameObjectManager();
        ~GameObjectManager();

        void Add(std::string name, VisibleGameObject* gameObject);
        void Remove(std::string name);
        int GetObjectCount() const;
        VisibleGameObject* Get(std::string name) const;

        void DrawAll(sf::RenderWindow& renderWindow);
        void UpdateAll();

    private:
        //��ֵ�Թ�������map����Ϊ�������ƣ�ֵΪ����ָ��
        std::map<std::string, VisibleGameObject*> _gameObjects;

        //���ز�����()���õ�һ����������VisibleGameObject�����ڴ�ĺ���(functor)���ӣ�����˵��ָ�����ɺ���ʹ�õĶ�����������ָGameObjectDeallocator()
        struct GameObjectDeallocator
        {
            void operator()(const std::pair<std::string, VisibleGameObject*>& p) const
            {
                delete p.second;
            }
        };
        //������ȡfps
        sf::Clock clock;
};
