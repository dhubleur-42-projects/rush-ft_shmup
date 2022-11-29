NAME		= 	ft_shmup

CPPC		= 	c++
CPPFLAGS	= 	-Wall -Wextra -Werror -g3
LDFLAGS		= 	-lncurses -g3

SRCDIR		= 	src/
OBJDIR		= 	obj/
INCLUDE		= 	include/

SRC			=	main.cpp					\
				$(addprefix menus/,			\
					StartMenu.cpp 			\
					EndMenu.cpp)			\
				$(addprefix background/,	\
					Background.cpp			\
					BackgroundDot.cpp)		\
				$(addprefix entity/,		\
					Entity.cpp				\
					Player.cpp				\
					Ennemy.cpp				\
					Rock.cpp				\
					Boss.cpp				\
					Alien.cpp)				\
				$(addprefix game/,			\
					Game.cpp)				\
				$(addprefix ray/,			\
					Ray.cpp)

OBJS		= $(SRC:%.cpp=$(OBJDIR)%.o)
DPNDS		= $(SRC:%.cpp=$(OBJDIR)%.d)

.PHONY: all
all: $(NAME)

.PHONY: clean
clean:
	rm -rf $(OBJDIR)

.PHONY: fclean
fclean: clean
	rm -f $(NAME)

.PHONY: re
re: fclean
	make all

.PHONY: test
test: all
	./$(NAME)

$(OBJDIR)%.o:	$(SRCDIR)%.cpp
	@mkdir -p $(dir $@)
	$(CPPC) $(CPPFLAGS) -MMD -MF $(@:.o=.d) -I $(INCLUDE) -o $@ -c $<

-include $(DPNDS)
$(NAME):	$(OBJS)
	$(CPPC) $(LDFLAGS) $(OBJS) -o $(NAME)
