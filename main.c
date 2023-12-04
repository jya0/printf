#include "libftprintf.h"
#include <stdio.h>

int	ft_printf(const char *, ...);


int	main()
 {
	// printf("|%d|\n", ft_printf("test %+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++0000000------   0- 10.10d", 42));
	printf("|%d|\n", printf("%d", 4200000));
 } 