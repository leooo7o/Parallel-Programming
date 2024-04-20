#include "pt4.h"
#include <omp.h>
#include <cmath>
using namespace std;
double np(double x,double n)
{
    double ans = 0;
    for (int i = 1; i <= n; i++)
    {
        double sum= 0;
        for (int j = 1; j <=i; j++)
        {
            sum += (j + pow(x + j, 0.25)) / (2 * i * j - 1);
        }
        ans += 1 / sum;
    }
    return ans;
}
double p(double x,double n)
{
    double ans = 0;
    int k = ((3 * n * n )) / 2,k0 = k / 4, C = 0, index = 1;
    int ind[5] = { 0 };
    for (int i = 1; i <= n; i++)
    {
        C += 2*n - i;
        if (C >= k0 )
        {
            ind[index++] = i;
            C = 0;
            ShowLine("k = ", ind[index-1]);
        }
    }
    ind[index] = n;
#pragma omp parallel num_threads(4) reduction(+:ans)
    {
        int num = omp_get_thread_num();
        int num_procs = omp_get_num_procs();
        int num_threads = omp_get_num_threads();
        int count = 0;
        if (num == 0)
        {
            ShowLine("num_procs: ", num_procs);
            ShowLine("num_threads: ", num_threads);
        }
        double time = omp_get_wtime();
        for (int i = ind[num]+1; i <=ind[num+1]; i++)
        {
            double tmp = 0;
            for (int j = 1; j <= i; j++)
            {
                tmp += (j + pow(x + j, 0.25)) / (2 * i * j - 1);
                count++;
            }
            ans += 1 / tmp;
        }
        double p_time = omp_get_wtime() - time;
        Show("thread_num:", num);
        Show("Count:", count);
        ShowLine("Thread time:", p_time);
    }
	return ans;		
}
void Solve()
{
    Task("OMPBegin13");
    double x;
	int n;
    pt>>x>>n;
    double time=omp_get_wtime();
    double ans=np(x,n);
    double npt=omp_get_wtime()-time;
    pt<<ans;
    ShowLine("Non-parallel time:",npt);
    pt>>x>>n;
    time=omp_get_wtime();
    ans=p(x,n);
    double t=omp_get_wtime()-time;
    pt<<ans;
    ShowLine("Parallel time:",t);
    ShowLine("Rate:",npt/t);
}
