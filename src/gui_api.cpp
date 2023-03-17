#include "solver.h"
#include "core.h"
#include <iostream>

int gen_chains_all_gui(const char** words, int len, char** result) {
    return gen_chains_all(words, len, result);
}

int gen_chain_word_gui(const char** words, int len, char** result, char head, char tail, char skip, bool enable_loop) {
    return gen_chain_word(words, len, result, head, tail, skip, enable_loop);
}

int gen_chain_char_gui(const char** words, int len, char** result, char head, char tail, char skip, bool enable_loop) {
    return gen_chain_char(words, len, result, head, tail, skip, enable_loop);
}