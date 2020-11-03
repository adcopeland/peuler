ifeq ($(PROBLEM),)
$(error Must select a problem number and use PROBLEM=N to specify it)
endif

SOURCES:=$(wildcard src/p$(PROBLEM)/*)
TARGET:=build/p$(PROBLEM)

all: $(TARGET)
	@echo Running $(TARGET)...
	@time -f "%e seconds  %U user cpu seconds  %M KB peak memory usage" $(TARGET)

$(TARGET): $(SOURCES)
	GOPATH=`pwd` go build -o $@ $(SOURCES)

