#include <string>
#include <stdexcept>
#include "graph.h"

class Solver {
    Graph *graph;
    vector<string> results_tmp;
    public:
    Solver(const char* words[], int len, bool weight) {
        graph = new Graph(words, len, weight);
    }

    int postprocess(vector<string> &results_tmp, char* results[]) {
        if (results_tmp.size() > 20000) {
            throw logic_error("Too many results.");
        }
        for (int i = 0; i < results_tmp.size(); i++) {
            results[i] = (char*)malloc(sizeof(char) * (results_tmp[i].size() + 1));
            strcpy_s(results[i], results_tmp.size()+1, results_tmp[i].c_str());
            //strcpy(results[i], results_tmp[i].c_str());
        }
        return results_tmp.size();
    }

    int get_all(char* results[]) {
        if (graph->check_circle()) {
            throw logic_error("There is a circle in the graph.");
        }
        int res = graph->get_all(results_tmp);
        
        return postprocess(results_tmp, results);
    }

    int get_max_word(char* results[], char head, char tail, char skip, bool loop) {
        if (loop == false) {
            if (graph->check_circle()) {
                throw logic_error("There is a circle in the graph.");
            }
        }
        int res = graph->get_max_word(results_tmp, head, tail, skip, loop);
        
        return postprocess(results_tmp, results);
    }

    int get_max_char(char* results[], char head, char tail, char skip, bool loop) {
        if (loop == false) {
            if (graph->check_circle()) {
                throw logic_error("There is a circle in the graph.");
            }
        }
        int res = graph->get_max_word(results_tmp, head, tail, skip, loop);
        
        return postprocess(results_tmp, results);
    }
};
