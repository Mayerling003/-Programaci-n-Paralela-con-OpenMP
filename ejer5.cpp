#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

void combinar(int a[], int izq[], int n1, int der[], int n2) {
	int i=0,j=0,k=0;
	while(i<n1 && j<n2)
		a[k++]=(izq[i]<=der[j])?izq[i++]:der[j++];
	while(i<n1) a[k++]=izq[i++];
	while(j<n2) a[k++]=der[j++];
}

void ordenar(int a[], int n) {
	if(n<2) return;
	int m=n/2;
	int* izq=new int[m];
	int* der=new int[n-m];
	for(int i=0;i<m;i++) izq[i]=a[i];
	for(int i=m;i<n;i++) der[i-m]=a[i];
	ordenar(izq,m);
	ordenar(der,n-m);
	combinar(a,izq,m,der,n-m);
	delete[] izq;
	delete[] der;
}

int buscar(int a[], int n, int valor) {
	int ini=0, fin=n-1;
	while(ini<=fin) {
		int mid=ini+(fin-ini)/2;
		if(a[mid]==valor) return mid;
		if(a[mid]<valor) ini=mid+1;
		else fin=mid-1;
	}
	return -1;
}

int main(){
	srand(time(0));
	const int N=100;
	const int M=5;
	int* datos=new int[N];
	int* buscar_valores=new int[M];
	for(int i=0;i<N;i++) datos[i]=rand()%100+1;
	for(int i=0;i<M;i++) buscar_valores[i]=rand()%100+1;
	ordenar(datos,N);

	omp_set_num_threads(4);
	#pragma omp parallel for
	for(int i=0;i<M;i++){
		int pos=buscar(datos,N,buscar_valores[i]);
		#pragma omp critical
		{
			if(pos!=-1)
				cout<<"Valor "<<buscar_valores[i]<<" en pos "<<pos<<" (hilo "<<omp_get_thread_num()<<")"<<endl;
			else
				cout<<"Valor "<<buscar_valores[i]<<" no encontrado (hilo "<<omp_get_thread_num()<<")"<<endl;
		}
	}
	delete[] datos;
	delete[] buscar_valores;
	return 0;
}
