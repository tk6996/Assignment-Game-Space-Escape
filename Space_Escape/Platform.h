using namespace sf;
class Platform
{
public:
	Platform(const char*);
	void draw(RenderWindow& Window);
	void Move();
	bool CollisionPlayer(Sprite& Player); 
	Sprite _Platform[2][30];
private:
	float x = 100, y = 0;
	Texture block,pricker;
};
