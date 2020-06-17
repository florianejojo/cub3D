#include "../includes/cub3d.h"

void	print_error(int error)
{

	if (error == SUCCESS) // à enlever à la fin
        ft_putstr_fd("SUCCESS\n", 1);
  if (error == ERROR_INVALID_ELEMENTS)
		ft_putstr_fd("Error\n Invalid elements\n", 1);
	if (error == LINE_NOT_CLOSED)
		ft_putstr_fd("Error\n Line not closed\n", 1);
	if (error == MAP_NOT_CLOSED)
		ft_putstr_fd("Error\n map not closed\n", 1);
	if (error == MAP_ERROR_WRONG_CHAR)
		ft_putstr_fd("Error\n Wrong char in the map\n", 1);
	if (error == ERROR_INVALID_FILE)
		ft_putstr_fd("Error\n Invalid file extention\n", 1);
	if (error == ERROR_FILE_NOT_OPENED)
		ft_putstr_fd("Error\n Fail opening file\n", 1);
	if (error == NO_PLAYER_POS)
		ft_putstr_fd("Error\n No player position detected\n", 1);
	if (error == TO_MANY_PLAYER_POS)
		ft_putstr_fd("Error\n Two or more player positions detected\n", 1);
}