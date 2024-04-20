#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI6File25");
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
    int* nums = new int[(rank + 1) * 3];
    for (int i = 0; i < (rank + 1) * 3; i++)pt >> nums[i];
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name,MPI_MODE_WRONLY | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    int siz;
    MPI_Type_size(MPI_INT, &siz);
    MPI_Datatype  t;
    int a=0;
    for (int i = 0; i <= size; i++)
    {
       a = a + i;
    }
    int pos = 0;
    for (int i = 0; i <= rank; i++)
    {
        pos = pos + i;
    }
    MPI_Type_vector(3, rank+1, a, MPI_INT, &t);
    char view[7] = "native";
    MPI_File_set_view(f, pos * siz, MPI_INT, t, view,MPI_INFO_NULL);
    MPI_File_write_all(f, nums, (rank+1)*3, MPI_INT, MPI_STATUS_IGNORE);
    MPI_File_close(&f);
}
