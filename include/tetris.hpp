#ifndef TETRIS_HPP_INCLUDED
#define TETRIS_HPP_INCLUDED

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "music.hpp"
#include "l_object.hpp"
#include "t_objects.hpp"

class       tetris
{
public:
  tetris();
  ~tetris();
  void	  load_objects();
  void    play();
  void    world(bool);
  void    refresh();
  void	  delete_line(int y);
  void	  test_line();
  bool	  touch_down();
  bool	  touch_left();
  bool	  touch_right();
  void	  color_mur();
  void	  color_object(int x, int y);
  void	  game_over();
  bool	  inside();
  void    event(sf::RenderWindow &window);
  void	  action();
private:
  
  bool		      _game_over;
  music		      _music;
  int		      _pause;
  int                 _level;
  int		      _score;
  bool		      _fall;
  bool		      _touch;
  bool                _event_ok;
  bool                _case[5];
  int                 _world[20][10];
  std::string	      _music_path;
  std::string	      _gameover_path;
  t_objects	      *_objects[7];
  l_object            _l_object;
  sf::Clock	      _clock;
  sf::Clock	      _clock_level;
  sf::Time	      _time;
  sf::Time	      _time_level;
};

#endif // TETRIS_HPP_INCLUDED
