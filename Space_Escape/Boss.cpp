#include "SFMLHeaderPack.h"
#include "Extention_tool.h"
#include <vector>
#include "Boss.h"
Boss::Boss()
{
	BossTex.loadFromFile("Resource/Boss.png");
	picsize = (Vector2f) BossTex.getSize();
	sprite.setTexture(BossTex);
	sprite.setOrigin(picsize.x / 2, picsize.y / 2);
	sprite.setScale(144 / picsize.x, 144 / picsize.y);
	frameeffect.loadFromFile("Resource/Flame.png");
	frameSprite.setTexture(frameeffect);
	frameSprite.setScale(2, 2);
	frameSprite.setRotation(90.0f);
	frameSprite.setOrigin((float)frameeffect.getSize().x / 6 / 2, (float)frameeffect.getSize().y/2);
	frameSprite.setTextureRect(IntRect(0, 0, frameeffect.getSize().x / 6, frameeffect.getSize().y));
}
Boss::~Boss(){}
void Boss::framechange()
{
	frameSprite.setTextureRect(IntRect(frame * frameeffect.getSize().x / 6, 0, frameeffect.getSize().x / 6, frameeffect.getSize().y));
	frameSprite.setPosition(sprite.getPosition().x + 96.0f, sprite.getPosition().y);
	if (++frame >= cframe) frame = 0;
}
void Boss::draw(RenderWindow& win)
{
	win.draw(frameSprite);
	win.draw(sprite);
}
void Boss::movePattern()
{
	if (sprite.getPosition().y <= 222.0f)
	{
		MovdDirection = 0;
	}
	if (sprite.getPosition().y >= 510.0f)
	{
		MovdDirection = 1;
	}
	if (MovdDirection)
	{
		sprite.move(0.0f,-1.0f);
	}
	else 
		sprite.move(0.0f, 1.0f);
}
int Boss::damage(int d)
{
	Health -= d;
	if (Health < 0) Health = 0;
	if (d <= 100) return 40;
	else if (d <= 200) return 100;
	else if (d <= 300) return 300;
	else return 1000;
}