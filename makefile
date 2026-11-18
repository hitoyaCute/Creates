CC            = gcc
TARGET        = Creates
SRC_DIR       = src
BUILD_DIR     = build
LIB_DIR       = lib

SRC           = $(wildcard $(SRC_DIR)/*.c)
OBJ           = $(SRC:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEP           = $(OBJ:.o=.d)

RAYLIB_VER    = 6.2
RAYLIB_DIR    = vendor/raylib
RAYLIB_SRC    = $(RAYLIB_DIR)/src
RAYLIB_LIB    = $(RAYLIB_SRC)/libraylib.a
RAYGUI_H      = $(LIB_DIR)/raygui.h

INC_DIRS      = $(LIB_DIR) $(SRC_DIR)
SYS_INC_DIRS  = $(RAYLIB_SRC) $(LIB_DIR)
INCLUDES      = $(addprefix -I,$(INC_DIRS)) $(addprefix -isystem ,$(SYS_INC_DIRS))

CFLAGS        = -Wall -Wextra -std=c99 -O2 -MMD -MP $(INCLUDES)

COMPDB        = compile_commands.json

ifeq ($(OS),Windows_NT)
    TARGET   := $(TARGET).exe
    LDFLAGS   = -L$(RAYLIB_SRC) -lraylib -lopengl32 -lgdi32 -lwinmm
else
    LDFLAGS   = -L$(RAYLIB_SRC) -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
endif

all: $(TARGET)

# generate compile_commands
$(COMPDB): $(SRC) makefile
	@echo "[" > $@
	@first=1; for f in $(SRC); do \
	  if [ $$first -eq 0 ]; then echo "," >> $@; fi; first=0; \
	  printf '  {"directory": "%s", "command": "$(CC) $(CFLAGS) -c %s", "file": "%s"}' "$(CURDIR)" "$$f" "$$f" >> $@; \
	done
	@echo "" >> $@
	@echo "]" >> $@

compdb: $(COMPDB)

# download raylib
$(RAYLIB_SRC)/raylib.h:
	git clone --depth 1 --branch $(RAYLIB_VER) https://github.com/raysan5/raylib.git $(RAYLIB_DIR)

# download raygui
$(RAYGUI_H):
	mkdir -p $(LIB_DIR)
	curl -L -o $@ https://raw.githubusercontent.com/raysan5/raygui/master/src/raygui.h

# build raylib static
$(RAYLIB_LIB): $(RAYLIB_SRC)/raylib.h
	$(MAKE) -C $(RAYLIB_SRC) PLATFORM=PLATFORM_DESKTOP

# compile
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c | $(RAYLIB_SRC)/raylib.h $(RAYGUI_H)
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

# link
$(TARGET): $(OBJ) $(RAYLIB_LIB)
	$(CC) $(OBJ) -o $@ $(LDFLAGS)

run: $(TARGET)
	./$(TARGET)

clean:
	rm -rf $(BUILD_DIR) $(TARGET)

distclean: clean
	rm -rf vendor $(LIB_DIR)

-include $(DEP)

.PHONY: all run clean distclean compdb

