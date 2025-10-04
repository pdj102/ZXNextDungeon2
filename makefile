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
CFILES=$(wildcard $(SRCDIR)/*.c)

# Set assembly files 
# Add other source file directories as needed
# Note don't use the same file name for both C and ASM files
AFILES=$(wildcard $(SRCDIR)/*.asm)

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



# Make targets
# Default target
# Rule to build all
all: $(PROGRAM)

# Rule to clean build files
# Add other directories as needed
clean:
	del $(OBJDIR)/*.o $(BINDIR)/$(PROGRAM)
	@echo "Clean complete"

# Rule to build object files from C source files
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) $< -o $@
	@echo "Compiled C: $< -> $@"

# Rule to build the program
$(PROGRAM): $(OFILES)
	$(CC) $(LDFLAGS) $(OFILES) $(LDLIBS) -o $(BINDIR)/$(PROGRAM)
	@echo "Build complete: $(BINDIR)/$(PROGRAM)"
