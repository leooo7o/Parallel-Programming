#include "pt4.h"
#include "mpi.h"

void Solve()
{
    Task("MPI5Comm32");
    int flag;
    MPI_Initialized(&flag);
    if (flag == 0)
        return;
    int rank, size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int k,n;
    pt >> k;
    int* sources;
    int* degrees;
    int* destinations;
	int s = size- 1;
	if (rank == 0)
	{
		n = size;
		sources = new int[size];
		for (int i = 0; i < size; i++)
		{
			sources[i] = i;
		}
		degrees = new int[size]{ 0 };
		destinations = new int[size - 1];
		if (s > 6)
		{
			if (s == 7)
			{
				for (int i = 0; i <= 2; i++)
				{
					degrees[i] = 2;
				}
				degrees[3] = 1;
			}
			else if (s == 8)
			{
				for (int i = 0; i <= 2; i++)
				{
					degrees[i] = 2;
				}
				degrees[3] = 2;
			}
			else if (s == 9) {  degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 1; }
			else if (s == 10) {  degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 2; }
			else if (s == 11) { degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 2; degrees[5] = 1; }
			else if (s == 12) {  degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 2; degrees[5] = 2; }
			else if (s == 13) {  degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 2; degrees[5] = 2; degrees[6] = 1; }
			else { degrees[0] = 2; degrees[1] = 2; degrees[2] = 2; degrees[3] = 2; degrees[4] = 2; degrees[5] = 2; degrees[6] = 2; }
		}
		else if (s >= 5)
		{
			
			degrees[0] = 2;
			degrees[1] = 2;
			if (s == 5) { degrees[2] = 1; }
			else
			{
				degrees[2] = 2;
			}
		}
		else
		{	
			degrees[0] = 2;
			degrees[1] = 2;
		}
		for (int i = 0; i < size - 1; i++)
		{
			destinations[i] = i + 1;
		}
	}
	else 
	{
		n = 0;
		sources = new int[0];
		degrees = new int[0];
		destinations = new int[0];
	}
    MPI_Comm comm;
	MPI_Dist_graph_create(MPI_COMM_WORLD, n, sources, degrees, destinations, MPI_UNWEIGHTED, MPI_INFO_NULL, 0, &comm);
    int indegree, outdegree, weighted;
    MPI_Dist_graph_neighbors_count(comm, &indegree, &outdegree, &weighted);
	Show(indegree);
	Show(outdegree);
	int* sources_2 = new int[indegree], maxindegree = 0, * sourceweights = new int[indegree], maxoutdegree = 0, * destinations_2 = new int[outdegree], * destweighs = new int[outdegree];
	MPI_Dist_graph_neighbors(comm, indegree, sources_2, sourceweights, outdegree, destinations_2, destweighs);
	int ans =k,x=0;
	for (int i = 0; i < indegree; i++) {
		MPI_Recv(&x, 1, MPI_INT, sources_2[i], 0, comm, MPI_STATUS_IGNORE);
		ans += x;
	}
	for (int i = 0; i < outdegree; i++)
		MPI_Send(&ans, 1, MPI_INT, destinations_2[i], 0, comm);
	pt << ans;
}
