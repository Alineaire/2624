#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <map>
#include <string>

#include <SDL.h>
#include <SDL2/SDL_mixer.h>

using namespace std;

class SoundManager
{
    public:
        SoundManager();
        virtual ~SoundManager();
        static SoundManager* Instance()
        {
            if (SoundManager::m_instance == nullptr)
            {
                SoundManager::m_instance = new SoundManager();
            }
            return SoundManager::m_instance;
        }

        void init();
        void loadMusic(string _path);
        void loadSFX(string _path);
        void playMusic(string _path = "", float _fade = -1);
        void playSFX(string _path);

    protected:

    private:
        static SoundManager* m_instance;

        float fadeMusic;
        string m_nextMusic;
        Mix_Music* m_music;
        map<string, Mix_Music*> m_musics;

        map<string, Mix_Chunk*> m_sfx;

        static void musicFinished();
};

#endif // SOUNDMANAGER_H
