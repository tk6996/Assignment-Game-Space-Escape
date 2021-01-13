using namespace sf;
class Effect
{
public:
	Effect();
	~Effect();
	Sprite _Effect;
	void E_Frame_Update();
	void E_Upload(int numdex,const Vector2f pos);
	void E_Update_Position();
	void E_Draw(RenderWindow& win);
	int frame_order_e = 0;
	bool bossend = 0;
	int Numdex;
	Clock eClock;
	Vector2i countframe_pic[2] = { {4,4},{5,3} };
	double eTime = 0.0;
private:
	Texture pic[2];
	Vector2f size_pic, ScaleSize[2] = { {3.0f,3.0f},{2.5f,2.5f} };
	IntRect frame_exp; 
};

