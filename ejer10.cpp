#include <iostream>
#include <ctime>
#include <omp.h>
using namespace std;

long long fibonacci_secuencial(int n) {
    if (n <= 1) return n;
    return fibonacci_secuencial(n - 1) + fibonacci_secuencial(n - 2);
}

long long fibonacci_paralelo(int n) {
    if (n <= 10) {
        return fibonacci_secuencial(n);
    }
    long long x, y;
    #pragma omp task shared(x)
    x = fibonacci_paralelo(n - 1);

    #pragma omp task shared(y)
    y = fibonacci_paralelo(n - 2);

    #pragma omp taskwait
    return x + y;
}

int main() {
    int n = 40;
    long long resultado;
    double inicio, fin;

    // Cálculo secuencial
    inicio = omp_get_wtime();
    resultado = fibonacci_secuencial(n);
    fin = omp_get_wtime();
    cout << "Secuencial: Fibonacci(" << n << ") = " << resultado << "\n";
    cout << "Tiempo secuencial: " << (fin - inicio) << " segundos\n\n";

    resultado = 0;

    // Cálculo paralelo
    double inicio_p = omp_get_wtime();
    #pragma omp parallel
    {
        #pragma omp single
        resultado = fibonacci_paralelo(n);
    }
    double fin_p = omp_get_wtime();
    cout << "Paralelo: Fibonacci(" << n << ") = " << resultado << "\n";
    cout << "Tiempo paralelo: " << (fin_p - inicio_p) << " segundos\n\n";

    return 0;
}
