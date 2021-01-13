using namespace sf;
class Background
{
public:
	Background(const char*);
	void MoveBackground();
	void DrawBackground(RenderWindow&);
private:
	Texture T;
	Sprite _Background[3];
};