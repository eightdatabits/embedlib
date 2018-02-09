##
# Unit Test Template
#
# Params:
# 1 - Target name. Used to uniquely identify all variables.
# 2 - Family. Used to uniquely identify path to source files.
# 3 - Sources
# 4 - Include paths
# 5 - C flags
# 6 - CPP flags
# 7 - Linker flags
# 8 - Linker libs
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
$(1)_OUTPUT_DIR = $$(AVR_OUTPUT_DIR)/$(1)

# Build Flags #
$(1)_CFLAGS = $$(AVR_CFLAGS) $(5)
$(1)_CPPFLAGS = $$(AVR_CPPFLAGS) $(6)
$(1)_LDFLAGS = $$(AVR_LDFLAGS) $(7)
$(1)_LDLIBS = $$(AVR_LDLIBS) $(8)

# Source Files #
$(1)_SOURCES = $(3)
$(1)_OBJECTS = $$(addprefix $$($(1)_BUILD_DIR)/,$$(notdir $$(addsuffix .o,$$(basename $$($(1)_SOURCES)))))

# Include Paths #
$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $$(AVR_INCLUDE_DIR) $(4)
$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$($(1)_INCLUDES))

# Output Files #
$(1)_EXE = $$($(1)_OUTPUT_DIR)/$(1)

# Set VPATH #
VPATH += $(THIRDPARTY_DIR)/unity/src

### Targets ###

# Build Rule #
.PHONY: $(1)_build
$(1)_build: $$($(1)_EXE)

# Run Rule #
.PHONY: $(1)_run
$(1)_run: $(1)_build
	@$$($(1)_EXE)

# Clean Rule #
.PHONY: $(1)_clean
$(1)_clean:
	$$(RMDIR) $$($(1)_BUILD_DIR)
	$$(RMDIR) $$($(1)_OUTPUT_DIR)

### Build Recipes ###

# Build Dependencies #
-include $$($(1)_OBJECTS:.o=.d)

# Build Directory #
$$($(1)_BUILD_DIR):
	@$$(MKDIR) $$@

# Output Directory #
$$($(1)_OUTPUT_DIR):
	@$$(MKDIR) $$@

# Common Sources #
$$($(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common AVR Sources #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Sources #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Mocks #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Stubs #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Tests #
$$($(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# General Sources #
$$($(1)_BUILD_DIR)/%.o: %.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: %.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Link Target #
$$($(1)_EXE): $$($(1)_OBJECTS) | $$($(1)_OUTPUT_DIR)
	$$(CXX) $$($(1)_LDFLAGS) $$^ $$($(1)_LDLIBS) -o $$@

endef
