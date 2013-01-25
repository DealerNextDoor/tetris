#ifndef	__FILE_HPP__
#define	__FILE_HPP__

#include <string>

class	file
{
public:

  file();
  ~file();

  void		save(const char *path);

  void		show();
  void		show(int start, int end);
  void		show_line(int nb);
  void		show_line(int start, int end);

  std::string	get();
  std::string	get(int start, int end);
  std::string	get_line(int nb);
  std::string	*get_line(int start, int end);

  std::string	get_line_word(int line, int word);
  std::string	get_line_word(int line, int word, char *sep);
  std::string	*get_line_word(int line, int start, int end);
  std::string	*get_line_word(int line, int start, int end, char *sep);

  int		get_line_nb_word(int line);
  int		get_line_nb_word(int line, char *sep);

  int		get_nb_line();

  void		del();

private:

  int		_size;
  int		_nb_line;
  char		*_tab;
  std::string	*_file;
  char		tab[256];
};

#endif
