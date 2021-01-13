using namespace sf;
using namespace std;
class Bossbullet
{
public:
	Bossbullet();
	~Bossbullet();
	RectangleShape bullet;
	void Uploadbullet(Sprite boss);
	void bulletmove(Vector2f pos);
	void changeframe();
	void draw(RenderWindow& win);
	void Collision(Player* player);
private:
	int Numdex=-1;
	int direction = 0;
	int rotation = 0;
	vector<Texture> pic; 
	Sprite s;
};

