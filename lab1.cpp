#include <iostream>
#include <omp.h>
using namespace std;

int** multiplyMatrixOnOMP(int** a, int** b, int row1, int col1, int col2) {
    // Умножение матриц c OMP
    int** c;
    c = new int* [row1];
    double start;
    double end;
    start = omp_get_wtime();
#pragma omp parallel for
    for (int i = 0; i < row1; i++)
    {
        c[i] = new int[col2];
        for (int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    end = omp_get_wtime();
    cout << "Время с OMP: " << end - start;
    return c;
}
int** multiplyMatrixNotOMP(int** a, int** b, int row1, int col1, int col2) {
    // Умножение матриц без OMP
    int** c;
    c = new int* [row1];
    double start;
    double end;
    start = omp_get_wtime();
    for (int i = 0; i < row1; i++)
    {
        c[i] = new int[col2];
        for (int j = 0; j < col2; j++)
        {
            c[i][j] = 0;
            for (int k = 0; k < col1; k++)
                c[i][j] += a[i][k] * b[k][j];
        }
    }
    end = omp_get_wtime();
    cout << "Время без OMP: " << end - start;
    return c;
}

int main()
{
    int row1, row2, col1, col2;
    int** a, ** b, ** c;
    system("chcp 1251");
    system("cls");
    cin >> row1 >> col1;
    cin >> row2 >> col2;
    if (col1 != row2)
    {
        cout << "Умножение невозможно!";
        cin.get(); cin.get();
        return 0;
    }
    // Ввод элементов первой матрицы
    a = new int* [row1];
    for (int i = 0; i < row1; i++)
    {
        a[i] = new int[col1];
        for (int j = 0; j < col1; j++)
        {
            a[i][j] = 0 + rand()%10;
        }
    }
    b = new int* [row2];
    for (int i = 0; i < row2; i++)
    {
        b[i] = new int[col2];
        for (int j = 0; j < col2; j++)
        {
            b[i][j] = 0 + rand() % 10;
        }
    }
    cout << endl;
    c = multiplyMatrixNotOMP(a, b, row1, col1, col2);
    cout << endl;
    c = multiplyMatrixOnOMP(a, b, row1, col1, col2);
 
    cout << endl;
    cin.get(); cin.get();
    return 0;
}

/*
100 100
100 100

1000 1000
1000 1000

1000 2000
2000 1000

2000 2000
2000 2000

5000 5000
5000 5000
*/
