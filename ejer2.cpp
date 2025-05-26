#include <iostream>
#include <omp.h>
#include <ctime>
#include <cstdlib>
using namespace std;

int main() {
    const int N = 100;
    int** A = new int*[N];
    int** B = new int*[N];
    int** C_seq = new int*[N];
    int** C_par = new int*[N];

    for (int i = 0; i < N; i++) {
        A[i] = new int[N];
        B[i] = new int[N];
        C_seq[i] = new int[N];
        C_par[i] = new int[N];
    }

    srand(time(0));
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++) {
            A[i][j] = rand() % 10 + 1;
            B[i][j] = rand() % 10 + 1;
            C_seq[i][j] = 0;
            C_par[i][j] = 0;
        }

    // Multiplicación secuencial
    double t1 = omp_get_wtime();
    for (int fila = 0; fila < N; fila++)
        for (int col = 0; col < N; col++)
            for (int k = 0; k < N; k++)
                C_seq[fila][col] += A[fila][k] * B[k][col];
    double t2 = omp_get_wtime();

    // Multiplicación paralela
    double t3 = omp_get_wtime();
    #pragma omp parallel for collapse(2)
    for (int fila = 0; fila < N; fila++) {
        for (int col = 0; col < N; col++) {
            int temp = 0;
            for (int k = 0; k < N; k++)
                temp += A[fila][k] * B[k][col];
            C_par[fila][col] = temp;
        }
    }
    double t4 = omp_get_wtime();

    cout << "Tiempo secuencial: " << (t2 - t1) << " segundos" << endl;
    cout << "Tiempo paralelo: " << (t4 - t3) << " segundos" << endl;

    for (int i = 0; i < N; i++) {
        delete[] A[i];
        delete[] B[i];
        delete[] C_seq[i];
        delete[] C_par[i];
    }

    delete[] A;
    delete[] B;
    delete[] C_seq;
    delete[] C_par;

    return 0;
}
