#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <ctime>

using namespace std;

int main() {
    const int N = 1000000;
    int* datos = new int[N];
    long long suma_seq=0;
    long long suma_par=0;

    srand(time(0));

    for (int i=0;i<N;i++) {
        datos[i]=rand()%100+1;
    }

    omp_set_num_threads(4);
    cout << "Hilos disponibles: " << omp_get_num_threads() << endl;

    // Suma secuencial
    double t1 = omp_get_wtime();
    for (int i=0;i<N;i++) {
        suma_seq += datos[i];
    }
    double t2=omp_get_wtime();

    // Suma paralela
    double t3 = omp_get_wtime();
    #pragma omp parallel for reduction(+:suma_par)
    for (int i=0;i<N;i++) {
        if (i==0) cout << "Hilos en uso: " << omp_get_num_threads() << endl;
        suma_par += datos[i];
    }
    double t4 = omp_get_wtime();

    cout << "Suma secuencial: " << suma_seq << " | Tiempo: " << (t2-t1) << " s" << endl;
    cout << "Suma paralela:   " << suma_par << " | Tiempo: " << (t4-t3) << " s" << endl;

    delete[] datos;
    return 0;
}
