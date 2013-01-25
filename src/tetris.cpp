#include "tetris.hpp"
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include "file.hpp"

int random(int min, int max);

void    clean(int _world[20][10])
{
  for(int i = 0; i < 20; i++)
    for (int u = 0; u < 10; u++)
      _world[i][u] = 0;
}

tetris::tetris()
{
  file	f;

  f.save("sound/music.path");
  _music_path = f.get_line(0);
  _music_path.erase(_music_path.size() - 1);
  f.save("sound/gameover.path");
  _gameover_path = f.get_line(0);
  _gameover_path.erase(_gameover_path.size() - 1);
  load_objects();
  srand(time(NULL));
  _game_over = false;
  _music.load(_music_path);
  _music.set_repeat(-1);
  _music.play();
  _event_ok = true;
  _score = 0;
  _level = 1;
  _touch = false;
  _fall = true;
  for(int i = 0; i < 5; i++)
    _case[i] = false;
  clean(_world);
  _pause = -1;
}

tetris::~tetris()
{

}

void	tetris::load_objects()
{
  file	file;
  int	y;
  std::string	line;
  std::string	path;
  std::string	     fuckcpp;
  t_objects *first;

  for (int i = 0; i < 7; i++)
    {
      std::ostringstream os;

      os << i + 1;
      path = "objects/" + os.str();
      file.save(path.c_str());
      first = _objects[i] = new t_objects;
      y = 0;
      for (int l = 0; l < file.get_nb_line(); l++)
	{
	  if (y >= 4)
	    {
	      _objects[i]->next = new t_objects;
	      _objects[i] = _objects[i]->next;
	      y = 0;
	      l += 1;
	    }
	  line = file.get_line(l);
	  for (int x = 0; x < 4; x++)
	    {
	      fuckcpp = line[x];
	      if (fuckcpp == ".")
		_objects[i]->_tab[y][x] = 0;
	      else
		_objects[i]->_tab[y][x] = i + 1;
	    }
	  y++;
	}
      _objects[i]->next = first;
      _objects[i] = first;
    }
}

void    tetris::event(sf::RenderWindow &window)
{
  sf::Event event;

  while (window.pollEvent(event))
    {
      if (event.type == sf::Event::Closed)
	window.close();
      else if (event.type == sf::Event::KeyPressed)
        {
	  if (event.key.code == sf::Keyboard::Escape)
	    window.close();
	  else if (event.key.code == sf::Keyboard::P)
	    {
	      _pause *= -1;
	      if (_pause == 1)
		{
		  _music.pause();
		}
	      else
		{
		  //_music.play();
		}
	    }
	  else if (event.key.code == sf::Keyboard::Up)
            {
	      _case[0] = true;
            }
	  else if (event.key.code == sf::Keyboard::Down)
            {
	      _case[1] = true;
            }
	  else if (event.key.code == sf::Keyboard::Left)
            {
	      _case[2] = true;
            }
	  else if (event.key.code == sf::Keyboard::Right)
            {
	      _case[3] = true;
            }
	  else if (event.key.code == sf::Keyboard::Space)
            {
	      _case[4] = true;
            }
        }
      else if (event.type == sf::Event::KeyReleased)
        {
	  if (event.key.code == sf::Keyboard::Up)
            {
	      _event_ok = true;
	      _case[0] = false;
            }
	  else if (event.key.code == sf::Keyboard::Down)
            {
	      _event_ok = true;
	      _case[1] = false;
            }
	  else if (event.key.code == sf::Keyboard::Left)
            {
	      _event_ok = true;
	      _case[2] = false;
            }
	  else if (event.key.code == sf::Keyboard::Right)
            {
	      _event_ok = true;
	      _case[3] = false;
            }
	  else if (event.key.code == sf::Keyboard::Space)
            {
	      _event_ok = true;
	      _case[4] = false;
            }
        }
    }
}

void    wait()
{
  usleep(250000);
}

void	tetris::color_mur()
{
  if (_level == 1)
    printf("\033[%sm", "31");
  else if (_level == 2)
    printf("\033[%sm", "33");
  else if (_level == 3)
    printf("\033[%sm", "34");
  else if (_level == 4)
    printf("\033[%sm", "35");
  else if (_level == 5)
    printf("\033[%sm", "36");
  else if (_level == 6)
    printf("\033[%sm", "37");
}

void	tetris::color_object(int u, int i)
{
  if (_world[i][u] == 1)
    printf("\033[%sm", "31");
  else if (_world[i][u] == 2)
    printf("\033[%sm", "32");
  else if (_world[i][u] == 3)
    printf("\033[%sm", "33");
  else if (_world[i][u] == 4)
    printf("\033[%sm", "34");
  else if (_world[i][u] == 5)
    printf("\033[%sm", "35");
  else if (_world[i][u] == 6)
    printf("\033[%sm", "36");
  else if (_world[i][u] == 7)
    printf("\033[%sm", "37");
}

void    tetris::refresh()
{
  printf("\033[H\033[2J");
  color_mur();
  std::cout << "############\n";
  for (int i = 0; i < 20; i++)
    {
      color_mur();
      std::cout << "#";
      for (int u = 0; u < 10; u++)
        {
	  if (_world[i][u])
	    {
	      color_object(u, i);
	      std::cout << "X";
	    }
	  else
	    std::cout << " ";
        }
      color_mur();
      std::cout << "#\n";
    }
  std::cout << "############\n\n";
  printf("\033[%sm", "39");
  std::cout << "Score : " << _score << "\n";
  std::cout << "Level : " << _level << "\n";
}

void	tetris::delete_line(int y)
{
  for (y = y; y > 0; y--)
    {
      for (int x = 0; x < 10; x++)
	_world[y][x] = _world[y - 1][x];
    }
  for (int x = 0; x < 10; x++)
    _world[y][x] = false;
  _score += 10 * _level;
}

void	tetris::test_line()
{
  for (int y = 0; y < 20; y++)
    {
      for (int x = 0; x < 10 && _world[y][x]; x++)
	;
      if (x == 10) 
	delete_line(y);
    }
}

bool    tetris::touch_down()
{
  int   x = 0, y;

  while (x < SIZE)
    {
      y = 0;
      while (y < SIZE && _l_object.get()->get_value(x, y) == 0)
	y++;
      if (y < SIZE)
	{
          while (y < SIZE && _l_object.get()->get_value(x, y))
            y++;
          if (_l_object.get()->get_pos().y + y > 19)
	    {
	      if (_touch)
		_fall = false;
	      _touch = true;
	      return (true);
	    }
          if (_world[_l_object.get()->get_pos().y + y][_l_object.get()->get_pos().x + x])
	    {        
	      if (_touch)
		_fall = false;
	      _touch = true;
	      return (true);
	    }
	}
      x++;
    }
  _touch = false;
  return (false);
}

bool    tetris::touch_right()
{
  int   x, y = 0;

  while (y < SIZE)
    {
      x = 0;
      while (y < SIZE && _l_object.get()->get_value(x, y) == 0)
	x++;
      if (x < SIZE)
	{
          while (y < SIZE && _l_object.get()->get_value(x, y))
            x++;
          if (_l_object.get()->get_pos().x + x > 9)
            return (true);
          if (_world[_l_object.get()->get_pos().y + y][_l_object.get()->get_pos().x + x])
            return (true);
	}
      y++;
    }
  return (false);
}

bool    tetris::touch_left()
{
  int   x, y = 0;

  while (y < SIZE)
    {
      x = SIZE - 1;
      while (y < SIZE && _l_object.get()->get_value(x, y) == 0)
	x--;
      if (x >= 0)
	{
          while (y < SIZE && _l_object.get()->get_value(x, y))
            x--;
          if (_l_object.get()->get_pos().x + x < 0)
            return (true);
          if (_world[_l_object.get()->get_pos().y + y][_l_object.get()->get_pos().x + x])
            return (true);
	}
      y++;
    }
  return (false);
}

bool    tetris::inside()
{
  int   x, y = 0;

  while (y < SIZE)
    {
      x = 0;
      while (y < SIZE && _l_object.get()->get_value(x, y) == 0)
	x++;
      if (x < SIZE)
	{
          while (y < SIZE && _l_object.get()->get_value(x, y))
            x++;
          if (_l_object.get()->get_pos().x + x > 10)
            return (true);
	  if (_world[_l_object.get()->get_pos().y + y][_l_object.get()->get_pos().x + x - 1])
	    return (true);
	}
      y++;
    }
  y = 0;
  while (y < SIZE)
    {
      x = SIZE;
      while (y < SIZE && _l_object.get()->get_value(x, y) == 0)
	x--;
      if (x > 0)
	{
          while (y < SIZE && _l_object.get()->get_value(x, y))
            x--;
          if (_l_object.get()->get_pos().x + x < -1)
            return (true);
	  if (_world[_l_object.get()->get_pos().y + y][_l_object.get()->get_pos().x + x])
	    return (true);
	}
      y++;
    }
  return (false);
}

void	tetris::game_over()
{
  if (_l_object.get()->get_pos().y == 0)
    {
      _music.stop();
      _music.load(_gameover_path);
      _music.play();
      _game_over = true;
      usleep(4500000);
    }
}

void    tetris::world(bool fall)
{
  if (_l_object.get() == NULL)
    _l_object.add(_objects);
  if (touch_down() == false && fall)
    _l_object.get()->fall(_world);
  _l_object.actualise(_world);
  if (_fall == false)
    {
      game_over();
      test_line();
      _l_object.add(_objects);
      _fall = true;
    }
}

void	tetris::action()
{
  if (_event_ok == false)
    return ;

  if (_case[0])
    {
      _l_object.get()->flip(_world, _objects);
      _event_ok = false;
      world(false);
      refresh();
    }
  else if (_case[1])
    {
      _l_object.get()->fall(_world);
      if (touch_down() == true)
	_l_object.get()->jump(_world);
      _event_ok = false;
      world(false);
      refresh();
    }
  else if (_case[2])
    {
      if (touch_left() == false)
	_l_object.get()->left(_world);
      _event_ok = false;
      world(false);
      refresh();
    }
  else if (_case[3])
    {
      if (touch_right() == false)
	_l_object.get()->right(_world);
      _event_ok = false;
      world(false);
      refresh();
    }
  else if (_case[4])
    {
      _l_object.get()->down(_world);
      _score += 1 * _level;
      _event_ok = false;
      _fall = false;
      world(true);
      refresh();
    }
}

void    tetris::play()
{
  sf::RenderWindow window(sf::VideoMode(42, 42), "SFML window");

  window.setFramerateLimit(60);
  window.setVerticalSyncEnabled(true);
  _clock.restart();
  _clock_level.restart();
  while (window.isOpen() && _game_over == false)
    {
      event(window);
      if (_pause == -1)
	{
	  action();
	  _time = _clock.getElapsedTime();
	  _time_level = _clock_level.getElapsedTime();
	  if (_time_level.asMilliseconds() >= 30000)
	    {
	      _clock_level.restart();
	      _level += 1;
	    }
	  if (_time.asMilliseconds() >= 500)
	    {
	      _clock.restart();
	      world(true);
	      refresh();
	    }
	  usleep(1000);
	}
    }
  window.close();
  _music.stop();
  exit(0);
}
