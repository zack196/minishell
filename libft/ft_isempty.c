
#include "libft.h"

int	ft_isempty(char *str)
{
	if (ft_isspace(str) == 1)
		return (1);
	return (0);
}
