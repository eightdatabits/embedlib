##
# @file Makefile
# @brief Top level build file. Calls make recursively on sub-Makefiles.
# @copyright Copyright (c) Liam Bucci. See included LICENSE file.

### Top-level Goals ###

# Default target #
.PHONY: all
all: build

# Build all platforms #
.PHONY: build
build:
	@cd c/avr ; make build

# Run all unit tests on all platforms #
.PHONY: test
test:
	@cd c/avr ; make test

# Clean all platforms #
.PHONY: clean
clean:
	@cd c/avr ; make clean

# Print the help message #
.PHONY: help
help:
	@echo "Embedlib build system."
	@echo "For more build system information see the readme.md"
	@echo "Make targets:"
	@echo "    all        Invokes `build`."
	@echo "    build      Build all targets and tests on all platforms."
	@echo "    test       Build and run all unit tests on all platforms. Prints results to stdout."
	@echo "    clean      Clean all build and output files on all platforms."
	@echo "    help       Print this message."

# Debug tool: prints the value of the variable `varname` when make is called like this:
#     make print-varname
# Taken from here: https://www.cmcrossroads.com/article/printing-value-makefile-variable
print-%:
	@echo $* = $($*)
