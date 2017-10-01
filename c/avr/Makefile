##
# @file Makefile
# @brief Build file for all AVR C targets.
# @copyright Copyright (c) Liam Bucci. See included LICENSE file.

### Global Configuration ###

# Build Commands #
CC = gcc
AVR_CC = avr-gcc

# Shell Commands #
CP = cp -fr
MKDIR = mkdir -p
RM    = rm -f
RMDIR = rm -fr

# Directories #
COMMON_SOURCE_DIR = ../common/src
COMMON_INCLUDE_DIR = ../common/include
AVR_BUILD_DIR = build
AVR_OUTPUT_DIR = output
AVR_SOURCE_DIR = src
AVR_COMMON_DIR = src/common
AVR_INCLUDE_DIR = include
AVR_TESTS_DIR = tests
AVR_MOCKS_DIR = mocks
AVR_STUBS_DIR = stubs
THIRDPARTY_DIR = ../../thirdparty

# Build Flags #
AVR_CFLAGS = -Wall -Werror -ggdb
AVR_LDFLAGS =
AVR_LDLIBS =

### Application Configuration ###


### Test Configuration ###

# Unity Sources #
UNITY_SOURCES = $(THIRDPARTY_DIR)/unity/src/unity.c
UNITY_INCLUDES = $(THIRDPARTY_DIR)/unity/src

### Global Goals ###

ALL_APPLICATION_TARGETS =
ALL_UNITTEST_TARGETS = $(PIN_ATTINYx5_TARGET)

.PHONY: all
all: build

.SECONDEXPANSION:
.PHONY: build
build: $$(addsuffix _build,$$(ALL_APPLICATION_TARGETS) $$(ALL_UNITTEST_TARGETS))

.PHONY: test
test: $$(addsuffix _run,$$(ALL_UNITTEST_TARGETS))

.PHONY: clean
clean: $$(addsuffix _clean,$$(ALL_APPLICATION_TARGETS) $$(ALL_UNITTEST_TARGETS))

# Output Directory #
$(AVR_OUTPUT_DIR):
	@$(MKDIR) $@

### Applications ###


### Unit Tests ###

include make/unittest.mk

# ATTinyx5 Pin Driver #
PIN_ATTINYx5_TARGET := test_pin_attinyx5
PIN_ATTINYx5_FAMILY := attinyx5
PIN_ATTINYx5_SOURCES := $(AVR_TESTS_DIR)/attinyx5/test_pin_attinyx5.c \
                       $(AVR_SOURCE_DIR)/attinyx5/pin.c \
                       $(AVR_MOCKS_DIR)/attinyx5/io.c \
                       $(UNITY_SOURCES)
PIN_ATTINYx5_INCLUDES := $(AVR_MOCKS_DIR)/attinyx5/include \
                        $(UNITY_INCLUDES)
PIN_ATTINYx5_CFLAGS := -D__AVR_ATtiny85__
PIN_ATTINYx5_LDFLAGS :=
PIN_ATTINYx5_LDLIBS :=

$(eval $(call UT_tmpl,$(PIN_ATTINYx5_TARGET),$(PIN_ATTINYx5_FAMILY),$(PIN_ATTINYx5_SOURCES),$(PIN_ATTINYx5_INCLUDES),$(PIN_ATTINYx5_CFLAGS),$(PIN_ATTINYx5_LDFLAGS),$(PIN_ATTINYx5_LDLIBS)))

# Directories #
#TEST_BUILD_DIR = $(AVR_BUILD_DIR)/test_pin_attinyx5
#TEST_OUTPUT_DIR = $(AVR_OUTPUT_DIR)/test_pin_attinyx5
#
## Build Flags #
#TEST_CFLAGS = $(AVR_CFLAGS) -D__AVR_ATtiny85__
#TEST_LDFLAGS = $(AVR_LDFLAGS)
#TEST_LDLIBS = $(AVR_LDLIBS)
#
## Target #
#TEST_TARGET = test_pin_attinyx5
#
## Source Files #
#TEST_SOURCES = $(AVR_SOURCE_DIR)/attinyx5/pin.c \
#$(AVR_TEST_DIR)/attinyx5/test_pin_attinyx5.c \
#			   $(AVR_MOCKS_DIR)/attinyx5/io.c \
#			   $(THIRDPARTY_DIR)/unity/src/unity.c
#TEST_OBJECTS = $(addprefix $(TEST_BUILD_DIR)/,$(notdir $(TEST_SOURCES:.c=.o)))
#
## Source Paths #
#TEST_SOURCE_PATHS = $(dir $(TEST_SOURCES))
#VPATH += $(THIRDPARTY_DIR)/unity/src
#
## Include Paths #
#TEST_INCLUDES = $(AVR_INCLUDE_DIR) $(THIRDPARTY_DIR)/unity/src $(AVR_MOCKS_DIR)/attinyx5/include
#TEST_INCLUDE_FLAGS = $(addprefix -I,$(TEST_INCLUDES))
#
## Build Dependencies #
#-include $(APP_OBJECTS:.o=.d)
#
## Build Targets #
#.PHONY: test_pin_attinyx5
#test_pin_attinyx5: $(TEST_OUTPUT_DIR)/$(TEST_TARGET)
#
#.PHONY: clean
#clean:
#	$(RMDIR) $(TEST_BUILD_DIR)
#	$(RMDIR) $(TEST_OUTPUT_DIR)
#
## Build Recipes #
#$(TEST_OUTPUT_DIR):
#	$(MKDIR) $@
#
#$(TEST_BUILD_DIR):
#	$(MKDIR) $@

# Other dependencies defined in %.d
#$(TEST_BUILD_DIR)/%.o: %.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<

#$(TEST_BUILD_DIR)/%.o: src/common/%.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<
#
#$(TEST_BUILD_DIR)/%.o: src/attinyx5/%.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<
#
#$(TEST_BUILD_DIR)/%.o: mocks/attinyx5/%.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<
#
#$(TEST_BUILD_DIR)/%.o: tests/attinyx5/%.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<
#
#$(TEST_BUILD_DIR)/%.o: %.c | $(TEST_BUILD_DIR)
#	@$(MKDIR) $(TEST_BUILD_DIR)
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -c $< -o $@
#	$(CC) $(TEST_CFLAGS) $(TEST_INCLUDE_FLAGS) -MM -MF $(@:.o=.d) $<
#
#$(TEST_OUTPUT_DIR)/$(TEST_TARGET): $(TEST_OBJECTS) | $(TEST_OUTPUT_DIR)
#	$(CC) $(TEST_LDFLAGS) $(TEST_OBJECTS) $(TEST_LDLIBS) -o $@

