//  TILE BASED MATRIX MULTIPLICATION
//  BY: ARMIN MEHRABIAN

#include <stdio.h>
#include <stdlib.h>
#include <omp.h>


#define MIN(A,B) (((A)<(B))?(A):(B))




int main(int argc, char *argv[]) {

int n                   =atoi(argv[1]);
int number_of_threads   =atoi(argv[2]);
int tile_size            =atoi(argv[3]);
        
// A, B and C are two dimensional arrays of size n by n
// tile_size  is the size of the blocking
int i,j,k,ii,jj,kk,sum;
double **A, **B, **C;
int total_threads,tid;
omp_set_num_threads(number_of_threads);

        #pragma omp parallel
        {
                total_threads = omp_get_num_threads();
                tid = omp_get_thread_num();
                if(tid==0)
                        printf("Running tiled with %d threads\n",total_threads);
        }

        A = (double**) malloc(sizeof(double*)*n);
        for (i=0;i<n;i++) {
                A[i] = (double*) malloc(sizeof(double)*n);
        }

        for (i=0;i<n;i++) {
                for (j=0;j<n;j++) {
                        A[i][j] = i+j;
                }
        }

        B = (double**) malloc(sizeof(double*)*n);
        for (i=0;i<n;i++) {
                B[i] = (double*) malloc(sizeof(double)*n);
        }

        srand(0);

        for (i=0;i<n;i++) {
                for (j=0;j<n;j++) {
                        B[i][j] = i-j;
                }
        }

        C = (double**) malloc(sizeof(double*)*n);
        for (i=0;i<n;i++) {
                C[i] = (double*) malloc(sizeof(double)*n);
        }
        for(i=0; i<n; i++) {
                for(j=0; j<n; j++)
                        C[i][j] = 0.0;
        }

        C = (double**) malloc(sizeof(double*)*n);
        for (i=0;i<n;i++) {
                C[i] = (double*) malloc(sizeof(double)*n);
        }
        for(i=0; i<n; i++) {
                for(j=0; j<n; j++)
                        C[i][j] = 0.0;
        }
posix_memalign((void**)&A, n*sizeof(double), n*sizeof(double));
posix_memalign((void**)&B, n*sizeof(double), n*sizeof(double));
posix_memalign((void**)&C, n*sizeof(double), n*sizeof(double));

double start_time = omp_get_wtime();
        
        //#pragma omp parallel for private(jj,kk,i,j,k,sum) collapse(3)
        #pragma omp parallel for private(j,k,sum) schedule(dynamic)
        for(i=0;i<n;i++) {
                //#pragma omp parallel for collapse(2)
                //#pragma omp parallel for private(k,sum)
                for(j=0;j<n;j++) {
                        sum = 0;
                        //#pragma omp parallel for reduction(+:sum)
                        for(k=0;k<n;k++) {
                                sum += A[i][k] * B[k][j];
                        }
                        C[i][j] = sum;

printf("CALCULATION COMPLETED!!\n");
double time = omp_get_wtime()-start_time;



/*      UNBLOCK THIS BLOCK TO PRINT THE RESULTS AND VERIFY FUNCTIONALITY
printf("################################## TILE SIZE: %d ################################\n",tile_size);

printf("................................ INPUT MATRIX A: ................................\n");
for (i=0; i<n; i++)
  {
  for (j=0; j<n; j++)
    printf("%6.2f   ", A[i][j]);
  printf("\n");
  }
printf(".................................................................................\n");
printf("................................ INPUT MATRIX B: ................................\n");
for (i=0; i<n; i++)
  {
  for (j=0; j<n; j++)
    printf("%6.2f   ", B[i][j]);
  printf("\n");
  }
printf(".................................................................................\n");

printf("................................ RESULT MATRIX: ................................\n");
for (i=0; i<n; i++)
  {
  for (j=0; j<n; j++)
    printf("%6.2f   ", C[i][j]);
  printf("\n");
  }
printf(".................................................................................\n");
printf ("\n");
printf ("\n");
*/
printf("Time:%f\n\n",time);
        printf("Number of threads:%i, Time:%f\n",number_of_threads,time);

        return 0;
}

