#include "../includes/cub3d.h"

void	print_error(int error)
{

	if (error == ERROR_INVALID_ELEMENTS)
		ft_putstr_fd("Error\n Invalid elements", 1);
	if (error == LINE_NOT_CLOSED)
		ft_putstr_fd("Error\n Line not closed", 1);
	if (error == MAP_NOT_CLOSED)
		ft_putstr_fd("Error\n map not closed", 1);
	if (error == MAP_ERROR_WRONG_CHAR)
		ft_putstr_fd("Error\n Wrong char in the map", 1);
	if (error == ERROR_INVALID_FILE)
		ft_putstr_fd("Error\n Invalid file extention", 1);
	if (error == ERROR_FILE_NOT_OPENED)
		ft_putstr_fd("Error\n Fail opening file", 1);
}