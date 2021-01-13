#define _USE_MATH_DEFINES
#include "SFMLHeaderPack.h"
#include <cmath>
#include "Extention_tool.h"
#include "EnemyBullet.h"
using namespace sf;
using namespace std;
EnemyBullet::EnemyBullet()
{
	pic[0].loadFromFile("Resource/EnemyBullet01.png");
	pic[1].loadFromFile("Resource/EnemyBullet02.png");
	pic[2].loadFromFile("Resource/EnemyBullet03.png");
	pic[3].loadFromFile("Resource/EnemyBullet04.png");
}
void EnemyBullet::UploadBullet(Sprite enemy)
{
	picsize = (Vector2f)pic[bulletT].getSize();
	bullet.setTexture(pic[bulletT],true);
	StartplayerPosition = playerPosition;
	StartenemyPosition = enemy.getPosition();
	bullet.setRotation(0);
	if (bulletT == 0) bullet.setScale(1 / picsize.x * 20, 1 / picsize.y * 20);
	if (bulletT == 1) bullet.setScale(1 / picsize.x * 30, 1 / picsize.y * 30);
	if (bulletT == 2) { bullet.setScale(1 / picsize.x * 30, 1 / picsize.y * 10); bullet.setRotation(180 + 180.0f/(float)M_PI *atan((StartplayerPosition.y - StartenemyPosition.y) / (StartplayerPosition.x - StartenemyPosition.x))); }
	if (bulletT == 3) bullet.setScale(1 / picsize.x * 48, 1 / picsize.y * 48);
	bullet.setOrigin(picsize.x / 2, picsize.y / 2);
	bullet.setPosition(enemy.getPosition().x-enemy.getGlobalBounds().width/2, enemy.getPosition().y);
}
void EnemyBullet::BulletMove(Vector2f move)
{
	bullet.move(move.x, move.y);
	if (bulletT == 1) { if (playerPosition.y > bullet.getPosition().y) bullet.move(0.0f, 0.5f); else if (playerPosition.y < bullet.getPosition().y) bullet.move(0.0f, -0.5f); }
	if (bulletT == 2) { bullet.move(0.0f, move.x*(StartplayerPosition.y- StartenemyPosition.y) / (StartplayerPosition.x- StartenemyPosition.x)); }
	if (bulletT == 3) { bullet.move(random(-1.0f, 1.0f), random(-1.0f, 1.0f));
	if (bullet.getPosition().y < 174.0f) bullet.move(0.0f,2.0f); 
	if (bullet.getPosition().y > 559.0f) bullet.move(0.0f,-2.0f);
	}
}
void EnemyBullet::draw(RenderWindow&win)
{
	win.draw(bullet);
}
int EnemyBullet::DamageofBullet()
{
	switch (bulletT)
	{
	case 0: return 3; break;
	case 1: return 5; break;
	case 2: return 3; break;
	case 3: return 9; break;
	default:return 0; break;
	}
}