#include "graph.h"

class Solver {
    Graph graph;
    public:

    Solver(const char* words[], int len, char* results[]) {
        graph = Graph(words, len);
    }

    int get_all(char* results[]) {
        graph.get_all(results);
    }

    int get_max_word(char* results[]) {
        graph.get_max_word(results);
    }
};

int solve(const char* inputs[], char* results[], int type) {
    Graph graph = Graph(inputs, 1);
    if (type == 1) {
        graph.get_all(results);
    }
}