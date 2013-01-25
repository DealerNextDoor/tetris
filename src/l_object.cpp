#include <stdlib.h>
#include <iostream>
#include "l_object.hpp"

l_object::l_object()
{
  _first = NULL;
}

l_object::~l_object()
{

}

void    l_object::add(t_objects *_objects[7])
{
  t_object    *nouveau;

  nouveau = new t_object;
  nouveau->obj = new object(_objects);
  nouveau->next = _first;
  _first = nouveau;
}

void    l_object::actualise(int world[20][10])
{
  t_object    *tmp = _first;

  for (int i = 0; i < SIZE; i++)
    {
      for (int u = 0; u < SIZE; u++)
	{
	  if (tmp->obj->get_pos().y + i >= 0 && tmp->obj->get_pos().x + u >= 0)
	    {
	      if (tmp->obj->get_value(u, i))
		world[tmp->obj->get_pos().y + i][tmp->obj->get_pos().x + u] = tmp->obj->get_value(u, i);
	    }
	}
    }
}

object  *l_object::get()
{
  if (_first == NULL)
    return (NULL);
  return (_first->obj);
}

object	*l_object::get(int nb)
{
  t_object	*ret = _first;

  for(int i = 0; i < nb; i++)
    {
      if (ret->next != NULL)
	ret = ret->next;
    }
  return (ret->obj);
}
