##
# Library Template
#
# Params:
# 1 - Target name. Used to uniquely identify all variables.
# 2 - Family. Used to uniquely identify path to source files.
# 3 - Sources
# 4 - Include paths
# 5 - C flags
# 6 - CPP flags
# 7 - Archive flags
# 8 - Objdump flags
#
# Output Targets:
# $(1)_build - Build the library
# $(1)_clean - Clean all build and output files
#
define LIB_tmpl

### Setup ###

# Directories #
LIB_$(1)_BUILD_DIR = $$(AVR_BUILD_DIR)/$(1)
LIB_$(1)_OUTPUT_DIR = $$(AVR_OUTPUT_DIR)/$(1)

# Build Flags #
LIB_$(1)_CFLAGS = $$(AVR_LIB_CFLAGS) $(5)
LIB_$(1)_CPPFLAGS = $$(AVR_LIB_CPPFLAGS) $(6)
LIB_$(1)_ARFLAGS = $$(AVR_LIB_ARFLAGS) $(7)
LIB_$(1)_OBJDUMPFLAGS = $$(AVR_LIB_OBJDUMPFLAGS) $(8)

# Source Files #
LIB_$(1)_SOURCES = $(3)
LIB_$(1)_OBJECTS = $$(addprefix $$(LIB_$(1)_BUILD_DIR)/,$$(notdir $$(addsuffix .o,$$(basename $$(LIB_$(1)_SOURCES)))))

# Include Paths #
LIB_$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $$(AVR_INCLUDE_DIR) $(4)
LIB_$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$(LIB_$(1)_INCLUDES))

# Output Files #
LIB_$(1)_LST = $$(LIB_$(1)_OUTPUT_DIR)/junkhal-$(1).lst
LIB_$(1)_A = $$(LIB_$(1)_OUTPUT_DIR)/junkhal-$(1).a

### Targets ###

ALL_LIBS += lib_$(1)

# Build Rule #
.PHONY: lib_$(1)_build
lib_$(1)_build: $$(LIB_$(1)_A)

# Clean Rule #
.PHONY: lib_$(1)_clean
lib_$(1)_clean:
	$$(RMDIR) $$(LIB_$(1)_BUILD_DIR)
	$$(RMDIR) $$(LIB_$(1)_OUTPUT_DIR)

### Build Recipes ###

# Build Dependencies #
-include $$(LIB_$(1)_OBJECTS:.o=.d)

# Build Directory #
$$(LIB_$(1)_BUILD_DIR):
	@$$(MKDIR) $$@

# Output Directory #
$$(LIB_$(1)_OUTPUT_DIR):
	@$$(MKDIR) $$@

# Common Sources #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common AVR Sources #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Sources #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Mocks #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Stubs #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Tests #
$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# General Sources #
$$(LIB_$(1)_BUILD_DIR)/%.o: %.c | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(LIB_$(1)_BUILD_DIR)/%.o: %.cpp | $$(LIB_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(LIB_$(1)_CPPFLAGS) $$(LIB_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Link Target #
$$(LIB_$(1)_A): $$(LIB_$(1)_OBJECTS) | $$(LIB_$(1)_OUTPUT_DIR)
	$$(AVR_AR) $$(LIB_$(1)_ARFLAGS) -rc $$@ $$^
	$$(AVR_OBJDUMP) $$(LIB_$(1)_OBJDUMPFLAGS) -h -S $$@ > $$(LIB_$(1)_LST)

endef
