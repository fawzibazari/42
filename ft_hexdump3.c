/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump3.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fbazari <fbazari@learner.42.tech>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/07/23 14:28:03 by fbazari           #+#    #+#             */
/*   Updated: 2026/07/23 15:43:15 by fbazari          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>


int     ft_strlen(char *str)
{
        int     i;

        i = 0;
        while (str[i] != '\0')
        {
                i++;
        }
        return (i);
}

void	read_file(char *filename, int *line)
{
        int             i;
	int		j;
        int             rd;
        int             fd;
        char    buffer[16];

        rd = 1;
        i = 0;
        fd = open(filename, O_RDONLY);
        while (rd)
        {
                rd = read(fd, &buffer, 16);
                if (rd == 0 || rd == -1)
                        break ;
		
		j = 0;
		while (j < rd)
		{
			if (buffer[j] >= 32 && buffer[j] <= 126)
				write(1, &buffer[j], 1);
                	else
                	{
				write(1, ".", 1);
			}
			j++;
			*line = *line + 1;
			if (*line % 16 == 0)
                        	write(1, "\n", 1);
		}
		//printf("%dteststs", *line);
		//*line += rd;
		//if (rd < 16)
		//	rd = rd + (16 - rd);
		//if (*line % 16 == 0)
		//	write(1, "\n", 1);
                i++;
        }
        close(fd);
}

int     main(int argc, char **argv)
{
        int     i;
	int	line;
        i = 2;
	line = 0;
        if (argc >= 3 && argv[1][0] == '-' && argv[1][1] == 'C')
        {
                while (argv[i])
                {
			read_file(argv[i], &line);
			//printf("line :%d\n", line);
		i++;
		}
	}
	return(0);
}
