#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm8");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	int n;
	pt >> n;
	MPI_Comm new_comm;
	int color = n == 1 ? 0 : MPI_UNDEFINED;
	MPI_Comm_split(MPI_COMM_WORLD, color, rank, &new_comm);
	if (new_comm == MPI_COMM_NULL)
		return;
	int new_comm_rank;
	int new_comm_size;
	double a;
    pt >> a;
	MPI_Comm_size(new_comm, &new_comm_size);
	MPI_Comm_rank(new_comm, &new_comm_rank);
	double* b = new double[new_comm_size];
	MPI_Gather(&a, 1, MPI_DOUBLE, b, 1, MPI_DOUBLE, new_comm_size-1, new_comm);
	if (new_comm_rank == new_comm_size - 1)
	{
		for (int i = 0; i < new_comm_size; i++)
			pt << b[i];
	}
}
