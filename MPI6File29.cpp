#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI6File29");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    char name[20];
    if (!rank) pt >> name;
    MPI_Bcast(name, 20, MPI_CHAR, 0, MPI_COMM_WORLD);
    MPI_File f;
    MPI_File_open(MPI_COMM_WORLD, name, MPI_MODE_RDWR | MPI_MODE_CREATE, MPI_INFO_NULL, &f);
    MPI_Datatype t;
    MPI_Offset offset;
    MPI_File_get_size(f, &offset);
    int x = offset / sizeof(int) / size;
    MPI_Datatype vec;
    MPI_Type_contiguous(sqrt(x), MPI_INT, &vec);
    MPI_Type_create_resized(vec, 0, sqrt(x)  * 3 * 4, &t);
    char view[] = "native";
    MPI_File_set_view(f, (rank / 3) * x * 3 * 4  + (rank % 3) * 4 * sqrt(x), MPI_INT, t, view, MPI_INFO_NULL);
    int*nums = new int[x];
    MPI_File_read_all(f, nums, x, MPI_INT, MPI_STATUS_IGNORE);
    for (int i = 0; i <x; i++)
    {
        pt << nums[i];
    }
}
