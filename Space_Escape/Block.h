using namespace sf;
class Block
{
public:
	Block(const String Name);
	void Move();
	Vector2f position;
	void draw(RenderWindow& window);
	void setposition(float x, float y);
	Vector2f getposition() const;
	int patternSize;
	int Collision(Sprite Player,RectangleShape Line);
	Sprite _Block;
private:
	Texture pic;
	Vector2f blocksize;
};

