#include <ctime>
#include <iostream>
#include <omp.h>

using namespace std;
int *alloc_matrix(int size){
    int *matrix = (int*)malloc(size * size * sizeof(int));
//    printf("matrix %dx%d allocated\n", size, size);
    return matrix;
}

void del_matrix(int *matrix){
    free(matrix);
}

int main() {

    int N = 1000;
    int tread_number;
    int k;
    int i;
    int j;
    int THR;

    cout << "Keep the maximum number of threads" << endl;
    cin >> tread_number;

    int *A = alloc_matrix(N);
    int *B = alloc_matrix(N);
    int *C = alloc_matrix(N);

    srand(::clock());

    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            A[i + j * N] = rand() % 5;
            B[i + j * N] = rand() % 5;
        }
    }

    for(THR = tread_number; THR >= 1; THR--) {

        omp_set_dynamic(0);
        omp_set_num_threads(THR);

        unsigned int t0 = clock();

#pragma omp parallel for shared(A, B, C, N) private(i, j, k)

        for (i = 0; i < N; i++)
            for (j = 0; j < N; j++)
                for (k = 0; k < N; k++)
                    C[i + j * N] += A[i + k * N] * B[k + j * N];
        cout << "The multiplication time of the matrices is " << N << " by " << N << " using " << THR << " threads:" << endl << (clock() - t0) / 1000. << " sec." << endl;

    }
    del_matrix(A);
    del_matrix(B);
    del_matrix(C);
    return 0;
}