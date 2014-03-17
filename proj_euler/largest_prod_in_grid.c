#include <stdio.h>
#include <stdlib.h>
#define M 20
#define C 4

int largest_prod_in_grid(int (*a)[], int, int, int);
int largest_prod_diag_grid(int (*a)[], int, int, int);
int largestHorizontalProduct(int (*a)[], int, int, int, int);
int largestDiagProduct(int (*a)[], int, int, int, int);
int largestDiagCrossProduct(int (*a)[], int, int, int);
int calculate_cross_product(int (*a)[], int, int, int);

int main() {
    unsigned long largest_hor_prod = 0;
    unsigned long largest_ver_prod = 0;
    unsigned long largest_diag_prod1 = 0;
    unsigned long largest_diag_prod2 = 0;
    unsigned long  max_linear = 0;

    int a[M][M] = {
        {8, 2, 22, 97, 38, 15, 0, 40, 0, 75, 4, 5, 7, 78, 52, 12, 50, 77, 91, 8}
,{49, 49, 99, 40, 17, 81, 18, 57, 60, 87, 17, 40, 98, 43, 69, 48, 4, 56, 62, 0}
,{81, 49, 31, 73, 55, 79, 14, 29, 93, 71, 40, 67, 53, 88, 30, 3, 49, 13, 36, 65}
,{52, 70, 95, 23, 4, 60, 11, 42, 69, 24, 68, 56, 1, 32, 56, 71, 37, 2, 36, 91}
,{22, 31, 16, 71, 51, 67, 63, 89, 41, 92, 36, 54, 22, 40, 40, 28, 66, 33, 13, 80}
,{24, 47, 32, 60, 99, 3, 45, 2, 44, 75, 33, 53, 78, 36, 84, 20, 35, 17, 12, 50}
,{32, 98, 81, 28, 64, 23, 67, 10, 26, 38, 40, 67, 59, 54, 70, 66, 18, 38, 64, 70}
,{67, 26, 20, 68, 2, 62, 12, 20, 95, 63, 94, 39, 63, 8, 40, 91, 66, 49, 94, 21}
,{24, 55, 58, 5, 66, 73, 99, 26, 97, 17, 78, 78, 96, 83, 14, 88, 34, 89, 63, 72}
,{21, 36, 23, 9, 75, 0, 76, 44, 20, 45, 35, 14, 0, 61, 33, 97, 34, 31, 33, 95}
,{78, 17, 53, 28, 22, 75, 31, 67, 15, 94, 3, 80, 4, 62, 16, 14, 9, 53, 56, 92}
,{16, 39, 5, 42, 96, 35, 31, 47, 55, 58, 88, 24, 0, 17, 54, 24, 36, 29, 85, 57}
,{86, 56, 0, 48, 35, 71, 89, 7, 5, 44, 44, 37, 44, 60, 21, 58, 51, 54, 17, 58}
,{19, 80, 81, 68, 5, 94, 47, 69, 28, 73, 92, 13, 86, 52, 17, 77, 4, 89, 55, 40}
,{4, 52, 8, 83, 97, 35, 99, 16, 7, 97, 57, 32, 16, 26, 26, 79, 33, 27, 98, 66}
,{88, 36, 68, 87, 57, 62, 20, 72, 3, 46, 33, 67, 46, 55, 12, 32, 63, 93, 53, 69}
,{4, 42, 16, 73, 38, 25, 39, 11, 24, 94, 72, 18, 8, 46, 29, 32, 40, 62, 76, 36}
,{20, 69, 36, 41, 72, 30, 23, 88, 34, 62, 99, 69, 82, 67, 59, 85, 74, 4, 36, 16}
,{20, 73, 35, 29, 78, 31, 90, 1, 74, 31, 49, 71, 48, 86, 81, 16, 23, 57, 5, 54}
,{1, 70, 54, 71, 83, 51, 54, 69, 16, 92, 33, 48, 61, 43, 52, 1, 89, 19, 67, 48},

    };

    largest_hor_prod = largest_prod_in_grid(a, 0, 19, 0);
    largest_ver_prod = largest_prod_in_grid(a, 0, 19, 1);
    largest_diag_prod1 = largest_prod_diag_grid(a, 3, ((M - 1) * 2) - 1, 0);
    largest_diag_prod2 = largest_prod_diag_grid(a, 3, ((M - 1) * 2) - 1, 1);

    printf("largestHorizontalProduct: %lu\n", largest_hor_prod);
    printf("largestVerticalProduct: %lu\n", largest_ver_prod);
    printf("largestdiag1Product: %lu\n", largest_diag_prod1);
    printf("largestdiag2Product: %lu\n", largest_diag_prod2);


    if (largest_hor_prod > largest_ver_prod) 
        max_linear = largest_hor_prod;
    else
        max_linear = largest_ver_prod;

    if (largest_diag_prod1 > largest_diag_prod2) {
        if (largest_diag_prod1 > max_linear) 
            printf("Largest sum: %lu", largest_diag_prod1);
        else
            printf("Largest sum: %lu", max_linear);
    } else {
        if (largest_diag_prod2 > max_linear) 
            printf("Largest sum: %lu", largest_diag_prod2);
        else
            printf("Largest sum: %lu", max_linear);
    }



}

int largest_prod_diag_grid(int (*a)[M], int lo, int hi, int dir) {
    int mid = 0;
    mid = (lo + hi) / 2;
    int i = 0;
    int k = 0;
    int j = 0;
    unsigned long d_prod = 1;
    unsigned long left_prod = 1;
    unsigned long right_prod = 1;

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
                d_prod = largestDiagProduct(a, M - 1, lo, M - lo, 0);
            } else {
                k = (M - 1) - lo ;
                for (i = M - 1; i >= lo; i--) {
                    printf("%d ", a[i][k--]);
                }
                d_prod = largestDiagProduct(a, lo, 0, (M - 1) - lo,  1);
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
                d_prod = largestDiagProduct(a, lo, 0, lo,  0);
            } else {
                k = lo;
                for (j = M - 1; k >= 0; j--) {
                    printf("%d ", a[k--][j]);
                }
                printf("\n");
                d_prod = largestDiagProduct(a, 0, (M - 1) - lo, M - 1, 1); 
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

int largestDiagProduct(int (*a)[M], int x, int y_lo, int y_hi, int dir) {
    int mid_y = (y_lo + y_hi) / 2;
    unsigned long prod = 1;
    unsigned long right_prod = 1;
    unsigned long left_prod = 1;
    unsigned long cross_prod = 1;
    int i = 0;
    int k = 0;

    if (x >= M)
        return 0;
    printf("x: %d y_lo: %d y_hi: %d\n",  x, y_lo, y_hi);
    if ((y_hi - y_lo) + 1 == C) {
        if (!dir) {
            k = x;
            for (i = y_lo; i <= y_hi; i++) {
                printf("%d ", a[k--][i]);
                //prod *= a[k--][i];
            }
            printf("prod: %lu\n", prod);
            return prod;
        } else {
            k = x;
            for (i = y_lo; i <= y_hi; i++) {
                printf("%d ", a[k++][i]);
                //prod *= a[k++][i];
            }
            printf("dir : 1 prod: %lu\n", prod);
            return prod;
        }
    } else if (y_hi - y_lo <= C) {
        return 0;
    }
    if (!dir) {
        left_prod = largestDiagProduct(a, x, y_lo, mid_y, dir);
        cross_prod = largestDiagCrossProduct(a, x, mid_y, dir);
        x = x - 2;
        right_prod = largestDiagProduct(a, x, mid_y + 1, y_hi, dir);
    } else {
        left_prod = largestDiagProduct(a, x, y_lo, mid_y, dir);
        cross_prod = largestDiagCrossProduct(a, x, mid_y, dir);
        x = x + 2;
        right_prod = largestDiagProduct(a, x, mid_y + 1, y_hi, dir);
    }


    printf("left_prod: %lu right_prod: %lu cross_prod: %lu\n", left_prod, right_prod, cross_prod);
    

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

int largestDiagCrossProduct(int (*a)[M], int x, int mid, int dir) {
    int i = 0;
    int j = 0;
    int count = 0;
    unsigned long prod = 1;
    unsigned long max_cross = 0;
    int k = 0;
    int n = 0;

    if (!mid) 
        return 0;

    if (!dir) 
        n = x - 1;
    else 
        n = x + 1;
 
    k = n;
    printf("x: %d, mid: %d k: %d\n", x, mid, k);
    for (i = 0; i < C; i++) {
        for (j = -i, count = 0, prod = 1; count < C; count++, j++) {
            printf("k: %d j: %d\n", k, mid + j);
            if (!dir) 
                prod *= a[k--][mid + j];
            else
                prod *= a[k++][mid + j];
        }
        if (prod > max_cross) {
            max_cross = prod;
        }
        if (!dir)
            k = --n;
       else
           k = ++n;
    }
    printf("Cross prod: %lu\n", max_cross);
    return max_cross;
}

int largestHorizontalProduct(int (*a)[M], int x, int y_lo, int y_hi, int dir) {
    // divide y recursivley
    int mid_y = (y_lo + y_hi) / 2;
    unsigned long  prod = 1;
    unsigned long right_prod = 1;
    unsigned long left_prod = 1;
    unsigned long cross_prod = 1;
    int i = 0;

    printf("y_lo: %d y_hi: %d\n", y_lo, y_hi);
    if (((y_hi - y_lo) + 1) == C) {
        for (i = y_lo; i <= y_hi; i++) {
            if (!dir)
                prod *= a[x][i];
            else 
                prod *= a[i][x];
        }
        printf("prod: %lu\n", prod);
        return prod;
    } else if ((y_hi - y_lo) + 1 < C) {
        return 0;
    }

    left_prod = largestHorizontalProduct(a, x, y_lo, mid_y, dir);
    right_prod = largestHorizontalProduct(a, x, mid_y + 1, y_hi, dir);
    cross_prod = calculate_cross_product(a, x, mid_y, dir);

    printf("left_prod: %lu right_prod: %lu cross_prod: %lu\n", left_prod, right_prod, cross_prod);
    

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

int calculate_cross_product(int (*a)[M], int x, int mid, int dir) {
    int i = 0;
    int j = 0;
    int count = 0;
    unsigned long prod = 1;
    int max_cross = 0;

    for (i = 0; i < C; i++) {
        for (j = -i, count = 0, prod = 1; count < C; count++, j++) {
            if (!dir)
                prod *= a[x][mid + j];
            else 
                prod *= a[mid + j][x];
        }
        if (prod > max_cross) {
            max_cross = prod;
        }
    }
    return max_cross;
}

int largest_prod_in_grid(int (*a)[M], int lo, int hi, int direction) {
    int i = 0;
    int n = 0;
    int j = 0;
    int mid = 0;
    int m = 3;
    unsigned long h_prod = 0;
    unsigned long v_prod = 0;
    unsigned long left_prod = 1;
    unsigned long right_prod = 1;
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
            printf("h_prod: %lu\n", h_prod);
            return h_prod;
        } else {
            v_prod = largestHorizontalProduct(a, lo, 0, m, 1);
            printf("v_prod: %lu\n", v_prod);
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
