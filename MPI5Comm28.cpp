#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm28");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int* index = new int[size];
    index[0] = size / 2;
    for (int i = 1; i < size; i++)
    {
        int x = i % 2 ? 2 : 1;
        index[i] = index[i - 1] + x;
    }
    int n = index[size - 1];
    int*edges = new int[n];
    for (int i = 0; i < size/2; i++)
    {
        edges[i] = 2 * i + 1;
    }
    int f = 1;
    int odd = 0;
    for (int i = size/2; i < n; i++)
    {
        if (odd == 1)
        {
            f++;
            edges[i] = f;
            odd++;
        }
        else if (odd == 0)
        {
            edges[i] = 0;
            odd++;
        }
        else
        {
            edges[i] = f - 1;
            f++;
            odd = 0;
        }
    }
    MPI_Comm comm;
    MPI_Graph_create(MPI_COMM_WORLD, size, index, edges, 0, &comm);
    int count;
    MPI_Graph_neighbors_count(comm,rank,&count);
    int* neighbors = new int[count];
    MPI_Graph_neighbors(comm, rank, count, neighbors);
    int a, b;
    pt >> a;
    for (int i = 0; i < count; i++)
    {
        MPI_Sendrecv(&a, 1, MPI_INT, neighbors[i], 0, &b, 1, MPI_INT, neighbors[i], 0, comm, MPI_STATUSES_IGNORE);
        pt << b;
    }
}
