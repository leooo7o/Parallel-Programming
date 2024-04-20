#include "pt4.h"
#include <omp.h>
#include <cmath>
using namespace std;

void Solve()
{
    Task("OMPBegin16");
    double x;
    int n;
    pt >> x >> n;
    double t = omp_get_wtime();
    double res = non_parallel(X, N);
    double np_time = omp_get_wtime() - t;
    ShowLine("Non-parallel time: ", np_time);
    pt << res;
    pt >> X >> N;
    t = omp_get_wtime();
    res = parallel(X, N);
    double p_time = omp_get_wtime() - t;
    ShowLine("Parallel time: ", p_time);
    ShowLine("Rate: ", np_time / p_time);
    pt << res;
}
