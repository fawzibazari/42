/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexdump.c                                       :+:      :+:    :+:   */
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

void	offset_in_hex(int nbr)
{
	int		i;
	char	*hex_offset;
	char	*hex_base;

	i = 0;
	hex_base = "0123456789abcdef";
	hex_offset = malloc(sizeof(char) * 8);
        if (hex_offset == NULL)
		return;

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
	free(hex_offset);
	write(1, " ", 1);
}

char	*ascii_to_hex(unsigned char nbr)
{
        int             i;
        char    *hex_offset;
        char    *hex_base;
	int	nbr_count;

        i = 0;
	nbr_count = 0;
        hex_base = "0123456789abcdef";
        hex_offset = malloc(sizeof(char) * 3);
        if (hex_offset == NULL)
                return (NULL);

        while(nbr > 0)
        {
		nbr_count++;
                hex_offset[i] = hex_base[nbr % 16];
                nbr /= 16;
                i++;
        }
	if (nbr_count == 1)
		hex_offset[i++] = '0';
        reverse(hex_offset);
        hex_offset[i] = '\0';
	return (hex_offset);
}

void    write_hex(unsigned char *str, int rd, int **line)
{

        int     i;
	int	j;
	char	*hex_str;

        i = 0;
	j = **line;
        while (i < rd)
        {
		write(1, " ", 1);
		hex_str = ascii_to_hex(str[i]);
		write(1, hex_str, 2);
		if (j % 16 == 7)
		{
			write(1, " ", 1);
		}
		j++;
		i++;
		free(hex_str);
        }
}

void	display(unsigned char *str, int range)
{
	int	j;

	write(1, "  |", 3);
	j = 0;
	while (j < range)
	{
		// ASCII
		if (str[j] >= 32 && str[j] <= 126)
			write(1, &str[j], 1);
               	else
			write(1, ".", 1);
		j++;
	}
	write(1, "|\n", 2);
}


void	read_file(char *filename, int *line, unsigned char *buffer)
{
	int		j;
	int		k;
	int             rd;
        int             fd;
	unsigned char   temp[16];

        rd = 1;
        fd = open(filename, O_RDONLY);
        while (rd)
	{
		
                rd = read(fd, &temp, (16 - (*line % 16)));
		if (rd == 0 || rd == -1)
                        break ;
		if (*line % 16 == 0)
			offset_in_hex(*line);	
		
		j = 0;
		k = *line % 16;
		while (j < rd)
		{
			buffer[k] = temp[j];
			j++;
			k++;
		}
		*line += rd;
		if (*line % 16 == 0)
		{
			write_hex(buffer, 16, &line);
			display(buffer, 16);
		}
        }
        close(fd);
}

int     main(int argc, char **argv)
{
        int     i;
	int	line;
	unsigned char   buffer[16];

	i = 2;
	line = 0;
        if (argc >= 3 && argv[1][0] == '-' && argv[1][1] == 'C')
        {
                while (argv[i])
                {
			read_file(argv[i], &line, buffer);
			i++;
		}
		
		int *line2 = &line;
		if(line % 16 != 0)
		{
		write_hex(buffer, line %16, &line2);
		display(buffer, line % 16);
		}
		offset_in_hex(line); 
		
	}
	return(0);
}
