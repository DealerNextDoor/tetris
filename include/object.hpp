#ifndef OBJECT_HPP_INCLUDED
#define OBJECT_HPP_INCLUDED

#include "t_objects.hpp"

typedef struct s_pos
{
    int x;
    int y;
}               t_pos;

class   object
{
public:
  object(t_objects *_objects[7]);
  ~object();
  void	clean(int world[20][10]);
   void	fall(int world[20][10]);
  void	jump(int world[20][10]);
  void	left(int world[20][10]);
  void	right(int world[20][10]);
  bool	touch(int world[20][10]);
  void	down(int world[20][10]);
  void	flip(int world[20][10], t_objects *_objects[7]);
  t_pos	get_pos();
  int	get_value(int x, int y);
private:
  int	_type;
  int	_color;
  bool	_touch;
  bool	_fall;
  int	_tab[SIZE][SIZE];
  t_pos _pos;
};

#endif // OBJECT_HPP_INCLUDED
