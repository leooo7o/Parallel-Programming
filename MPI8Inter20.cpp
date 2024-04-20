#include "mpi.h"
#include "pt4.h"

void Solve()
{
    Task("MPI8Inter20");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size,ans;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int root,a,r,K0;
    char name[10] = "ptprj.exe";
	MPI_Comm inter, c1;
	MPI_Comm_get_parent(&inter);
	if (inter == MPI_COMM_NULL)
	{
		pt >> a;
		int x =(4 - size % 4);
		K0 = size + (4 - size % 4);
		MPI_Comm_spawn(name, NULL, x, MPI_INFO_NULL, 0,MPI_COMM_WORLD, &inter, MPI_ERRCODES_IGNORE);
		root = 0;
		MPI_Intercomm_merge(inter, 0, &c1);
		MPI_Comm_rank(c1, &r);
	}
	else
	{
		root = MPI_ROOT;
		a = -rank - 1;
		MPI_Intercomm_merge(inter, 1, &c1);
		MPI_Comm_rank(c1, &r);
		int sz;
		MPI_Comm_remote_size(inter, &sz);
		K0 = sz + 4 - sz % 4;
	}
	int ndims = 2;
	int dims[2] = { K0 / 4, 4 };
	int periods[2] = { true, true };
	int reorder = 0;
	int new_rank;
	int my_coords[2];
	MPI_Comm new_comm;
	MPI_Cart_create(c1, ndims, dims, periods, reorder, &new_comm);
	MPI_Comm_rank(new_comm, &new_rank);
	MPI_Cart_coords(new_comm, new_rank, 2, my_coords);
	int neigbours_ranks[2];
	MPI_Cart_shift(new_comm, 0, -1, &neigbours_ranks[0], &neigbours_ranks[1]);
	MPI_Sendrecv(&a, 1, MPI_INT, neigbours_ranks[1], 0, &ans, 1, MPI_INT, neigbours_ranks[0], 0, new_comm, MPI_STATUSES_IGNORE);
    pt << my_coords[0] << my_coords[1] <<ans;
}
