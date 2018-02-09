##
# @file Makefile
# @brief Build file for all AVR C targets.
# @copyright Copyright (c) Liam Bucci. See included LICENSE file.

### Global Configuration ###

# Build Commands #
CC = gcc
CXX = g++
AVR_CC = avr-gcc
AVR_AR = avr-ar
AVR_OBJDUMP = avr-objdump

# Shell Commands #
CP    = cp -fr
MKDIR = mkdir -p
RM    = rm -f
RMDIR = rm -fr

# Directories #
JUNK_ROOT = ../..
COMMON_SOURCE_DIR = $(JUNK_ROOT)/hal/common/src
COMMON_INCLUDE_DIR = $(JUNK_ROOT)/hal/common/include
UTIL_SOURCE_DIR = $(JUNK_ROOT)/util/src
UTIL_INCLUDE_DIR = $(JUNK_ROOT)/util/include
AVR_BUILD_DIR = build
AVR_OUTPUT_DIR = output
AVR_SOURCE_DIR = src
AVR_COMMON_DIR = src/common
AVR_INCLUDE_DIR = include
AVR_LINKER_DIR = linker
AVR_TESTS_DIR = tests
AVR_MOCKS_DIR = mocks
AVR_STUBS_DIR = stubs
THIRDPARTY_DIR = $(JUNK_ROOT)/thirdparty

# Build Flags #
AVR_LIB_CFLAGS = -Wall -Werror -ggdb
AVR_LIB_CPPFLAGS = -Wall -Werror -ggdb
AVR_LIB_ARFLAGS =
AVR_LIB_OBJDUMPFLAGS =
AVR_UT_CFLAGS = -Wall -Werror -ggdb
AVR_UT_CPPFLAGS = -Wall -Werror -ggdb
AVR_UT_LDFLAGS =
AVR_UT_LDLIBS =

### Application Configuration ###


### Test Configuration ###

# Unity Sources #
UNITY_SOURCES = $(THIRDPARTY_DIR)/unity/src/unity.c
UNITY_INCLUDES = $(THIRDPARTY_DIR)/unity/src

### Global Goals ###

ALL_LIB_TARGETS = $(LIB_ATTINY85_TARGET)
ALL_UT_TARGETS = $(PIN_ATTINYx5_TARGET)

.PHONY: all
all: build

.SECONDEXPANSION:
.PHONY: build
build: $$(addsuffix _build,$$(ALL_LIB_TARGETS) $$(ALL_UT_TARGETS))

.PHONY: test
test: $$(addsuffix _run,$$(ALL_UT_TARGETS))

.PHONY: clean
clean: $$(addsuffix _clean,$$(ALL_LIB_TARGETS) $$(ALL_UT_TARGETS))

# Output Directory #
$(AVR_OUTPUT_DIR):
	@$(MKDIR) $@

### Libraries ###

include make/library.mk

# ATTiny85 Library #
LIB_ATTINY85_TARGET := attiny85
LIB_ATTINY85_FAMILY := attinyx5
LIB_ATTINY85_SOURCES := $(AVR_SOURCE_DIR)/attinyx5/pin.cpp \
                        $(AVR_SOURCE_DIR)/attinyx5/spi.cpp \
                        $(AVR_SOURCE_DIR)/attinyx5/timer1.cpp
LIB_ATTINY85_INCLUDES := $(AVR_INCLUDE_DIR) \
                         $(UTIL_INCLUDE_DIR)
LIB_ATTINY85_CFLAGS := -mmcu=attiny85 -Wall -Werror -Os
LIB_ATTINY85_CPPFLAGS := -mmcu=attiny85 -Wall -Werror -Os
LIB_ATTINY85_ARFLAGS :=
LIB_ATTINY85_OBJDUMPFLAGS :=

$(eval $(call LIB_tmpl,$(LIB_ATTINY85_TARGET),$(LIB_ATTINY85_FAMILY),$(LIB_ATTINY85_SOURCES),$(LIB_ATTINY85_INCLUDES),$(LIB_ATTINY85_CFLAGS),$(LIB_ATTINY85_CPPFLAGS),$(LIB_ATTINY85_ARFLAGS),$(LIB_ATTINY85_OBJDUMPFLAGS)))

### Unit Tests ###

include make/unittest.mk

# ATTinyx5 Pin Driver #
PIN_ATTINYx5_TARGET := test_pin_attinyx5
PIN_ATTINYx5_FAMILY := attinyx5
PIN_ATTINYx5_SOURCES := $(AVR_TESTS_DIR)/attinyx5/test_pin_attinyx5.cpp \
                        $(AVR_SOURCE_DIR)/attinyx5/pin.cpp \
                        $(AVR_MOCKS_DIR)/attinyx5/io.c \
                        $(UNITY_SOURCES)
PIN_ATTINYx5_INCLUDES := $(AVR_MOCKS_DIR)/attinyx5/include \
                         $(UTIL_INCLUDE_DIR) \
                         $(UNITY_INCLUDES)
PIN_ATTINYx5_CFLAGS := -D__AVR_ATtiny85__
PIN_ATTINYx5_CPPFLAGS := -D__AVR_ATtiny85__
PIN_ATTINYx5_LDFLAGS :=
PIN_ATTINYx5_LDLIBS :=

$(eval $(call UT_tmpl,$(PIN_ATTINYx5_TARGET),$(PIN_ATTINYx5_FAMILY),$(PIN_ATTINYx5_SOURCES),$(PIN_ATTINYx5_INCLUDES),$(PIN_ATTINYx5_CFLAGS),$(PIN_ATTINYx5_CPPFLAGS),$(PIN_ATTINYx5_LDFLAGS),$(PIN_ATTINYx5_LDLIBS)))
