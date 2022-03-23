#include <stdio.h>

int  getfrom(char  *str, int i)
{
  while (str[++i])
  {
	if (str[i] != '-')
	{
		return (0);
	}
    else if (str[i] == '-' && str[i + 1] == 'n')
    {
      i++;
      while (str[i] == 'n')
        i++;
      if (str[i] == ' ')
      {
        while (str[i] == ' ')
          i++;
        if (str[i] == '-' && str[i + 1] == 'n' && str[i - 1] == ' ')
          return (getfrom(str, i - 1));
        return (i);
      }
      else if (str[i - 1] == ' ')
        return (i - 2);
      else
        return (0);
    }
  }
  return (-1);
}

void  ft_echo(char *str)
{
  int i = getfrom(str, -1);
  printf("%s\n", str + i);
}

int main(void) {
	ft_echo("5-nnnnnn hello");
	ft_echo("-n 5-nnnnnn hello");
	ft_echo("-nns 5-nnnnnn hello");
	ft_echo("-g5-nnnnnn hello");
	ft_echo("-n 5-nnnnnn hello");
	ft_echo("-nns 5-nnnnnn hello");
	return 0;
}




