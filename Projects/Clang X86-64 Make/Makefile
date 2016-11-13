PROGRAM_NAME = maxGif
CODE_DIRECTORY = ../../Code/TranslationUnits
CXX_SRCS = \
	$(CODE_DIRECTORY)/EntryPoint.cpp
CXX_OBJS = $(CXX_SRCS:.cpp=.o)

INCLUDE_PATHS = \
	$(CODE_DIRECTORY)/../Include \
	$(CODE_DIRECTOY)/../../Dependencies/max/Code/Include
INCLUDE_PATHS_FLAGS = $(foreach d, $(INCLUDE_PATHS), -I$d)

LIBRARY_PATHS = \
	.
LIBRARY_PATHS_FLAGS = $(foreach d, $(LIBRARY_PATHS), -L$d)

AUTOMATED_TEST_CODE_DIRECTORY = ../../Code/AutomatedTests
AUTOMATED_TEST_CXX_SRCS = \
	$(AUTOMATED_TEST_CODE_DIRECTORY)/HeaderBlockTokenTest.cpp
AUTOMATED_TEST_CXX_OBJS = $(AUTOMATED_TEST_CXX_SRCS:.cpp=.o)

CPPFLAGS += $(INCLUDE_PATHS_FLAGS) -std=c++14 -Werror -Wall -Wextra -Wpedantic -Wconversion -Wsign-conversion -m64
LINKER_FLAGS += $(LIBRARY_PATHS_FLAGS)




all: lib$(PROGRAM_NAME).a maxAutomatedTests maxManualTests

lib$(PROGRAM_NAME).a: $(PCH_OBJS) $(CXX_OBJS)
	ar rcs lib$(PROGRAM_NAME).a $(CXX_OBJS)

maxAutomatedTests: $(AUTOMATED_TEST_CXX_OBJS)
	clang++ -g $(AUTOMATED_TEST_CXX_OBJS) $(LINKER_FLAGS) -l$(PROGRAM_NAME) -o maxAutomatedTests

.cpp.o:
	clang++ -g $(CPPFLAGS) -c $< -o $@

clean:
	@- $(RM) lib$(PROGRAM_NAME).a
	@- $(RM) $(CXX_OBJS)
	@- $(RM) maxAutomatedTests
	@- $(RM) $(AUTOMATED_TEST_CXX_OBJS)

distclean: clean
