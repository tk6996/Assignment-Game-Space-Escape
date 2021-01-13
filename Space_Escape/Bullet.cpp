#include "SFMLHeaderPack.h"
#include "Bullet.h"
using namespace sf;


Bullet::Bullet()
{
	pic[0].loadFromFile("Resource/BulletDefault.png");
	pic[1].loadFromFile("Resource/Laser.png");
	pic[2].loadFromFile("Resource/BulletBomb.png");
	pic[3].loadFromFile("Resource/Missile.png");
}
void Bullet::UploadBullet()
{
	picsize.x = (float)pic[BulletMode].getSize().x ;
	picsize.y = (float)pic[BulletMode].getSize().y ;
	bullet.setTexture(pic[BulletMode],true);
	if (BulletMode == 0) bullet.setScale(1 / picsize.x*count[BulletMode] * 20, 1 / picsize.y * 10);
	if (BulletMode == 1) bullet.setScale(1 / picsize.x*count[BulletMode] * 48, 1 / picsize.y * 20);
	if (BulletMode == 2) bullet.setScale(1 / picsize.x*count[BulletMode] * 36, 1 / picsize.y * 36);
	if (BulletMode == 3) bullet.setScale(1 / picsize.x*count[BulletMode] * 48, 1 / picsize.y * 46);
	bullet.setOrigin(picsize.x / count[BulletMode]/2, picsize.y/2);
	_frame = {0, 0, (int)picsize.x / count[BulletMode], (int)picsize.y };
	bullet.setTextureRect(_frame);
}
void Bullet::Updateframe()
{
	if (frame < count[BulletMode])
	{
		_frame.left = frame *(int) picsize.x / count[BulletMode];
		frame++;
		bullet.setTextureRect(_frame);
	}
	if (BulletMode == 0) bullet.move(2.0f, 0.0f);
	if (BulletMode == 1) bullet.move(8.0f, 0.0f);
	if (BulletMode == 2) bullet.move(1.5f, 0.0f);
	if (BulletMode == 3) bullet.move(1.0f, 0.0f);
	position = bullet.getPosition();
}
void Bullet::setPosition(float x, float y)
{
	bullet.setPosition(x, y);
	position = bullet.getPosition();
}
void Bullet::draw(RenderWindow& win)
{
	win.draw(bullet);
}
int Bullet::DamageofBullet()
{
	switch (BulletMode)
	{
	case 0: return 50; break;
	case 1: return 120; break;
	case 2: return 300; break;
	case 3: return 800; break;
	default:return 0; break;
	}
}