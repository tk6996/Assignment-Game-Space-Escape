#include "SFMLHeaderPack.h"
#include "Player.h"
using namespace sf;
IntRect flip_y(IntRect&);
Player::Player(const char* Name)
{
	pic.loadFromFile(Name);
	pic.setSmooth(true);
	_Sprite.setTexture(pic);
	_Sprite.setOrigin(24, 24);
	_Position = { 120.0f,366.0f };
	_frame = { 0,0,48,48 };
	_Sprite.setTextureRect(_frame);
	IceBlock.setSize(Vector2f(48, 48));
	IceBlock.setOrigin(23.5, 23.5);
	picshield.loadFromFile("Resource/Shield.png");
	picshield.setSmooth(true);
	picsizeShiledX = picshield.getSize().x;
	picsizeShiledY = picshield.getSize().y;
	Shield.setTexture(picshield);
	Shield.setOrigin((float)picsizeShiledX/2, (float)picsizeShiledY/2);
	Shield.setScale( 0.12f,0.12f );
	LinePlay.setSize(Vector2f(48.0f, 432.0f));
	LinePlay.setPosition(96.0f, 150.0f);
	LinePlay.setFillColor(Color::Transparent);
}
void Player::Gravity(bool Gravity_Mode,bool move)
{
	if (Gravity_Mode) { if(move==0)_Position.y++;
	_Sprite.setTextureRect(_frame);
	}
	else { if(move==0)_Position.y--; 
	_Sprite.setTextureRect(flip_y(_frame));
	}
}
void Player::setPosition()
{
	_Sprite.setPosition(_Position);
	if (ShieldGate) { Shield.setScale(0.12f, 0.12f); Shield.setPosition(_Position); }
	else Shield.setScale(0.0f, 0.0f);
	if (freezeStatus) { IceBlock.setFillColor(Color(204, 229, 255, 180)); IceBlock.setPosition(_Position); }
	else IceBlock.setFillColor(Color(0));
}
IntRect flip_y(IntRect& R)
{
	return { R.left,R.height,R.width,-R.height };
}
void Player::changeframe()
{
	if (frame == 3) frame = 0;
	_frame.left = 48 * frame;
	frame++;
}
void Player::draw(RenderWindow* window,double DamageTime)
{ 
	window->draw(LinePlay);
	if(DamageTime<=1.0 && int(DamageTime*10)%2)window->draw(_Sprite,BlendAdd); 
	else window->draw(_Sprite);
	if (ShieldGate) window->draw(Shield);
	if (freezeStatus) window->draw(IceBlock);
}
void Player::Effectitem(int Num)
{
	switch (Num)
	{
	case 0:	SpeedLevel = 7; disableChangeSL = 1;	break;//BoostSpeed
	case 1: disableshoot=1; break;//Disablegun
	case 2: freezeStatus=1; break;//Freeze
	case 3:	Health += 4; if (Health > 10) Health = 10; break;//Healthpack
	case 4:	Health += 7; if (Health > 10) Health = 10; break;//LargeHealthpack
	case 5: Gun = 1; break;//Lasergun
	case 6: Gun = 3; break;//MissileLauncher
	case 7: Health -= 3; if (Health < 0) Health = 0; break;//Posion
	case 8: Gun = 2; break;//RocketLancher
	case 9: ShieldGate = 10; break;//Shield
	case 10: Score += 300; break;//Coin
	default:;
	}
}
void Player::Damage(int damage)
{
	int damageleft=0;
	if (ShieldGate)
	{
		ShieldGate -= damage;
		damage = 0;
		if (ShieldGate < 0) { damageleft = ShieldGate; ShieldGate = 0; }
	}
	if (ShieldGate == 0)
	{
		Health = Health - damage + damageleft;
		if (Health < 0) Health = 0;
	}
}