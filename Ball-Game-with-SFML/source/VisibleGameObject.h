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
        //获取弹板对象的宽
        virtual float GetWidth() const;
        //获取弹板对象的高
        virtual float GetHeight() const;
        //获取弹板对象的矩形区域
        virtual sf::Rect<float> GetBoundingRect() const;

        //设置成protected是为了只供继承的子类调用
    protected:
        sf::Sprite& GetSprite();

    private:
        sf::Sprite  _sprite; //存储图片
        sf::Texture _image;  //读取图片
        std::string _filename; //图片路径
        bool _isLoaded; //读取是否成功
};