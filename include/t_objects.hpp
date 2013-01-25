#ifndef __T_OJECTS_HPP__
#define __T_OJECTS_HPP__

#define	SIZE	4

typedef struct s_objects
{
  int                   _tab[SIZE][SIZE];
  struct s_objects      *next;
}                       t_objects;

#endif	/*__T_OBJECTS_HPP__*/
