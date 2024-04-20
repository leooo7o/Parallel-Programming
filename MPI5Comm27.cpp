#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm27");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    double a,b;
    pt >> a;
    MPI_Comm comm;
    int x = size / 4;
    int* dims = new int[x] {2,2,x};
    int* periods=new int [x] {0,0,1};
    MPI_Cart_create(MPI_COMM_WORLD, 3, dims, periods, 0, &comm);
    int dirs[2];
    MPI_Cart_shift(comm,2,1,&dirs[0],&dirs[1]);
    MPI_Comm_size(comm, &size);
    MPI_Comm_rank(comm, &rank);
    Show(dirs[1]);
    MPI_Sendrecv(&a, 1, MPI_DOUBLE,dirs[1],1,&b,1,MPI_DOUBLE,MPI_ANY_SOURCE,1,comm,MPI_STATUSES_IGNORE);
    pt << b;
}
