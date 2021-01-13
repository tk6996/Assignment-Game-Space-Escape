using namespace sf;

class Enemy
{
public:
	Enemy();
	~Enemy();
	int Numdex=-1,Health=0;
	void AddEnemy();
	void move();
	bool Collision(Sprite player);
	void draw(RenderWindow& win);
	void Damage(int);
	int EnemyRate[25] = { 5,3,3,3,4,4,4,4,2,2,2,2,2,2,1,1,1,1,1,1,0,0,0,0,0 };
	Sprite E;
	double delayShoot = 0.0;
	Clock clock;
private:
	Vector2f picsize;
	Texture pic[6];
};