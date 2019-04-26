#include "SoundManager.h"
#include "window.h"

#include <iostream>

SoundManager::SoundManager()
{
    m_music = nullptr;
}

SoundManager::~SoundManager()
{
    for (std::map<string,Mix_Music*>::iterator it = m_musics.begin(); it != m_musics.end(); ++it)
    {
        Mix_FreeMusic(it->second);
    }
    for (std::map<string,Mix_Chunk*>::iterator it = m_sfx.begin(); it != m_sfx.end(); ++it)
    {
        Mix_FreeChunk(it->second);
    }
	Mix_CloseAudio();
}

void SoundManager::init()
{
	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 4096) == -1)
		throw InitError();

    Mix_HookMusicFinished(SoundManager::musicFinished);
}

void SoundManager::loadMusic(string _path)
{
    Mix_Music* music = m_musics[_path];
    if (music == nullptr)
        m_musics[_path] = Mix_LoadMUS(_path.c_str());
}
void SoundManager::loadSFX(string _path)
{
    Mix_Chunk* sfx = m_sfx[_path];
    if (sfx == nullptr)
        m_sfx[_path] = Mix_LoadWAV(_path.c_str());
}

void SoundManager::playMusic(string _path, float _fade)
{
    string path = (_path != "" ? _path : m_nextMusic);
    fadeMusic = (_fade != -1 ? _fade/2.0f : fadeMusic);
    Mix_Music* music = m_musics[path];

    if (Mix_PlayingMusic())
    {
        if (m_music != music && Mix_FadeOutMusic(fadeMusic))
            m_nextMusic = path;
    }
    else
    {
        m_music = music;
        if (Mix_FadeInMusic(m_music, -1, fadeMusic) == -1)
            cerr << "Mix_FadeInMusic: " << Mix_GetError() << endl;
    }
}

void SoundManager::musicFinished()
{
    SoundManager::Instance()->playMusic();
}

void SoundManager::playSFX(string _path)
{
    Mix_Chunk* sfx = m_sfx[_path];
	if (Mix_PlayChannel(-1, sfx, 0) == -1)
        cerr << "Mix_PlayChannel: " << Mix_GetError() << endl;
}
