#include <fmodex/fmod.h>
#include <stdlib.h>
#include <iostream>

class	music
{
public:

  music();
  ~music();
  void	load(std::string path);
  void	set_repeat(int nb);
  void	play();
  void	pause();
  void	stop();
  void	set_volum(const float volume);
private:

  std::string	_path;
  FMOD_SYSTEM *system;
  FMOD_SOUND *musique;
  FMOD_CHANNEL *canal;
  FMOD_CHANNELGROUP *canal_group;
  FMOD_RESULT resultat;
};
