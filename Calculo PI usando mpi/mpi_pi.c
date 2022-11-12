// Programa para calcular pi usando MPI
// El algoritmo esta basado en la integral que representa a PI. si f(x)=4/(1+x^2), entonces PI es la intergral de f(x) desde 0 hasta 1
// JOSE HERVAS, CARLOS ARAYA 
#include <stdio.h>
#include <mpi.h>

#define N 1E7
#define d 1E-7
#define d2 1E-14

int main (int argc, char* argv[])
{
    int rank, size, error, i;
    double pi=0.0, result=0.0, sum=0.0, begin=0.0, end=0.0, x2;
    
    error=MPI_Init (&argc, &argv);
    
    //Obtenemos el ID del proceso
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);
    
    //obtenemos el proceso del numero
    MPI_Comm_size (MPI_COMM_WORLD, &size);
    
    //Sincronizamos los procesos al mismo tiempo
    MPI_Barrier(MPI_COMM_WORLD);
    begin = MPI_Wtime();
    
    //Funcion para calcular una parte de la suma
    for (i=rank; i<N; i+=size)
    {
        x2=d2*i*i;
        result+=1.0/(1.0+x2);
    }
    
    //Suma y subida de los resultados
    MPI_Reduce(&result, &sum, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
    
    //Sincroniza todo los procesos y da finalizacion al mpi
    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();
    
    //Caclula y imprime pi
    if (rank==0)
    {
        pi=4*d*sum;
        printf("np=%2d;    Time=%fs;    PI=%lf\n", size, end-begin, pi);
    }
    //Obtener e imprimir hilos
    omp_get_num_threads(MPI_Comm_size);
    printf("NUMERO DE HILOS: "MPI_Comm_size),
    error=MPI_Finalize();
    
    return 0;
}
