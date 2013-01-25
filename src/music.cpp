#include <music.hpp>

music::music()
{

}

music::~music()
{

}

void	music::load(std::string path)
{
  FMOD_System_Create(&system);
  FMOD_System_Init(system, 1, FMOD_INIT_NORMAL, NULL);
  resultat = FMOD_System_CreateSound(system, path.c_str(), FMOD_SOFTWARE | FMOD_2D | FMOD_CREATESTREAM, 0, &musique);
  if (resultat != FMOD_OK)
    {
      std::cout << "Impossible de lire cette musique : " << path << std::endl;
    }
}


void	music::set_repeat(int nb)
{
  FMOD_Sound_SetLoopCount(musique, nb);
}

void	music::play()
{
  FMOD_System_PlaySound(system, FMOD_CHANNEL_FREE, musique, 0, NULL);
  FMOD_System_GetChannel(system, 0, &canal);
  FMOD_System_GetMasterChannelGroup(system, &canal_group);
}

void	music::pause()
{
}

void	music::stop()
{
  FMOD_System_Close(system);
  FMOD_System_Release(system);  
}

void	music::set_volum(const float volume)
{
  if (volume >= 0 && volume <= 1)
    {
      FMOD_Channel_SetPaused(canal, true);
      FMOD_ChannelGroup_SetVolume(canal_group, volume);
      FMOD_Channel_SetPaused(canal, false);
    }
}
