#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI6File2");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char f_name[20];
    if (!rank)
    {
        pt >> f_name;
    }
    MPI_Bcast(f_name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_File f = MPI_FILE_NULL;
    MPI_File_open(MPI_COMM_WORLD, f_name, MPI_MODE_CREATE | MPI_MODE_RDWR, MPI_INFO_NULL, &f);
    if (rank)
    {
        int size;
        pt >> size;
        int* a = new int[size];
        int* b = new int[size];
        for (int i = 0; i < size; i++)
        {
            pt >> a[i] >> b[i];
        }
        MPI_Aint aint, t_size;
        MPI_Type_get_extent(MPI_INT, &aint, &t_size);
        for (int i = 0; i < size; i++) {
            MPI_File_write_at(f, (a[i] - 1) * t_size, b + i, 1, MPI_INT, MPI_STATUSES_IGNORE);
        }
    }
    MPI_File_close(&f);
}
