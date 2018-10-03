#include "../headers/maze.h"

void addMusic(const char* musicfile)
{
    Mix_OpenAudio(22050, AUDIO_S16SYS, 2, 640);
    Mix_Music *music = Mix_LoadMUS(musicfile);
    Mix_PlayMusic(music, 3);
}
