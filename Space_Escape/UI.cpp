#include "SFMLHeaderPack.h"
#include <iostream>
#include "Extention_tool.h"
#include "TextGame.h"
#include "UI.h"
using namespace std;
UI::UI()
{
	text.setFont("Resource/Font.ttf");
	Red_button_0 = "Resource/red_button00.png";
    Grey_button_3 = "Resource/grey_button03.png";
	Red_button_10 = "Resource/red_button10.png";
	Red_panel = "Resource/red_panel.png";
	HeadBarTex.loadFromFile(Red_button_0);
	BarBeforeTex.loadFromFile(Grey_button_3);
	NameBarTex.loadFromFile(Red_button_10);
	BackbarTex.loadFromFile(Red_panel);
}
void UI::BackgroundMenuPause(RenderWindow& win, int state)
{
	HeadBar.setTexture(HeadBarTex);
	HeadBar.setScale(300.0f / HeadBarTex.getSize().x, 1);
	HeadBar.setPosition(385.0f, 200.0f);
	setMiddlepositionX(HeadBar, win);
	BarBefore.setTexture(BarBeforeTex);
	BarBefore.setScale(300.0f / BarBeforeTex.getSize().x, 1);
	BarBefore.setPosition(HeadBar.getPosition().x, HeadBar.getPosition().y + HeadBar.getGlobalBounds().height);
	win.draw(HeadBar);
	win.draw(BarBefore);
	BarBefore.setPosition(HeadBar.getPosition().x, HeadBar.getPosition().y + HeadBar.getGlobalBounds().height + BarBefore.getGlobalBounds().height);
	win.draw(BarBefore);
	BarBefore.setPosition(HeadBar.getPosition().x, HeadBar.getPosition().y + HeadBar.getGlobalBounds().height +2 * BarBefore.getGlobalBounds().height);
	win.draw(BarBefore);
	text.setSize(26);
	text.setColor(Color::White);
	text.setMiddleTextPrint (HeadBar.getPosition().y+5.0f,"Pause", win);
	if (state == 0) { text.setColor(Color(232, 106, 23)); }else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + 5.0f + BarBefore.getGlobalBounds().height, "Resume", win);
	if (state == 1) { text.setColor(Color(232, 106, 23)); }else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + 5.0f + 2*BarBefore.getGlobalBounds().height, "Restart", win);
	if (state == 2) { text.setColor(Color(232, 106, 23)); }else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + 5.0f + 3*BarBefore.getGlobalBounds().height, "Back to Menu", win);
	BoxMenu.setFillColor(Color::Transparent);
	BoxMenu.setSize(Vector2f(300.0f , 3 * BarBefore.getGlobalBounds().height));
	BoxMenu.setPosition((960.0f - BoxMenu.getGlobalBounds().width) / 2, HeadBar.getPosition().y + BarBefore.getGlobalBounds().height - 5.0f);
	//cout << BoxMenu.getGlobalBounds().left << " " << BoxMenu.getGlobalBounds().top << " " << BoxMenu.getGlobalBounds().width << " " << BoxMenu.getGlobalBounds().height << endl;
	win.draw(BoxMenu);
}
void UI::StartMenu(RenderWindow& win, int state)
{
	float StartYposition = 400.0f;
	BarBefore.setTexture(BarBeforeTex);
	BarBefore.setScale(300.0f / BarBeforeTex.getSize().x, 1);
	setMiddlepositionX(BarBefore, win);
	BarBefore.setPosition(BarBefore.getPosition().x, StartYposition);
	//win.draw(BarBefore);
	text.setSize(26);
	text.setColor(Color::White);
	if (state == 0) { text.setColor(Color(232, 106, 23)); }
	else text.setColor(Color::White);
	text.setMiddleTextPrint(StartYposition + 5.0f, "Start Game", win);
	if (state == 1) { text.setColor(Color(232, 106, 23)); }
	else text.setColor(Color::White);
	text.setMiddleTextPrint(StartYposition + 5.0f +  BarBefore.getGlobalBounds().height, "High Score", win);
	if (state == 2) { text.setColor(Color(232, 106, 23)); }
	else text.setColor(Color::White);
	text.setMiddleTextPrint(StartYposition + 5.0f + 2 * BarBefore.getGlobalBounds().height, "Exit", win);
	BoxMenu.setFillColor(Color::Transparent);
	BoxMenu.setSize(Vector2f(300.0f, 3 * BarBefore.getGlobalBounds().height));
	BoxMenu.setPosition((960.0f - BoxMenu.getGlobalBounds().width) / 2, StartYposition );
	//cout << text.getSizeMessage().left << " " << text.getSizeMessage().top << " " << text.getSizeMessage().width << " " << text.getSizeMessage().height << endl;
	//cout << BoxMenu.getGlobalBounds().left << " " << BoxMenu.getGlobalBounds().top << " " << BoxMenu.getGlobalBounds().width << " " << BoxMenu.getGlobalBounds().height << endl;
	win.draw(BoxMenu);
	text.setColor(Color::White);
	text.setSize(36);
	text.setMiddleTextPrint(600, "Watcharin Kanha 61010960", win);
}
void UI::EndGameMenu(RenderWindow& win, int state, bool winner,int score)
{
	HeadBar.setTexture(HeadBarTex);
	HeadBar.setScale(600.0f / HeadBarTex.getSize().x, 2);
	HeadBar.setPosition(385.0f, 200.0f);
	setMiddlepositionX(HeadBar, win);
	win.draw(HeadBar);
	NameBar.setTexture(NameBarTex);
	NameBar.setScale(600.0f / NameBarTex.getSize().x, 1);
	NameBar.setPosition(HeadBar.getPosition().x, HeadBar.getPosition().y+HeadBar.getGlobalBounds().height);
	win.draw(NameBar);
	BarBefore.setTexture(BarBeforeTex);
	BarBefore.setScale(600.0f / BarBeforeTex.getSize().x, 1);
	for(int i=1;i<=3;i++){
		BarBefore.setPosition(NameBar.getPosition().x, HeadBar.getPosition().y + HeadBar.getGlobalBounds().height + i * NameBarTex.getSize().y);
		//showFloatRect(BarBefore.getGlobalBounds());
		win.draw(BarBefore);
	}
	text.setSize(26);
	text.setColor(Color::White);
	if(winner)text.setMiddleTextPrint(HeadBar.getPosition().y + 5.0f, "Winner", win);
	else text.setMiddleTextPrint(HeadBar.getPosition().y + 5.0f, "Game Over", win);
	text.setMiddleTextPrint(HeadBar.getPosition().y + HeadBar.getGlobalBounds().height / 2.0f,score, win);
	if (state == 1) { text.setColor(Color(232, 106, 23)); } else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + HeadBar.getGlobalBounds().height + 5.0f + NameBar.getGlobalBounds().height, "Record Score", win);
	if (state == 2) { text.setColor(Color(232, 106, 23)); } else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + HeadBar.getGlobalBounds().height + 5.0f + 2*NameBar.getGlobalBounds().height, "Restart without Record Score", win);
	if (state == 3) { text.setColor(Color(232, 106, 23)); } else text.setColor(Color::Black);
	text.setMiddleTextPrint(HeadBar.getPosition().y + HeadBar.getGlobalBounds().height + 5.0f + 3*NameBar.getGlobalBounds().height, "Back to Menu without Record Score", win);
}
int UI::ScoreBoard(RenderWindow& win, int state,bool cursor_box)
{
	const Vector2f posName = { 150.0f,250.0f }, posScore = { 710.0f,250.0f };
	vector<pair<string, int>> score_list;
	int Max_print;
	text.setColor(Color::White);
	text.setSize(72);
	text.setMiddleTextPrint(100, "High Score", win);
	text.setOrigin(0.0f, 0.0f);
	text.setSize(26);
	score_list = ScoreboardBuffer();
	BarBefore.setTexture(BarBeforeTex);
	BarBefore.setPosition(Vector2f(5.0f, 10.0f));
	BarBefore.setScale(210.0f / BarBeforeTex.getSize().x, 80.0f / BarBeforeTex.getSize().y);
	win.draw(BarBefore);
	cursor_box ? text.setColor(Color(232, 106, 23)) :text.setColor(Color::Black);
	text.TextPrint(15.0f, 15.0f, "Back to Menu", win);
	text.TextPrint(15.0f, 45.0f, "          Esc    ", win);
	text.setColor(Color::White);
	text.TextPrint(posName.x,posName.y, "Name", win); text.TextPrint(posScore.x, posScore.y, "Score", win);
	score_list.size() < 5 ? Max_print = score_list.size() : Max_print = 5;
	for(int i=0 ;i<Max_print;i++)
	{ 
	text.TextPrint(posName.x,posName.y+100.0f+ 50.0f*i, const_cast<char*> (score_list[state+i].first.c_str()) , win); text.TextPrint(posScore.x,posScore.y+ 100.0f+50.0f*i,score_list[state+i].second, win);
	}
	return score_list.size() - 5;
}
void UI::TutorialMenu(RenderWindow& win)
{
	Vector2f S = {650.0f,150.0f};
	Backbar.setTexture(BackbarTex);
	Backbar.setPosition(635.0f, 90.0f);
	Backbar.setScale(3.25, 4);
	win.draw(Backbar);
	text.setColor(Color::White);
	text.setOrigin(0, 0);
	text.setSize(26);
	text.TextPrint( S.x,S.y - 50.0f,"Tutorials",win );
	text.setSize(16);
	text.TextPrint(S.x, S.y,          "W or UP      Turn Off Gravity", win);
	text.TextPrint(S.x, S.y + 50.0f,  "S or Down Turn On Gravity", win);
	text.TextPrint(S.x, S.y + 100.0f, "D or Right Increase Speed Level", win);
	text.TextPrint(S.x, S.y + 150.0f, "A or Left  Decrease Speed Level", win);
	text.TextPrint(S.x, S.y + 200.0f, "SpaceBar Shoot Bullet", win);
	text.TextPrint(S.x, S.y + 250.0f, "Enter          Choose Menu", win);
	text.TextPrint(S.x, S.y + 300.0f, "Esc               Pause", win);
}