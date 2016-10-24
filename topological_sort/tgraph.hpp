#ifndef TGRAPH_HPP_INCLUDED
#define TGRAPH_HPP_INCLUDED

#include <stack>

enum Type { MATRIX, LIST };

stack<int> s;
bool *checked;

class TGraph
{
    private:
        int **arr;
        int vertex_count;
        bool have_weights;
        Type type;

    public:
        TGraph(int c, Type t = MATRIX, bool weights = false);
        int add_link(int from, int where);
        int* topological_sort();

        void dfs(int i, bool checked[], void (*callback)(int));
};

TGraph::TGraph( int c, Type t /* = MATRIX */, bool weights /* = false */)
{
    vertex_count = c;
    have_weights = weights;
    type = t;
    if (t == MATRIX)
    {
        arr = new int*[c];
        for (int i = 0; i < c; i++)
            arr[i] = new int[c];

        if (weights == false)
        {
            for (int i = 0; i < c; i++)
               for (int k = 0; k < c; k++)
                    arr[i][k] = 0;
        }
    }
}

int TGraph::add_link(int from, int where)
{
    if (have_weights == false)
        arr[from - 1][where - 1] = 1;
    return 0;
}

void push(int i)
{
    s.push(i);
}

void TGraph::dfs(int i, bool checked[], void (*callback)(int))
{
    checked[i] = true;
    for (int k = 0; k < vertex_count; k++)
        if ((arr[i][k] != 0) && (checked[k] == false))
            dfs(k, checked, callback);
    callback(i);
}

int* TGraph::topological_sort()
{
    if (type = MATRIX)
    {
        int* result = new int[vertex_count];
        bool* checked = new bool[vertex_count];
        std::stack<int> s;

        for (int i = 0; i < vertex_count; i++)
                checked[i] = false;


        for (int i = 0; i < vertex_count; i++)
            if (checked[i] == false)
                dfs(i, checked, push);

        for (int i = 0; i < vertex_count; i++)
        {
            result[i] = s.top();
            s.pop();
        }
        return result;
    }
}

#endif // TGRAPH_HPP_INCLUDED
