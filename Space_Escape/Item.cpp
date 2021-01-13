#include "SFMLHeaderPack.h"
#include "Item.h"
#include "Extention_tool.h"
using namespace sf;
Item::Item()
{
	pic[0].loadFromFile("Resource/BoxBoostSpeed.png");
	pic[1].loadFromFile("Resource/BoxDisablegun.png");
	pic[2].loadFromFile("Resource/BoxFreeze.png");
	pic[3].loadFromFile("Resource/BoxHealth.png");
	pic[4].loadFromFile("Resource/BoxHealthBig.png");
	pic[5].loadFromFile("Resource/BoxLasergun.png");
	pic[6].loadFromFile("Resource/BoxMissileLauncher.png");
	pic[7].loadFromFile("Resource/BoxPosion.png");
	pic[8].loadFromFile("Resource/BoxRocketLauncher.png");
	pic[9].loadFromFile("Resource/BoxShield.png");
	pic[10].loadFromFile("Resource/coin.png");
}
void Item::ItemIndex(int IndexItem)
{
	Num = IndexItem;
	count = C[Num];
}
void Item::Updateframe()
{
	if (frame == count) frame = 0;
	_frame.left = frame * (int)Texsize.x/count;
	frame++;
	_item.setTextureRect(_frame);
}
void Item::Drawitem(RenderWindow& win)
{
	win.draw(_item);
}
void Item::Uploaditem(const Vector2f& pos)
{
	_item.setTexture(pic[Num]);
	Texsize.x =(float)pic[Num].getSize().x;
	Texsize.y =(float)pic[Num].getSize().y;
	_frame = { 0, 0, (int)Texsize.x / count, (int)Texsize.y};
	_item.setTextureRect(_frame);
	_item.setScale(1 / Texsize.x * 48 *count, 1 / Texsize.y * 48);
	_item.setOrigin(Texsize.x/count/2,Texsize.y/2);
	_item.setPosition(pos);
}
void Item::Uploaditem(float x,float y)
{
	_item.setTexture(pic[Num]);
	Texsize.x = (float)pic[Num].getSize().x;
	Texsize.y = (float)pic[Num].getSize().y;
	_frame = { 0, 0, (int)Texsize.x / count, (int)Texsize.y };
	_item.setTextureRect(_frame);
	_item.setScale(1 / Texsize.x * 48 * count, 1 / Texsize.y * 48);
	_item.setOrigin(24, 24);
	_item.setPosition(x,y);
}
void Item::Move()
{
	_item.move(Vector2f(-8.0f,0.0f));
	itempos.x = _item.getPosition().x;
	itempos.y = _item.getPosition().y;
}
bool Item::CheckCollision(Sprite& Player)
{
	if (Player.getGlobalBounds().intersects(_item.getGlobalBounds())) return 1;
	else return 0;
}
int Item::readNumberItemIndex()
{
	return Num;
}