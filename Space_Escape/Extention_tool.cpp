#include "SFMLHeaderPack.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
using namespace sf;
int random(int min, int max)
{
	return rand() % (max - min) + min;
}
float random(float min, float max)
{
	return min + (float)rand() / (float)(RAND_MAX/(max - min));
}
int randomexcept(int min, int max, vector<int> except)
{
	int randnum;
	randnum=rand() % (max - min) + min;
	for (unsigned int i = 0; i < except.size(); i++)
	{
		if (randnum == except[i])
		{
			randnum=randomexcept(min, max, except); break;
		}
	}
	return randnum;
}
void setMiddlepositionX(Sprite& Object, RenderWindow& win)
{
	Object.setPosition((float)(960.0f-Object.getGlobalBounds().width) / 2, (float)Object.getPosition().y);
}
void showFloatRect(FloatRect Object)
{
	cout << " Left = " << Object.left;
	cout << " Top = " << Object.top;
	cout << " Width = " << Object.width;
	cout << " Height = " << Object.height << endl;
}
void Recordscore(const char* Name, int Score)
{
	vector<pair<string, int>> scoreboard;
	unsigned int i;
	string Namefile = "Score List.txt";
	ifstream fin(Namefile);
	if (fin.is_open())
	{
		while (!fin.eof())
		{
			string Player;
			int score;
			fin >> Player >> score;
			scoreboard.push_back({ Player,score });
		}
		scoreboard.pop_back();
		for (i = 0; i < scoreboard.size(); i++)
		{
			if (Score >= scoreboard[i].second) break;
		}
		scoreboard.insert(scoreboard.begin() + i, { Name,Score });  
		fin.close();
	}
	else scoreboard.push_back({ Name,Score });
	fstream fnew(Namefile, ios::out | ios::trunc);
	for (auto iter = scoreboard.begin(); iter != scoreboard.end(); iter++)
	{
		fnew << (*iter).first << " " << (*iter).second << endl;
	}
	fnew << "end";
	fnew.close();
}
vector<pair<string, int>> ScoreboardBuffer()
{
	vector<pair<string, int>> scoreboard;
	string Namefile = "Score List.txt";
	ifstream fin(Namefile);
	if (fin.is_open())
	{ 
		while (!fin.eof())
		{
			string Player;
			int score;
			fin >> Player >> score;
			scoreboard.push_back({ Player,score });
		}
		scoreboard.pop_back();
		fin.close();
	}
	return scoreboard;
}