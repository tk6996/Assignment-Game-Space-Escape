#include "SFMLHeaderPack.h"
#include "Background.h"
using namespace sf;
Background::Background(const char* Name)
{
	T.loadFromFile(Name);
	for (int i = 0; i < 3; i++)
	{
		_Background[i].setTexture(T);
		_Background[i].setPosition((float)T.getSize().x/(float)T.getSize().y*432.0f*i, 150.0f);
		_Background[i].setScale( 432 / _Background[i].getGlobalBounds().height , 1 / _Background[i].getGlobalBounds().height * 432);
	}
}
void Background::MoveBackground()
{
	for (int i=0; i < 3; i++)
	{
		if (_Background[i].getPosition().x <= -(_Background[i].getGlobalBounds().width))
		_Background[i].setPosition(_Background[i].getPosition().x + (_Background[i].getGlobalBounds().width*3) , _Background[i].getPosition().y);
		_Background[i].move( - 4.0f, 0.0f);
	}
}
void Background::DrawBackground(RenderWindow& window)
{
	for(int i=0;i<3;i++)
	window.draw(_Background[i]);
}