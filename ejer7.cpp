#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

double pi_seq(long long n){
	long long d=0;
	srand(time(0));
	for(long long i=0;i<n;i++){
		double x=rand()/(double)RAND_MAX;
		double y=rand()/(double)RAND_MAX;
		if(x*x+y*y<=1.0) d++;
	}
	return 4.0*d/n;
}

double pi_par(long long n,int h){
	long long d=0;
	omp_set_num_threads(h);
	#pragma omp parallel for reduction(+:d)
	for(long long i=0;i<n;i++){
		double x=rand()/(double)RAND_MAX;
		double y=rand()/(double)RAND_MAX;
		if(x*x+y*y<=1.0) d++;
	}
	return 4.0*d/n;
}

int main(){
	long long n=1000000000;
	int h=4;
	double t1=omp_get_wtime(), pi1=pi_seq(n), t2=omp_get_wtime();
	double t3=omp_get_wtime(), pi2=pi_par(n,h), t4=omp_get_wtime();
	cout<<"Pi secuencial: "<<pi1<<"\nTiempo: "<<(t2-t1)<<" s\n";
	cout<<"Pi paralelo: "<<pi2<<"\nTiempo: "<<(t4-t3)<<" s\n";
}
