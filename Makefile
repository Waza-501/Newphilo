NAME :=					philo
CC := 					gcc
CFLAGS :=				-Wall -Werror -Wextra

SOURCES	:=		cleanup.c\
				eat_sleep_think.c\
				grim_reaper.c\
				initialize.c\
				input_check.c\
				printing.c\
				symposium.c\
				threads.c\
				time.c\
				utils.c\
				main.c\

INCLUDE_DIR :=	./includes
HEADERS :=		-I ./includes
SOURCE_DIR :=	./sources
OBJECT_DIR	:=	./objects
OBJECTS :=		$(addprefix $(OBJECT_DIR)/, $(SOURCES:.c=.o))

all:	$(NAME)

$(NAME):		$(OBJECTS) 
					$(CC) $(CFLAGS) -o $@ $^ $(HEADERS)


$(OBJECT_DIR)/%.o:	$(SOURCE_DIR)/%.c
						mkdir -p $(dir $@)
						$(CC) $(CFLAGS) $(HEADERS) -c -o $@ $< -O3

clean:
		rm -f $(OBJECTS)

fclean:	clean
		rm -f $(NAME)
		if [ -d "$(OBJECT_DIR)" ]; then rm -drf $(OBJECT_DIR); fi

re: fclean all

.PHONY: all clean fclean re libraries