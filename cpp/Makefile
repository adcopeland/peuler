ifeq ($(PROBLEM),)
$(error Must select a problem number and use PROBLEM=N to specify it)
endif

SOURCES:=$(wildcard src/p$(PROBLEM)/*)
TARGET:=build/p$(PROBLEM)

all: $(TARGET)
	@echo Running $(TARGET)...
	@time -f "%E seconds" $(TARGET)

$(TARGET): $(SOURCES) | build
	g++ -O3 -Wall -Werror -flto -std=c++17 -o $@ $(SOURCES)

build:
	@mkdir -p build/cpp
