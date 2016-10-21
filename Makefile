# ==============================================================================
# 			Build tool
# ==============================================================================

CC	= clang
RM	= rm -f
AR	= ar

# ==============================================================================
#			Sources
# ==============================================================================

NAME	= beercrypto

STATIC	= lib$(NAME).a
DYNAMIC	= lib$(NAME).so

SRCS	= arcfour.c
OBJS	= $(addprefix src/, $(SRCS:.c=.o))

# ==============================================================================
#			Build flags
# ==============================================================================

CFLAGS	+= -fPIC -Wall -Werror 
LDFLAGS	+= -shared

ARFLAGS	= rcs

# ==============================================================================
#			Rules
# ==============================================================================

all: $(STATIC) $(DYNAMIC)

$(STATIC): $(OBJS)
	$(AR) $(ARFLAGS) $@ $^

$(DYNAMIC): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(STATIC) $(DYNAMIC)

re: fclean all

.PHONY: all clean fclean
