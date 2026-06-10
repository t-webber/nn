#include "Vneuron_layer.h"
#include "verilated.h"
#include <cassert>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <ostream>

template <typename T, typename U, typename... Args>
void test(const T &expected, const U &computed, Args... args) {
        if (expected == computed) return;
        std::cerr << "\x1b[31mFAILED\x1b[0m: (expected) " << expected << " != " << computed
                  << " (computed) : ";
        ((std::cerr << args << " "), ...);
        std::cerr << "\n";
        std::abort();
}

static void check(Vneuron_layer *const nl, const char *const test_name) {
        std::cerr << "Test '" << test_name << "': " << std::flush;

        nl->eval();

        for (SData i = 0; i < nl->B.size(); ++i) {
                signed short expected = (signed short)nl->B[i];
                for (SData k = 0; k < nl->A.size(); ++k)
                        expected += (signed short)nl->W[i][k] * (signed short)nl->A[k];
                if (expected <= 0) expected = 0;
                test((signed short)expected, (signed short)nl->Y[i], i);
        }
        std::cerr << "\x1b[32mPASSED\x1b[0m" << std::endl;
}

int main(int argc, char **argv) {
        VerilatedContext contextp;
        contextp.commandArgs(argc, argv);

        Vneuron_layer nl(&contextp);

        size_t p = nl.A.size();
        size_t n = nl.W.size();

        for (SData i = 0; i < n; ++i) {
                for (SData j = 0; j < p; ++j) nl.W[i][j] = (SData)(((i + j) * (i + j)) / 2);
                nl.A[i] = (SData)((i - 1) / 2);
                nl.B[i] = (SData)((i + 12) * 3 * i);
        }

        check(&nl, "first");

        for (SData i = 0; i < n; ++i) {
                for (SData j = 0; j < p; ++j) nl.W[i][j] = (SData)(((i - j) * (j - i)) / 2);
                nl.A[i] = (SData)((i - 10) / 2);
                nl.B[i] = (SData)((i + 12) * 3 * i);
        }

        check(&nl, "second");

        return 0;
}
