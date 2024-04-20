#include "mpi.h"
#include "pt4.h"

void Solve()
{
    Task("MPI7Win3");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int *window_buffer=new int[size-1];
    if(rank==0)
    {
    	for(int i=0;i<size-1;i++)
    	pt>>window_buffer[rank-1];
	}
	int sz;
	MPI_Type_size(MPI_INT,&sz);
	MPI_Win window;
    MPI_Win_create(window_buffer, sz*(size-1), sz, MPI_INFO_NULL, MPI_COMM_WORLD, &window);
    MPI_Win_fence(0, window);
    int a[1];
    if (rank) {
        MPI_Get(a, 1, MPI_INT, 0, size-rank, 1, MPI_INT, window);
        MPI_Win_fence(0, window);
        pt<<1;
    }
}
