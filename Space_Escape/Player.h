using namespace sf;
class Player
{
public:
	Player(const char*);
	void Gravity(bool, bool);
	void setPosition();
	void draw(RenderWindow* window,double DamageTime);
	void changeframe();
	void Effectitem(int Num);
	void Damage(int damage);
	int Health = 10, Score = 0,SpeedLevel = 3, ShieldGate = 0,Gun=0;
	unsigned int picsizeShiledX, picsizeShiledY;
	bool disableChangeSL = 0, freezeStatus = 0,disableshoot =0;
	Vector2f _Position;
	Sprite _Sprite;
	RectangleShape LinePlay; 
private:
	Texture pic,picshield;
	IntRect _frame,frameshiled;
	RectangleShape IceBlock;
	Sprite Shield;
	int frame = 0;
};