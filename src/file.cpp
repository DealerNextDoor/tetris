#include "file.hpp"
#include <iostream>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

file::file()
{
}

file::~file()
{

}

int	space(char a, char *sep)
{
  int	i = 0;

  while (sep[i])
    {
      if (a == sep[i])
	return (1);
      i++;
    }
  return (0);
}

void		file::save(const char *path)
{
  int		fd, i = 0, line = 0;  
  struct stat	statbuf;
 
  _nb_line = 0;
  stat(path, &statbuf);
  _size = (long)statbuf.st_size; 
  _tab = new char[_size];
  fd = open(path, O_RDONLY);
  read(fd, _tab, _size);
  close(fd);
  while (i < _size)
    {
      if (_tab[i] == '\n')
	_nb_line++;
      i++;
    }
  _file = new std::string[_nb_line];
  i = 0;
  while (i < _size)
    {
      _file[line] += _tab[i];
      if (_tab[i] == '\n')
        line++;
      i++;
    }
}

void	file::show()
{
  int	line = 0;

  while (line < _nb_line)
    std::cout << _file[line++];
}

void	file::show(int start, int end)
{
  int	line = start;

  if (start > end)
    {
      std::cout << "start > end !" << std::endl;
      return ;
    }
  while (line < start)
    std::cout << _file[line++];
}

void	file::show_line(int nb)
{
  std::cout << _file[nb];
}

void	file::show_line(int start, int end)
{
  int	line = start;

  if (start > end)
    {
      std::cout<< "start > end !" << std::endl;
      return ;
    }
  while (line <= end)
    std::cout << _file[line++];
}

std::string	file::get()
{
  return (_tab);
}

std::string     file::get(int start, int end)
{
  int		i = 0;
  std::string	str;

  while (i < start)
    i++;
  while (i < end)
    str += _tab[i++];
  return (str);
}

std::string     file::get_line(int nb)
{
  return (_file[nb]);
}

std::string     *file::get_line(int start, int end)
{
  int		line = start;
  std::string	*str;

  str = new std::string[(end - start + 1)];
  while (line <= end)
    {
      str[line] = _file[line];
      line++;
    }
  return (str);
}

std::string	file::get_line_word(int line, int word)
{
  std::string	str;
  int		i = 0, w = 0;

  if (word < 0 || line >= _nb_line)
    return ("");
  while (w < word)
    {
      if (_file[line][i] == ' ')
	w++;
      if (_file[line][i] == '\0')
	{
	  w++;
	  i = 0;
	}
      else
	i++;
    }
  while (_file[line][i] != ' ' && _file[line][i] != '\0')
    {
      str += _file[line][i];
      i++;
    }
  return (str);
}

std::string     file::get_line_word(int line, int word, char *sep)
{
  std::string   str;
  int           i = 0, w = 1;

  if (word < 0 || line >= _nb_line)
    return ("");
  while (w < word)
    {
      if (space(_file[line][i], sep))
	w++;
      if (_file[line][i] == '\0')
        {
          w++;
          i = 0;
        }
      else
	i++;
    }
  while (!space(_file[line][i], sep) && _file[line][i] != '\0')
    str += _file[line][i++];
  return (str);
}


std::string	*file::get_line_word(int line, int start, int end)
{
  std::string	*str;
  int		w = 1, i = 0;

  str = new std::string[(end - start + 1)];
  while (w < start)
    {
      if (_file[line][i] == ' ')
        w++;
      if (_file[line][i] == '\0')
        {
          w++;
          i = 0;
        }
      else
	i++;
    }
  while (w <= end + 1)
    {
      if (_file[line][i] == ' ')
        w++;
      else
	str[w - start - 1] += _file[line][i];
      if (_file[line][i] == '\0')
        {
          w++;
          i = 0;
        }
      else
	i++;
    }
  return (str);
}

std::string     *file::get_line_word(int line, int start, int end, char *sep)
{
  std::string   *str;
  int           w = 1, i = 0;

  str = new std::string[(end - start + 1)];
  while (w < start)
    {
      if (space(_file[line][i], sep))
	w++;
      if (_file[line][i] == '\0')
        {
          w++;
          i = 0;
        }
      else
        i++;
    }
  w++;
  while (w <= end + 1)
    {
      if (space(_file[line][i], sep))
        w++;
      else
        str[w - start - 1] += _file[line][i];
      if (_file[line][i] == '\0')
        {
          w++;
          i = 0;
        }
      else
        i++;
    }
  return (str);
}

int	file::get_line_nb_word(int line)
{
  int	word = 0;
  int	i = 0;

  while (_file[line][i] != '\0')
    {
      if (_file[line][i] == ' ')
	word++;
      i++;
    }
  return (word);
}

int	file::get_line_nb_word(int line, char *sep)
{
  int	word = 1;
  int	i = 0;

  while (_file[line][i] != '\0')
    {
      if (space(_file[line][i], sep))
	word++;
      i++;
    }
  return (word);
}


int	file::get_nb_line()
{
  return (_nb_line);
}

void	file::del()
{

}
