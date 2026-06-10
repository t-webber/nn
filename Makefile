VERILATOR ?= verilator
VFLAGS    ?= --cc --exe --build -j 0 -Wall -GN=7 -GP=2

RTL_FILES := $(wildcard rtl/*.v)

.PHONY: default run-% clean

.PRECIOUS: obj_dir/V%

default: run-neuron_layer

run-%: obj_dir/V%
	@echo -e "\x1b[33m===== Running tests =====\x1b[0m"
	./$^

obj_dir/V%: rtl/%.v sim.cpp
	@echo -e "\x1b[33m=====   Compiling   =====\x1b[0m"
	$(VERILATOR) $(VFLAGS) $^

clean:
	rm -rf obj_dir
