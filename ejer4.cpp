#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;
int main(){
	const int N=1000000;
	long long suma_mal=0;
	long long suma_bien=0;
	int* datos=new int[N];
	srand(time(0));
	for(int i=0;i<N;i++) datos[i]=rand()%100+1;

	double t1=omp_get_wtime();
	#pragma omp parallel for
	for(int i=0;i<N;i++)
		suma_mal+=datos[i];
	double t2=omp_get_wtime();

	double t3=omp_get_wtime();
	#pragma omp parallel for reduction(+:suma_bien)
	for(int i=0;i<N;i++)
		suma_bien+=datos[i];
	double t4=omp_get_wtime();

	cout<<"Tiempo sin reduccion: "<<(t2-t1)<<" segundos"<<endl;
	cout<<"Tiempo con reduccion: "<<(t4-t3)<<" segundos"<<endl;

	delete[] datos;
	return 0;
}
