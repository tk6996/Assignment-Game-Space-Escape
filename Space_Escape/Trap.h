using namespace sf;
class Trap
{
public:
	Trap();
	Sprite _pricker[16],laserbase;
	bool laserbasestatus = 0,laserstatus =0;
	unsigned int numberPricker=0;
	void Prickerdraw(RenderWindow& win);
	void patternPricker(unsigned int pattern);
	void PrickerUpdate();
	void PrickerUpdateSpecial(float move);
	bool PrickerCollision(Sprite Player);
	void laserbasecreate();
	void laserbaseUpdate();
	void laserbasedraw(RenderWindow& win);
	bool laserCoillision(Sprite Player);
private:
	Texture _prickerTex,_laserbaseTex,_laserTex;
	RectangleShape laser;
	Vector2f size_pic_pricker, size_pic_laserbase;
};