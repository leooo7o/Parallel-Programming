#include "mpi.h"
#include "pt4.h"

#include <cmath>

int k;              // number of processes
int r;              // rank of the current process

int m, p, q;        // sizes of the given matrices
int na, nb;         // sizes of the matrix bands

int *a_, *b_, *c_;  // arrays to store matrices in the master process
int *a, *b, *c;     // arrays to store matrix bands in each process

MPI_Datatype MPI_COLS; // datatype for the band of the matrix B
void Matr2Calc(int n) {
    int sum;
    for (int i = 0; i < na; i++) {
        for (int j = 0; j < nb; j++) {
            sum = 0;
            for (int z = 0; z < p; z++) {
                sum += a[z+i * p ] * b[j+z * nb];
            }
            c[(r +  n+ k) % k * na * nb + i * nb + j] = sum;
        }
    }
    MPI_Sendrecv_replace(a, p*na, MPI_INT, (r + k - 1) % k, 0, (r + k + 1) % k, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
} 
void Solve()
{
    Task("MPI9Matr14");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    k = size;
    r = rank;
    pt >> na >> p >> nb;
    int sza=p*na;
    int szb=p*nb;
    int szc=na*nb*k;
    a = new int[sza];
    b = new int[szb];
    c = new int[szc];
    for (int i = 0; i <sza ; i++) {
        pt >> a[i];
    }
    for (int i = 0; i <szb; i++) {
        pt >> b[i];
    }
    for (int i = 0; i <szc; i++) {
        pt >> c[i];
    }
    Matr2Calc(0);Matr2Calc(1);
    for (int i = 0; i < szc; i++) {
        pt << c[i];
    }
    for (int i = 0; i < sza; i++) {
        pt << a[i];
    }
}
