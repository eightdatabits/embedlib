##
# Func Test Template
#
# Params:
# 1 - Target name. Used to uniquely identify all variables.
# 2 - Family. Used to uniquely identify path to source files.
# 3 - MCU
# 4 - Sources
# 5 - Include paths
# 6 - C flags
# 7 - CPP flags
# 8 - Linker flags
# 9 - Linker libs
# 10 - Objcpy flags
# 11 - Programming flags
#
#
# Output Targets:
# FT_$(2)_$(1)_build - Build the functest target
# FT_$(2)_$(1)_flash - Flash the functest target
# FT_$(2)_$(1)_clean - Clean all build and output files
#
define FT_tmpl

### Setup ###

# Directories #
FT_$(2)_$(1)_BUILD_DIR = $$(AVR_BUILD_DIR)/ft/$(2)/$(1)
FT_$(2)_$(1)_OUTPUT_DIR = $$(AVR_OUTPUT_DIR)/ft/$(2)/$(1)

# Build Flags #
FT_$(2)_$(1)_CFLAGS = $$(AVR_FT_CFLAGS) $(6)
FT_$(2)_$(1)_CPPFLAGS = $$(AVR_FT_CPPFLAGS) $(7)
FT_$(2)_$(1)_LDFLAGS = $$(AVR_FT_LDFLAGS) -Wl,-Map,$$(FT_$(2)_$(1)_MAP) $(8)
FT_$(2)_$(1)_LDLIBS = $$(AVR_FT_LDLIBS) $(9)
FT_$(2)_$(1)_OBJCOPY_FLAGS = $$(AVR_FT_OBJCOPYFLAGS) $(10)
FT_$(2)_$(1)_PROG_FLAGS = $$(AVR_FT_PROGFLAGS) $(11)

# Source Files #
FT_$(2)_$(1)_SOURCES = $(4) $$(AVR_COMMON_DIR)/stdcpp.cpp
FT_$(2)_$(1)_OBJECTS = $$(addprefix $$(FT_$(2)_$(1)_BUILD_DIR)/,$$(notdir $$(addsuffix .o,$$(basename $$(FT_$(2)_$(1)_SOURCES)))))

# Include Paths #
FT_$(2)_$(1)_INCLUDES = $$(COMMON_INCLUDE_DIR) $$(AVR_INCLUDE_DIR) $(5)
FT_$(2)_$(1)_INCLUDE_FLAGS = $$(addprefix -I,$$(FT_$(2)_$(1)_INCLUDES))

# Output Files #
FT_$(2)_$(1)_ELF = $$(FT_$(2)_$(1)_BUILD_DIR)/$(1).elf
FT_$(2)_$(1)_HEX = $$(FT_$(2)_$(1)_OUTPUT_DIR)/$(1).hex
FT_$(2)_$(1)_MAP = $$(FT_$(2)_$(1)_OUTPUT_DIR)/$(1).map

# Set VPATH #
VPATH += $(THIRDPARTY_DIR)/unity/src

### Targets ###

ALL_FTS += ft_$(2)_$(1)

# Build Rule #
.PHONY: ft_$(2)_$(1)_build
ft_$(2)_$(1)_build: $$(FT_$(2)_$(1)_HEX)

# Flash Rule #
.PHONY: ft_$(2)_$(1)_run
ft_$(2)_$(1)_run: FT_$(2)_$(1)_build
	$$(AVR_PROG) $$(FT_$(2)_$(1)_PROG_FLAGS) -v -U flash:w:$$(FT_$(2)_$(1)_HEX)

# Clean Rule #
.PHONY: ft_$(2)_$(1)_clean
ft_$(2)_$(1)_clean:
	$$(RMDIR) $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(RMDIR) $$(FT_$(2)_$(1)_OUTPUT_DIR)

### Build Recipes ###

# Build Dependencies #
-include $$(FT_$(2)_$(1)_OBJECTS:.o=.d)

# Build Directory #
$$(FT_$(2)_$(1)_BUILD_DIR):
	@$$(MKDIR) $$@

# Output Directory #
$$(FT_$(2)_$(1)_OUTPUT_DIR):
	@$$(MKDIR) $$@

# Common Sources #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(COMMON_SOURCE_DIR)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Common AVR Sources #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_COMMON_DIR)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Sources #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_SOURCE_DIR)/$(2)/%.S | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Mocks #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_MOCKS_DIR)/$(2)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Stubs #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_STUBS_DIR)/$(2)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CPPFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Family Specific Tests #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: $$(AVR_TESTS_DIR)/$(2)/%.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CPPFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# General Sources #
$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: %.c | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CC) $$(FT_$(2)_$(1)_CFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

$$(FT_$(2)_$(1)_BUILD_DIR)/%.o: %.cpp | $$(FT_$(2)_$(1)_BUILD_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_CPPFLAGS) $$(FT_$(2)_$(1)_INCLUDE_FLAGS) -MD -c $$< -o $$@

# Elf Target #
$$(FT_$(2)_$(1)_ELF): $$(FT_$(2)_$(1)_OBJECTS) | $$(FT_$(2)_$(1)_OUTPUT_DIR)
	$$(AVR_CXX) $$(FT_$(2)_$(1)_LDFLAGS) $$^ $$(FT_$(2)_$(1)_LDLIBS) -o $$@

# Hex Target #
$$(FT_$(2)_$(1)_HEX): $$(FT_$(2)_$(1)_ELF)
	$$(AVR_OBJCOPY) $$(FT_$(2)_$(1)_OBJCOPY_FLAGS) $$(FT_$(2)_$(1)_ELF) $$@
endef
