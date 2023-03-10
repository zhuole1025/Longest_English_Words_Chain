#include "graph.h"

class Solver {
    Graph graph;
    vector<string> results_tmp;
    public:
    Solver(const char* words[], int len, bool weight) {
        graph = Graph(words, len, weight);
    }

    void postprocess(vector<string> &results_tmp, char* results[]) {
        for (int i = 0; i < results_tmp.size(); i++) {
            results[i] = (char*)malloc(sizeof(char) * (results_tmp[i].size() + 1));
            strcpy(results[i], results_tmp[i].c_str());
        }
    }

    int get_all(char* results[]) {
        int res = graph.get_all(results_tmp);
        postprocess(results_tmp, results);
        return res;
    }

    int get_max_word(char* results[], char head, char tail, bool loop) {
        int res = graph.get_max_word(results_tmp, head, tail, loop);
        postprocess(results_tmp, results);
        return res;
    }

    int get_max_char(char* results[], char head, char tail, bool loop) {
        int res = graph.get_max_word(results_tmp, head, tail, loop);
        postprocess(results_tmp, results);
        return res;
    }
};
