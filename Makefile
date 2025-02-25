CC = g++
CFLAGS = -g -Wall -Wextra -std=c++17 $(addprefix -I, $(INCLUDE_DIRS))

SRC_DIRS = src src/commands
INCLUDE_DIRS = include include/commands
BUILD_DIR = build

SRCS = $(wildcard $(addsuffix /*.cpp, $(SRC_DIRS)))
OBJS = $(SRCS:src/%.cpp=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all clean run

all: client

client: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

$(BUILD_DIR)/%.o: src/%.cpp
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(BUILD_DIR) client

run: client
	./client

-include $(DEPS)
