#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
    //释放map容器里面所有VisibleGameObject对象的内存
    std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
    //通过一个pair把对象名跟对象添加进容器
    _gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
    //用容器的find方法查找对象，若找到则释放其内存并清除键名
    std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
    if (results != _gameObjects.end())
    {
        delete results->second;
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    //find方法查找对象，找到则返回对象
    std::map<std::string, VisibleGameObject*>::const_iterator results = _gameObjects.find(name);
    if (results == _gameObjects.end())
        return NULL;
    return results->second;

}

int GameObjectManager::GetObjectCount() const
{
    return _gameObjects.size();
}


void GameObjectManager::DrawAll(sf::RenderWindow& renderWindow)
{
    //把对象添加进游戏场景里面
    std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
    while (itr != _gameObjects.end())
    {
        itr->second->Draw(renderWindow);
        itr++;
    }
}

void GameObjectManager::UpdateAll()
{
    std::map<std::string, VisibleGameObject*>::const_iterator itr = _gameObjects.begin();
    float timeDelta = clock.restart().asSeconds();

    while (itr != _gameObjects.end())
    {
        itr->second->Update(timeDelta);
        itr++;
    }

}