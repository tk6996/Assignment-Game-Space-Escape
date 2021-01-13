#include "SFMLHeaderPack.h"
#include "Extention_tool.h"
#include "Enemy.h"
using namespace sf;
Enemy::Enemy()
{
	pic[0].loadFromFile("Resource/Enemy00.png");
	pic[1].loadFromFile("Resource/Enemy01.png");
	pic[2].loadFromFile("Resource/Enemy02.png");
	pic[3].loadFromFile("Resource/Enemy03.png");
	pic[4].loadFromFile("Resource/Enemy04.png");
	pic[5].loadFromFile("Resource/Enemy05.png");
}
Enemy::~Enemy(){}
void Enemy::AddEnemy()
{
	E.setTexture(pic[Numdex],true);
	picsize = (Vector2f)pic[Numdex].getSize();
	E.setOrigin(picsize.x / 2, picsize.y / 2);
	switch (Numdex)
	{
	case 0: 
		E.setTexture(pic[Numdex]);
		E.setScale(48.0f/picsize.x, 9.0f*48.0f/picsize.y);
		E.setPosition(1008.0f, 366.0f);
		Health = 300;break;
	case 1: 
		E.setTexture(pic[Numdex]);
		E.setScale(48.0f*1.5f / picsize.x, 48.0f*1.5f / picsize.y);
		E.setPosition(1008.0f,546.0f);
		Health = 250;break;
	case 2:
		E.setTexture(pic[Numdex]);
		E.setScale(48.0f*1.25f / picsize.x, 48.0f*1.25f / picsize.y);
		E.setPosition(1008.0f,(float)random(180, 553));
		Health = 110; break;
	case 3:
		E.setTexture(pic[Numdex]);
		E.setScale(48.0f*1.5f / picsize.x, 48.0f*1.5f / picsize.y);
		E.setPosition(1008.0f, (float)random(186, 547));
		Health = 250; break;
	case 4:
		E.setTexture(pic[Numdex]);
		E.setScale(-48.0f / picsize.x, 46.0f / picsize.y);
		E.setPosition(1008.0f, (float)random(174, 559));
		Health = 50; break;
	case 5:
		E.setTexture(pic[Numdex]);
		E.setScale(48.0f*3 / picsize.x, 48.0f*3 / picsize.y);
		E.setPosition(1008.0f, (float)random(198,511));
		Health = 350; break;
	default:break;
	}
}
void Enemy::draw(RenderWindow& win)
{
	win.draw(E);
}
void Enemy::move()
{
	E.move(-8.0f, 0.0f);
}
bool Enemy::Collision(Sprite player)
{
	if (Numdex == 0) {
		if (E.getGlobalBounds().intersects(FloatRect(player.getGlobalBounds().left + 0.1f, player.getGlobalBounds().top, player.getGlobalBounds().width,
			player.getGlobalBounds().height))) {return 1;}else return 0;
	}
	else {
		if (E.getGlobalBounds().intersects(player.getGlobalBounds())) { return 1; } else return 0;
	}
}
void Enemy::Damage(int damage)
{
	Health -= damage;
}