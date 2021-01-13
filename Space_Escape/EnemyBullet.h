using namespace sf;
class EnemyBullet
{
public:
	EnemyBullet();
	void UploadBullet(Sprite enemy);
	void BulletMove(Vector2f move = { 0.0f,0.0f });
	void draw(RenderWindow& win);
	Vector2f playerPosition;
	int bulletT;
	int DamageofBullet();
	Sprite bullet;
private:
	Texture pic[4];
	Vector2f picsize;
	Vector2f StartplayerPosition,StartenemyPosition;
};
