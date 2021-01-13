#include "SFMLHeaderPack.h"
#include "Platform.h"
#include <iostream>
using namespace sf;
using namespace std;
Platform::Platform(const char* Name)
{
	block.loadFromFile(Name);
	block.setSmooth(true);
	for (int j = 0; j < 2; j++)
	for (int i = 0; i < 30; i++)
	{
		_Platform[j][i].setTexture(block);
		_Platform[j][i].setPosition(i*48.0f, 102.0f+(480*j));
		_Platform[j][i].setScale( 1 / _Platform[j][i].getGlobalBounds().width * 48, 1 / _Platform[j][i].getGlobalBounds().height * 48);
	}
}
void Platform::Move()
{
	for (int j = 0; j < 2; j++)
		for (int i = 0; i < 30; i++)
		{
			_Platform[j][i].setPosition(_Platform[j][i].getPosition().x - 8, _Platform[j][i].getPosition().y);
			if (_Platform[j][i].getPosition().x < -48)
			{
				_Platform[j][i].setPosition(1000, _Platform[j][i].getPosition().y);
			}

		}
}
void Platform::draw(RenderWindow& window)
{
	for (int i = 0; i < 30; i++)
	{
		window.draw(_Platform[0][i]);
		window.draw(_Platform[1][i]);
	}
}
bool Platform::CollisionPlayer(Sprite& Player)
{
	if (Player.getGlobalBounds().top > _Platform[0][0].getPosition().y + 47  && Player.getGlobalBounds().top + Player.getGlobalBounds().height < _Platform[1][0].getPosition().y) return 0;
	else return 1;
}