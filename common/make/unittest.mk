##
# Unit Test Template
#
# Params:
# 1 - Target name. Used to uniquely identify all variables.
# 2 - Sources
# 3 - Include paths
# 4 - C flags
# 5 - CPP flags
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
$(1)_BUILD_DIR = $$(COMMON_BUILD_DIR)/$(1)
$(1)_OUTPUT_DIR = $$(COMMON_OUTPUT_DIR)/$(1)

# Build Flags #
$(1)_CFLAGS = $$(COMMON_UT_CFLAGS) $(4)
$(1)_CPPFLAGS = $$(COMMON_UT_CPPFLAGS) $(5)
$(1)_LDFLAGS = $$(COMMON_UT_LDFLAGS) $(6)
$(1)_LDLIBS = $$(COMMON_UT_LDLIBS) $(7)

# Source Files #
$(1)_SOURCES = $(2)
$(1)_OBJECTS = $$(addprefix $$($(1)_BUILD_DIR)/,$$(notdir $$(addsuffix .o,$$(basename $$($(1)_SOURCES)))))

# Include Paths #
$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $(3)
$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$($(1)_INCLUDES))

# Output Files #
$(1)_OUT = $$($(1)_OUTPUT_DIR)/$(1)

# Set VPATH #
VPATH += $(THIRDPARTY_DIR)/unity/src

### Targets ###

# Build Rule #
.PHONY: $(1)_build
$(1)_build: $$($(1)_OUT)

# Run Rule #
.PHONY: $(1)_run
$(1)_run: $(1)_build
	@$$($(1)_OUT)

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

# Common Mocks #
$$($(1)_BUILD_DIR)/%.o: $$(COMMON_MOCKS_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(COMMON_MOCKS_DIR)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common Stubs #
$$($(1)_BUILD_DIR)/%.o: $$(COMMON_STUBS_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(COMMON_STUBS_DIR)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common Tests #
$$($(1)_BUILD_DIR)/%.o: $$(COMMON_TESTS_DIR)/%.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: $$(COMMON_TESTS_DIR)/%.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# General Sources #
$$($(1)_BUILD_DIR)/%.o: %.c | $$($(1)_BUILD_DIR)
	$$(CC) $$($(1)_CFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$($(1)_BUILD_DIR)/%.o: %.cpp | $$($(1)_BUILD_DIR)
	$$(CXX) $$($(1)_CPPFLAGS) $$($(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Link Target #
$$($(1)_OUT): $$($(1)_OBJECTS) | $$($(1)_OUTPUT_DIR)
	$$(CXX) $$($(1)_LDFLAGS) $$^ $$($(1)_LDLIBS) -o $$@

endef
