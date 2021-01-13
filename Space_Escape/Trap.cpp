#include "SFMLHeaderPack.h"
#include "Trap.h"
#include "Extention_tool.h"
using namespace sf;
Trap::Trap()
{
	_prickerTex.loadFromFile("Resource/Trap_pricker.png");
	_prickerTex.setSmooth(true);
	size_pic_pricker.x =(float) _prickerTex.getSize().x;
	size_pic_pricker.y =(float) _prickerTex.getSize().y;
	for (int i = 0; i < 16; i++)
	{
		_pricker[i].setTexture(_prickerTex);
		_pricker[i].setScale(1/size_pic_pricker.x*48.0f, 1 / size_pic_pricker.y*48.0f);
		_pricker[i].setOrigin(size_pic_pricker.x / 2, size_pic_pricker.y / 2);
	}
	_laserbaseTex.loadFromFile("Resource/Laserbase.png");
	size_pic_laserbase.x = (float)_laserbaseTex.getSize().x;
	size_pic_laserbase.y = (float)_laserbaseTex.getSize().y;
	laserbase.setTexture(_laserbaseTex);
	laserbase.setScale(1 / size_pic_laserbase.x*48.0f, 1 / size_pic_laserbase.y*24.0f);
	laserbase.setOrigin(size_pic_laserbase.x / 2, size_pic_laserbase.y / 2);
	_laserTex.loadFromFile("Resource/LaserTrap.png");
	laser.setTexture(&_laserTex);
	laser.setSize(Vector2f(16, 432));
	laser.setOrigin(5,216);
}
void Trap::patternPricker(unsigned int pattern)
{
	if (pattern == 0)
	{
		int paltform = random(0, 2);
			for (unsigned int i = 0; i < numberPricker; i++)
			{
				if (paltform) {
					_pricker[i].setPosition(1000.0f + i * 48, 560.0f);
					_pricker[i].setRotation(-90.0f);
				}
				else {
					_pricker[i].setPosition(1000.0f + i * 48, 172.0f);
					_pricker[i].setRotation(90.0f);
				}
			}
	}
	if (pattern == 1)
	{
		int j=0, k=0;
		numberPricker *= 2;
		for (unsigned int i = 0; i < numberPricker; i++)
		{
			if (i<numberPricker/2) {
				_pricker[i].setPosition(1000.0f + j * 48, 560.0f);
				_pricker[i].setRotation(-90.0f);
				j++;
			}
			else {
				_pricker[i].setPosition(1000.0f + k * 48, 172.0f);
				_pricker[i].setRotation(90.0f);
				k++;
			}
		}
	}
	if (pattern == 2)
	{
		for (unsigned int i = 0; i < numberPricker; i++)
		{
			_pricker[i].setPosition(-24.0f, 174.0f + 48.0f*i);
		}
	}
}
void Trap::Prickerdraw(RenderWindow& win)
{
	for(unsigned int i=0;i<numberPricker;i++)
	win.draw(_pricker[i]);
}
void Trap::PrickerUpdate()
{
	for (unsigned int i = 0; i < numberPricker; i++)
	_pricker[i].move(-8.0f, 0.0f);
}
bool Trap::PrickerCollision(Sprite Player)
{
	bool c=0;
	for (unsigned int i = 0; i < numberPricker; i++)
		if (_pricker[i].getGlobalBounds().intersects(Player.getGlobalBounds()) )
		{
			c=1;break;
		}
	return c;
}
void Trap::laserbasecreate()
{
	laserbase.setPosition(988, 162);
	laserbasestatus = 1;
	laser.setPosition(985,366);
}
void Trap::laserbaseUpdate()
{
	laserbase.move(-8.0f,0.0f);
	laser.move(-8.0f, 0.0f);
	if (laserbase.getPosition().x < -24.0f) { laserbasestatus = 0; }
}
void Trap::laserbasedraw(RenderWindow& win)
{
	if(laserstatus) win.draw(laser);
	win.draw(laserbase);
	laserbase.setScale(1 / size_pic_laserbase.x*48.0f, -1 / size_pic_laserbase.y*24.0f);
	laserbase.move(0.0f, 408.0f);
	win.draw(laserbase);
	laserbase.setScale(1 / size_pic_laserbase.x*48.0f, 1 / size_pic_laserbase.y*24.0f);
	laserbase.move(0.0f,-408.0f);
}
bool Trap::laserCoillision(Sprite Player)
{
	if(laserstatus && laser.getGlobalBounds().intersects(Player.getGlobalBounds())) return 1;
	else return 0;
}
void Trap::PrickerUpdateSpecial(float move)
{
	for (unsigned int i = 0; i < numberPricker; i++)
		_pricker[i].move(move, 0.0f);
}