#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI7Win13");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int n[3];
    for (int i = 0; i < 3; ++i)
        pt >> n[i];
    double* a = new double[rank + 1];
    for (int i = 0; i < rank + 1; ++i)
        pt >> a[i];
    double* b = new double[size];
    for (int i = 0; i < size; ++i)
        b[i] = rank + 1;
    int dbl_sz;
    MPI_Type_size(MPI_DOUBLE, &dbl_sz);
    MPI_Win win;
    MPI_Win_create(a, (rank + 1) * dbl_sz, dbl_sz, MPI_INFO_NULL,
        MPI_COMM_WORLD, &win);
    MPI_Win_fence(0, win);
    for (int i = 0; i < 3; ++i)
        MPI_Accumulate(b, n[i] + 1, MPI_DOUBLE, n[i], 0, n[i] + 1,
            MPI_DOUBLE, MPI_SUM, win);
    MPI_Win_fence(0, win);
    for (int i = 0; i < rank + 1; ++i)
        pt << a[i];
    MPI_Win_free(&win);
    delete[] a;
    delete[] b;
}
