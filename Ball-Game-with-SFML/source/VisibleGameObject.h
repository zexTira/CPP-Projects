#include "stdafx.h"
#pragma once

class VisibleGameObject
{
    public:
        VisibleGameObject();
        virtual ~VisibleGameObject();
        virtual void Load(std::string filename);
        virtual void Draw(sf::RenderWindow& window);
        virtual void Update(float elapsedTime);
        virtual void SetPosition(float x, float y);
        virtual sf::Vector2f GetPosition() const;
        virtual bool IsLoaded() const;
        //��ȡ�������Ŀ�
        virtual float GetWidth() const;
        //��ȡ�������ĸ�
        virtual float GetHeight() const;
        //��ȡ�������ľ�������
        virtual sf::Rect<float> GetBoundingRect() const;

        //���ó�protected��Ϊ��ֻ���̳е��������
    protected:
        sf::Sprite& GetSprite();

    private:
        sf::Sprite  _sprite; //�洢ͼƬ
        sf::Texture _image;  //��ȡͼƬ
        std::string _filename; //ͼƬ·��
        bool _isLoaded; //��ȡ�Ƿ�ɹ�
};