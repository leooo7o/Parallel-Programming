#include "mpi.h"
#include "pt4.h"

void Solve()
{
    Task("MPI6File11");
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
    MPI_Comm comm;
    int color=n>0?1:MPI_UNDEFINED;
    MPI_Comm_split(MPI_COMM_WORLD,color,rank,&comm);
    if (comm != MPI_COMM_NULL)
    {
        MPI_File f = MPI_FILE_NULL;
        MPI_File_open(comm, name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
        double a;
        MPI_File_read_at_all(f, (n - 1) * 8, &a, 1, MPI_DOUBLE, MPI_STATUSES_IGNORE);
        pt << a;
        MPI_File_close(&f);
    }
}
