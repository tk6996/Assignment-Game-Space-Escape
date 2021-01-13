#include"SFMLHeaderPack.h"
#include "Block.h"
using namespace sf;
Block::Block(const String Name)
{
	pic.loadFromFile(Name);
	_Block.setTexture(pic);
	_Block.setTextureRect(IntRect(0, 0, pic.getSize().x, pic.getSize().y));
	blocksize.x = 1 / (float)pic.getSize().x * 48; blocksize.y = 1 / (float)pic.getSize().y * 48;
	_Block.setScale(blocksize.x,blocksize.y);
	_Block.setOrigin((float)pic.getSize().x/2, (float)pic.getSize().y / 2);
}
void Block::Move()
{
	_Block.move(-8.0f, 0.0f);
	position.x = _Block.getPosition().x;
	position.y = _Block.getPosition().y;
}
void Block::draw(RenderWindow& win)
{
	switch (patternSize)
	{
	case 0: _Block.setScale(blocksize.x, blocksize.y); win.draw(_Block); break;
	case 1: _Block.setScale(blocksize.x * 2, blocksize.y*2); win.draw(_Block); break;
	case 2: _Block.setScale(blocksize.x * 3, blocksize.y * 3); win.draw(_Block); break;
	case 3: _Block.setScale(blocksize.x * 3, blocksize.y); win.draw(_Block); break;
	case 4: _Block.setScale(blocksize.x, blocksize.y * 3); win.draw(_Block); break;
	default:;
	}
}
void Block::setposition(float x, float y)
{
	_Block.setPosition(x, y);
} 
Vector2f Block::getposition() const
{
	return _Block.getPosition();
}
int Block::Collision(Sprite Player, RectangleShape Line)
{
	if (Player.getGlobalBounds().intersects(FloatRect( _Block.getGlobalBounds().left-0.1f, _Block.getGlobalBounds().top 
			, _Block.getGlobalBounds().width ,_Block.getGlobalBounds().height )))
		{
			if (Line.getGlobalBounds().intersects(_Block.getGlobalBounds()))
				return 2;
			else
				return 1;
		}
	else return 0;
}