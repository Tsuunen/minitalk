CC := cc
NAME := minitalk
BUILD_DIR := .build
LIBFT = libft/libft.a
INCLUDES = -Ilibft/includes -Iincludes
CFLAGS = -Werror -Wextra -Wall -MD $(INCLUDES)
MODE ?= release

VPATH = srcs:srcs/server:srcs/client
SERVER_SRCS = main_server.c
CLIENT_SRCS = main_client.c

SERVER_OBJS = $(addprefix $(BUILD_DIR)/, $(SERVER_SRCS:.c=.o))
CLIENT_OBJS = $(addprefix $(BUILD_DIR)/, $(CLIENT_SRCS:.c=.o))
DEPS = $(SERVER_OBJS:.o=.d) $(CLIENT_OBJS:.o=.d)

ifeq ($(MODE), debug)
	CFLAGS += -g3
endif

all: server client

server: $(LIBFT) $(BUILD_DIR) $(SERVER_OBJS)
	$(CC) $(CFLAGS) $(SERVER_OBJS) -o server $(LIBFT)

client: $(LIBFT) $(BUILD_DIR) $(CLIENT_OBJS)
	$(CC) $(CFLAGS) $(CLIENT_OBJS) -o client $(LIBFT)

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(LIBFT):
	$(MAKE) -C libft

$(BUILD_DIR)/%.o: %.c Makefile | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(MAKE) -C libft clean
	rm -rf $(BUILD_DIR)

fclean: clean
	$(MAKE) -C libft fclean
	rm -f server client

re: fclean all

.PHONY: all clean fclean re libft

-include $(DEPS)
