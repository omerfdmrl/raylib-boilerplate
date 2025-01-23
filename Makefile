GCC = gcc
GDB = gdb
RM = rm -rf
MKDIR = mkdir -p

ifeq ($(OS),Windows_NT)
	RM = del /s /q
    MKDIR = mkdir
endif

LIBRARIES := -lm
INCLUDE_PATH := 
FLAGS :=

SOURCE = main.c
OUTPUT = program
TEST_OUTPUT = bin

SRC_PATH = src/
VENDOR_PATH = vendor/
LIB_PATH = lib/
TEST_PATH = test/
RESULT_PATH = build/results/

UNITY_PATH = $(LIB_PATH)unity/
RAYLIB_PATH = $(LIB_PATH)raylib/

LIBRARIES := -L$(RAYLIB_PATH) -lraylib $(LIBRARIES)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(RAYLIB_PATH)

SRC_DIRS := $(wildcard $(SRC_PATH)*/)
SRC_DIRS := $(SRC_PATH) $(SRC_DIRS)

CFILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)*.c))

VENDOR_DIRS := $(wildcard $(VENDOR_PATH)*/)
VENDOR_DIRS := $(VENDOR_PATH) $(VENDOR_DIRS)

CFILES := $(foreach dir, $(VENDOR_DIRS), $(wildcard $(dir)*.c)) $(CFILES)
LIBRARIES := $(foreach dir, $(VENDOR_DIRS), -I$(dir)) $(LIBRARIES)

$(OUTPUT): $(CFILES)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)

run: $(OUTPUT)
	./$(RESULT_PATH)$(OUTPUT)

test: $(UNITY_PATH)
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

.PHONY: all run test gdb clean
.DEFAULT_GOAL = run
