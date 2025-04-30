/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aldiaz-u <aldiaz-u@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 11:56:13 by aldiaz-u          #+#    #+#             */
/*   Updated: 2025/04/30 18:48:48 by aldiaz-u         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*free_and_return(char *to_free1, char *to_free2)
{
	if (to_free1)
		free(to_free1);
	if (to_free2)
		free(to_free2);
	return (NULL);
}

char	*read_line(int fd, char *stack)
{
	char	*buffer;
	char	*temp;
	size_t	number_bytes;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free_and_return(stack, NULL));
	while (!ft_strchr(stack, '\n'))
	{
		number_bytes = read(fd, buffer, BUFFER_SIZE);
		if (number_bytes == 0)
			break ;
		if (number_bytes < 0)
			return (free_and_return(buffer, stack));
		buffer[number_bytes] = '\0';
		temp = stack;
		stack = ft_strjoin(stack, buffer);
		free(temp);
		if (!stack)
			return (free_and_return(buffer, NULL));
	}
	free(buffer);
	return (stack);
}

static char	*extract_line(char *stack, char **remainder)
{
	char	*line;
	char	*start_line;
	char	*start_stack;

	if (*stack == '\0')
		return (free_and_return(stack, NULL));
	line = malloc(ft_strlen(stack) + 1);
	if (!line)
		return (free_and_return(stack, NULL));
	start_line = line;
	start_stack = stack;
	while (*stack != '\0' && *stack != '\n')
		*line++ = *stack++;
	if (*stack == '\n')
		*line++ = *stack++;
	*line = '\0';
	*remainder = ft_strdup(stack);
	free(start_stack);
	if (!*remainder && *stack)
		return (free_and_return(start_line, NULL));
	return (start_line);
}

char	*get_next_line(int fd)
{
	static char	*remainder;
	char		*stack;
	char		*line;

	if (fd == -1)
	{
		free(remainder);
		return (NULL);
	}
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (remainder)
		stack = ft_strdup(remainder);
	else
		stack = ft_strdup("");
	free(remainder);
	remainder = NULL;
	if (!stack)
		return (NULL);
	stack = read_line(fd, stack);
	if (!stack)
		return (NULL);
	line = extract_line(stack, &remainder);
	return (line);
}
int	main(void)
{
	int fd = open("prueba.txt", O_RDONLY);
	if (fd < 0)
	{
		perror("Error al abrir el archivo");
		return (1);
	}

	char *line;
	int count = 0;

	// 🔁 Leer solo 3 líneas
	while (count < 3 && (line = get_next_line(fd)))
	{
		printf("Línea %d: %s", count + 1, line);
		free(line);
		count++;
	}

	get_next_line(-1);
	close(fd);
	return (0);
}
