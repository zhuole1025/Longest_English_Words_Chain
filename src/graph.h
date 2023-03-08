#include <vector>
#include <stack>
#include <string>
#include "word.h"

using namespace std;

#define MAX_POINT 30
#define NUM_POINT 26

class Graph {
    vector<vector<Word>> v;
    vector<string> bak;
    bool vis[MAX_POINT], vis_tmp[MAX_POINT];
    int dfn[MAX_POINT], low[MAX_POINT], color[MAX_POINT], index, sum, num, max;
    stack<int> stk;
    public:
    Graph(const char* words[], int len) {
        for (int i = 0; i < len; i ++) {
            if (strlen(words[i]) > 1) {
                bak.push_back(words[i]);
            }
        }
        num = bak.size();
        for (int i = 0; i < MAX_POINT; i++) {
            v[i].clear();
            vis[i] = false;
        }
        for (int i = 0; i < num; i++) {
            string tmp = bak[i];
            if (tmp.size() > 1) {
                v[tmp[0] - 'a'].push_back(Word(tmp));
            }
        }
        // index = sum = 0;
        // for (int i = 0; i < NUM_POINT; i++) {
        //     if (!vis[i]) {
        //         tarjan(i);
        //     }
        // }
    }

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

    int get_all(vector<string> &results, bool loop) {
        for (int i = 0; i < NUM_POINT; i++) {
            for (Word &w: v[i]) {
                vector<string> tmp;
                dfs_all(results, w, tmp, loop);
            }
        }
        return 0;
    }

    void dfs_all(vector<string> &results, Word &u, vector<string> &ans, bool loop) {
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
            if (w.word == u.word && !loop) {
                continue;
            }
            ans.push_back(w.word);
            dfs_all(results, w, ans, loop);
            ans.pop_back();
        }
    }

    int get_max_word(vector<string> &results, char head, char tail, bool loop) {
        int ans = 0;
        vector<int> task;
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
                if (!u.visit) {
                    vector<string> result_tmp;
                    dfs_max_word(result_tmp, u, tail, loop);
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

    void dfs_max_word(vector<string> &results, Word u, char tail, bool loop) {
        u.visit = true;
        int ans = 0;
        Word *max_word = nullptr;
        for (Word w: v[u.tail - 'a']) {
            if (w.word == u.word && !loop) {
                continue;
            }
            if (!w.visit) {
                dfs_max_word(results, w, tail, loop);
            }
            if (ans < w.max) {
                ans = w.max;
                max_word = &w;
            }
        }
        if (tail == '\0' || u.tail == tail) {
            u.max = 1;
            results.push_back(u.word);
        }
        else if (max > 0) {
            u.max = ans + 1;
            u.path.assign(max_word->path.begin(), max_word->path.end());
            u.path.push_back(max_word->word);
        }
    }
};