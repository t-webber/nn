#include "Vand_gate.h"
#include "verilated.h"
#include <cassert>

int main(int argc, char **argv) {
        VerilatedContext *contextp = new VerilatedContext;
        contextp->commandArgs(argc, argv);

        Vand_gate *dut = new Vand_gate{contextp};

        dut->a = 0;
        dut->b = 0;
        dut->eval();
        assert(dut->c == 0);

        dut->a = 1;
        dut->b = 0;
        dut->eval();
        assert(dut->c == 0);

        dut->a = 0;
        dut->b = 1;
        dut->eval();
        assert(dut->c == 0);

        dut->a = 1;
        dut->b = 1;
        dut->eval();
        assert(dut->c == 1);

        delete dut;
        delete contextp;
        return 0;
}
