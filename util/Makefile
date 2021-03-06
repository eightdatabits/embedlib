##
# @file Makefile
# @brief Build file for all AVR C targets.
# @copyright Copyright (c) Liam Bucci. See included LICENSE file.

### Global Configuration ###

# Shell Commands #
CP    = cp -fr
MKDIR = mkdir -p
RM    = rm -f
RMDIR = rm -fr

# Directories #
COMMON_SOURCE_DIR = src
COMMON_INCLUDE_DIR = include
COMMON_BUILD_DIR = build
COMMON_OUTPUT_DIR = output
COMMON_TESTS_DIR = tests
COMMON_MOCKS_DIR = mocks
COMMON_STUBS_DIR = stubs
THIRDPARTY_DIR = ../thirdparty

# Build Flags #
COMMON_UT_CFLAGS = -Wall -Werror -ggdb
COMMON_UT_CPPFLAGS = -std=c++11 -Wall -Werror -ggdb
COMMON_UT_LDFLAGS =
COMMON_UT_LDLIBS =

### Application Configuration ###


### Test Configuration ###

# Unity Sources #
UNITY_SOURCES = $(THIRDPARTY_DIR)/unity/src/unity.c
UNITY_INCLUDES = $(THIRDPARTY_DIR)/unity/src

### Global Goals ###

ALL_UT_TARGETS = $(MEMPOOL_TARGET) \
                 $(BITARRAY_TARGET) \
                 $(QUEUE_TARGET) \
                 $(RBTREE_TARGET) \
                 $(BINARY_SEARCH_TARGET) \
                 $(SPAN_TARGET) \
                 $(STACK_TARGET)

.PHONY: all
all: build

.SECONDEXPANSION:
.PHONY: build
build: $$(addsuffix _build,$$(ALL_UT_TARGETS))

.PHONY: test
test: $$(addsuffix _run,$$(ALL_UT_TARGETS))

.PHONY: clean
clean: $$(addsuffix _clean,$$(ALL_UT_TARGETS))

# Output Directory #
$(COMMON_OUTPUT_DIR):
	@$(MKDIR) $@

### Unit Tests ###

include make/unittest.mk

# MemPool Unit Test #
MEMPOOL_TARGET   := test_mem_pool
MEMPOOL_SOURCES  := $(COMMON_TESTS_DIR)/test_mem_pool.cpp \
                    $(UNITY_SOURCES)
MEMPOOL_INCLUDES := $(UNITY_INCLUDES)
MEMPOOL_CFLAGS   :=
MEMPOOL_CPPFLAGS :=
MEMPOOL_LDFLAGS  :=
MEMPOOL_LDLIBS   :=

# BitArray Unit Test #
BITARRAY_TARGET   := test_bit_array
BITARRAY_SOURCES  := $(COMMON_TESTS_DIR)/test_bit_array.cpp \
                     $(UNITY_SOURCES)
BITARRAY_INCLUDES := $(UNITY_INCLUDES)
BITARRAY_CFLAGS   :=
BITARRAY_CPPFLAGS :=
BITARRAY_LDFLAGS  :=
BITARRAY_LDLIBS   :=

# Queue Unit Test #
QUEUE_TARGET   := test_queue
QUEUE_SOURCES  := $(COMMON_TESTS_DIR)/test_queue.cpp \
                  $(UNITY_SOURCES)
QUEUE_INCLUDES := $(UNITY_INCLUDES)
QUEUE_CFLAGS   :=
QUEUE_CPPFLAGS :=
QUEUE_LDFLAGS  :=
QUEUE_LDLIBS   :=

# RbTree Unit Test #
RBTREE_TARGET   := test_rb_tree
RBTREE_SOURCES  := $(COMMON_TESTS_DIR)/test_rb_tree.cpp \
                   $(UNITY_SOURCES)
RBTREE_INCLUDES := $(UNITY_INCLUDES)
RBTREE_CFLAGS   :=
RBTREE_CPPFLAGS :=
RBTREE_LDFLAGS  :=
RBTREE_LDLIBS   :=

# BinarySearch Unit Test #
BINARY_SEARCH_TARGET   := test_search
BINARY_SEARCH_SOURCES  := $(COMMON_TESTS_DIR)/test_binary_search.cpp \
                          $(UNITY_SOURCES)
BINARY_SEARCH_INCLUDES := $(UNITY_INCLUDES)
BINARY_SEARCH_CFLAGS   :=
BINARY_SEARCH_CPPFLAGS :=
BINARY_SEARCH_LDFLAGS  :=
BINARY_SEARCH_LDLIBS   :=

# Span Unit Test #
SPAN_TARGET   := test_span
SPAN_SOURCES  := $(COMMON_TESTS_DIR)/test_span.cpp \
                 $(UNITY_SOURCES)
SPAN_INCLUDES := $(UNITY_INCLUDES)
SPAN_CFLAGS   :=
SPAN_CPPFLAGS :=
SPAN_LDFLAGS  :=
SPAN_LDLIBS   :=

# Stack Unit Test #
STACK_TARGET   := test_stack
STACK_SOURCES  := $(COMMON_TESTS_DIR)/test_stack.cpp \
                  $(UNITY_SOURCES)
STACK_INCLUDES := $(UNITY_INCLUDES)
STACK_CFLAGS   :=
STACK_CPPFLAGS :=
STACK_LDFLAGS  :=
STACK_LDLIBS   :=

$(eval $(call UT_tmpl,$(MEMPOOL_TARGET),$(MEMPOOL_SOURCES),$(MEMPOOL_INCLUDES),$(MEMPOOL_CFLAGS),$(MEMPOOL_CPPFLAGS),$(MEMPOOL_LDFLAGS),$(MEMPOOL_LDLIBS)))
$(eval $(call UT_tmpl,$(BITARRAY_TARGET),$(BITARRAY_SOURCES),$(BITARRAY_INCLUDES),$(BITARRAY_CFLAGS),$(BITARRAY_CPPFLAGS),$(BITARRAY_LDFLAGS),$(BITARRAY_LDLIBS)))
$(eval $(call UT_tmpl,$(QUEUE_TARGET),$(QUEUE_SOURCES),$(QUEUE_INCLUDES),$(QUEUE_CFLAGS),$(QUEUE_CPPFLAGS),$(QUEUE_LDFLAGS),$(QUEUE_LDLIBS)))
$(eval $(call UT_tmpl,$(RBTREE_TARGET),$(RBTREE_SOURCES),$(RBTREE_INCLUDES),$(RBTREE_CFLAGS),$(RBTREE_CPPFLAGS),$(RBTREE_LDFLAGS),$(RBTREE_LDLIBS)))
$(eval $(call UT_tmpl,$(BINARY_SEARCH_TARGET),$(BINARY_SEARCH_SOURCES),$(BINARY_SEARCH_INCLUDES),$(BINARY_SEARCH_CFLAGS),$(BINARY_SEARCH_CPPFLAGS),$(BINARY_SEARCH_LDFLAGS),$(BINARY_SEARCH_LDLIBS)))
$(eval $(call UT_tmpl,$(SPAN_TARGET),$(SPAN_SOURCES),$(SPAN_INCLUDES),$(SPAN_CFLAGS),$(SPAN_CPPFLAGS),$(SPAN_LDFLAGS),$(SPAN_LDLIBS)))
$(eval $(call UT_tmpl,$(STACK_TARGET),$(STACK_SOURCES),$(STACK_INCLUDES),$(STACK_CFLAGS),$(STACK_CPPFLAGS),$(STACK_LDFLAGS),$(STACK_LDLIBS)))
