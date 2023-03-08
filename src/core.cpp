#include "solver.h"

int postporcess(char* result[], int len, char* results[]) {
    int pos = 0;
    for (int i = 0; i < len; i++) {
        if (result[i] != NULL) {
            results[pos++] = result[i];
        }
    }
    return pos;
}

int gen_chain_word(const char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    Solver solver = Solver(words, len);
    auto result = solver.get_max_word();
    return postporcess(result);
}

int gen_chains_all(const char* words[], int len, char* result[]) {
    Solver solver = Solver(words, len);
    auto result = solver.get_all();
    return result;
}

int gen_chain_word_unique(const char* words[], int len, char* result[]) {
    Solver solver = Solver(words, len);
    auto result = solver.get_unique_word();
    return result;
}

int gen_chain_char(const char* words[], int len, char* result[], char head, char tail, bool enable_loop) {
    Solver solver = Solver(words, len);
    auto result = solver.get_max_char();
    return result;
}