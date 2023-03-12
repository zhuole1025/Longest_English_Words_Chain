#include <string>
#include <vector>

using namespace std;

class Word {
    public:
        string word;
        int len;
        int head;
        int tail;
        int max;
        int visit;
        int visit_circle;
        int weight;
        vector<string> path = vector<string>();
        Word() {}
        Word(const char *input, bool weight) {
            this->word = input;
            this->len = (int)strlen(input);
            this->head = input[0] - 'a';
            this->tail = input[len - 1] - 'a';
            this->max = 0;
            this->visit = 0;
            this->visit_circle = 0;
            if (weight) {
                this->weight = len;
            } else {
                this->weight = 1;
            }
            this->path.clear();
        }
};