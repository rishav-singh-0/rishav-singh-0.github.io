#include <stdio.h>
void print(int arr[], int m, int n, int o)
{
	int i, j, k;
    int index = 0;
    for (i = 0; i < m; i++){
        for (j = 0; j < n; j++){
            for (k = 0; k < o; k++) {
                index = (i*n*o) + j*o +k;
                // printf("%d %d %d\n", i, j, k);
                printf("%d %d\n", *(arr + i*n*o + j*o + k), index);
            }
        }
    }
      // arr[i][j][k]
}


int main()
{
    int m = 3, n = 3,o = 3;
    int arr[3][3][3] = {{{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
                        {{10, 20, 30}, {40, 50, 60}, {70, 80, 90}},
                        {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}},
                    };

    // We can also use "print(&arr[0][0], m, n);"
    print(arr, m, n, o);
    return 0;
}