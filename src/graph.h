#include <vector>
#include <stack>
#include <string>
#include <unordered_set>
#include "word.h"

using namespace std;

#define MAX_POINT 30
#define NUM_POINT 26

class Graph {
    vector<vector<Word> > v;
    vector<string> bak;
    int num, max;
    public:
    Graph(const char* words[], int len, bool weight) {
        for (int i = 0; i < NUM_POINT; i++) {
            v.push_back(vector<Word>());
        }
        for (int i = 0; i < len; i ++) {
            if (strlen(words[i]) > 1) {
                bak.push_back(words[i]);
                Word word = Word(words[i], weight);
                v[word.head].push_back(word);
            }
        }
        this->num = (int)bak.size();
    }

    void update_graph(char skip) {
        v[skip].clear();
    }

    bool check_circle() {
        for (int i = 0; i < NUM_POINT; i++) {
            for (Word &w: v[i]) {
                if (!w.visit_circle && dfs_circle(w)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs_circle(Word &u) {
        u.visit_circle = 1;
        for (Word &w: v[u.tail]) {
            if (w.word == u.word) {
                continue;
            }
            if (w.visit_circle == 1) {
                return true;
            }
            if (w.visit_circle == 0 && dfs_circle(w)) {
                return true;
            }
        }
        u.visit_circle = 2;
        return false;
    }

    int get_all(vector<string> &results) {
        for (int i = 0; i < NUM_POINT; i++) {
            for (Word &w: v[i]) {
                vector<string> tmp;
                tmp.push_back(w.word);
                dfs_all(results, w, tmp);
            }
        }
        return 0;
    }

    void dfs_all(vector<string> &results, Word &u, vector<string> &ans) {
        if (ans.size() > 1) {
            string str = "";
            for (string &s: ans) {
                if (str == "") {
                    str = s;
                }
                else {
                    str = str + " " + s;
                }
            }
            results.push_back(str);
        }
        for (Word &w: v[u.tail]) {
            if (w.word == u.word) {
                continue;
            }
            ans.push_back(w.word);
            dfs_all(results, w, ans);
            ans.pop_back();
        }
    }

    int get_max_word(vector<string> &results, char head, char tail, char skip, bool loop) {
        int ans = 0;
        head = head == 0 ? -1 : head - 'a';
        tail = tail == 0 ? -1 : tail - 'a';
        skip = skip == 0 ? -1 : skip - 'a';
        vector<int> task;
        if (skip >= 0) {
            update_graph(skip);
        }
        if (head >= 0) {
            task.push_back(head);
        }
        else {
            for (int i = 0; i < NUM_POINT; i++) {
                task.push_back(i);
            }
        }
        if (loop) {
            for (int i: task) 
            {
                for (Word &u: v[i]) {
                    unordered_set<string> vis;
                    vector<string> res;
                    int num = dfs_max_loop(u, tail, vis, res);
                    if (ans < num && res.size() > 1) 
                    {
                        ans = num;
                        results = res;
                    }
                }
            }
        }
        else {
            for (int i: task) {
                for (Word &u: v[i]) {
                    if (!u.visit){
                        dfs_max(u, tail);       
                        if (ans < u.max && u.path.size() > 1) {
                            ans = u.max;
                            results = u.path;
                        }
                    }
                }
            }
        }
        if (ans == 1) {
            return 0;
        }
        reverse(results.begin(), results.end());
        return ans;
    }

    void dfs_max(Word &u, char tail) {
        u.visit = true;
        int ans = 0;
        Word max_word;
        for (Word &w: v[u.tail]) {
            if (w.word == u.word) {
                continue;
            }
            if (!w.visit) {
                dfs_max(w, tail);
            }
            if (ans < w.max) {
                ans = w.max;
                max_word = w;
            }
        }
        if (ans > 0) {
            u.max = ans + u.weight;
            u.path.assign(max_word.path.begin(), max_word.path.end());
            u.path.push_back(u.word);
        }
        else if (tail < 0 || u.tail == tail) {
            u.max = u.weight;
            u.path.push_back(u.word);
        }
    }

    int dfs_max_loop(Word &u, char tail, unordered_set<string> &vis, vector<string> &res) {
        vis.insert(u.word);
        int ans = 0;
        vector<string> max_res;
        for (Word &w: v[u.tail]) {
            if (vis.find(w.word) != vis.end()) {
                continue;
            }
            vector<string> tmp;
            int num = dfs_max_loop(w, tail, vis, tmp);
            if (ans < num) {
                ans = num;
                max_res = tmp;
            }
        }
        if (ans > 0) {
            res = max_res;
            res.push_back(u.word);
            return ans + u.weight;
        }
        else if (tail < 0 || u.tail == tail) {
            res.push_back(u.word);
            return u.weight;
        }
        return 0;
    }
};