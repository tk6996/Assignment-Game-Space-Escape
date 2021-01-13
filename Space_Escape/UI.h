using namespace sf;
class UI
{
public: UI();
		void BackgroundMenuPause(RenderWindow& win,int state);
		void StartMenu(RenderWindow& win, int state);
		void EndGameMenu(RenderWindow& win, int state,bool winner, int score);
		void TutorialMenu(RenderWindow& win);
		int ScoreBoard(RenderWindow& win, int state, bool cursor_box);
private:
	const char *Red_button_0, *Grey_button_3, *Red_button_10,*Red_panel;
	Texture HeadBarTex, BarBeforeTex, NameBarTex,BackbarTex;
	Sprite HeadBar, BarBefore, NameBar,Backbar;
	TextGame text;
	RectangleShape BoxMenu;
};