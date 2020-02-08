ifeq ($(LANGUAGE),)
  $(error LANGUAGE must be defined)
endif

ifeq ($(PROBLEM),)
  $(error PROBLEM must be defined)
endif

all: problem_data
	make -C $(LANGUAGE) PROBLEM=$(PROBLEM)


# Rest of the file sets up potential problem data dependencies
.PHONY: problem_data
problem_data:

ifeq ($(PROBLEM),22)
  problem_data: data/p022_names.txt
  data/p022_names.txt:
		@echo "Downloading p022_names.txt for problem 22"
		@mkdir -p $(dir $@)
		wget https://projecteuler.net/project/resources/p022_names.txt -O $@
endif
