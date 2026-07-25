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


int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		i++;
	}
	return (i);
}

void     reverse(char *converted)
{
        int     i;
        int     temp;
        int     size;

        size = ft_strlen(converted);
        i = 0;
        while (i < size / 2)
        {
                temp = converted[i];
                converted[i] = converted[size - 1 - i];
                converted[size - 1 - i] = temp;
                i++;
        }
}

char	*offset_in_hex(int nbr)
{
	int		i;
	char	*hex_offset;
	char	*hex_base;

	i = 0;
	hex_base = "0123456789abcdef";
	hex_offset = malloc(sizeof(char) * 8);
        if (hex_offset == NULL)
                return (NULL);

	while(i <= 7)
	{
		if (nbr > 0)
		{
			hex_offset[i] = hex_base[nbr % 16];
			nbr /= 16;
		}
		else
			hex_offset[i] = '0';
		i++;
	}
	reverse(hex_offset);
	hex_offset[i] = '\0';
	
	i = 0;
	while (hex_offset[i] != '\0')
	{
		write(1, &hex_offset[i], 1);
		i++;
	}
	write(1, "  ", 2);
	return (hex_offset);
}

void	read_file(char *filename, int *line)
{
	int		j;
        int             rd;
        int             fd;
        char    buffer[16];

        rd = 1;
        fd = open(filename, O_RDONLY);
        while (rd)
        {
                rd = read(fd, &buffer, 16);
                if (rd == 0 || rd == -1)
                        break ;

		j = 0;
		while (j < rd)
		{
			//Hexa counter
			
			//Hexa representation

			// ASCII
			if (*line % 16 == 0)
			{
				offset_in_hex(*line);
				write(1, "|", 1);
			}
			if (buffer[j] >= 32 && buffer[j] <= 126)
				write(1, &buffer[j], 1);
                	else
                	{
				write(1, ".", 1);
			}
			j++;
			*line = *line + 1;
			if (*line % 16 == 0)
                        	write(1, "|\n", 2);
		}
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
			//printf("%s\n", offset_in_hex(line));
			read_file(argv[i], &line);
			//printf("line :%d\n", line);
		i++;
		}
		write(1, "\n", 1);
		offset_in_hex(line);
	}
	return(0);
}
