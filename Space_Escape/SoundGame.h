#ifndef SOUNDGAME_H
#define SOUNDGAME_H
using namespace sf;
class SoundGame
{
public:
	SoundGame();
	SoundGame(const char* Name);
	void filename(const char* Name);
	void setLoop(bool);
	void play();
	void plause();
	void stop();
	void setPlayingOffset(Time timeOffset);
	void setVolume(float Volume);
private:
	SoundBuffer _Soundbuffer;
	Sound sound;
};
#endif
