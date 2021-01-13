using namespace sf;
class Bullet
{
public:
	Bullet();
	int BulletMode;
	void UploadBullet();
	void Updateframe();
	void setPosition(float x,float y);
	void draw(RenderWindow& win);
	int DamageofBullet();
	Vector2f position;
	Sprite bullet;
private:
	Texture pic[4];
	Vector2f picsize;
	IntRect _frame;
	int count[4] = { 4,1,1,1 }, frame = 0;
};