#define CORE_DLL
#include "solver.h"
#include "core.h"
#include <iostream>


// -w -h -t -j -r
int gen_chain_word(const char* words[], int len, char* results[], char head, char tail, char skip, bool enable_loop) {
    Solver solver = Solver(words, len, false);
    int ans = solver.get_max_word(results, head, tail, skip, enable_loop);
    return ans;
}

// -n
int gen_chains_all(const char* words[], int len, char* results[]) {
    Solver solver = Solver(words, len, false);
    int ans = solver.get_all(results);
    return ans;
}

// -c -h -t -j -r
int gen_chain_char(const char* words[], int len, char* results[], char head, char tail, char skip, bool enable_loop) {
    Solver solver = Solver(words, len, true);
    int ans = solver.get_max_char(results, head, tail, skip, enable_loop);
    return ans;
}