#include <vector>
#include <stack>
#include <string>
#include <unordered_set>
#include "word.h"

using namespace std;

#define MAX_POINT 30
#define NUM_POINT 26

class Graph {
    vector< vector<Word> > v = vector< vector<Word> >(MAX_POINT);
    vector<string> bak;
    bool vis[MAX_POINT], vis_tmp[MAX_POINT], has_cicle;
    int dfn[MAX_POINT], low[MAX_POINT], color[MAX_POINT], index, sum, num, max;
    stack<int> stk;
    public:
    Graph(const char* words[], int len, bool weight) {
        for (int i = 0; i < len; i ++) {
            if (strlen(words[i]) > 1) {
                bak.push_back(words[i]);
                Word word = Word(words[i], weight);
                v[word.head].push_back(word);
            }
        }
        this->num = (int)bak.size();
    }
        // for (int i = 0; i < MAX_POINT; i++) {
        //     v[i].clear();
        //     vis[i] = false;
        // }
        // for (int i = 0; i < num; i++) {
        //     string tmp = bak[i];
        //     if (tmp.size() > 1) {
        //         v[tmp[0] - 'a'].push_back(Word(tmp));
        //     }
        // }
        // index = sum = 0;
        // for (int i = 0; i < NUM_POINT; i++) {
        //     if (!vis[i]) {
        //         tarjan(i);
        //     }
        // }
    // }

    // void tarjan(int u) {
    //     dfn[u] = low[u] = ++index;
    //     stk.push(u);
    //     vis[u] = vis_tmp[u] = true;
    //     for(int w: v[u])
    //     {
    //         int target = bak[w].back() - 'a';
    //         if(!dfn[to])
    //         {
    //             tarjan(w);
    //             low[u] = min(low[u], low[to]);
    //         }
    //         else if(vis_tmp[to]) {
    //             low[u] = min(low[u], low[to]);
    //         }
    //     }
    //     if(dfn[u] == low[u]) {
    //         color[u] = ++sum;
    //         vis_tmp[u] = false;
    //         while (stk.top() != u) {
    //             color[stk.top()] = color[u];
    //             vis_tmp[stk.top()] = false;
    //             stk.pop();
    //         }
    //     } 
    // }

    void update_graph(char skip) {
        // for (int i = 0; i < num; i ++) {
        //     if (bak[i][0] == skip) {
        //         bak.erase(bak.begin() + i);

        //     }
        // }
        // this->num = bak.size();
        v[skip].clear();
    }

    bool check_circle() {
        for (int i = 0; i < NUM_POINT; i++) {
            for (Word &w: v[i]) {
                if (dfs_circle(w)) {
                    return true;
                }
            }
        }
        return false;
    }

    bool dfs_circle(Word &u) {
        u.visit_circle = 1;
        for (Word &w: v[u.tail - 'a']) {
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
        return false;
    }

    int get_all(vector<string> &results) {
        for (int i = 0; i < NUM_POINT; i++) {
            for (Word &w: v[i]) {
                vector<string> tmp;
                dfs_all(results, w, tmp);
            }
        }
        return 0;
    }

    void dfs_all(vector<string> &results, Word &u, vector<string> &ans) {
        if (u.visit) {
            return;
        }
        u.visit = true;
        if (ans.size() > 1) {
            for (string s: ans) {
                results.push_back(s);
            }
        }
        for (Word &w: v[u.tail - 'a']) {
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
        vector<int> task;
        update_graph(skip);
        if (head != '\0') {
            task.push_back(head - 'a');
        }
        else {
            for (int i = 0; i < NUM_POINT; i++) {
                task.push_back(i);
            }
        }
        for (int i: task) {
            for (Word u: v[i]) {
                if (!loop || !u.visit) {
                    vector<string> result_tmp;
                    dfs_max_word(result_tmp, u, tail, skip, loop);
                    if (ans < u.max) {
                        ans = u.max;
                        results = result_tmp;
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

    void dfs_max_word(vector<string> &results, Word u, char tail, char skip, bool loop) {
        u.visit = true;
        int ans = 0;
        Word *max_word = nullptr;
        for (Word w: v[u.tail - 'a']) {
            if (w.word == u.word) {
                continue;
            }
            if (loop || !w.visit) {
                dfs_max_word(results, w, tail, skip, loop);
            }
            if (ans < w.max) {
                ans = w.max;
                max_word = &w;
            }
        }
        if (tail == '\0' || u.tail == tail) {
            u.max = u.weight;
            results.push_back(u.word);
        }
        else if (max > 0) {
            u.max = ans + u.weight;
            u.path.assign(max_word->path.begin(), max_word->path.end());
            u.path.push_back(max_word->word);
        }
    }
};