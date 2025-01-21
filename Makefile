GCC = gcc
GDB = gdb
RM = rm -rf
MKDIR = mkdir -p

LIBRARIES := -lm
INCLUDE_PATH := 
FLAGS :=

SOURCE = main.c
OUTPUT = program
TEST_OUTPUT = bin

LIB_PATH = lib/
TEST_PATH = test/
RESULT_PATH = build/results/

UNITY_PATH = $(LIB_PATH)unity/
RAYLIB_PATH = $(LIB_PATH)raylib/

LIBRARIES := -L$(RAYLIB_PATH) -lraylib $(LIBRARIES)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(RAYLIB_PATH)

SRC_DIRS := src src/utils src/scenes
VPATH := $(SRC_DIRS)

CFILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)/*.c))

$(OUTPUT): $(CFILES)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)

run: $(OUTPUT)
	./$(RESULT_PATH)$(OUTPUT)

testing: $(UNITY_PATH)
	$(eval LIBRARIES := $(LIBRARIES) -L$(UNITY_PATH))
	$(eval INCLUDE_PATH := $(INCLUDE_PATH) -I$(UNITY_PATH))
	$(GCC) $(FLAGS) $(TEST_PATH)$(SOURCE) $(OFILES) -o $(RESULT_PATH)$(TEST_OUTPUT) $(LIBRARIES)
	./$(RESULT_PATH)$(TEST_OUTPUT)

gdb:
	$(eval FLAGS := $(FLAGS) -g)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)
	$(GDB) $(RESULT_PATH)$(OUTPUT)

valgrind: $(OUTPUT)
	valgrind $(RESULT_PATH)$(OUTPUT)

clean:
	$(RM) $(OFILES) $(OUTPUT)

.PHONY: all run testing gdb clean
.DEFAULT_GOAL = run
