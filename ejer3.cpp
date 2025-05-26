#include <iostream>
#include <ctime>
#include <omp.h>
#include <cstdlib>
using namespace std;
int main(){
	const int N=1000000;
	int mayor_seq=0;
	int mayor_par=0;
	int* datos=new int[N];
	srand(time(0));
	for(int i=0;i<N;i++) datos[i]=rand()%100+1;

	double t1=omp_get_wtime();
	for(int i=0;i<N;i++)
		if(datos[i]>mayor_seq)
			mayor_seq=datos[i];
	double t2=omp_get_wtime();

	double t3=omp_get_wtime();
	#pragma omp parallel for reduction(max:mayor_par)
	for(int i=0;i<N;i++)
		if(datos[i]>mayor_par)
			mayor_par=datos[i];
	double t4=omp_get_wtime();

	if(mayor_seq==mayor_par)
		cout<<"Mayor valor (ambos): "<<mayor_par<<endl;
	else{
		cout<<"Mayor secuencial: "<<mayor_seq<<endl;
		cout<<"Mayor paralelo: "<<mayor_par<<endl;
	}
	cout<<"Tiempo secuencial: "<<(t2-t1)<<" segundos"<<endl;
	cout<<"Tiempo paralelo: "<<(t4-t3)<<" segundos"<<endl;
	delete[] datos;
	return 0;
}
