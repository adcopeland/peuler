ifeq ($(PROBLEM),)
$(error Must select a problem number and use PROBLEM=N to specify it)
endif

SOURCES:=$(wildcard src/p$(PROBLEM)/*cc)
TARGET:=build/p$(PROBLEM)

CXXFLAGS?=-Isrc/acommon -Isrc/p$(PROBLEM) -O3 -Wall -Werror -flto -pthread -std=c++17

all: $(TARGET)
	@echo Running $(TARGET)...
	@time -f "%e seconds  %U user cpu seconds  %M KB peak memory usage" $(TARGET)

$(TARGET): $(wildcard src/p$(PROBLEM)/*) | build
	$(CXX) $(CXXFLAGS) -o $@ $(SOURCES)

build:
	@mkdir -p build/cpp

clean:
	@rm -rf build
