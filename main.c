
#include "includes/cub3d.h"
#include "libft/libft.h"

ft_count_chars()


int main (int argc, char **argv)
{
    int     fd;
    int     ret;
    char    buf[10];
    t_visu  *visu;
    char    *str;
    int     i;

    i = 0;
    visu = malloc(sizeof(t_visu));
    ft_bzero(visu, sizeof(t_visu));
    fd = open("maps/sujet.cub", O_RDONLY);
    //printf("fd = %d\n", fd);
    while ((ret = read(fd, buf, 1)) > 0) // tant que fichier pas fini d'être lu je compte les char et je rempli la chaine
     {
         visu->t_map.nb_char++;
     }
    str = (char*)malloc(sizeof(char)*(visu->t_map.nb_char + 1 ));
    close (fd);
    printf("fd = %d\n", fd);
    fd = open("maps/sujet.cub", O_RDONLY);
    while ((ret = read(fd, buf, 1)) > 0) // tant que fichier pas fini d'être lu je compte les char et je rempli la chaine
     {
         str[i] = buf[0];
         i++;
     }
    str[i] = '\0';
    printf("buf = '%s'\n", str);
    visu->t_map.map = ft_split(str, '\n');
    free (str);
    i = 0;
    while ( visu->t_map.map[i])
    {
        printf("%s", visu->t_map.map[i]);
        printf("\n");
        i++;
    }
}