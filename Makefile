VERILATOR ?= verilator
VFLAGS    ?= --cc --exe --build -j 0 -Wall -GN=2 -GP=7

.PHONY: default run-% clean

.PRECIOUS: obj_dir/V%

default: run-and_gate

run-%: obj_dir/V%
	@echo -e "\x1b[33m===== Running tests =====\x1b[0m"
	./$^

obj_dir/V%: rtl/%.v sim.cpp
	$(VERILATOR) $(VFLAGS) $^

clean:
	rm -rf obj_dir
