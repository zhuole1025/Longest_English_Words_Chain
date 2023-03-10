#include "solver.h"
#include "core.h"

int postporcess(char* result[], int len, char* results[]) {
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (result[i] != NULL) {
            results[pos++] = result[i];
        }
    }
    return pos;
}

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char skip, bool enable_loop) {
    Solver solver = Solver(words, len);
    int ans = solver.get_max_word();
    return ans;
}

// -w -h -t -j -r
int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, char jinz, bool enable_loop)
{
    Solver solver = Solver(words, len, result);
    int ans = solver.get_max_word();
    return ans;
}

int gen_chains_all(const char* words[], int len, char* result[]) {
    Solver solver = Solver(words, len, result);
    int ans = solver.get_all();
    return ans;
}

int gen_chain_word_unique(const char* words[], int len, char* result[]) {
    Solver solver = Solver(words, len, result);
    int ans = solver.get_unique_word();
    return ans;
}

// -c -h -t -j -r
int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, char jinz, bool enable_loop)
{
    Solver solver = Solver(words, len, result);
    int ans = solver.get_max_char();
    return ans;
}

int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    Solver solver = Solver(words, len, result);
    int ans = solver.get_max_char();
    return ans;
}