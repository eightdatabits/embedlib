##
# Unit Test Template
#
# Params:
# 1 - Target name: Used to uniquely identify all variables
# 2 - Family: Used to uniquely identify path to source files
# 3 - Sources
# 4 - Include paths
# 5 - C flags
# 6 - Linker flags
# 7 - Linker libs
#
# Output Targets:
# $(1)_build - Build the test target
# $(1)_run - Execute the test target
# $(1)_clean - Clean all build and output files
#
define UT_tmpl

### Setup ###

# Directories #
$(1)_BUILD_DIR = $$(AVR_BUILD_DIR)/$(1)

# Build Flags #
$(1)_CFLAGS = $$(AVR_CFLAGS) $(5)
$(1)_LDFLAGS = $$(AVR_LDFLAGS) $(6)
$(1)_LDLIBS = $$(AVR_LDLIBS) $(7)

# Source Files #
$(1)_SOURCES = $(3)
$(1)_OBJECTS = $$(addprefix $$($(1)_BUILD_DIR)/,$$(notdir $$($(1)_SOURCES:.c=.o)))

# Include Paths #
$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $$(AVR_INCLUDE_DIR) $(4)
$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$($(1)_INCLUDES))

# Set VPATH #
VPATH += $(THIRDPARTY_DIR)/unity/src

### Targets ###

# Build Rule #
.PHONY: $(1)_build
$(1)_build: $$(AVR_OUTPUT_DIR)/$(1)

# Run Rule #
.PHONY: $(1)_run
$(1)_run: $(1)_build
	@$$(AVR_OUTPUT_DIR)/$(1)

# Clean Rule #
.PHONY: $(1)_clean
$(1)_clean:
	$$(RMDIR) $$($(1)_BUILD_DIR)
	$$(RMDIR) $$(AVR_OUTPUT_DIR)/$(1)

### Build Recipes ###

# Build Dependencies #
-include $$($(1)_OBJECTS:.o=.d)

# Build Directory #
$$($(1)_BUILD_DIR):
	@$$(MKDIR) $$@

# Common Sources #
$$($(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Common AVR Sources #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Family Specific Sources #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Family Specific Mocks #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Family Specific Stubs #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Family Specific Tests #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# General Sources #
$$($(1)_BUILD_DIR)/%.o: %.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -c $$< -o $$@
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MM -MF $$(@:.o=.d) $$<

# Link Target #
$$(AVR_OUTPUT_DIR)/$(1): $$($(1)_OBJECTS) | $$(AVR_OUTPUT_DIR)
	$$(CC) $$($(1)_LDFLAGS) $$^ $$($(1)_LDLIBS) -o $$@

endef
