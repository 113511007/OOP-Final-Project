# ompiler & Linker settings 
CXX = g++
CXXFLAGS = -I ./inc -I ./main_function -I ./third-party/CImg -I ./third-party/libjpeg -I ./Data-Loader -std=c++11
OPTFLAGS = -march=native -flto -funroll-loops -finline-functions -ffast-math -O3
WARNINGS = -g -Wall
LINKER = -L/usr/X11R6/lib -lm -lpthread -lX11 -L./third-party/libjpeg -ljpeg -lpng

# Valgrind for memory issue
CHECKCC = valgrind
CHECKFLAGS = --leak-check=full -s --show-leak-kinds=all --track-origins=yes 

# Source files and object files
SRCDIR = src
MAIN_FUNCTION_SRCDIR = main_function
OBJDIR = obj
INCDIR = inc
MAIN_SRCS = $(wildcard $(MAIN_FUNCTION_SRCDIR)/*.cpp)
CORE_SRCS = $(wildcard $(SRCDIR)/*.cpp)
SRCS = $(MAIN_SRCS) $(CORE_SRCS)
OBJS = $(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(CORE_SRCS)) \
       $(patsubst $(MAIN_FUNCTION_SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(MAIN_SRCS))
DEPS = $(OBJS:.o=.d)

# Control the build verbosity
ifeq ("$(VERBOSE)","1")
    Q :=
    VECHO = @true
else
    Q := @
    VECHO = @printf
endif

.PHONY: all install check clean

# Name of the executable
TARGET = Image_Processing Data_Loader_Example

all: $(TARGET)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

Image_Processing: main.cpp $(OBJS) $(OBJDIR)/data_loader.o
	$(VECHO) "	LD\t$@\n"
	$(Q)$(CXX) $(WARNINGS) $(CXXFLAGS) $(OPTFLAGS) $^ -o $@ $(LINKER)

Data_Loader_Example: data_loader_demo.cpp $(OBJDIR)/data_loader.o
	$(VECHO) "	LD\t$@\n"
	$(Q)$(CXX) $(WARNINGS) $(CXXFLAGS) $(OPTFLAGS) $^ -o $@ $(LINKER)

# Include generated dependency files
-include $(DEPS)

# Compilation rule for object files with automatic dependency generation
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $(OBJDIR) Makefile
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CXX) $(WARNINGS) $(CXXFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

$(OBJDIR)/%.o: $(MAIN_FUNCTION_SRCDIR)/%.cpp | $(OBJDIR) Makefile
	$(VECHO) "  CC\t$@\n"
	$(Q)$(CXX) $(WARNINGS) $(CXXFLAGS) $(OPTFLAGS) -MMD -c $< -o $@

# Compilation rule for data_loader.o with explicit dependencies
$(OBJDIR)/data_loader.o: ./Data-Loader/data_loader.cpp ./Data-Loader/data_loader.h | $(OBJDIR) Makefile
	$(VECHO) "	CC\t$@\n"
	$(Q)$(CXX) $(WARNINGS) $(CXXFLAGS) $(OPTFLAGS) -MMD -c $< -o $@



install:
	$(VECHO) "Installing third party dependencies\n"
	$(Q)chmod +x scripts/clone_env.sh  
	$(Q)./scripts/clone_env.sh  > /dev/null 2>&1
	$(VECHO) "Finished installing third party dependencies!!\n"

check:
	$(CHECKCC) $(CHECKFLAGS) ./Image_Processing

clean:
	rm -rf $(OBJDIR) $(TARGET)