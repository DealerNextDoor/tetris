#include <stdlib.h>
#include <time.h>
#include "object.hpp"

int random(int min, int max)
{
    max++;
    return (rand() % (max - min) + min);
}

void	object::clean(int world[20][10])
{
  for (int y = 0; y < SIZE; y++)
    for (int x = 0; x < SIZE; x++)
      if (_tab[y][x])
	world[_pos.y + y][_pos.x + x] = 0;
}

object::object(t_objects *_objects[7])
{
  _type = random(1, 7);
  _touch = false;
  _pos.x = 5;
  _pos.y = 0;
  _fall = true;

  for(int i = 0; i < SIZE; i++)
    for (int u = 0; u < SIZE; u++)
      _tab[i][u] = _objects[_type - 1]->_tab[i][u];
  /*  
      for(int i = 0; i < SIZE; i++)
      for (int u = 0; u < SIZE; u++)
      _tab[i][u] = 0;
  
  
  
      switch (_type)
      {
      case 1:
      _tab[2][0] = _type;  _tab[2][1] = _type;  _tab[2][2] = _type;  _tab[2][3] = _type;
      break;
      case 2:
      _tab[1][1] = _type;  _tab[1][2] = _type;
      _tab[2][1] = _type;  _tab[2][2] = _type;
      break;
      case 3:
      _tab[1][1] = _type;  _tab[1][2] = _type;  _tab[1][3] = _type;
      _tab[2][2] = _type;
      break;
      case 4:
      _tab[1][1] = _type;  _tab[1][2] = _type;  _tab[1][3] = _type;
      _tab[2][1] = _type;
      break;
      case 5:
      _tab[1][1] = _type;  _tab[1][2] = _type;  _tab[1][3] = _type;
      _tab[2][3] = _type;
      break;
      case 6:
      _tab[1][1] = _type;  _tab[1][2] = _type;
      _tab[2][2] = _type;  _tab[2][3] = _type;
      break;
      case 7:
      _tab[1][2] = _type;  _tab[1][3] = _type;
      _tab[2][1] = _type;  _tab[2][2] = _type;
      break;
      }
  */
}

object::~object()
{

}

void    object::fall(int world[20][10])
{
  clean(world);
  _pos.y += 1;
}

void    object::jump(int world[20][10])
{
  clean(world);
  _pos.y -= 1;
}

void    object::left(int world[20][10])
{
  clean(world);
  _pos.x -= 1;
}

void    object::right(int world[20][10])
{
  clean(world);
  _pos.x += 1;
}

bool    object::touch(int world[20][10])
{
  int   x = 0, y;

  while (x < SIZE)
    {
      y = 0;
      while (y < SIZE && get_value(x, y) == 0)
        y++;
      if (y < 4)
        {
          while (y < SIZE && get_value(x, y))
            y++;
          if (get_pos().y + y > 19)
	    {
	      _touch = true;
	      return (true);
	    }
          if (world[get_pos().y + y][get_pos().x + x])
	    {
	      _touch = true;
	      return (true);
	    }
	}
      x++;
    }
  _touch = false;
  return (false);
}

void	object::down(int world[20][10])
{
  clean(world);  
  while (!touch(world))
    _pos.y += 1;
  _pos.y -= 1;
}

void    object::flip(int world[20][10], t_objects *_objects[7])
{
  _objects[_type - 1] = _objects[_type - 1]->next;

  clean(world);
  
  for(int i = 0; i < SIZE; i++)
    for (int u = 0; u < SIZE; u++)
      _tab[i][u] = _objects[_type - 1]->_tab[i][u];
}

t_pos   object::get_pos()
{
    return (_pos);
}

int    object::get_value(int x, int y)
{
    return (_tab[y][x]);
}
