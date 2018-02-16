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
# UT_$(2)_$(1)_build - Build the test target
# UT_$(2)_$(1)_run - Execute the test target
# UT_$(2)_$(1)_clean - Clean all build and output files
#
define UT_tmpl

### Setup ###

# Directories #
UT_$(2)_$(1)_BUILD_DIR = $$(AVR_BUILD_DIR)/ut/$(2)/$(1)
UT_$(2)_$(1)_OUTPUT_DIR = $$(AVR_OUTPUT_DIR)/ut/$(2)/$(1)

# Build Flags #
UT_$(2)_$(1)_CFLAGS = $$(AVR_CFLAGS) $(5)
UT_$(2)_$(1)_CPPFLAGS = $$(AVR_CPPFLAGS) $(6)
UT_$(2)_$(1)_LDFLAGS = $$(AVR_LDFLAGS) $(7)
UT_$(2)_$(1)_LDLIBS = $$(AVR_LDLIBS) $(8)

# Source Files #
UT_$(2)_$(1)_SOURCES = $(3)
UT_$(2)_$(1)_OBJECTS = $$(addprefix $$(UT_$(2)_$(1)_BUILD_DIR)/,$$(notdir $$(addsuffix .o,$$(basename $$(UT_$(2)_$(1)_SOURCES)))))

# Include Paths #
UT_$(2)_$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $$(AVR_INCLUDE_DIR) $(4)
UT_$(2)_$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$(UT_$(2)_$(1)_INCLUDES))

# Output Files #
UT_$(2)_$(1)_EXE = $$(UT_$(2)_$(1)_OUTPUT_DIR)/$(1)

# Set VPATH #
VPATH += $(THIRDPARTY_DIR)/unity/src

### Targets ###

ALL_UTS += ut_$(2)_$(1)

# Build Rule #
.PHONY: ut_$(2)_$(1)_build
ut_$(2)_$(1)_build: $$(UT_$(2)_$(1)_EXE)

# Run Rule #
.PHONY: ut_$(2)_$(1)_run
ut_$(2)_$(1)_run: ut_$(2)_$(1)_build
	@$$(UT_$(2)_$(1)_EXE)

# Clean Rule #
.PHONY: ut_$(2)_$(1)_clean
ut_$(2)_$(1)_clean:
	$$(RMDIR) $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(RMDIR) $$(UT_$(2)_$(1)_OUTPUT_DIR)

### Build Recipes ###

# Build Dependencies #
-include $$(UT_$(2)_$(1)_OBJECTS:.o=.d)

# Build Directory #
$$(UT_$(2)_$(1)_BUILD_DIR):
	@$$(MKDIR) $$@

# Output Directory #
$$(UT_$(2)_$(1)_OUTPUT_DIR):
	@$$(MKDIR) $$@

# Common Sources #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common AVR Sources #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Sources #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Mocks #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Stubs #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CPPFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Tests #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CPPFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# General Sources #
$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: %.c | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CC) $$(UT_$(2)_$(1)_CFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(UT_$(2)_$(1)_BUILD_DIR)/%.o: %.cpp | $$(UT_$(2)_$(1)_BUILD_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_CPPFLAGS) $$(UT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Link Target #
$$(UT_$(2)_$(1)_EXE): $$(UT_$(2)_$(1)_OBJECTS) | $$(UT_$(2)_$(1)_OUTPUT_DIR)
	$$(CXX) $$(UT_$(2)_$(1)_LDFLAGS) $$^ $$(UT_$(2)_$(1)_LDLIBS) -o $$@

endef
