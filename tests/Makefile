DEBUG=0
CXXFLAGS=-std=c++17 -Wall -Wextra -Wshadow -Wconversion -Wpedantic -Werror -Wno-deprecated-declarations -I../include  -mmacosx-version-min=13.0
LDFLAGS=-framework Cocoa -framework CoreVideo -framework Metal
SOURCES=main.cpp appkit.hpp corefoundation.cpp coregraphics.cpp corevideo.cpp dispatch.cpp foundation.cpp metal.cpp objc.cpp quartzcore.cpp
BASE_NAMES=$(basename $(SOURCES))
OBJECTS=$(BASE_NAMES:=.o)
DEPENDENCIES=$(OBJECTS:.o=.d)
EXECUTABLE=tests

all: $(EXECUTABLE)
ifeq ($(DEBUG),1)
all: CXXFLAGS+=-DDEBUG -g
else
all: CXXFLAGS+=-O3
all: LDFLAGS+=-O3
endif

$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(OBJECTS) $(LDFLAGS) -o $@ -fprofile-arcs -ftest-coverage

-include $(DEPENDENCIES)

%.o: %.cpp
	$(CXX) -c $(CXXFLAGS) -MMD -MP $< -o $@ -fprofile-arcs -ftest-coverage

.PHONY: clean
clean:
ifeq ($(OS),Windows_NT)
	-del /f /q "$(EXECUTABLE).exe" $(OBJECTS) *.gcda *.gcno
else
	$(RM) $(EXECUTABLE) $(OBJECTS) $(EXECUTABLE).exe $(DEPENDENCIES) *.gcda *.gcno
endif