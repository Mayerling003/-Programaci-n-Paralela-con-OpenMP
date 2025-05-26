#include <iostream>
#include <ctime>
#include <cstdlib>
#include <omp.h>
using namespace std;

const int size=500, generaciones=100;

int contar_vecinos(int** m, int x, int y){
	int v=0;
	for(int dx=-1; dx<=1; dx++)
	for(int dy=-1; dy<=1; dy++){
		if(dx==0 && dy==0) continue;
		int nx=x+dx, ny=y+dy;
		if(nx>=0 && nx<size && ny>=0 && ny<size)
			v+=m[nx][ny];
	}
	return v;
}

int** crear_matriz(){
	int** m=new int*[size];
	for(int i=0;i<size;i++) m[i]=new int[size];
	return m;
}

void eliminar_matriz(int** m){
	for(int i=0;i<size;i++) delete[] m[i];
	delete[] m;
}

void copiar(int** o, int** d){
	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
		d[i][j]=o[i][j];
}

int main(){
	srand(time(0));
	int** s=crear_matriz(), **sn=crear_matriz();
	int** p=crear_matriz(), **pn=crear_matriz();

	for(int i=0;i<size;i++)
	for(int j=0;j<size;j++)
		s[i][j]=p[i][j]=rand()%2;

	double t1=omp_get_wtime();
	for(int g=0;g<generaciones;g++){
		for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			int v=contar_vecinos(s,i,j);
			sn[i][j]=(s[i][j]? (v==2||v==3):(v==3));
		}
		copiar(sn,s);
	}
	double t2=omp_get_wtime();

	double t3=omp_get_wtime();
	for(int g=0;g<generaciones;g++){
		#pragma omp parallel for collapse(2)
		for(int i=0;i<size;i++)
		for(int j=0;j<size;j++){
			int v=contar_vecinos(p,i,j);
			pn[i][j]=(p[i][j]? (v==2||v==3):(v==3));
		}
		copiar(pn,p);
	}
	double t4=omp_get_wtime();

	cout<<"Tiempo secuencial: "<<(t2-t1)<<" s\n";
	cout<<"Tiempo paralelo: "<<(t4-t3)<<" s\n";

	eliminar_matriz(s); eliminar_matriz(sn);
	eliminar_matriz(p); eliminar_matriz(pn);
}
