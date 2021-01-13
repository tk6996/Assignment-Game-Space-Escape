using namespace sf;
class TextGame
{
public:
	TextGame();
	TextGame(const char* Name);
	void setFont(const char* Name);
	void TextPrint(const char* text, RenderWindow& win);
	void TextPrint(int number, RenderWindow& win);
	void TextPrint(const Vector2f& position,const char* text, RenderWindow& win);
	void TextPrint(float x,float y,const char* text, RenderWindow& win);
	void TextPrint(float x, float y,int number, RenderWindow& win);
	void TextPrint(const Vector2f& position, int number, RenderWindow& win);
	Vector2f getLastPosition();
	void setSize(int size);
	void setColor(const Color& color);
	void setPostion(const Vector2f& position);
	void setPostion(float x,float y);
	void setSytle(uint32_t);
	void setMiddleTextPrint(float y, const char* text, RenderWindow& win);
	void setMiddleTextPrint(float y, int number, RenderWindow& win);
	void setOrigin(float x, float y);
	FloatRect getSizeMessage();
private:
	Font font;
	Text Message;
};