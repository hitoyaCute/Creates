CC       ?= gcc
TARGET    = Creates
SRC_DIR   = src
BUILD_DIR = build

SRC = $(SRC_DIR)/main.c
OBJ = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP = $(OBJ:.o=.d)

VENDOR     = vendor

RAYLIB_VER = 6.2
RAYLIB_DIR = $(VENDOR)/raylib
RAYLIB_SRC = $(RAYLIB_DIR)/src
RAYLIB_H   = $(RAYLIB_SRC)/raylib.h
RAYLIB_LIB = $(RAYLIB_SRC)/libraylib.a
# override with: make GRAPHICS=GRAPHICS_API_OPENGL_33
GRAPHICS  ?= GRAPHICS_API_OPENGL_21

CLAY_VER   = v0.14
CLAY_DIR   = $(VENDOR)/clay
CLAY_H     = $(CLAY_DIR)/clay.h

VENDOR_HDRS = $(RAYLIB_H) $(RAYGUI_H) $(CLAY_H)

# project headers via -I, third-party via -isystem (no warnings from them)
INCLUDES = -I$(SRC_DIR)           \
           -isystem $(RAYLIB_SRC) \
	   -isystem $(CLAY_DIR)   \
           -isystem $(VENDOR)

CFLAGS  ?= -O2 -g
CFLAGS  += -Wall -Wextra -std=c23 -MD -MP $(INCLUDES)
LDLIBS   = -lGL -lm -lpthread -ldl -lrt -lX11

.DELETE_ON_ERROR:
.PHONY: all run clean distclean

all: $(TARGET)

# ---- fetch dependencies ----
$(RAYLIB_H):
	git clone --depth 1 --branch $(RAYLIB_VER) https://github.com/raysan5/raylib.git $(RAYLIB_DIR)

$(CLAY_H):
	git clone --depth 1 --branch $(CLAY_VER) https://github.com/nicbarker/clay.git $(CLAY_DIR)

$(RAYLIB_LIB): $(RAYLIB_H)
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP GRAPHICS=$(GRAPHICS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(VENDOR_HDRS)
	@mkdir -p $(dir $@)
	bear -- $(CC) $(CFLAGS) -c $< -o $@

$(TARGET): $(OBJ) $(RAYLIB_LIB)
	$(CC) $(OBJ) $(RAYLIB_LIB) -o $@ $(LDLIBS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

distclean: clean
	rm -rf $(VENDOR) compile_commands.json

-include $(DEP)
