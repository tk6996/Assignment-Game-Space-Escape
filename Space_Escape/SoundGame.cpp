#pragma once
#include "SFMLHeaderPack.h"
#include "SoundGame.h"
using namespace sf;

SoundGame::SoundGame(){}
SoundGame::SoundGame(const char* Name)
{
	_Soundbuffer.loadFromFile(Name);
	sound.setBuffer(_Soundbuffer);
}
void SoundGame::setLoop(bool T)
{
	sound.setLoop(T);
}
void SoundGame::play()
{
	sound.play();
}
void SoundGame::plause()
{
	sound.pause();
}
void SoundGame::stop()
{
	sound.stop();
}
void SoundGame::setPlayingOffset(Time timeOffset)
{
	sound.setPlayingOffset(timeOffset);
}
void SoundGame::filename(const char* Name)
{
	_Soundbuffer.loadFromFile(Name);
	sound.setBuffer(_Soundbuffer);
}
void SoundGame::setVolume(float Volume)
{
	sound.setVolume(Volume);
}
