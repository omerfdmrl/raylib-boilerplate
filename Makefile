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
FLAGS := -lpthread -ldl -lrt -lX11

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
CJSON_PATH = $(LIB_PATH)cJSON/

LIBRARIES := -L$(RAYLIB_PATH) -lraylib $(LIBRARIES)
INCLUDE_PATH := $(INCLUDE_PATH) -I$(RAYLIB_PATH) -I$(LIB_PATH) -I$(CJSON_PATH)

SRC_DIRS := $(SRC_PATH) \
            $(wildcard $(SRC_PATH)*/) \
            $(wildcard $(SRC_PATH)*/*/) \
            $(wildcard $(SRC_PATH)*/*/*/)

CFILES := $(foreach dir, $(SRC_DIRS), $(wildcard $(dir)*.c))
CFILES += $(CJSON_PATH)cJSON.c

VENDOR_DIRS := $(VENDOR_PATH) \
            $(wildcard $(VENDOR_PATH)*/) \
            $(wildcard $(VENDOR_PATH)*/*/) \
            $(wildcard $(VENDOR_PATH)*/*/*/)

CFILES := $(foreach dir, $(VENDOR_DIRS), $(wildcard $(dir)*.c)) $(CFILES)
LIBRARIES := $(foreach dir, $(VENDOR_DIRS), -I$(dir)) $(LIBRARIES)

$(OUTPUT): $(CFILES)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)

run: $(OUTPUT)
	./$(RESULT_PATH)$(OUTPUT)

test:
	$(GCC) -I$(RAYLIB_PATH) -I$(LIB_PATH) -I$(CJSON_PATH) -I$(UNITY_PATH) \
		-I$(VENDOR_PATH) -I$(VENDOR_PATH)utils -I$(VENDOR_PATH)scene \
		-I$(VENDOR_PATH)object -I$(VENDOR_PATH)helpers \
		-I$(TEST_PATH) -I$(TEST_PATH)utils -I$(TEST_PATH)scene -I$(TEST_PATH)object \
		$(UNITY_PATH)unity.c \
		$(VENDOR_PATH)utils/linked_list.c \
		$(VENDOR_PATH)utils/hashmap.c \
		$(VENDOR_PATH)utils/logger.c \
		$(VENDOR_PATH)utils/assert.c \
		$(VENDOR_PATH)scene/core.c \
		$(VENDOR_PATH)object/core.c \
		$(VENDOR_PATH)status.c \
		$(VENDOR_PATH)global.c \
		$(CJSON_PATH)cJSON.c \
		$(TEST_PATH)test_runner.c \
		$(TEST_PATH)utils/linked_list_test.c \
		$(TEST_PATH)utils/hashmap_test.c \
		$(TEST_PATH)utils/logger_test.c \
		$(TEST_PATH)utils/assert_test.c \
		$(TEST_PATH)scene/core_test.c \
		$(TEST_PATH)object/core_test.c \
		-L$(RAYLIB_PATH) -lraylib -lm -lpthread -ldl -lrt -lX11 \
		-o $(RESULT_PATH)$(TEST_OUTPUT)
	./$(RESULT_PATH)$(TEST_OUTPUT)

gdb:
	$(eval FLAGS := $(FLAGS) -g)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)
	$(GDB) $(RESULT_PATH)$(OUTPUT)

valgrind: $(OUTPUT)
	valgrind --leak-check=full --suppressions=valgrind.suppress --track-origins=yes $(RESULT_PATH)$(OUTPUT)

asan:
	$(eval GCC = clang)
	$(eval FLAGS := -fsanitize=address)
	$(GCC) $(FLAGS) $(SOURCE) $(INCLUDE_PATH) $(CFILES) -o $(RESULT_PATH)$(OUTPUT) $(LIBRARIES)
	./$(RESULT_PATH)$(OUTPUT)

clean:
	$(RM) $(OFILES) $(OUTPUT)

.PHONY: all run test gdb clean
.DEFAULT_GOAL = run
