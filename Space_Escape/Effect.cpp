#include "SFMLHeaderPack.h"
#include "Effect.h"
using namespace sf;
Effect::Effect()
{
	pic[0].loadFromFile("Resource/Explosion.png");
	pic[1].loadFromFile("Resource/Explosion2.png");
}
Effect::~Effect(){}
void Effect::E_Frame_Update()
{
	frame_exp.left = frame_order_e% countframe_pic[Numdex].x * (int)size_pic.x / countframe_pic[Numdex].x;
	frame_exp.top = frame_order_e/ countframe_pic[Numdex].x * (int)size_pic.y / countframe_pic[Numdex].y;
	_Effect.setTextureRect(frame_exp);
}
void Effect::E_Upload(int numdex,const Vector2f pos)
{
	size_pic = (Vector2f) pic[numdex].getSize();
	_Effect.setTexture(pic[numdex]);
	frame_exp = { 0, 0,(int)size_pic.x / countframe_pic[numdex].x,(int)size_pic.y / countframe_pic[numdex].y };
	_Effect.setTextureRect(frame_exp);
	_Effect.setOrigin(size_pic.x / 2 / countframe_pic[numdex].x, size_pic.y / 2 / countframe_pic[numdex].y);
	_Effect.setScale(ScaleSize[numdex].x, ScaleSize[numdex].y);
	_Effect.setPosition(pos);
	eClock.restart();
	Numdex = numdex;
}
void Effect::E_Update_Position()
{
	if(!bossend)
	_Effect.move(-8.0f, 0.0f);
}
void Effect::E_Draw(RenderWindow& win)
{
	win.draw(_Effect);
}