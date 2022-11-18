/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsodre-p <tsodre-p@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 11:54:45 by tsodre-p          #+#    #+#             */
/*   Updated: 2022/11/17 10:56:22 by tsodre-p         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

/*gives file the calloc size of the variable temp, that was used to
allocate the memory, according to the buffer size and then frees the memory*/
static char	*ft_join(char *file, char *temp)
{
	char	*final;

	final = ft_strjoin(file, temp);
	free(file);
	return (final);
}

//reads the file, returns the file with the allocated memory
static char	*create_file(int fd, char *file)
{
	char	*temp;
	int		nchar_read;

	if (ft_strchr(file, '\n'))
		return (file);
	temp = ft_calloc((BUFFER_SIZE + 1), sizeof(char));
	nchar_read = 1;
	while (nchar_read > 0)
	{
		nchar_read = read(fd, temp, BUFFER_SIZE);
		if (nchar_read == -1)
		{
			free(temp);
			return (NULL);
		}
		temp[nchar_read] = 0;
		file = ft_join(file, temp);
		if (ft_strchr(temp, '\n'))
			break ;
	}
	free(temp);
	return (file);
}

//returning the first line
static char	*first_line(char *file)
{
	char	*first_line;
	int		i;

	i = 0;
	if (file[i] == 0)
	{
		return (NULL);
	}
	while (file[i] && file[i] != '\n')
		i++;
	first_line = ft_calloc(i + 2, sizeof(char));
	i = 0;
	while (file[i] && file[i] != '\n')
	{
		first_line[i] = file[i];
		i++;
	}
	if (file[i] == '\n')
		first_line[i] = '\n';
	return (first_line);
}

//remove first line, returning only the next line.
static char	*next_line(char *file)
{
	char	*temp;
	int		i;
	int		j;

	i = 0;
	while (file[i] && file[i] != '\n')
		i++;
	if (!file[i])
	{
		free(file);
		return (NULL);
	}
	temp = ft_calloc((ft_strlen(file) - i + 1), sizeof(char));
	i++;
	j = 0;
	while (file[i])
		temp[j++] = file[i++];
	free(file);
	return (temp);
}

/*checks if values are null, then calls make to read
the file and then gets the next line*/
char	*get_next_line(int fd)
{
	static char	*file[10000];
	char		*line;

	if (fd < 0 || fd > 10000 || BUFFER_SIZE <= 0)
		return (NULL);
	if (file[fd] == 0)
		file[fd] = ft_calloc(1, 1);
	file[fd] = create_file(fd, file[fd]);
	if (file[fd] == 0)
	{
		return (NULL);
	}
	line = first_line(file[fd]);
	file[fd] = next_line(file[fd]);
	return (line);
}

/*int	main(void)
{
	char	*line;
	int		i;
	int		fd;
	int		fd1;
	fd = open("tests/test1.txt", O_RDONLY);
	fd1 = open("tests/test2.txt", O_RDONLY);
	i = 1;
	if (fd == -1)
		printf("No file found");
	printf("fd = %d\n", fd);
	while (i < 7)
	{
		line = get_next_line(fd);
		printf("line fd[%02d]: %s\n", i, line);
		free(line);
		line = get_next_line(fd1);
		printf("line fd1[%02d]: %s\n", i, line);
		free(line);
		i++;
	}
	close(fd);
	close(fd1);
}*/
