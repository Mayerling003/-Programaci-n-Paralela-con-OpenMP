#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

void combinar(int a[], int izq[], int n1, int der[], int n2) {
	int i=0,j=0,k=0;
	while(i<n1 && j<n2) a[k++]=(izq[i]<=der[j])?izq[i++]:der[j++];
	while(i<n1) a[k++]=izq[i++];
	while(j<n2) a[k++]=der[j++];
}

void ordenar_seq(int a[], int n) {
	if(n<2) return;
	int m=n/2;
	int* izq=new int[m];
	int* der=new int[n-m];
	for(int i=0;i<m;i++) izq[i]=a[i];
	for(int i=m;i<n;i++) der[i-m]=a[i];
	ordenar_seq(izq,m);
	ordenar_seq(der,n-m);
	combinar(a,izq,m,der,n-m);
	delete[] izq;
	delete[] der;
}

void ordenar_par(int a[], int n, int h) {
	if(n<2) return;
	int m=n/2;
	int* izq=new int[m];
	int* der=new int[n-m];
	for(int i=0;i<m;i++) izq[i]=a[i];
	for(int i=m;i<n;i++) der[i-m]=a[i];
	if(h<=0){
		ordenar_seq(izq,m);
		ordenar_seq(der,n-m);
	}else{
		#pragma omp parallel sections
		{
			#pragma omp section
			ordenar_par(izq,m,h-1);
			#pragma omp section
			ordenar_par(der,n-m,h-1);
		}
	}
	combinar(a,izq,m,der,n-m);
	delete[] izq;
	delete[] der;
}

int main(){
	const int N=1000000;
	int* a1=new int[N];
	int* a2=new int[N];
	srand(time(0));
	for(int i=0;i<N;i++) a1[i]=a2[i]=rand()%100+1;

	double t1=omp_get_wtime();
	ordenar_seq(a1,N);
	double t2=omp_get_wtime();

	double t3=omp_get_wtime();
	ordenar_par(a2,N,4);
	double t4=omp_get_wtime();

	cout<<"Tiempo secuencial: "<<(t2-t1)<<" s"<<endl;
	cout<<"Tiempo paralelo: "<<(t4-t3)<<" s"<<endl;

	delete[] a1;
	delete[] a2;
	return 0;
}
