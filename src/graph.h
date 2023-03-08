#include <vector>
#include <stack>
using namespace std;

#define MAX_POINT 30
#define NUM_POINT 26

class Graph {
    vector<int> v[MAX_POINT];
    bool vis[MAX_POINT], vis_tmp[MAX_POINT];
    int dfn[MAX_POINT], low[MAX_POINT], color[MAX_POINT], index, sum;
    stack<int> stk;
    public:
    Graph(const char* words[], int len) {
        for (int i = 0; i < MAX_POINT; i++) {
            v[i].clear();
            vis[i] = false;
        }
        for (int i = 0; i < len; i++) {
            int len = strlen(words[i]);
            if (len > 1) {
                v[words[i][0] - 'a'].push_back(i);
            }
        }
        index = sum = 0;
        for (int i = 0; i < NUM_POINT; i++) {
            if (!vis[i]) {
                tarjan(i);
            }
        }
    }

    void tarjan(int u) {
        dfn[u] = low[u] = ++index;
        stk.push(u);
        vis[u] = vis_tmp[u] = true;
        for(int w: v[u])
        {
            if(!dfn[w])
            {
                tarjan(w);
                low[u] = min(low[u], low[w]);
            }
            else if(vis_tmp[w]) {
                low[u] = min(low[u], dfn[w]);
            }
        }
        if(dfn[u] == low[u]) {
            color[u] = ++sum;
            vis_tmp[u] = false;
            while (stk.top() != u) {
                color[stk.top()] = color[u];
                vis_tmp[stk.top()] = false;
                stk.pop();
            }
        } 
    }
};