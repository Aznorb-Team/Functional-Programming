#include <iostream>
#include <stdlib.h>
#include <omp.h>
using namespace std;

int** gen_random_graph(int n, bool* &visited, bool*& visitedOmp)
{
	int** adj_matrix;
	adj_matrix = new int* [n];
	for(int u = 0; u < n; u++)
		adj_matrix[u] = new int[n];

	for (int u = 0; u < n; u++)
	{
		visited[u] = false;
		visitedOmp[u] = false;
		//cout << visited[u] << endl;
		for (int v = 0; v < n; v++)
		{
			adj_matrix[u][v] = 0 + rand() % 2;
			//adj_matrix[v][u] = adj_matrix[u][v];
			//cout << adj_matrix[u][v] << " ";
		}
		//cout << endl;
	}
	return adj_matrix;
}

//поиск в глубину
void DFS(int** graph, int n, int st, bool* &visited)
{
		int r;
		cout << st + 1 << " ";
		visited[st] = true;
		for (r = 0; r <= n; r++)
			if ((graph[st][r] != 0) && (!visited[r]))
				DFS(graph, n, r, visited);
}

//поиск в глубину
void DFSOmp(int** graph,int n, int st, bool* &visited)
{
	int r;
	cout << st + 1 << " ";
	visited[st] = true;
	double start;
	double end;
	start = omp_get_wtime();
#pragma omp parallel for
	for (r = 0; r <= n; r++)
		if ((graph[st][r] != 0) && (!visited[r]))
			DFS(graph, n, r, visited);
}

int main()
{
	int N;
	int** graph;

	cin >> N;
	bool* visited = new bool[N];
	bool* visitedOmp = new bool[N];

	double start;
	double end;
	
	
	graph = gen_random_graph(N, visited, visitedOmp);
	cout << endl;
	start = omp_get_wtime();
	DFSOmp(graph, N, 0, visitedOmp);
	
	end = omp_get_wtime();
	cout <<endl<< "OMP: " << end - start;
	cout << endl;
	DFS(graph, N, 0, visited);
	return 0;
}
