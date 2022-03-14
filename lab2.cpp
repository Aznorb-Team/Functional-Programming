#include <iostream>
#include <stdlib.h>
#include <omp.h>
#include <queue>
using namespace std;

vector<vector<int>> AdjacencyMatrix;

int n(0);

void adjecencyMatrix(bool* visited)
{
    //Матрица смежности
    AdjacencyMatrix.resize(n, vector<int>(n));

    //cout << "Матрица смежности: " << endl;
    for (int f = 0; f < n; f++)
    {
        visited[f] = false;
        for (int g = 0; g < n; g++)
        {
            AdjacencyMatrix[f][g] = 0 + rand() % 2;
            //cout << AdjacencyMatrix[f][g] << ' ';
        }
        //cout << "\n";
    }
}

void DFS(int st, bool* visited)
{
    int r;
    cout << st + 1 << " ";
    visited[st] = true;
    for (r = 0; r < n; r++)
    {
        if ((AdjacencyMatrix[st][r] != 0) && (!visited[r]))
        {
            DFS(r, visited);
        }
    }
}
void DFSOmp(int st, bool* visited)
{
    int r;
    cout << st + 1 << " ";
    visited[st] = true;
#pragma omp parallel for
    for (r = 0; r < n; r++)
    {
        if ((AdjacencyMatrix[st][r] != 0) && (!visited[r]))
        {
            DFSOmp(r, visited);
        }
    }
}
void BFS(int s) {
    queue <int> turn;
    vector<bool> used(n);
    used[s] = true;
    turn.push(s);
    while (!turn.empty()) //проверяем, пуста ли очередь
    {
        int ind = turn.front();//берем из очереди крайний элемент
        turn.pop();//удаляем его
        //cout << ind + 1 << ' ';
        for (int i = 0; i < AdjacencyMatrix[ind].size(); i++)//смотрим, с какими вершинами смежна вершина ind
        {
            if (AdjacencyMatrix[ind][i] == 1 && used[i] != true)
            {
                used[i] = true;
                turn.push(i);//добавляем в очередь вершину i

            }
        }
    }
}
void BFSOmp(int s) {
    queue <int> turn;
    vector<bool> used(n);
    used[s] = true;
    turn.push(s);
    while (!turn.empty()) //проверяем, пуста ли очередь
    {
        int ind = turn.front();//берем из очереди крайний элемент
        turn.pop();//удаляем его
        //cout << ind + 1 << ' ';
#pragma omp for
        for (int i = 0; i < AdjacencyMatrix[ind].size(); i++)//смотрим, с какими вершинами смежна вершина ind
        {
            if (AdjacencyMatrix[ind][i] == 1 && used[i] != true)
            {
                used[i] = true;
                turn.push(i);//добавляем в очередь вершину i

            }
        }
       
    }
}
int main()
{
    setlocale(LC_ALL, "rus");
    //Поиск в глубину
    n = 10000;
    bool* visited = new bool[n];
    bool* visited1 = visited;
    adjecencyMatrix(visited);
    int start;
    start = 1;
    double startT;
    double end;
    startT = omp_get_wtime();
    //cout << "Порядок обхода: ";
   // DFS(start - 1, visited);
    //cout << endl;
    cout << "Порядок обхода: ";
    BFS(start - 1);
    end = omp_get_wtime();
    cout << "Время без OMP: " << end - startT;
    startT = omp_get_wtime();
    cout << endl;
    cout << "Порядок обхода: ";
    BFSOmp(start - 1);
    end = omp_get_wtime();
    cout << "Время c OMP: " << end - startT;
    return 0;
}
