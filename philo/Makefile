NAME 		=	philo
MAIN		=	exit utils parse_settings struct_init time_utils routine state
OS			=	$(shell uname)
ifeq ($(OS), Linux)
	MAIN	+= main_linux
else
	MAIN	+= main_osx
endif

SRC			=	$(addsuffix .c, $(addprefix srcs/, $(MAIN)))
HEADER		=	srcs/philosophers.h
CC			=	clang
CFLAGS		= 	-Werror -Wextra -Wall -pthread -g
LFLAGS		=	-Iinclude/
OBJ			=	$(SRC:.c=.o)

all:	$(NAME)

$(NAME): $(OBJ)
		@$(CC) $(CFLAGS) $(LFLAGS) -I $(HEADER) $(OBJ) -o $(NAME)

%.o: %.c $(HEADER)
		@$(CC) $(CFLAGS) -I $(HEADER) -o $@ -c $<
		@echo $@

clean:
		@rm -rf $(OBJ)
		@echo ":::::::::::::::::::::::::::::::::::::::::::::::"
		@echo "\033[0;34mphilosophers\033[0m      binaries \033[0m          \033[0;32m |deleted|\033[0m"

fclean:
		@rm -rf $(OBJ)
		@echo ":::::::::::::::::::::::::::::::::::::::::::::::"
		@echo "\033[0;34mphilosophers\033[0m      binaries \033[0m          \033[0;32m |deleted|\033[0m"
		@rm -rf $(NAME)
		@echo "\033[0;34mphilosophers\033[0m      philo.a \033[0m           \033[0;32m |deleted|\033[0m"

re:		fclean
		@echo ":::::::::::::::::::::::::::::::::::::::::::::::"
		@make

norme:
	@norminette $(SRC) $(HEADER)

.PHONY : all clean fclean re bonus go norme
