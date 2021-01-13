using namespace std;
using namespace sf;
int random(int min, int max);
float random(float min, float max);
int randomexcept(int min, int max, vector<int> except);
void setMiddlepositionX(Sprite& Object,RenderWindow& win);
void showFloatRect(FloatRect);
void Recordscore(const char* Name, int Score);
vector<pair<string,int>> ScoreboardBuffer();
struct debounced
{
	bool W;
	bool S;
	bool Enter;
	bool Esc;
};