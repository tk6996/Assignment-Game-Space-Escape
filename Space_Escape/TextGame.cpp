#include "SFMLHeaderPack.h"
#include <string>
#include "TextGame.h"
using namespace sf;
using namespace std;
TextGame::TextGame(){}
TextGame::TextGame(const char* Name)
{
	font.loadFromFile(Name);
	Message.setFont(font);
}
void TextGame::setFont(const char* Name)
{
	font.loadFromFile(Name);
	Message.setFont(font);
}
Vector2f TextGame::getLastPosition()
{
	return Vector2f(Message.getPosition().x + Message.getGlobalBounds().width + 1, Message.getPosition().y);
}
void TextGame::TextPrint(const char* text,RenderWindow& win)
{
	Message.setPosition(Message.getPosition().x + Message.getGlobalBounds().width+1, Message.getPosition().y);
	Message.setString(text);
	win.draw(Message);
}
void TextGame::TextPrint(const Vector2f& position, const char* text, RenderWindow& win)
{
	Message.setPosition(position);
	Message.setString(text);
	win.draw(Message);
}
void TextGame::TextPrint(float x, float y, const char* text, RenderWindow& win)
{
	Message.setPosition(x,y);
	Message.setString(text);
	win.draw(Message);
}
void TextGame::TextPrint(int number, RenderWindow& win)
{
	Message.setPosition(Message.getPosition().x + Message.getGlobalBounds().width+1, Message.getPosition().y);
	Message.setString(to_string(number));
	win.draw(Message);
}
void TextGame::TextPrint(float x, float y,int number, RenderWindow& win)
{
	Message.setPosition(x, y);
	Message.setString(to_string(number));
	win.draw(Message);
}
void TextGame::TextPrint(const Vector2f& position,int number, RenderWindow& win)
{
	Message.setPosition(position);
	Message.setString(to_string(number));
	win.draw(Message);
}
void TextGame::setSize(int size)
{
	Message.setCharacterSize(size);
}
void TextGame::setColor(const Color& color)
{
	Message.setFillColor(color);
}
void TextGame::setPostion(const Vector2f& position)
{
	Message.setPosition(position);
}
void TextGame::setPostion(float x,float y)
{
	Message.setPosition(x,y);
}
void TextGame::setSytle(uint32_t style)
{
	Message.setStyle(style);
}
FloatRect TextGame::getSizeMessage()
{
	return Message.getGlobalBounds();
}
void TextGame::setMiddleTextPrint(float y, const char* text, RenderWindow& win)
{
	Message.setString(text);
	Message.setOrigin(Message.getGlobalBounds().width / 2, 0);
	Message.setPosition(960.0f / 2, y);
	win.draw(Message);
}
void TextGame::setMiddleTextPrint(float y,int number, RenderWindow& win)
{
	Message.setString(to_string(number));
	Message.setOrigin(Message.getGlobalBounds().width / 2, 0);
	Message.setPosition(960.0f / 2, y);
	win.draw(Message);
}
void TextGame::setOrigin(float x, float y)
{
	Message.setOrigin(x, y);
}