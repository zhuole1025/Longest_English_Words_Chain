#include <string>
using namespace std;

class Word {
    public:
        string word;
        int len;
        int head;
        int tail;
        int max;
        int visit;
        Word(string &input) {
            this->word = input;
            this->len = input.length();
            this->head = input[0] - 'a';
            this->tail = input[len - 1] - 'a';
            this->max = 0;
            this->visit = 0;
        }
}