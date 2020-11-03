ifeq ($(PROBLEM),)
$(error Must select a problem number and use PROBLEM=N to specify it)
endif

TARGET:=peuler/target/release/p$(PROBLEM)

all: $(TARGET)
	@echo Running $(TARGET)...
	@time -f "%e seconds  %U user cpu seconds  %M KB peak memory usage" $(TARGET)

.PHONY: $(TARGET)
$(TARGET):
	@cd peuler && cargo build --release --bin p$(PROBLEM)
