#include "SFMLHeaderPack.h"
#include <vector>
#include "Extention_tool.h"
#include "Player.h"
#include "Bossbullet.h"
Bossbullet::Bossbullet()
{
	pic.resize(5);
	pic[0].loadFromFile("Resource/Bossbullet0.png");
	pic[1].loadFromFile("Resource/Bossbullet1.png");
	pic[2].loadFromFile("Resource/Bossbullet2.png");
	pic[3].loadFromFile("Resource/Bossbullet3.png");
	pic[4].loadFromFile("Resource/Bossbullet4.png");
	bullet.setSize(Vector2f(24.0f, 24.0f));
	bullet.setFillColor(Color::Transparent);
	bullet.setOrigin(12, 12);
}
Bossbullet::~Bossbullet(){}
void Bossbullet::Uploadbullet(Sprite boss)
{
	Numdex = random(0, 5);
	s.setTexture(pic[Numdex],false);
	s.setScale(24.0f / pic[Numdex].getSize().x, 24.0f / pic[Numdex].getSize().y);
	s.setOrigin((float)pic[Numdex].getSize().x / 2, (float)pic[Numdex].getSize().y / 2);
	bullet.setPosition(boss.getPosition().x - 84.0f, boss.getPosition().y);
	direction = random(-1, 2);
}
void Bossbullet::bulletmove(Vector2f pos)
{
	if (bullet.getPosition().y <= 162.0f || bullet.getPosition().y >= 570.0f) direction *= -1;
	bullet.move(pos.x, 1.0f*direction);
}
void Bossbullet::changeframe()
{
	s.setPosition(bullet.getPosition());
	s.setRotation((float)rotation);
	rotation++;
	if (rotation == 360) rotation = 0;
}
void Bossbullet::draw(RenderWindow& win)
{
	win.draw(bullet);
	win.draw(s);
}
void Bossbullet::Collision(Player* player)
{
	if (Numdex == 0) player->Effectitem(1);
	if (Numdex == 1) player->Effectitem(0);
	if (Numdex == 2) player->Effectitem(7);
	if (Numdex == 3) player->Effectitem(2);
	if (Numdex == 4) player->ShieldGate = 0;
}