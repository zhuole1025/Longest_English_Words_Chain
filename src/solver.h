#include <string>
#include <cstring>
#include <stdexcept>
#include "graph.h"
#include <algorithm>

using namespace std;

class Solver {
    Graph *graph;
    vector<string> results_tmp;
    public:
    Solver(const char* words[], int len, bool weight) {
        graph = new Graph(words, len, weight);
    }

    int postprocess(vector<string> &results_tmp, char* results[]) {
        if (results_tmp.size() > 20000) {
            return -2;
            //throw logic_error("Too many results.");
        }
        for (int i = 0; i < results_tmp.size(); i++) {
            int len = results_tmp[i].size() + 1;
            results[i] = new char[len];
            strcpy_s(results[i], len, results_tmp[i].c_str());
        }
        return results_tmp.size();
    }

    int get_all(char* results[]) {
        if (graph->check_circle()) {
            return -1;
            //throw logic_error("There is a circle in the graph.");
        }
        int res = graph->get_all(results_tmp);
        sort(results_tmp.begin(), results_tmp.end());
        return postprocess(results_tmp, results);
    }

    int get_max_word(char* results[], char head, char tail, char skip, bool loop) {
        if (loop == false) {
            if (graph->check_circle()) {
                return -1;
                //throw logic_error("There is a circle in the graph.");
            }
        }
        int res = graph->get_max_word(results_tmp, head, tail, skip, loop);
        
        return postprocess(results_tmp, results);
    }

    int get_max_char(char* results[], char head, char tail, char skip, bool loop) {
        if (loop == false) {
            if (graph->check_circle()) {
                return -1;
                //throw logic_error("There is a circle in the graph.");
            }
        }
        int res = graph->get_max_word(results_tmp, head, tail, skip, loop);
        
        return postprocess(results_tmp, results);
    }
};
