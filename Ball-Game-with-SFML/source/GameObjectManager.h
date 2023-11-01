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
        //键值对关联容器map，键为对象名称，值为对象指针
        std::map<std::string, VisibleGameObject*> _gameObjects;

        //重载操作符()来得到一个用于清理VisibleGameObject对象内存的函子(functor)函子，简单来说是指被当成函数使用的对象，在这里是指GameObjectDeallocator()
        struct GameObjectDeallocator
        {
            void operator()(const std::pair<std::string, VisibleGameObject*>& p) const
            {
                delete p.second;
            }
        };
        //用来获取fps
        sf::Clock clock;
};
