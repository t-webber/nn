#include "Vneuron_layer.h"
#include "verilated.h"
#include <cassert>
#include <iostream>

template <typename T, typename U, typename... Args>
void test(const T &a, const U &b, Args... args) {
        if (a == b) return;
        std::cerr << "\x1b[31mAssert failed:\x1b[0m " << a << " != " << b << " (";
        ((std::cerr << args << " "), ...);
        std::cerr << ")" << "\n";
        std::abort();
}

int main(int argc, char **argv) {
        VerilatedContext contextp;
        contextp.commandArgs(argc, argv);

        Vneuron_layer nl(&contextp);

        size_t p = nl.A.size();
        size_t n = nl.W.size();

        std::cout << n << " " << p << std::endl;

        for (SData i = 0; i < n; ++i) {
                for (SData j = 0; j < p; ++j) nl.W[i][j] = (SData)(((i + j) * (i + j)) / 2);
                nl.A[i] = (SData)((i - 1) / 2);
                nl.B[i] = (SData)((i + 12) * 3 * i);
        }

        nl.eval();

        for (SData i = 0; i < 3; ++i) {
                int expected = nl.B[i];
                for (SData k = 0; k < 3; ++k) expected += nl.W[i][k] * nl.A[k];
                test(expected, nl.Y[i], i);
        }

        return 0;
}
