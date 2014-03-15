#include <stdio.h>
#include <stdlib.h>
#define M 4

int largest_prod_in_grid(int (*a)[], int, int, int);
int largest_prod_diag_grid(int (*a)[], int, int, int);
int largestHorizontalProduct(int (*a)[], int, int, int, int);
int largestDiagProduct(int (*a)[], int, int, int);
int calculate_cross_product(int (*a)[], int, int, int);

int main() {
    int largest_hor_prod = 0;
    int largest_ver_prod = 0;
    int largest_diag_prod1 = 0;
    int largest_diag_prod2 = 0;

    int a[4][4] = {
        {8, 2, 22, 97}, 
        {49, 49, 99, 40},
        {81, 49, 31, 73},
        {52, 70, 95, 23},
    };
//    largest_hor_prod = largest_prod_in_grid(a, 0, 3, 0);
 //   largest_ver_prod = largest_prod_in_grid(a, 0, 3, 1);
    largest_diag_prod1 = largest_prod_diag_grid(a, 1, 5, 0);
  //  largest_diag_prod2 = largest_prod_diag_grid(a, 0, 3, 1);

    //printf("largestHorizontalProduct: %d\n", largest_hor_prod);
    //printf("largestVerticalProduct: %d\n", largest_ver_prod);
    printf("largestdiag1Product: %d\n", largest_diag_prod1);
    //printf("largestdiag2Product: %d\n", largest_diag_prod2);
}

int largest_prod_diag_grid(int (*a)[4], int lo, int hi, int dir) {
    int mid = 0;
    mid = (lo + hi) / 2;
    int i = 0;
    int k = 0;
    int j = 0;
    int d_prod = 1;
    int left_prod = 1;
    int right_prod = 1;

    if (lo == hi) {
        printf("lo: %d hi: %d\n", lo, hi);
        if (lo >= M && hi >= M) {
            lo = (lo - M) + 1;
            hi = (hi - M) + 1;
            if (!dir) {
                k = lo;
                for (i = M - 1; i >= lo; i--) {
                    printf("%d ", a[i][k++]);
                }
                printf("\n");
                d_prod = largestDiagProduct(a, M - lo, M - lo, 0);
            } else {
                k = (M - 1) - lo ;
                for (i = M - 1; i >= lo; i--) {
                    printf("%d ", a[i][k--]);
                }
                d_prod = largestDiagProduct(a, M - 1, (M - 1) - lo, 1);
                printf("\n");
            }   
            return d_prod;
        } else {
            if (!dir) {
                k = lo;
                for (j = 0; j <= lo; j++) {
                    printf("%d ", a[k--][j]);
                }
                printf("\n");
                d_prod = largestDiagProduct(a, lo, 0, 0);
            } else {
                k = lo;
                for (j = M - 1; k >= 0; j--) {
                    printf("%d ", a[k--][j]);
                }
                printf("\n");
                d_prod = largestDiagProduct(a, lo, M - 1, 1); 
            }
            return d_prod;
        }
    }
    left_prod = largest_prod_diag_grid(a, lo, mid, dir);
    right_prod = largest_prod_diag_grid(a, mid + 1, hi, dir);

    if (left_prod > right_prod)
        return left_prod;
    else 
        return right_prod;
}

int largestDiagProduct(int (*a)[4], int y_lo, int y_hi, int dir) {
    int mid_y = (y_lo + y_hi) / 2;
    int prod = 1;
    int right_prod = 1;
    int left_prod = 1;
    int cross_prod = 1;
    int i = 0;
    int k = 0;
    int ele = 0;
    int limit = 0;

    if (y_lo == y_hi) {
        if ((y_lo - y_hi) + 1 == 2) {
            ele = y_lo;
            if (!dir) {
                k = ele;
                for (i = y_hi; i <= y_lo; i++) {
                    printf("%d ", a[k--][i]);
                    //prod *= a[k--][i];
                }
            }   
            printf("prod: %d\n", prod);
        
            return prod;
        }
        left_prod = largestDiagProduct(a, y_lo, mid_y, dir);
        right_prod = largestDiagProduct(a, (y_lo - mid_y) - 1, y_lo, dir);

        printf("left_prod: %d right_prod: %d\n", left_prod, right_prod);
        if (left_prod > right_prod)
            return left_prod;
        else
        return right_prod;
    }

    printf("y_lo: %d y_hi: %d\n", y_lo, y_hi);
    if ((y_lo - y_hi) > 0 && (y_hi + 1) == 2) {
        ele = y_lo;
        if (!dir) {
            k = ele;
            for (i = 0; i <= y_hi; i++) {
                printf("%d ", a[k--][i]);
                //prod *= a[k--][i];
            }
        }   
        printf("prod: %d\n", prod);
        
        return prod;
    } else if((y_hi - y_lo) > 0 && (y_lo + 1) == 2) {
        ele = y_lo;
        if (!dir) {
            k = ele;
            for (i = y_hi - y_lo; i <= y_hi; i++) {
                printf("%d ", a[k--][i]);
                //prod *= a[k--][i];
            }
        }   
        printf("prod: %d\n", prod);
        
        return prod;
    } else if ((y_lo - y_hi) < 2) {
            return 0;
    }

    left_prod = largestDiagProduct(a, y_lo, mid_y, dir);
    right_prod = largestDiagProduct(a, (y_lo - mid_y) - 1, y_lo, dir);

    printf("left_prod: %d right_prod: %d\n", left_prod, right_prod);
    if (left_prod > right_prod)
        return left_prod;
    else
        return right_prod;
}

int largestHorizontalProduct(int (*a)[4], int x, int y_lo, int y_hi, int dir) {
    // divide y recursivley
    int mid_y = (y_lo + y_hi) / 2;
    int prod = 1;
    int right_prod = 1;
    int left_prod = 1;
    int cross_prod = 1;
    int i = 0;

    printf("y_lo: %d y_hi: %d\n", y_lo, y_hi);
    if (((y_hi - y_lo) + 1) == 2) {
        for (i = y_lo; i <= y_hi; i++) {
            if (!dir)
                prod *= a[x][i];
            else 
                prod *= a[i][x];
        }
        printf("prod: %d\n", prod);
        return prod;
    } else if ((y_hi - y_lo) + 1 < 2) {
        return 0;
    }

    left_prod = largestHorizontalProduct(a, x, y_lo, mid_y, dir);
    right_prod = largestHorizontalProduct(a, x, mid_y + 1, y_hi, dir);
    cross_prod = calculate_cross_product(a, x, mid_y, dir);

    printf("left_prod: %d right_prod: %d cross_prod: %d\n", left_prod, right_prod, cross_prod);
    

    if (left_prod < right_prod) {
        if (right_prod > cross_prod) 
            return right_prod;
        else 
            return cross_prod;
    } else {
        if (left_prod > cross_prod)
            return left_prod;
        else 
            return cross_prod;
    }
}

int calculate_cross_product(int (*a)[4], int x, int mid, int dir) {
    int i = 0;
    int j = 0;
    int count = 0;
    int prod = 1;
    int max_cross = 0;

    for (i = 0; i < 1; i++) {
        for (j = -i, count = 0; count < 2; count++, j++) {
            if (!dir)
                prod *= a[x][mid + j];
            else 
                prod *= a[mid + j][x];
        }
        if (prod > max_cross) {
            max_cross = prod;
        }
        prod = 1;
    }
    return max_cross;
}

int largest_prod_in_grid(int (*a)[4], int lo, int hi, int direction) {
    int i = 0;
    int n = 0;
    int j = 0;
    int mid = 0;
    int m = 3;
    int h_prod = 0;
    int v_prod = 0;
    int left_prod = 1;
    int right_prod = 1;
    int max = 0;

    mid = (lo + hi) / 2;

    if (lo > hi)
        return 0;

    if (lo == hi) {
        for(i = 0; i <= m; i++) {
            if (!direction)
                printf("%d ", a[lo][i]);
            else 
                printf("%d ", a[i][lo]);
        }
        printf("\n");
        if (!direction) {
            h_prod = largestHorizontalProduct(a, lo, 0, m, 0);
            printf("h_prod: %d\n", h_prod);
            return h_prod;
        } else {
            v_prod = largestHorizontalProduct(a, lo, 0, m, 1);
            printf("v_prod: %d\n", v_prod);
            return v_prod;
        }
        printf("\n");
    }

    left_prod = largest_prod_in_grid(a, lo, mid, direction);
    right_prod = largest_prod_in_grid(a, mid + 1, hi, direction);

    if (left_prod < right_prod)
        max = right_prod;
    else 
        max = left_prod;
    return max;
    
}
