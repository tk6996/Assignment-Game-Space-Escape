using namespace sf;
class Item
{
public:
	Item();
	void ItemIndex(int IndexItem);
	void Uploaditem(const Vector2f& Position);
	void Uploaditem(float x,float y);
	void Updateframe();
	void Drawitem(RenderWindow&);
	void Move();
	bool CheckCollision(Sprite& Player);
	int readNumberItemIndex();
	Vector2f itempos;
	int RateItem[25] = { 0,0,0,1,1,2,2,2,3,3,3,3,3,4,5,5,6,7,7,7,8,8,9,9,9 };
private:
	int C[11] = { 1,1,1,1,1,1,1,1,1,1,6};
	int count, Num, frame = 0;
	Sprite _item;
	IntRect _frame;
	Texture pic[11];
	Vector2f Texsize;
};

