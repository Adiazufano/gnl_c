/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:56:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/30 14:22:24 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	size_t number_bytes;
	char	*buffer;
	static char	*remainder;
	char	*stack;
	char	*line;
	char *start_line;
	char	*result;
	char	*temp;

	buffer  = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	if (remainder != NULL)
		stack = ft_strdup(remainder);
	else
		stack = ft_strdup("");
	if (!stack)
	{
		free(buffer);
		return (NULL);
	}
	free(remainder);
	remainder = NULL;
	line = malloc(ft_strlen(stack) + 1);
	if (!line)
	{
		free(buffer);
		free(stack);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(buffer);
		free(stack);
		return (NULL);
	}
	while (ft_strchr(buffer, '\n') == NULL)
	{
		number_bytes = read(fd, buffer, BUFFER_SIZE);
		if (number_bytes == 0)
			break;
		if (number_bytes < 0)
		{
			free(buffer);
			free(stack);
			break;
		}
		buffer[number_bytes] = '\0';
		temp = stack;
		stack = ft_strjoin(stack, buffer);
		free(temp);
	}
	free(buffer);
	start_line = line;
	while (*stack != '\0' && *stack != '\n')
	{
		*line = *stack;
		line++;
		stack++;
	}
	if (*stack == '\n')
	{
		*line = *stack;
		line++;
		stack++;
	}
	remainder = ft_strdup(stack);
	*line = '\0';
	// result = ft_strjoin(remainder, start_line);
	return (start_line);
}

int	main(void)
{
	int fd = open("prueba.txt", O_RDONLY, 0700);
	printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd));
printf("%s",get_next_line(fd));
	close(fd);
	return (0);
}