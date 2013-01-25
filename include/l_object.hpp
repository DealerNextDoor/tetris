#ifndef L_OBJECT_HPP_INCLUDED
#define L_OBJECT_HPP_INCLUDED

#include "object.hpp"

typedef struct s_object
{
  object           *obj;
  struct s_object  *next;
}              t_object;

class   l_object
{
public:
    l_object();
    ~l_object();
    void    add(t_objects *_objects[7]);
    void    actualise(int world[20][10]);
    object  *get();
    object  *get(int nb);
private:
    t_object    *_first;
};

#endif // L_OBJECT_HPP_INCLUDED
