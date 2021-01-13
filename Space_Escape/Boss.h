using namespace sf;
class Boss
{
public:
	Boss();
	~Boss();
	Sprite sprite;
	int Health = 15000;
	bool startboss=0;
	void framechange();
	void draw(RenderWindow& win);
	void movePattern();
	int damage(int);
private:
	Texture BossTex,frameeffect;
	Sprite frameSprite;
	Vector2f picsize;
	int MovdDirection=random(0,2),frame=0,cframe=6;
};

