#include "mpi.h"
#include "pt4.h"

void Solve()
{
    Task("MPI6File16");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[20];
if (!rank)pt >> name;
MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
int n;
pt >> n;
int color = (n > 0) ? 1 : MPI_UNDEFINED;
MPI_Comm c;
MPI_Comm_split(MPI_COMM_WORLD, color,size-rank, &c);
if (c != MPI_COMM_NULL)
{
    MPI_File f = MPI_FILE_NULL;
    MPI_File_open(c, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
    double* nums = new double[n]; 
    for (int i = n - 1;i >= 0;i--)pt >> nums[i];
    MPI_File_write_ordered(f, nums, n, MPI_DOUBLE, MPI_STATUSES_IGNORE);
    MPI_File_close(&f);
}
}
