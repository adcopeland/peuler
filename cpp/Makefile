ifeq ($(PROBLEM),)
$(error Must select a problem number and use PROBLEM=N to specify it)
endif

SOURCES:=$(wildcard src/p$(PROBLEM)/*cc)
TARGET:=build/p$(PROBLEM)

all: $(TARGET)
	@echo Running $(TARGET)...
	@time -f "%E seconds" $(TARGET)

$(TARGET): $(wildcard src/p$(PROBLEM)/*) | build
	g++ -I src/acommon -I src/p$(PROBLEM) -O3 -Wall -Werror -flto -pthread -std=c++17 -o $@ $(SOURCES)

build:
	@mkdir -p build/cpp
