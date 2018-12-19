BUILD_DIR = Build

CFLAGS = `sdl-config --cflags`
LIBS = `sdl-config --libs` -lSDL_image

WARNINGS = -Wall
DEBUG = -ggdb -fno-omit-frame-pointer
OPTIMIZE = -O2

SOURCES = $(wildcard Source/*.c)
SOURCES += $(wildcard Source/Blocks/*.c)
SOURCES += $(wildcard Source/Objects/*.c)
SOURCES += $(wildcard Source/Objects/Behaviors/*.c)
SOURCES += $(wildcard Source/States/*.c)
_OBJECTS = $(SOURCES:.c=.o)
OBJECTS = $(patsubst %,$(BUILD_DIR)/%,$(_OBJECTS))
PROGRAM = $(BUILD_DIR)/MineAndBuild

all: create_build_dir $(OBJECTS) $(PROGRAM)

create_build_dir:
	mkdir -p $(BUILD_DIR)/Source/Blocks
	mkdir -p $(BUILD_DIR)/Source/Objects
	mkdir -p $(BUILD_DIR)/Source/Objects/Behaviors
	mkdir -p $(BUILD_DIR)/Source/States

$(PROGRAM):
	$(CC) $(OBJECTS) -o $(PROGRAM) $(LIBS)

$(BUILD_DIR)/%.o: %.c
	$(CC) -o $@ $(WARNINGS) $(DEBUG) $(OPTIMIZE) $(FLAGS) -c $<

clean:
	rm -rf $(BUILD_DIR)

# Builder will call this to install the application before running.
install:
	echo "Installing is not supported"

# Builder uses this target to run your application.
run:
	./$(PROGRAM)

