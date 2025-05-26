#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

double f(double x){ return x*x; }

double trap_seq(double a,double b,int n){
	double h=(b-a)/n,s=0,c=a;
	for(int i=1;i<=n;i++){
		double x=(h/2)*(f(c)+f(a+i*h));
		c=a+i*h;
		s+=x;
	}
	return s;
}

double trap_par(double a,double b,int n){
	double h=(b-a)/n,s=0;
	#pragma omp parallel for reduction(+:s)
	for(int i=1;i<=n;i++)
		s+=(h/2)*(f(a+(i-1)*h)+f(a+i*h));
	return s;
}

int main(){
	double a=3,b=5;
	int n=1000000;
	double t1=omp_get_wtime(), r1=trap_seq(a,b,n), t2=omp_get_wtime();
	double t3=omp_get_wtime(), r2=trap_par(a,b,n), t4=omp_get_wtime();
	
	if(r1==r2) cout<<"Resultados iguales: "<<r1<<endl;
	else{
		cout<<"Resultados diferentes\n";
		cout<<"Secuencial: "<<r1<<"\nParalelo: "<<r2<<endl;
	}
	cout<<"Tiempo secuencial: "<<(t2-t1)<<" s\n";
	cout<<"Tiempo paralelo: "<<(t4-t3)<<" s\n";
}
