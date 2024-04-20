#include "mpi.h"
#include "pt4.h"

void Solve()
{
    Task("MPI7Win28");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double coord[2];
    if (rank)
    {
        pt >> coord[0] >> coord[1];
    }
    MPI_Win w;
    int sz;
    MPI_Type_size(MPI_DOUBLE,&sz);
    MPI_Win_create(coord, 2*sz,sz, MPI_INFO_NULL, MPI_COMM_WORLD, &w);
    if(rank!=0) {
        MPI_Barrier(MPI_COMM_WORLD);
        MPI_Win_lock(MPI_LOCK_SHARED, 0, 0, w);
        MPI_Get(coord, 2, MPI_DOUBLE, 0, 0, 2, MPI_DOUBLE, w);
        MPI_Win_unlock(0, w);
        pt << coord[0] << coord[1];
    }
    else if (rank == 0) {
        double a[2];
        for (int i = 1; i < size; i++) {
            MPI_Win_lock(MPI_LOCK_EXCLUSIVE, i, 0, w);
            MPI_Get(a, 2, MPI_DOUBLE, i, 0, 2, MPI_DOUBLE, w);
            MPI_Win_unlock(i, w);
            if ((a[0] * a[0] + a[1] * a[1]) >= (coord[0] * coord[0] + coord[1] * coord[1])) 
            {
                coord[0] = a[0];
                coord[1] = a[1];
            }
        }
        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Win_free(&w);
}
