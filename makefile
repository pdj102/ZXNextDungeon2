# Make file for ZX Spectrum Next Dungeon II project

# This makefile is designed to be used with the z88dk toolchain.
# It assumes you have zcc and related tools installed and available in your PATH.
# Adjust paths and flags as necessary for your environment.
# To build the project, simply run `make` in the terminal.
# To clean the build files, run `make clean`.
# Copy the resulting .NEX file to your ZX Spectrum Next SD card or emulator.

# A few notes on Makefiles:
# - Lines starting with '#' are comments.
# - Variables are defined using '=' and can be referenced using $(VAR_NAME).
# - Targets are defined with a colon ':' and can have dependencies (target:depedency).
# - The default target is the first one defined in the file.
# - The 'clean' target is a common convention to remove generated files.
# - The 'all' target is a common convention to build all necessary files.
# - Use tabs (not spaces) for indentation in command lines.
# - $@ is the target name, $< is the first dependency, and $^ is all dependencies.
# - Use 'make -jN' to run N jobs in parallel (where N is a number) to speed up the build process.
# - Use 'make -n' to see what commands would be executed without actually running them.


# Set variables

# Target - zcc compiler target platform 
TARGET=+zxn

# Verbosity - verbose off (-vn) or on (-v)
VERBOSE=-vn

# CRT - C runtime to use - 31 = no stdin, stout, stderr streams setup
CRT=31

# Pragma file - file containing pragmas for zcc
PRAGMAS=pragmas.inc

# C Optimisation Flags for zcc
 C_OPT_FLAGS=-SO3 --max-allocs-per-node200000

# Set program executable name
PROGRAM=dungeon2.nex

# Set any C preprocessor defines here (e.g., -DDEBUG)
# DDEBUG - Enable debug information
# DDEBUG_ERROR - Enable debug error information
DEFINES=-DDEBUG_INFO -DDEBUG_ERROR


# Set source and build directories
SRCDIR=./src
BINDIR=./bin
OBJDIR=./obj

# Set C files
# Add other source file directories as needed
CFILES=$(wildcard $(SRCDIR)/*.c) \
	   $(wildcard $(SRCDIR)/core/*.c) \
	   $(wildcard $(SRCDIR)/core/PAGE0/*.c) \
	   $(wildcard $(SRCDIR)/core/PAGE1/*.c) \
	   $(wildcard $(SRCDIR)/ecs/*.c) \
	   $(wildcard $(SRCDIR)/ecs/PAGE30/*.c) \
	   $(wildcard $(SRCDIR)/ecs/PAGE32/*.c) \
	   $(wildcard $(SRCDIR)/game/*.c) \
	   $(wildcard $(SRCDIR)/game/PAGE34/*.c)

# Set assembly files 
# Add other source file directories as needed
# Note don't use the same file name for both C and ASM files
AFILES=$(wildcard $(SRCDIR)/core/*.asm) \
	   $(wildcard $(SRCDIR)/core/PAGE1/*.asm)

# Set object files
# Convert source file names to object file names
OFILES=$(patsubst $(SRCDIR)/%.c,$(OBJDIR)/%.o,$(CFILES)) \
	   $(patsubst $(SRCDIR)/%.asm,$(OBJDIR)/%.o,$(AFILES))


# Set standard Makefile variables

# AS - Program for compiling assembly files; default 'as'
AS=zcc

# CC - C Compiler
CC=zcc

# ASFLAGS - Flags for the assembler
# Used to create object files from assembly source files
# Note: there is no linking at this stage of the build
# $(TARGET) specifies the target platform (zxn)
# $(VERBOSITY) specifies verbosity level
# $(C_OPT_FLAGS) specifies optimization flags
# -c flag is used to compile only, without linking
# -compiler=sdcc tells zcc to use sdcc to compile the assembly code
# -pragma-include:$(PRAGMAS) tells zcc to include the pragmas
ASFLAGS=$(TARGET) $(VERBOSITY) $(C_OPT_FLAGS) -c -compiler=sdcc -pragma-include:$(PRAGMAS)

# CFLAGS - Flags for the C compiler
# Used to create object files from C source files
# Note: there is no linking at this stage of the build
# $(TARGET) specifies the target platform (zxn)
# $(VERBOSITY) specifies verbosity level
# $(C_OPT_FLAGS) specifies optimization flags
# -c flag is used to compile only, without linking
# -compiler=sdcc tells zcc to use sdcc to compile the C code
# -clib=sdcc_iy tells zcc to use the sdcc_iy C library
# -pragma-include:$(PRAGMAS) tells zcc to include the pragmas
# $(DEFINES) includes any preprocessor definitions
CFLAGS=$(TARGET) $(VERBOSITY) $(C_OPT_FLAGS) -c -compiler=sdcc -pragma-include:$(PRAGMAS) $(DEFINES)

# LDFLAGS - Flags for the linker, sucj as -L [Libraries (-lfoo) should be added to LDLIBS]
# Used to link object files into the final executable
# $(TARGET) specifies the target platform (zxn)
# $(VERBOSITY) specifies verbosity level
# -startup=$(CRT) specifies the C runtime to use
# -clib=sdcc_iy tells zcc to use the sdcc_iy C library
# -pragma-include:$(PRAGMAS) tells zcc to include the pragmas
# -create-app tells zcc to create an application
# -subtype=nex specifies the subtype as nex for ZX Spectrum Next
LDFLAGS=$(TARGET) $(VERBOSITY) -startup=$(CRT) -clib=sdcc_iy -pragma-include:$(PRAGMAS) -create-app -subtype=nex

# LDLIBS - Libraries to link against, such as -lfoo
LDLIBS=

# Function: bankflags_for <target>
# Extracts the PAGE## part from a path and builds the bank flags
# Usage: $(call bankflags_for,<file_path>)
# Example: $(call bankflags_for,src/init_page1/startup.asm) -> --codesegPAGE_1 --constsegPAGE_1
# Note: This function assumes that the PAGE## directory is directly under the src directory


bankflags_for = $(strip \
$(patsubst PAGE%,--codesegPAGE_%, \
$(notdir $(word 1,$(filter PAGE%,$(subst /, ,$(dir $(1)))))) \
) \
$(patsubst PAGE%,--constsegPAGE_%, \
$(notdir $(word 1,$(filter PAGE%,$(subst /, ,$(dir $(1)))))) \
) \
)

# Make targets and rules

# Rule to build all
# Default target is 'all'
all: $(PROGRAM)

# Create build directories if they don't exist
# Add other directories as needed	
$(OBJDIR):
	mkdir $(OBJDIR)

$(BINDIR):
	mkdir $(BINDIR)

# Rule to clean build files
# Deletes all object files and the final executable
clean:
	del /s .\obj\*.o 
	del .\bin\$(PROGRAM)
	@echo "Clean complete"


# Rule to test bankflags function
test_bankflags:
	@echo "Testing bankflags function"
	@echo "File: src/init_page1/startup.asm -> Flags: $(call bankflags_for,src/init_page1/startup.asm)"
	@echo "File: src/tile_defs_data.asm -> Flags: $(call bankflags_for,src/tile_defs_data.asm)"
	@echo "File: src/text.c -> Flags: $(call bankflags_for,src/text.c)"
	@echo "File: src/PAGE01/somefile.asm -> Flags: $(call bankflags_for,src/PAGE01/somefile.asm)"
	@echo "File: src/PAGE1/somefile.asm -> Flags: $(call bankflags_for,src/PAGE1/somefile.asm)"
	@echo "Test complete"

# Rule to build object files from C source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $(call bankflags_for,$@) $< -o $@
	@echo "Compiled C: $< -> $@"

# Rule to build object files from assembly source files
$(OBJDIR)/%.o: $(SRCDIR)/%.asm
	$(AS) $(ASFLAGS) $(call bankflags_for,$@) $< -o $@
	@echo "Assembled ASM: $< -> $@"

# Rule to build the program
$(PROGRAM): $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) $(LDLIBS) -o $(BINDIR)/$(PROGRAM)
	@echo "Build complete: $(BINDIR)/$(PROGRAM)"
