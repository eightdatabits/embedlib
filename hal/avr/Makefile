##
# @file Makefile
# @brief Build file for all AVR C targets.
# @copyright Copyright (c) Liam Bucci. See included LICENSE file.

### Global Configuration ###

# Build Commands #
CC = gcc
CXX = g++
AVR_CC = avr-gcc
AVR_CXX = avr-g++
AVR_AR = avr-ar
AVR_OBJCOPY = avr-objcopy
AVR_OBJDUMP = avr-objdump
AVR_PROG = avrdude

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
AVR_LIB_CPPFLAGS = -std=c++11 -Wall -Werror -ggdb
AVR_LIB_ARFLAGS =
AVR_LIB_OBJDUMPFLAGS =
AVR_UT_CFLAGS = -Wall -Werror -ggdb
AVR_UT_CPPFLAGS = -std=c++11 -Wall -Werror -ggdb
AVR_UT_LDFLAGS =
AVR_UT_LDLIBS =
AVR_FT_CFLAGS = -Wall -Werror
AVR_FT_CPPFLAGS = -std=c++11 -Wall -Werror
AVR_FT_LDFLAGS =
AVR_FT_LDLIBS =
AVR_FT_OBJCOPYFLAGS = -j .text -j .data -O ihex
AVR_FT_OBJDUMPFLAGS = -h -S
AVR_FT_PROGFLAGS = -c atmelice_isp -P usb


### Application Configuration ###


### Test Configuration ###

# Unity Sources #
UNITY_SOURCES = $(THIRDPARTY_DIR)/unity/src/unity.c
UNITY_INCLUDES = $(THIRDPARTY_DIR)/unity/src

### Global Goals ###

.PHONY: all
all: build

.PHONY: help
help:
	@echo "##################"
	@echo "#  JunkHAL: AVR  #"
	@echo "##################"
	@echo ""
	@echo "General options:"
	@echo "    all        Build all targets [default]"
	@echo "    build      Build all targets"
	@echo "    libs       Build all library targets"
	@echo "    uts        Build all unit test targets"
	@echo "    fts        Build all functional test targets"
	@echo "    test       Build and run all unit test targets"
	@echo "    clean      Clean all targets"
	@echo ""
	@echo "Library targets:"
	@echo "    lib_<proc>_[build|clean]                Builds the JunkHAL into a static library for"
	@echo "                                            the given AVR processor."
	@echo ""
	@echo "Available library targets:"
	@echo $(foreach target,$(ALL_LIBS),"    $(target)_build\n    $(target)_clean\n")
	@echo ""
	@echo "Unit test targets:"
	@echo "    ut_<family>_<unit>_[build|run|clean]    Builds/runs the unit test for the given"
	@echo "                                            unit/driver of the specified family of AVR"
	@echo "                                            processors."
	@echo ""
	@echo "Available unit test targets:"
	@echo $(foreach target,$(ALL_UTS),"    $(target)_build\n    $(target)_run\n    $(target)_clean\n")
	@echo ""
	@echo "Functional test targets:"
	@echo "    ft_<family>_<unit>_[build|run|clean]    Builds/flashes the functional test for the"
	@echo "                                            given unit/driver with the specified family"
	@echo "                                            of AVR processors. Running means flashing"
	@echo "                                            the application via an AVR-ISP mkII."
	@echo ""
	@echo "Available functional test targets:"
	@echo $(foreach target,$(ALL_FTS),"    $(target)_build\n    $(target)_run\n    $(target)_clean\n")
	@echo ""

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
UT_PIN_ATTINYx5_TARGET := pin
UT_PIN_ATTINYx5_FAMILY := attinyx5
UT_PIN_ATTINYx5_SOURCES := $(AVR_TESTS_DIR)/attinyx5/test_pin_attinyx5.cpp \
                        $(AVR_SOURCE_DIR)/attinyx5/pin.cpp \
                        $(AVR_MOCKS_DIR)/attinyx5/io.c \
                        $(UNITY_SOURCES)
UT_PIN_ATTINYx5_INCLUDES := $(AVR_MOCKS_DIR)/attinyx5/include \
                         $(UTIL_INCLUDE_DIR) \
                         $(UNITY_INCLUDES)
UT_PIN_ATTINYx5_CFLAGS := -D__AVR_ATtiny85__
UT_PIN_ATTINYx5_CPPFLAGS := -D__AVR_ATtiny85__
UT_PIN_ATTINYx5_LDFLAGS :=
UT_PIN_ATTINYx5_LDLIBS :=

$(eval $(call UT_tmpl,$(UT_PIN_ATTINYx5_TARGET),$(UT_PIN_ATTINYx5_FAMILY),$(UT_PIN_ATTINYx5_SOURCES),$(UT_PIN_ATTINYx5_INCLUDES),$(UT_PIN_ATTINYx5_CFLAGS),$(UT_PIN_ATTINYx5_CPPFLAGS),$(UT_PIN_ATTINYx5_LDFLAGS),$(UT_PIN_ATTINYx5_LDLIBS)))

### Functional Tests ###

include make/functest.mk

# ATTiny85 Pin Driver #
FT_PIN_ATTINY85_TARGET := pin
FT_PIN_ATTINY85_FAMILY := attinyx5
FT_PIN_ATTINY85_MCU := attiny85
FT_PIN_ATTINY85_SOURCES := $(AVR_TESTS_DIR)/attinyx5/functest_pin.cpp \
                           $(AVR_SOURCE_DIR)/attinyx5/pin.cpp
FT_PIN_ATTINY85_INCLUDES := $(AVR_INCLUDE_DIR) \
                            $(UTIL_INCLUDE_DIR)
FT_PIN_ATTINY85_CFLAGS := -g -Os -mmcu=$(FT_PIN_ATTINY85_MCU) -DFOSC=1000000
FT_PIN_ATTINY85_CPPFLAGS := -g -Os -mmcu=$(FT_PIN_ATTINY85_MCU) -DFOSC=1000000
FT_PIN_ATTINY85_LDFLAGS := -g -mmcu=$(FT_PIN_ATTINY85_MCU) -Wl,-T,$(AVR_LINKER_DIR)/attiny85.x
FT_PIN_ATTINY85_LDLIBS :=
FT_PIN_ATTINY85_OBJCOPY_FLAGS :=
FT_PIN_ATTINY85_OBJDUMP_FLAGS :=
FT_PIN_ATTINY85_LFUSE := 0xE2
FT_PIN_ATTINY85_HFUSE := 0xDF
FT_PIN_ATTINY85_EFUSE := 0xFF
FT_PIN_ATTINY85_PROG_FLAGS := -p t85 -U lfuse:w:$(FT_PIN_ATTINY85_LFUSE):m -U hfuse:w:$(FT_PIN_ATTINY85_HFUSE):m -U efuse:w:$(FT_PIN_ATTINY85_EFUSE):m

$(eval $(call FT_tmpl,$(FT_PIN_ATTINY85_TARGET),$(FT_PIN_ATTINY85_FAMILY),$(FT_PIN_ATTINY85_MCU),$(FT_PIN_ATTINY85_SOURCES),$(FT_PIN_ATTINY85_INCLUDES),$(FT_PIN_ATTINY85_CFLAGS),$(FT_PIN_ATTINY85_CPPFLAGS),$(FT_PIN_ATTINY85_LDFLAGS),$(FT_PIN_ATTINY85_LDLIBS),$(FT_PIN_ATTINY85_OBJCOPY_FLAGS),$(FT_PIN_ATTINY85_OBJDUMP_FLAGS),$(FT_PIN_ATTINY85_PROG_FLAGS)))

# ATTiny85 SPI Driver #
FT_SPI_ATTINY85_TARGET := spi
FT_SPI_ATTINY85_FAMILY := attinyx5
FT_SPI_ATTINY85_MCU := attiny85
FT_SPI_ATTINY85_SOURCES := $(AVR_TESTS_DIR)/attinyx5/functest_spi.cpp \
                           $(AVR_SOURCE_DIR)/attinyx5/spi.cpp \
                           $(AVR_SOURCE_DIR)/attinyx5/pin.cpp \
                           $(AVR_SOURCE_DIR)/attinyx5/delay.S
FT_SPI_ATTINY85_INCLUDES := $(AVR_INCLUDE_DIR) \
                            $(UTIL_INCLUDE_DIR)
FT_SPI_ATTINY85_CFLAGS := -g -Os -mmcu=$(FT_SPI_ATTINY85_MCU) -DFOSC=1000000
FT_SPI_ATTINY85_CPPFLAGS := -g -Os -mmcu=$(FT_SPI_ATTINY85_MCU) -DFOSC=1000000
FT_SPI_ATTINY85_LDFLAGS := -g -mmcu=$(FT_SPI_ATTINY85_MCU) -Wl,-T,$(AVR_LINKER_DIR)/attiny85.x
FT_SPI_ATTINY85_LDLIBS :=
FT_SPI_ATTINY85_OBJCOPY_FLAGS :=
FT_SPI_ATTINY85_OBJDUMP_FLAGS :=
FT_SPI_ATTINY85_LFUSE := 0xE2
FT_SPI_ATTINY85_HFUSE := 0xDF
FT_SPI_ATTINY85_EFUSE := 0xFF
FT_SPI_ATTINY85_PROG_FLAGS := -p t85 -U lfuse:w:$(FT_SPI_ATTINY85_LFUSE):m -U hfuse:w:$(FT_SPI_ATTINY85_HFUSE):m -U efuse:w:$(FT_SPI_ATTINY85_EFUSE):m

$(eval $(call FT_tmpl,$(FT_SPI_ATTINY85_TARGET),$(FT_SPI_ATTINY85_FAMILY),$(FT_SPI_ATTINY85_MCU),$(FT_SPI_ATTINY85_SOURCES),$(FT_SPI_ATTINY85_INCLUDES),$(FT_SPI_ATTINY85_CFLAGS),$(FT_SPI_ATTINY85_CPPFLAGS),$(FT_SPI_ATTINY85_LDFLAGS),$(FT_SPI_ATTINY85_LDLIBS),$(FT_SPI_ATTINY85_OBJCOPY_FLAGS),$(FT_SPI_ATTINY85_OBJDUMP_FLAGS),$(FT_SPI_ATTINY85_PROG_FLAGS)))


## These must be at the bottom of the file ##

.PHONY: build
build: $(addsuffix _build,$(ALL_LIBS) $(ALL_UTS) $(ALL_FTS))

.PHONY: libs
libs: $(addsuffix _build,$(ALL_LIBS))

.PHONY: uts
uts: $(addsuffix _build,$(ALL_UTS))

.PHONY: fts
fts: $(addsuffix _build,$(ALL_FTS))

.PHONY: test
test: $(addsuffix _run,$(ALL_UTS))

.PHONY: clean
clean: $(addsuffix _clean,$(ALL_LIBS) $(ALL_UTS) $(ALL_FTS))
