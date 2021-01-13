#include "SFMLHeaderPack.h"
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "Extention_tool.h"
#include "Player.h"
#include "Platform.h"
#include "Background.h"
#include "Item.h"
#include "TextGame.h"
#include "SoundGame.h"
#include "Block.h"
#include "Bullet.h"
#include "Trap.h"
#include "Effect.h"
#include "Enemy.h"
#include "EnemyBullet.h"
#include "Boss.h"
#include "Bossbullet.h"
#include "UI.h"
using namespace sf;
using namespace std;
int MenuMode(RenderWindow& Window);
int GameMode(RenderWindow& Window);
int ScoreMode(RenderWindow& Window);
void addBox(Item& box, vector<Item>& Box);
void addCoin(Item& coin, vector<Item>& Coin);
int addBlock(Block& block, vector<Block>& _Block);
void addPricker(Trap& Pricker, vector<Trap>& pricker);
int addEnemy(Enemy& enemy, vector<Enemy>& e);
void addEnemyBullet(EnemyBullet& enemybullet, vector<EnemyBullet>& eB, Enemy& enemy, Sprite player, SoundGame* EbSound);
Texture MainBG;
RectangleShape BG,filter;
TextGame text;
SoundGame Movestate, ClickSound;
UI Menu;
int main()
{
	srand((unsigned int)time(NULL));
	int ModeScreen=1;
	MainBG.loadFromFile("Resource/backgroundMain.png");
	BG.setTexture(&MainBG);
	text.setFont("Resource/Font.ttf");
	Movestate.filename("Resource/Movestate.ogg"); 
	ClickSound.filename("Resource/Click.ogg");
	Image icon;
	icon.loadFromFile("Resource\\icon.png");
	RenderWindow window(VideoMode(960, 680), "Space_Escape",Style::Close);
	window.setPosition(Vector2i(203, 10));
	window.setIcon(159,159,icon.getPixelsPtr());
	BG.setSize((Vector2f)window.getSize());
	filter.setSize(Vector2f(window.getSize()));
	filter.setFillColor(Color(0, 0, 0, 125));
	while (ModeScreen)
	{
		window.clear();
		window.display();
		if (ModeScreen == 1) ModeScreen = MenuMode(window);
		else
		if (ModeScreen == 2) ModeScreen = GameMode(window);
		else
		if (ModeScreen == 3) ModeScreen = ScoreMode(window);
	}
	return 0;
}
int MenuMode(RenderWindow& win)
{
	debounced button = { 0,0,0,0 };
	int ModeScreen = 1,state = 0;
	bool Exit = 0;
	win.setMouseCursorVisible(true);
	TextGame tittle("Resource/tittle.ttf");
	SoundGame Menusound("Resource/MenuSound.ogg");
	vector<CircleShape> Meteor;
	Meteor.resize(100); for (vector<CircleShape>::iterator iter = Meteor.begin(); iter != Meteor.end(); iter++) { (*iter).setRadius(3.0f); (*iter).setPosition(0.0f,685.0f); (*iter).setFillColor(Color(random(0, 256), random(0, 256), random(0, 256), 255)); }
	Menusound.setLoop(true);
	Menusound.play();
	tittle.setSize(100);
	while (win.isOpen())
	{
		if (Exit)break;
		Event events;
		while (win.pollEvent(events))
		{
			if (events.type == Event::Closed)
			{
				win.close();
				ModeScreen = 0;
			}
			if (Keyboard::isKeyPressed(Keyboard::W)|| Keyboard::isKeyPressed(Keyboard::Up))
			{
				if(!button.W)
				{ 
					Movestate.play();
					state--;
					button.W = 1;
					if (state < 0) state = 2;
				}
			} else button.W=0;
			if (Keyboard::isKeyPressed(Keyboard::S)|| Keyboard::isKeyPressed(Keyboard::Down))
				{
					if(!button.S)
					{ 
					Movestate.play();
					state++;
					if (state > 2) state = 0;
					button.S = 1;
					}
				}else button.S = 0;
			if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					if (!button.Enter)
					{
						ClickSound.play();
						if (state == 0) { ModeScreen = 2; Exit = 1; }
						if (state == 1) { ModeScreen = 3; Exit = 1; }
						if (state == 2) { win.close(); ModeScreen = 0; }
						sleep(milliseconds(300));
						button.Enter = 0;
					}
			} else button.Enter=0;
			if (Mouse::getPosition(win).x >= 399.0f && Mouse::getPosition(win).x <= 561.0f && Mouse::getPosition(win).y >= 415.0f && Mouse::getPosition(win).y <= 431.0f) { if (state != 0) { Movestate.play(); state = 0; } 
				if (events.mouseButton.button == Mouse::Left&& events.type == Event::MouseButtonPressed) { ClickSound.play(); ModeScreen = 2; Exit = 1; sleep(milliseconds(300)); break; }}
			if (Mouse::getPosition(win).x >= 402.5f && Mouse::getPosition(win).x <= 557.5f && Mouse::getPosition(win).y >= 464.0f && Mouse::getPosition(win).y <= 480.0f) { if (state != 1) { Movestate.play(); state = 1; } 
				if (events.mouseButton.button == Mouse::Left&& events.type == Event::MouseButtonPressed) { ClickSound.play(); ModeScreen = 3; Exit = 1; sleep(milliseconds(300)); break;} }
			if (Mouse::getPosition(win).x >= 452.5f && Mouse::getPosition(win).x <= 502.5f && Mouse::getPosition(win).y >= 513.0f && Mouse::getPosition(win).y <= 529.0f) { if (state != 2) { Movestate.play(); state = 2; } 
				if (events.mouseButton.button == Mouse::Left&& events.type == Event::MouseButtonPressed) { ClickSound.play(); win.close(); ModeScreen = 0; sleep(milliseconds(300)); break;} }
		}
		win.clear();
		win.draw(BG);
		for (vector<CircleShape>::iterator iter = Meteor.begin(); iter != Meteor.end(); iter++)
		{
			(*iter).move(0.0f, 0.5f);
			win.draw(*iter);
			if(random(0,1000)==0) if ((*iter).getPosition().y > 683.0f) { (*iter).setPosition(random(3.0f, 957.0f), random(-45.0f, -3.0f)); (*iter).setFillColor(Color(random(0, 256), random(0, 256), random(0, 256), 255)); }
		}
		tittle.TextPrint(50.0f, 150.0f, "Space  Escape", win);
		Menu.StartMenu(win, state);
		win.display();
	}
	return ModeScreen;
}
int GameMode(RenderWindow& window)
{
	////////////////////Variable/////////////////
	debounced button = { 0,0,0,0 };
	char Name[26] = { 0 };
	int ModeScreen = 1, AmmoBomb = 0, AmmoMissile = 0, BlockGen = 0, Objdis = 0, FrameRun = 0, framebossend = 0, state = 0,charNum=0;
	bool Generate, G = true, PrevA = 0, PrevD = 0, Exit = 0, Collision_Player_x, Collision_Player_y,ready_in =0,
		setfreezetime = 0, setdisableshoottime = 0, setLaser = 0, pauseMode = 0, boss_status = 0, backpause = 0, backafterpause = 0, backend = 0, win = 0, conend = 0, ready = 0;
	double timemoveframe = 0.0, timechange = 0.045, timeregeneration = 0.0, timeCoinrol = 0.0, time = 0.0,
		disableSpeedLeveltime = 0.0, timefreeze = 0.0, BulletTime = 0.0, disableGunTime = 0.0, laserdelay = 0.12, countdownTime = 3.0,
		laserTime = 0.0, DamageTime = 1.0, PrickerbackTime = 20.0, pauselaser = 0.0, bosstime = 0.0;
	Time pauseTime = microseconds(0);
	Clock c, Timeframe, Timeregen, TimeCoinrol, GameTime, dSLT, FreezeTime, BulletClock, disableGunClock, LaserClock,
		DamageClock, PrickerbackClock, LaserTrapClock, ClockBoss, Countdown;
	/////////////////////Text GI////////////////////
	Texture HeartTex, Gun_pic[4], Red_Cross_Tex; Sprite Heart, gun[4], Red_Cross; RectangleShape AmmoPoint, ShieldPoint, BossPoint;
	HeartTex.loadFromFile("Resource/Heart.png"); Heart.setTexture(HeartTex); Heart.setScale(16.0f / HeartTex.getSize().x, 16.0f / HeartTex.getSize().y);
	Gun_pic[0].loadFromFile("Resource/GunDefault.png"); gun[0].setTexture(Gun_pic[0]);
	Gun_pic[1].loadFromFile("Resource/Lasergun.png"); gun[1].setTexture(Gun_pic[1]);
	Gun_pic[2].loadFromFile("Resource/RocketLauncher.png"); gun[2].setTexture(Gun_pic[2]);
	Gun_pic[3].loadFromFile("Resource/MissileLuncher.png"); gun[3].setTexture(Gun_pic[3]);
	Red_Cross_Tex.loadFromFile("Resource/RedCross.png"); Red_Cross.setTexture(Red_Cross_Tex); Red_Cross.setScale(20.0f / Red_Cross_Tex.getSize().x, 20.0f / Red_Cross_Tex.getSize().y);
	ShieldPoint.setSize(Vector2f(20.0f, 20.0f)); ShieldPoint.setFillColor(Color::Blue); ShieldPoint.setOutlineThickness(1.0f); ShieldPoint.setOutlineColor(Color::Black);
	BossPoint.setFillColor(Color(215, 175, 0, 255));
	////////////////////////Load & Add Texture & Create Object/////////////
	Player player("Resource/Player.png"); player.setPosition();
	Platform platform("Resource/Platform.png");
	Background bg("Resource/Background.png");
	/////////////////Item//////////////////
	Item box, coin;
	vector<Item> Box, Coin;
	/////////////////Block/////////////////
	Block block("Resource/Platform.png");
	vector<Block> _Block;
	///////////////Bullet /////////////////
	Bullet bullet;
	bullet.BulletMode = 0;
	vector<Bullet> B;
	////////////////Trap /////////////////
	Trap Pricker, LaserTrap, PrickerBack;
	vector <Trap> pricker;
	PrickerBack.numberPricker = 9;
	PrickerBack.patternPricker(2);
	//////////////////Effect ////////////////
	Effect Explosion;
	vector <Effect> explosion, missileexp;
	//////////////// Enemy ////////////////
	Enemy enemy;
	vector <Enemy> e;
	EnemyBullet enemybullet;
	vector <EnemyBullet> eB;
	/////////////////Boss/////////////////
	Boss boss;
	Bossbullet bossBullet;
	vector<Bossbullet> bB;
	//////////////////Sound////////////////

	SoundGame playing("Resource/Playing.ogg"), getItem("Resource/Alert.ogg"), getCoin("Resource/CoinSound.ogg"),
		shootdefaut("Resource/ShootDefault.wav"), shootlaser("Resource/LaserShot.ogg"), shootRocketLauncher("Resource/Rocket_Launcher.wav"),
		shootMissile("Resource/Missile.wav"), DamageSound("Resource/DamageSound.ogg"), Lasersound("Resource/LaserTrap.wav"),
		ExploBomb("Resource/BombExplosion.wav"), ExploMissle("Resource/Explosion2.wav"), SCE1("Resource/SCE1.ogg"),
		SCE2("Resource/SCE2.wav"), SCE3("Resource/SCE3.ogg"), EnemySoundBullet[3], SoundBoss("Resource/SCB.ogg"), SoundBossShoot("Resource/Boss_shoot.wav"),
		Countdown_Sound("Resource/Countdown_Sound.ogg");
	EnemySoundBullet[0].filename("Resource/ShootDefault.wav");
	EnemySoundBullet[1].filename("Resource/LaserShot.ogg");
	EnemySoundBullet[2].filename("Resource/Rocket_Launcher.wav");
	playing.setLoop(true);
	Lasersound.setLoop(true);
	//////////////Loop//////////////////////////
	goto BeforeReady;
	while (window.isOpen())
	{
		if (Exit == 1)
		{
			break;
		}
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed)
			{
				window.close();
				ModeScreen = 0;
			}
			if (event.type == Event::LostFocus)
			{
				pauseMode = 1;
			}
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			if (!button.Esc)
			{
				pauseMode = 1;
				button.Esc = 1;
			}
		}
		else button.Esc = 0;
		window.setMouseCursorVisible(false);
		window.clear();
		///////////////////////Time Check ///////////////////////////////
		Generate = 0;
		if (FrameRun == 7500) { boss.sprite.setPosition(1033.0f, 366.0f); boss_status = 1; }
		if (FrameRun <= 15000) { PrickerbackTime = 30.0 - FrameRun / 500.0; }
		timemoveframe = timemoveframe+ Timeframe.restart().asSeconds() - pauseTime.asSeconds();
		timeregeneration = timeregeneration + Timeregen.restart().asSeconds() - pauseTime.asSeconds();
		timeCoinrol = timeCoinrol + TimeCoinrol.restart().asMilliseconds() - pauseTime.asMilliseconds();
		time = time + GameTime.restart().asMilliseconds() - pauseTime.asMilliseconds();
		BulletTime = BulletTime + BulletClock.restart().asSeconds() - pauseTime.asSeconds();
		DamageTime = DamageTime + DamageClock.restart().asSeconds() - pauseTime.asSeconds();
		for (unsigned int i = 0; i < e.size(); i++) e[i].delayShoot = e[i].delayShoot + e[i].clock.restart().asSeconds() - pauseTime.asSeconds();
		/////////////////////PrintPlatform & Collision ////////////////
		Collision_Player_x = 0;  Collision_Player_y = 0;
		Collision_Player_y = platform.CollisionPlayer(player._Sprite);
		for (unsigned int b = 0; b < _Block.size(); b++) {
			if (_Block[b].Collision(player._Sprite, player.LinePlay) == 1) Collision_Player_x = 1;
			if (_Block[b].Collision(player._Sprite, player.LinePlay) == 2) Collision_Player_y = 1;
		}
		for (unsigned int b = 0; b < e.size(); b++) { if (e[b].Collision(player._Sprite) && e[b].Numdex == 0) { Collision_Player_x = 1; break; } }
		/////////////////////CheckKey//////////////////////////////////////////
		//if (Keyboard::isKeyPressed(Keyboard::Key::B)) { FrameRun = 7998; }
		if (Keyboard::isKeyPressed(Keyboard::Key::Space) && player.disableshoot == 0)
		{
			if (bullet.BulletMode == 0 && BulletTime > 0.25) { shootdefaut.play(); BulletTime = 0.0; bullet.setPosition(player._Position.x + 24.0f, player._Position.y); bullet.UploadBullet(); B.push_back(bullet); }
			if (bullet.BulletMode == 1) {
				laserdelay = laserdelay - LaserClock.getElapsedTime().asSeconds() + pauseTime.asSeconds();
				laserTime = laserTime - LaserClock.getElapsedTime().asSeconds() + pauseTime.asSeconds();
				if (laserdelay < 0.0) {
					laserdelay = 0.12; shootlaser.play();
					bullet.setPosition(player._Position.x + 24.0f, player._Position.y); bullet.UploadBullet(); B.push_back(bullet);
				}
				if (laserTime < 0.0) bullet.BulletMode = 0;
			}
			if (bullet.BulletMode == 2 && BulletTime > 0.5) {
				shootRocketLauncher.play();
				AmmoBomb--; BulletTime = 0.0; bullet.setPosition(player._Position.x + 24.0f, player._Position.y); bullet.UploadBullet(); B.push_back(bullet);
				if (AmmoBomb == 0) bullet.BulletMode = 0;
			}
			if (bullet.BulletMode == 3 && BulletTime > 0.5) {
				shootMissile.play();
				AmmoMissile--; BulletTime = 0.0; bullet.setPosition(player._Position.x + 24.0f, player._Position.y); bullet.UploadBullet(); B.push_back(bullet);
				if (AmmoMissile == 0) bullet.BulletMode = 0;
			}
		} LaserClock.restart();
		if (Keyboard::isKeyPressed(Keyboard::Key::W)|| Keyboard::isKeyPressed(Keyboard::Key::Up)) { if (G == true) Collision_Player_y = 0; G = false; }
		else
		if (Keyboard::isKeyPressed(Keyboard::Key::S)|| Keyboard::isKeyPressed(Keyboard::Key::Down)) { if (G == false)Collision_Player_y = 0; G = true; }
		if (((Keyboard::isKeyPressed(Keyboard::Key::A) != PrevA)|| (Keyboard::isKeyPressed(Keyboard::Key::Left) != PrevA)) && PrevA == 0)
			if (player.SpeedLevel > 1) { player.SpeedLevel--; }
		if (((Keyboard::isKeyPressed(Keyboard::Key::D) != PrevD) ||(Keyboard::isKeyPressed(Keyboard::Key::Right) != PrevD)) && PrevD == 0)
			if (player.SpeedLevel < 5) { player.SpeedLevel++; }
		PrevA = Keyboard::isKeyPressed(Keyboard::Key::A)|| Keyboard::isKeyPressed(Keyboard::Key::Left);
		PrevD = Keyboard::isKeyPressed(Keyboard::Key::D)|| Keyboard::isKeyPressed(Keyboard::Key::Right);
		///////////////////////Player Option/////////////////
		player.Gravity(G, Collision_Player_y);
		if (timeregeneration >= 10) { if (player.Health < 10) player.Health++; timeregeneration = 0; }
		player.setPosition();
		//////////////////////Moving frame ///////////
		//cout << PrickerbackClock.getElapsedTime().asMilliseconds()-pauseTime.asMilliseconds() << endl;
		if (PrickerbackClock.getElapsedTime().asMilliseconds() - pauseTime.asMilliseconds() > PrickerbackTime) PrickerBack.PrickerUpdateSpecial(0.1f);
		if (player.freezeStatus != true && Collision_Player_x == 0)
			if (timemoveframe > timechange - player.SpeedLevel * 0.005) {
				player.changeframe();
				timemoveframe = 0;
				platform.Move();
				bg.MoveBackground();
				for (unsigned int m = 0; m < Box.size(); m++) Box[m].Move();
				for (unsigned int m = 0; m < Coin.size(); m++) Coin[m].Move();
				for (unsigned int m = 0; m < _Block.size(); m++) _Block[m].Move();
				for (unsigned int m = 0; m < pricker.size(); m++)  pricker[m].PrickerUpdate();
				if (Pricker.numberPricker > 0) Pricker.numberPricker--;
				if (LaserTrap.laserbasestatus) LaserTrap.laserbaseUpdate();
				for (unsigned int m = 0; m < explosion.size(); m++) explosion[m].E_Update_Position();
				for (unsigned int m = 0; m < missileexp.size(); m++) missileexp[m].E_Update_Position();
				for (unsigned int m = 0; m < e.size(); m++) {
					e[m].move(); if (e[m].Numdex != 0 && e[m].Collision(player._Sprite) && DamageTime>1.0 && e[m].Numdex!=0)
					{
						DamageSound.play(); DamageTime = 0.0; 
						if(e[m].Numdex!=4) if(e[m].Numdex==5) player.Damage(10); else player.Damage(5);
						else { player.Damage(15); ExploMissle.play(); Explosion.E_Upload(1, e[m].E.getPosition()); missileexp.push_back(Explosion);
						e[m].Health = 0;
						}
					}
				}
				for (unsigned int m = 0; m < eB.size(); m++) eB[m].BulletMove(Vector2f(-8.0f,0.0f));
				for (unsigned int m = 0; m < bB.size(); m++) bB[m].bulletmove(Vector2f(-8.0f,0.0f));
				if (PrickerBack._pricker[PrickerBack.numberPricker - 1].getPosition().x >= -24.0f) PrickerBack.PrickerUpdateSpecial(-0.5f);
				PrickerbackClock.restart();
				BlockGen -= 8;
				Objdis -= 8;
				Generate = 1;
				FrameRun++;
			}
		//////////////////////Effect time///////
		for (unsigned int m = 0; m < explosion.size(); m++)
		{
			explosion[m].eTime = explosion[m].eTime + explosion[m].eClock.restart().asSeconds() - pauseTime.asSeconds();
			if (explosion[m].eTime > 0.04) {
				explosion[m].eTime = 0.0;
				explosion[m].frame_order_e++;
				explosion[m].E_Frame_Update();
			}
			if (explosion[m].frame_order_e == explosion[m].countframe_pic[explosion[m].Numdex].x*explosion[m].countframe_pic[explosion[m].Numdex].y)
			{
				explosion.erase(explosion.begin() + m);
			}
		}
		for (unsigned int m = 0; m < missileexp.size(); m++)
		{
			missileexp[m].eTime = missileexp[m].eTime + missileexp[m].eClock.restart().asSeconds() - pauseTime.asSeconds();
			if (missileexp[m].eTime > 0.03) {
				missileexp[m].eTime = 0.0;
				missileexp[m].frame_order_e++;
				missileexp[m].E_Frame_Update();
			}
			if (missileexp[m].frame_order_e == missileexp[m].countframe_pic[missileexp[m].Numdex].x*missileexp[m].countframe_pic[missileexp[m].Numdex].y)
			{
				missileexp.erase(missileexp.begin() + m);
			}
		}
		//////////////////////Collision Item////////////////////
		////////////////Box item///////////////////
		for (unsigned int m = 0; m < Box.size(); m++)
		{
			if (Box[m].itempos.x < -24.0f)
			{
				Box.erase(Box.begin() + m);
			}
			else
				if (Box[m].CheckCollision(player._Sprite))
				{
					getItem.play();
					player.Effectitem(Box[m].readNumberItemIndex());
					Box.erase(Box.begin() + m);
				}
		}
		////////////////Coin/////////////////////
		if (timeCoinrol > 50) { timeCoinrol = 0; for (unsigned int b = 0; b < Coin.size(); b++) Coin[b].Updateframe(); }
		for (unsigned int m = 0; m < Coin.size(); m++)
		{
			if (Coin[m].itempos.x < -24.0f)
			{
				Coin.erase(Coin.begin() + m);
			}
			else
				if (Coin[m].CheckCollision(player._Sprite))
				{
					getCoin.plause();
					getCoin.setPlayingOffset(seconds(0.4f));
					getCoin.play();
					player.Effectitem(Coin[m].readNumberItemIndex());
					Coin.erase(Coin.begin() + m);
				}
		}
		//////////////////Block/////////////////
		for (unsigned int m = 0; m < _Block.size(); m++)
		{
			if (_Block[m].position.x < -216.0f)
			{
				_Block.erase(_Block.begin() + m);
			}
		}
		/////////////////Bullet/////////////////
		for (unsigned int m = 0; m < B.size(); m++)
		{
			bool Do = 0;
			if (B[m].position.x > 1000.0f)
			{
				B.erase(B.begin() + m); Do = 1;
			}
			if(!Do) for (unsigned int n = 0; n < _Block.size(); n++)
			{
				if (B[m].bullet.getGlobalBounds().intersects(_Block[n]._Block.getGlobalBounds()))
				{
					if (B[m].BulletMode == 2) { ExploBomb.play(); Explosion.E_Upload(0,B[m].position); explosion.push_back(Explosion); }
					if (B[m].BulletMode == 3) { ExploMissle.play(); Explosion.E_Upload(1,B[m].position); missileexp.push_back(Explosion); }
					B.erase(B.begin() + m); Do = 1; break;
				}
			}if(!Do) for (unsigned int n = 0; n < e.size(); n++)
			{
				if (B[m].bullet.getGlobalBounds().intersects(e[n].E.getGlobalBounds()))
				{
					if (e[n].Numdex == 0) { SCE1.plause(); SCE1.setPlayingOffset(milliseconds(500)); SCE1.play(); }
					else if (e[n].Numdex == 2 || e[n].Numdex == 3) SCE2.play(); else SCE3.play();
					if (B[m].BulletMode == 2) { ExploBomb.play(); Explosion.E_Upload(0, B[m].position); explosion.push_back(Explosion); }
					if (B[m].BulletMode == 3) { ExploMissle.play(); Explosion.E_Upload(1, B[m].position); missileexp.push_back(Explosion); }
					e[n].Damage(B[m].DamageofBullet());
					B.erase(B.begin() + m); Do = 1; break;
				}
			}
			if(!Do) B[m].Updateframe();
		}
		////////////////////Pricker//////////////////
		for (unsigned int m = 0; m < pricker.size(); m++)
		{
			if (pricker[m]._pricker[pricker[m].numberPricker - 1].getPosition().x < -24.0f)
			{
				pricker.erase(pricker.begin() + m);
			}
		}
		/////////////////Enemy///////////////////////
		for (unsigned int m = 0; m < e.size(); m++)
		{
			if (e[m].delayShoot > 1.5) addEnemyBullet(enemybullet, eB, e[m], player._Sprite,EnemySoundBullet);
			if (e[m].Numdex == 4) e[m].E.move(-1.0f, 0.0f);
			if (e[m].E.getPosition().x < -100.0f)
			{
				e.erase(e.begin() + m);
			}
			else if (e[m].Health <= 0)
			{
				player.Score += 100; if (e[m].Numdex == 3) player.Score += 200; if (e[m].Numdex == 5) player.Score += 400;
				if(e[m].Numdex==4) {
					ExploMissle.play(); Explosion.E_Upload(1, e[m].E.getPosition()); missileexp.push_back(Explosion);
				}
				e.erase(e.begin() + m);
			}
		}
		////////////////////Enemy Bullet ////////////
		for (unsigned int m = 0; m < eB.size(); m++)
		{
			bool Do = 0;
			eB[m].BulletMove(Vector2f(-1.0f, 0.0f));
			eB[m].playerPosition = player._Position;
			if (eB[m].bullet.getPosition().x < -50.0f)
			{
				eB.erase(eB.begin() + m); Do = 1;
			}
			if (!Do) if (eB[m].bullet.getGlobalBounds().intersects(player._Sprite.getGlobalBounds()))
			{
				if (eB[m].bulletT == 3) { ExploBomb.play(); Explosion.E_Upload(0, eB[m].bullet.getPosition()); explosion.push_back(Explosion); }
				DamageSound.play(); DamageTime = 0.0; player.Damage(eB[m].DamageofBullet()); eB.erase(eB.begin() + m); Do = 1;
			}
			if (!Do) for (unsigned int n = 0; n < B.size(); n++)
			{
				if (eB[m].bullet.getGlobalBounds().intersects(B[n].bullet.getGlobalBounds()))
				{
					if (eB[m].bulletT == 3 && B[n].BulletMode>=2) 
					{ ExploBomb.play(); Explosion.E_Upload(0, eB[m].bullet.getPosition()); explosion.push_back(Explosion); 
						if (B[n].BulletMode == 2) { ExploBomb.play(); Explosion.E_Upload(0, B[n].position); explosion.push_back(Explosion); }
						if (B[n].BulletMode == 3) { ExploMissle.play(); Explosion.E_Upload(1, B[n].position); missileexp.push_back(Explosion); }
						eB.erase(eB.begin() + m); B.erase(B.begin() + n); break;
					}
					if (eB[m].bulletT == 3 && B[n].BulletMode < 2){B.erase(B.begin() + n); break;}
					if (eB[m].bulletT < 3 && B[n].BulletMode >= 2){eB.erase(eB.begin() + m);break;}
					if (eB[m].bulletT < 3 && B[n].BulletMode < 2){ eB.erase(eB.begin() + m); B.erase(B.begin() + n); break; }
				}
			}
		}
		////////////////Effect Item /////////////////
		if (disableSpeedLeveltime > 0) {
			disableSpeedLeveltime = disableSpeedLeveltime - dSLT.restart().asSeconds() + pauseTime.asSeconds();
			player.SpeedLevel = 7;
			if (disableSpeedLeveltime <= 0) player.SpeedLevel = 3;
		}
		if (player.disableChangeSL == 1) { player.disableChangeSL = 0; disableSpeedLeveltime = 5.0; dSLT.restart(); }
		if (player.freezeStatus) {
			if (setfreezetime == 0) { timefreeze = 1.75; FreezeTime.restart(); }
			setfreezetime = 1;
			timefreeze = timefreeze-FreezeTime.restart().asSeconds() + pauseTime.asSeconds();
			player.SpeedLevel = 0;
			if (timefreeze <= 0) { disableSpeedLeveltime = 0.0; player.freezeStatus = 0; setfreezetime = 0; player.SpeedLevel = 3; }
		}
		if (player.disableshoot) {
			if (setdisableshoottime == 0) { disableGunTime = 2.5; disableGunClock.restart(); }
			setdisableshoottime = 1;
			disableGunTime = disableGunTime - disableGunClock.restart().asSeconds() + pauseTime.asSeconds();
			if (disableGunTime <= 0) { player.disableshoot = 0; setdisableshoottime = 0; }
		}
		if (player.Gun == 1) { bullet.BulletMode = 1; laserTime = 5.0; player.Gun = 0; }
		if (player.Gun == 2) { bullet.BulletMode = 2; AmmoBomb = 10; player.Gun = 0; }
		if (player.Gun == 3) { bullet.BulletMode = 3; AmmoMissile = 5; player.Gun = 0; }
		///////////////Random ///////////////////////
		if (Generate)
		{
			if (random(0, 100) == 0 && Pricker.numberPricker == 0) addPricker(Pricker, pricker);
			if (random(0, 1200) == 0 && LaserTrap.laserbasestatus == 0) { LaserTrap.laserbasecreate(); LaserTrapClock.restart(); pauselaser = 0.0; }
			if (random(0, 100) == 0 && BlockGen <= 0 && Objdis <= 0) BlockGen = (48 * addBlock(block, _Block)+48);
			if(BlockGen<=0)
			{ 
				if (random(0, 150) == 0) { addCoin(coin, Coin); Objdis = 96; }
				if (random(0, 125) == 0) { addBox(box, Box); Objdis = 96;}
				if (random(0, 200) == 0) { BlockGen=addEnemy(enemy, e)+48 ;}
			}
		}
		/////////////////////////Coillision Trap///////////////////
		for (unsigned int m = 0; m < pricker.size(); m++)
			if (pricker[m].PrickerCollision(player._Sprite) && DamageTime > 1.0) {
				player.Damage(7); DamageTime = 0.0; DamageSound.play();
			}
		if (LaserTrap.laserbasestatus) {LaserTrap.laserstatus = (int)(LaserTrapClock.getElapsedTime().asSeconds() - pauseTime.asSeconds() - pauselaser) % 2; pauselaser += pauseTime.asSeconds();}
		if (LaserTrap.laserCoillision(player._Sprite) && DamageTime > 1.0) {
			player.Damage(8); DamageTime = 0.0; DamageSound.play();
		}
		if (LaserTrap.laserstatus&&LaserTrap.laserbasestatus) Lasersound.play();
		else Lasersound.plause();
		if (PrickerBack.PrickerCollision(player._Sprite)) { DamageSound.play();  player.Damage(20);}
		///////////////////////Boss ///////////////////////////////
		if (boss_status&&!boss.startboss) {
			
			if (boss.sprite.getPosition().x > 800.0f)
				boss.sprite.move(-0.5f, 0.0f);
			else
			{
				boss.startboss = 1; ClockBoss.restart();
			}
			for (unsigned int m = 0; m < B.size(); m++)if (B[m].bullet.getGlobalBounds().intersects(boss.sprite.getGlobalBounds()))
			{
				if (B[m].BulletMode == 2) { ExploBomb.play(); Explosion.E_Upload(0, B[m].position); explosion.push_back(Explosion); }
				if (B[m].BulletMode == 3) { ExploMissle.play(); Explosion.E_Upload(1, B[m].position); missileexp.push_back(Explosion); }
				SoundBoss.play();
				player.Score += boss.damage(B[m].DamageofBullet());
				B.erase(B.begin() + m); break;
			}
		}
		if (boss_status) boss.framechange();
		if (boss.startboss)
		{
			bosstime = bosstime + ClockBoss.restart().asSeconds() - pauseTime.asSeconds();
			if(boss.Health)boss.movePattern();
			for (unsigned int m = 0; m < bB.size(); m++)
			{
				bB[m].bulletmove(Vector2f(-1.0f, 0.0f));
				bB[m].changeframe();
				if (bB[m].bullet.getPosition().x < -24.0f) bB.erase(bB.begin() + m);
				else if (bB[m].bullet.getGlobalBounds().intersects(player._Sprite.getGlobalBounds()))
				{
					bB[m].Collision(&player);
					bB.erase(bB.begin() + m);
				}
			}
			if (bosstime > 1.0) {
				bosstime = 0.0;
				SoundBossShoot.play();
				bossBullet.Uploadbullet(boss.sprite);
				bB.push_back(bossBullet);
				if(random(0,200)==0&& BlockGen <= 0) BlockGen = addEnemy(enemy, e) + 48;
			}
			for(unsigned int m=0;m<B.size();m++)if (B[m].bullet.getGlobalBounds().intersects(boss.sprite.getGlobalBounds()))
			{
				if (B[m].BulletMode == 2) { ExploBomb.play(); Explosion.E_Upload(0, B[m].position); explosion.push_back(Explosion); }
				if (B[m].BulletMode == 3) { ExploMissle.play(); Explosion.E_Upload(1, B[m].position); missileexp.push_back(Explosion); }
				SoundBoss.play();
				player.Score += boss.damage(B[m].DamageofBullet());
				B.erase(B.begin() + m);
			}
			if (boss.Health == 0)
			{
				Explosion.bossend = 1;
				framebossend++;
				if(framebossend==1||framebossend==41||framebossend==81 || framebossend == 121 || framebossend == 161 || framebossend == 201 || framebossend == 241)
				{ 
				ExploBomb.play(); 
				Explosion.E_Upload(0,Vector2f(random(boss.sprite.getPosition().x-72.0f, boss.sprite.getPosition().x+72.0f), random(boss.sprite.getPosition().y - 72.0f, boss.sprite.getPosition().y + 72.0f)));
				explosion.push_back(Explosion);
				}
				if (framebossend == 261) { ExploMissle.play(); Explosion.E_Upload(1,boss.sprite.getPosition()); missileexp.push_back(Explosion); }
				if (framebossend == 400) { boss_status = 0; boss.startboss = 0; win = 1; player.Score += 5000; }
			}
		}
		DrawFrame: window.draw(BG);
		/////////////////////// Text //////////////////////////////
		text.setSize(20);
		text.setOrigin(0, 0);
		text.setColor(Color::White);
		text.TextPrint(15, 15,"HP : ", window);
		for (int i = 0; i < player.Health; i++)
		{
			Heart.setPosition(text.getLastPosition().x,text.getLastPosition().y+5.0f);
			Heart.setPosition(Heart.getPosition().x + 16.0f*i, Heart.getPosition().y);
			window.draw(Heart);
		}
		text.TextPrint(815, 15, "Time : ", window);
		text.TextPrint((int)time / 1000, window);
		text.TextPrint(240,15, "Gun : ", window);
		gun[bullet.BulletMode].setPosition(text.getLastPosition().x, text.getLastPosition().y-10.0f);
		window.draw(gun[bullet.BulletMode]);
		if (player.disableshoot) {Red_Cross.setPosition(text.getLastPosition().x+13.0f, text.getLastPosition().y+3.0f); window.draw(Red_Cross);};
		text.TextPrint(375, 15, "Ammo : ", window);
		if (bullet.BulletMode == 0) { AmmoPoint.setFillColor(Color::Yellow);AmmoPoint.setPosition(text.getLastPosition()); AmmoPoint.setSize(Vector2f(250.0f, 20.0f)); }
		if (bullet.BulletMode == 1) { AmmoPoint.setFillColor(Color::Cyan); AmmoPoint.setPosition(text.getLastPosition()); AmmoPoint.setSize(Vector2f(250.0f*(float)laserTime/5.0f, 20.0f)); }
		if (bullet.BulletMode == 2) { AmmoPoint.setFillColor(Color::Red); AmmoPoint.setPosition(text.getLastPosition()); AmmoPoint.setSize(Vector2f(250.0f*(float)AmmoBomb / 10.0f, 20.0f)); }
		if (bullet.BulletMode == 3) { AmmoPoint.setFillColor(Color::Green); AmmoPoint.setPosition(text.getLastPosition()); AmmoPoint.setSize(Vector2f(250.0f*(float)AmmoMissile / 5.0f, 20.0f)); }
		window.draw(AmmoPoint);
		text.TextPrint(15, 60, "Shield : ", window);
		if(player.ShieldGate)
		for (int i = 0; i < player.ShieldGate; i++)
		{
			ShieldPoint.setPosition(text.getLastPosition().x + 20.0f*i, text.getLastPosition().y+3.0f);
			window.draw(ShieldPoint);
		}
		else text.TextPrint("Empty Shiled", window);
		text.TextPrint(325.0f,60.0f, "Speed Level : ", window);
		if (player.SpeedLevel == 1) { text.setColor(Color::Magenta); }
		if (player.SpeedLevel == 2) { text.setColor(Color::Blue); }
		if (player.SpeedLevel == 3) { text.setColor(Color::Cyan); }
		if (player.SpeedLevel == 4) { text.setColor(Color::Green); }
		if (player.SpeedLevel == 5) { text.setColor(Color::Yellow); }
		if (player.SpeedLevel == 7) { text.setColor(Color::Red); }
		text.TextPrint(player.SpeedLevel, window);
		text.setColor(Color::White);
		text.TextPrint(625.0f, 60.0f, "Score : ", window);
		text.TextPrint(player.Score, window);
		if (boss_status) {
			text.TextPrint(15.0f, 640.0f, "Boss Health : ", window);
			BossPoint.setPosition(text.getLastPosition());
			BossPoint.setSize(Vector2f(770.0f*boss.Health/15000.0f, 25.0f));
			window.draw(BossPoint);
		}
		/////////////////////Draw frame ////////////
		bg.DrawBackground(window);
		platform.draw(window);
		for (unsigned int b = 0; b < pricker.size(); b++) pricker[b].Prickerdraw(window);
		if (LaserTrap.laserbasestatus) LaserTrap.laserbasedraw(window);
		for (unsigned int b = 0; b < Box.size(); b++) Box[b].Drawitem(window);
		for (unsigned int b = 0; b < Coin.size(); b++) Coin[b].Drawitem(window);
		for (unsigned int b = 0; b < _Block.size(); b++) _Block[b].draw(window);
		for (unsigned int b = 0; b < e.size(); b++) e[b].draw(window);
		for (unsigned int b = 0; b < B.size(); b++)  B[b].draw(window); 
		for (unsigned int b = 0; b < eB.size(); b++) eB[b].draw(window);
		for (unsigned int b = 0; b < bB.size(); b++) bB[b].draw(window);
		if (boss_status)  boss.draw(window);
		for (unsigned int b = 0; b < explosion.size(); b++) explosion[b].E_Draw(window);
		for (unsigned int b = 0; b < missileexp.size(); b++) missileexp[b].E_Draw(window);
		player.draw(&window, DamageTime);
		PrickerBack.Prickerdraw(window);
		if (backpause == 1) { backpause = 0; goto loop_pause; }
		if (backafterpause == 1) { backafterpause = 0; goto loop_afterpause; }
		if (backend == 1) { backend = 0; goto loop_end; }
		////////////////// Check ////////////////////
		//cout << player._Position.x << " " << player._Position.y << endl;
		//cout << timechange - player.SpeedLevel * 0.005 << endl;
		//cout << disableSpeedLeveltime << endl;
		//cout << player.Health << endl;
		//cout << player.CheckCollision().left << " " << player.CheckCollision().top << " "
		//	<< player.CheckCollision().width << " " << player.CheckCollision().height << endl;
		//cout << Coin.size() << endl;
		//cout << player.freezeStatus << endl;
		//cout << player.Shieldstatus << endl;
		//cout << player.picsizeShiledX << " " << player.picsizeShiledY << endl;
		//cout << time << endl;
		//cout << _Block.size() << endl;
		//cout << B.size() << endl;
		//cout << BulletTime << endl;
		//cout << laserTime << endl;
		//cout << pricker.size() << endl;
		//cout << LaserTrap.laserbase.getPosition().x << endl;
		//cout << e.size() << endl;
		//cout << BlockGen << endl;
		//cout << pauseTime.asMicroseconds()<< endl;
		//cout << timefreeze << endl;
		//cout << eB.size() << endl;
		//cout << PrickerbackTime << endl;
		//cout << PrickerBack._pricker[PrickerBack.numberPricker - 1].getPosition().x << endl;
		//cout << random(100000.012f, 300000.4560f) << endl;
		//cout << bB.size() << endl;
		//cout << FrameRun << endl;
		//////////////////////////////////////////////////////
		window.display();
		//////////////////////End Game /////////////////////
		if (player.Health == 0 || win) 
		{
			state = 0;
			window.setMouseCursorVisible(true);
			playing.stop();
			Lasersound.stop();
			while (!conend)
			{
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						ModeScreen = 0;
						conend = 1;
					}
					if (ready_in && event.type == Event::KeyPressed && event.key.code != Keyboard::Return)
					{
						if (event.key.code == Keyboard::BackSpace) { if (charNum > 0) { ClickSound.play(); charNum--; Name[charNum] = 0; } }
						else if (charNum < 25)
							if (event.key.code >= Keyboard::A && event.key.code <= Keyboard::Z) { ClickSound.play(); Name[charNum] = event.key.code + 'A'; charNum++; }
							else if (event.key.code >= Keyboard::Num0 && event.key.code <= Keyboard::Num9) { ClickSound.play(); Name[charNum] = event.key.code + '0' - Keyboard::Num0; charNum++; }
							else if (event.key.code >= Keyboard::Numpad0 && event.key.code <= Keyboard::Numpad9) { ClickSound.play(); Name[charNum] = event.key.code + '0' - Keyboard::Numpad0; charNum++; }
					}
					if (Mouse::getPosition(window).x >= 180.0f && Mouse::getPosition(window).x <= 780.0f)
					{
						if (Mouse::getPosition(window).y > 290.0f && Mouse::getPosition(window).y <= 339.0f) {
							if (state != 0) { Movestate.play(); state = 0; }
							if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonPressed) { ClickSound.play();  if (ready_in == 0) ready_in = 1; else ready_in = 0; }
						}
						if ((Mouse::getPosition(window).y > 339.0f && Mouse::getPosition(window).y <= 388.0f) && !ready_in) {
							if (state != 1) { Movestate.play(); state = 1; }
							if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonPressed && Name[0] != 0)
							{
								ClickSound.play(); Recordscore(Name, player.Score); conend = 1; ModeScreen = 3; Exit = 1; sleep(milliseconds(300)); break;
							}
						}
						if ((Mouse::getPosition(window).y > 388.0f && Mouse::getPosition(window).y <= 437.0f) && !ready_in) {
							if (state != 2) { Movestate.play(); state = 2; }
							if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonPressed) { ClickSound.play(); conend = 1; ModeScreen = 2; Exit = 1; sleep(milliseconds(300)); break; }
						}
						if ((Mouse::getPosition(window).y > 437.0f && Mouse::getPosition(window).y <= 486.0f) && !ready_in) {
							if (state != 3) { Movestate.play(); state = 3; }
							if (event.mouseButton.button == Mouse::Left && event.type == Event::MouseButtonPressed) { ClickSound.play(); conend = 1; ModeScreen = 1; Exit = 1; sleep(milliseconds(300)); break; }
						}
					}
				}
				if (!ready_in)
				{
					if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
					{
						if (!button.W) {
							Movestate.play();
							state--;
							if (state < 0) state = 3;
							button.W = 1;
						}
					}
					else button.W = 0;
					if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
					{
						if (!button.S)
						{
							button.S = 1;
							Movestate.play();
							state++;
							if (state > 3) state = 0;
						}
					}
					else button.S = 0;
				}
				if (Keyboard::Return == event.key.code)
				{
						if (!button.Enter)
							{
							if (state == 0) { ClickSound.play(); if (ready_in == 0) ready_in = 1; else ready_in = 0; }
							if (state == 1 && Name[0] != 0) { ClickSound.play(); Recordscore(Name, player.Score); conend = 1; ModeScreen = 3; Exit = 1; }
							if (state == 2) { ClickSound.play(); conend = 1; ModeScreen = 2; Exit = 1; }
							if (state == 3) { ClickSound.play(); conend = 1; ModeScreen = 1; Exit = 1; }
							sleep(milliseconds(300));
							button.Enter = 1;
							}
				}else button.Enter =0;
				//cout << state << endl;
				//cout << Mouse::getPosition(window).x << " " << Mouse::getPosition(window).y << endl;
				window.clear();
				backend = 1;
				goto DrawFrame;
				loop_end:
				window.draw(filter);
				Menu.EndGameMenu(window, state,win,player.Score);
				if (Name[0] != 0)
				{
					if (!ready_in) { text.setColor(Color::Black); } else { text.setColor(Color::Blue); }
					text.setSize(26);
					text.setMiddleTextPrint(295.0f,Name, window);
					text.TextPrint(" ", window);
				}
				if (state == 0)
				{
					if(!ready_in) {text.setColor(Color::Black);} else { text.setColor(Color::Blue); }
					if (Name[0] == 0) { text.setSize(40); text.setMiddleTextPrint(285.0f, "|", window); text.setSize(26); }
					else { text.setSize(40); text.TextPrint(text.getLastPosition().x-text.getSizeMessage().width/2,285.0f,"|", window); text.setSize(26); }
					text.setOrigin(0, 0);
				}
				window.display();
			}
		}
		////////////////////////Pause///////////////////////
		pauseTime = pauseTime.Zero;
		if (pauseMode)
		{
			c.restart();
			repause:
			window.setMouseCursorVisible(true);
			state = 0;
			playing.plause();
			if (LaserTrap.laserstatus&&LaserTrap.laserbasestatus) Lasersound.plause();
			while (pauseMode && event.type)
			{
				if (Mouse::getPosition(window).x >= 330.0f && Mouse::getPosition(window).x <= 630.0f)
				{
					if (Mouse::getPosition(window).y > 244.0f && Mouse::getPosition(window).y <= 293.0f && state != 0) { Movestate.play(); state = 0; }
					if (Mouse::getPosition(window).y > 293.0f && Mouse::getPosition(window).y <= 342.0f && state != 1) { Movestate.play(); state = 1; }
					if (Mouse::getPosition(window).y > 342.0f && Mouse::getPosition(window).y <= 391.0f && state != 2) { Movestate.play(); state = 2; }
				}
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						ModeScreen = 0;
						Exit = 1;
					}
					if (event.type == Event::MouseButtonPressed)
					{
						FloatRect BoxMenu = { 330.0f,244.0f,300.0f,147.0f };
						if (event.mouseButton.x >= BoxMenu.left&&event.mouseButton.x <= BoxMenu.left + BoxMenu.width&&
							event.mouseButton.y >= BoxMenu.top&&event.mouseButton.y <= BoxMenu.top + BoxMenu.height&&
							event.mouseButton.button == Mouse::Left)
						{
							ClickSound.play();
							if (state == 0) pauseMode = 0;
							if (state == 1) { pauseMode = 0; ModeScreen = 2; Exit = 1; }
							if (state == 2) { pauseMode = 0; ModeScreen = 1; Exit = 1; }
							sleep(milliseconds(300));
						}
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					if (!button.Esc)
					{
						button.Esc = 1;
						pauseMode = 0;
						state = 0;
					}
				} else button.Esc =0;
				if (Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up))
				{
					if (!button.W)
					{
						button.W = 1;
						Movestate.play();
						state--;
						if (state < 0) state = 2;
					}
				}else button.W=0;
				if (Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down))
				{
					if (!button.S)
					{
						button.S = 1;
						Movestate.play();
						state++;
						if (state > 2) state = 0;
					}
				}
				else button.S = 0;
				if (Keyboard::isKeyPressed(Keyboard::Return))
				{
					if(!button.Enter)
					{
						ClickSound.play();
						if (state == 0) pauseMode = 0;
						if (state == 1) { pauseMode = 0; ModeScreen = 2; Exit = 1; }
						if (state == 2) { pauseMode = 0; ModeScreen = 1; Exit = 1; }
						sleep(milliseconds(300));
						button.Enter = 1;
					}
				} else button.Enter = 0;
				/////////////////////////
				window.clear();
				backpause = 1;
				goto DrawFrame;
				loop_pause :
				window.draw(filter);
				if(!ready)Menu.TutorialMenu(window);
				Menu.BackgroundMenuPause(window,state);
				window.display();
				////////////////////////
			}
			//cout << pauseTime.asSeconds() << endl;
			BeforeReady:
			countdownTime = 3.0;
			int movepos;
			Countdown.restart();
			if(!Exit)Countdown_Sound.play();
			while (countdownTime&&state == 0)
			{
				if (Exit) break;
				while (window.pollEvent(event))
				{
					if (event.type == Event::Closed)
					{
						window.close();
						ModeScreen = 0;
						Exit = 1;
					}
				}
				if (Keyboard::isKeyPressed(Keyboard::Escape))
				{
					if (!button.Esc)
					{
						button.Esc = 1;
						pauseMode = 1;
						goto repause;
					}
				}else button.Esc = 0;
				window.clear();
				backafterpause = 1;
				goto DrawFrame;
				loop_afterpause:
				text.setSize(500);
				if (countdownTime == 1) movepos = 40; else movepos = 0;
				switch ((int)countdownTime) { case 3 : text.setColor(Color::Green); break; case 2 : text.setColor(Color::Yellow); break; 
										 case 1: text.setColor(Color::Red); break; default:break;
				}
				text.TextPrint(350.0f+movepos,0.0f,(int)countdownTime, window);
				if (!ready) { Menu.TutorialMenu(window); }
				window.display();
				if (countdownTime != 3 - (int)Countdown.getElapsedTime().asSeconds())Countdown_Sound.play();
				countdownTime = 3 - (int)Countdown.getElapsedTime().asSeconds();
			}
			if (LaserTrap.laserstatus&&LaserTrap.laserbasestatus) Lasersound.play();
			playing.play();
			pauseTime = c.getElapsedTime();
			if (ready == 0) { GameTime.restart(); pauseTime = pauseTime.Zero; ready = 1; }
		}
	}
	return ModeScreen;
}
void addBox(Item&box,vector<Item>& Box)
{
	box.ItemIndex(box.RateItem[random(0, 25)]);
	//box.ItemIndex(9);
	box.Uploaditem(Vector2f(1008.0f, (float)random(174, 559)));
	Box.push_back(box);
}
void addCoin(Item&coin, vector<Item>& Coin)
{
	coin.ItemIndex(10);
	coin.Uploaditem(Vector2f(1008.0f, (float)random(174, 559)));
	Coin.push_back(coin);
}
int addBlock(Block& block,vector<Block>& _Block)
{
	int rate[10] = { 5,4,3,3,2,1,1,0,0,0 };
	int pattern = rate[random(0,9)];
	switch (pattern)
	{
	case 0:block.patternSize = 0; block.setposition(1008.0f,(float)random(174, 559)); _Block.push_back(block); return 1; break;
	case 1:block.patternSize = 1; block.setposition(1008.0f,(float)random(198, 535)); _Block.push_back(block); return 2; break;
	case 2:block.patternSize = 2; block.setposition(1008.0f,(float)random(222, 511)); _Block.push_back(block); return 3; break;
	case 3:block.patternSize = 3; block.setposition(1008.0f,(float)random(174, 559)); _Block.push_back(block); return 3; break;
	case 4:block.patternSize = 4; block.setposition(1008.0f,(float)random(222, 511)); _Block.push_back(block); return 1; break;
	case 5:block.patternSize = 3; block.setposition(1008.0f,(float)random(222, 511)); _Block.push_back(block);
		   block.patternSize = 4; block.setposition(block.getposition().x, block.getposition().y); _Block.push_back(block); return 3; break;
	default: return 0;break;
	}
}
void addPricker(Trap& Pricker, vector<Trap>& pricker)
{
	int p = random(0, 2);
	Pricker.numberPricker = (unsigned int)random(1, 9);
	Pricker.patternPricker(p);
	pricker.push_back(Pricker);
	if (p == 0) Pricker.numberPricker *= 6;
	if (p == 1) Pricker.numberPricker *= 3;
}
int addEnemy(Enemy& enemy, vector<Enemy>& e)
{
	enemy.Numdex = enemy.EnemyRate[random(0, 25)]; 
	enemy.AddEnemy(); 
	e.push_back(enemy);
	switch (enemy.Numdex)
	{
	case 0: return 0 ; break;
	case 1: return 72; break;
	case 2: return 60; break;
	case 3: return 72; break;
	case 4: return 0 ; break;
	case 5: return 144; break;
	default:return 0; break;
	}
}
void addEnemyBullet(EnemyBullet& enemybullet,vector<EnemyBullet>& eB,Enemy& enemy, Sprite player, SoundGame* EbSound)
{
	enemy.delayShoot = 0.0;
	if (player.getPosition().x < enemy.E.getPosition().x)
	if(enemy.Numdex!=0&& enemy.Numdex != 4)
	{ 
	enemybullet.playerPosition = player.getPosition();
	if (enemy.Numdex == 1) { (EbSound+1)->play(); enemybullet.bulletT = 2; }
	if (enemy.Numdex == 2) { EbSound->play(); enemybullet.bulletT = 0; }
	if (enemy.Numdex == 3) { EbSound->play(); enemybullet.bulletT = 1; }
	if (enemy.Numdex == 5) { (EbSound+2)->play(); enemybullet.bulletT = 3; }
	enemybullet.UploadBullet(enemy.E); 
	eB.push_back(enemybullet);
	}
}
int ScoreMode(RenderWindow& win)
{
	win.setMouseCursorVisible(true);
	debounced button = { 0,0,0,0 };
	int ModeScreen = 3;
	int state = 0,MAX=5;
	bool cursor_box = 0,Exit=0;
	SoundGame music("Resource\\High Score Menu.ogg");
	music.setLoop(true);
	music.play();
	while (win.isOpen())
	{
		if (Exit) break;
		Event events;
		while (win.pollEvent(events))
		{
			if (events.type == Event::Closed)
			{
				win.close();
				ModeScreen = 0;
			}
			if (events.type == Event::MouseWheelScrolled)
			{
				if (events.mouseWheelScroll.delta > 0 && state > 0)
				{
					Movestate.play();
					state--;
				}
				if (events.mouseWheelScroll.delta < 0 && state < MAX)
				{
					Movestate.play();
					state++;
				}
			}
			if (Mouse::getPosition(win).x >= 5.0f&&Mouse::getPosition(win).x <= 215.0f&&Mouse::getPosition(win).y >= 10.0f&&Mouse::getPosition(win).y <= 90.0f)
			{
				if (!cursor_box) { Movestate.play(); cursor_box = 1; }
				if (events.mouseButton.button == Mouse::Left && events.type == Event::MouseButtonPressed)
				{
					ClickSound.play();
					ModeScreen = 1;
					sleep(milliseconds(300));
					Exit = 1;
					break;
				}
			}
			else cursor_box = 0 ;
		}
		if (Keyboard::isKeyPressed(Keyboard::Escape))
		{
			if (!button.Esc)
			{
				ClickSound.play();
				ModeScreen = 1;
				sleep(milliseconds(300));
				Exit = 1;
				button.Esc = 1;
			}
		}else button.Esc=0;
		if ((Keyboard::isKeyPressed(Keyboard::W) || Keyboard::isKeyPressed(Keyboard::Up)) && state > 0)
		{
			if (!button.W)
			{
				Movestate.play();
				state--;
				button.W=1;
			}
		}else button.W=0;
		if ((Keyboard::isKeyPressed(Keyboard::S) || Keyboard::isKeyPressed(Keyboard::Down)) && state < MAX)
		{
			if (!button.S)
			{
				Movestate.play();
				state++;
				button.S = 1;
			}
		}else button.S=0;
		win.clear();
		win.draw(BG);
		MAX = Menu.ScoreBoard(win, state, cursor_box);
		win.display();
	}
	return ModeScreen;
}