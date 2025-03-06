NAME = cub3d

MY_SOURCES = src/cub3d.c src/read.c src/flood_fill.c src/free.c \
			src/raycasting.c src/move.c src/draw.c src/render.c
MY_OBJECTS =  $(MY_SOURCES:.c=.o)

CC = gcc -Wall -Wextra -Werror -g3 #-fsanitize=address
MLXFLAGS = -lX11 -lXext -lm
$(NAME): $(MY_OBJECTS)
	@${MAKE} -C ./libft
	@${MAKE} -C ./ft_printf
	@${MAKE} -C ./get_next_line
	@${CC} ${CFLAGS} ${MY_OBJECTS} -L./mlx_linux -lmlx -lXext -lX11 -lm ./libft/libft.a ./ft_printf/libftprintf.a ./get_next_line/libftgetnextline.a -o $(NAME)


all: ${NAME}

%.o: %.c
	$(CC) -c $< -o $@

clean:
	@${MAKE} -C ./libft fclean
	@${MAKE} -C ./ft_printf fclean
	@${MAKE} -C ./get_next_line fclean
	@rm -f $(MY_OBJECTS) $(NAME)


fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
