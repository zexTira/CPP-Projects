#include "stdafx.h"
#include "GameObjectManager.h"

GameObjectManager::GameObjectManager()
{
}

GameObjectManager::~GameObjectManager()
{
    //�ͷ�map������������VisibleGameObject������ڴ�
    std::for_each(_gameObjects.begin(), _gameObjects.end(), GameObjectDeallocator());
}

void GameObjectManager::Add(std::string name, VisibleGameObject* gameObject)
{
    //ͨ��һ��pair�Ѷ�������������ӽ�����
    _gameObjects.insert(std::pair<std::string, VisibleGameObject*>(name, gameObject));
}

void GameObjectManager::Remove(std::string name)
{
    //��������find�������Ҷ������ҵ����ͷ����ڴ沢�������
    std::map<std::string, VisibleGameObject*>::iterator results = _gameObjects.find(name);
    if (results != _gameObjects.end())
    {
        delete results->second;
        _gameObjects.erase(results);
    }
}

VisibleGameObject* GameObjectManager::Get(std::string name) const
{
    //find�������Ҷ����ҵ��򷵻ض���
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
    //�Ѷ�����ӽ���Ϸ��������
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