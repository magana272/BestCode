#include "matrix.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <omp.h>

// Include SSE intrinsics
#if defined(_MSC_VER)
#include <intrin.h>
#elif defined(__GNUC__) && (defined(__x86_64__) || defined(__i386__))
#include <immintrin.h>
#include <x86intrin.h>
#endif

/* Below are some intel intrinsics that might be useful
 * void _mm256_storeu_pd (double * mem_addr, __m256d a)
 * __m256d _mm256_set1_pd (double a)
 * __m256d _mm256_set_pd (double e3, double e2, double e1, double e0)
 * __m256d _mm256_loadu_pd (double const * mem_addr)
 * __m256d _mm256_add_pd (__m256d a, __m256d b)
 * __m256d _mm256_sub_pd (__m256d a, __m256d b)
 * __m256d _mm256_fmadd_pd (__m256d a, __m256d b, __m256d c)
 * __m256d _mm256_mul_pd (__m256d a, __m256d b)
 * __m256d _mm256_cmp_pd (__m256d a, __m256d b, const int imm8)
 * __m256d _mm256_and_pd (__m256d a, __m256d b)
 * __m256d _mm256_max_pd (__m256d a, __m256d b)
*/

/* Generates a random double between low and high */
double rand_double(double low, double high) {
    double range = (high - low);
    double div = RAND_MAX / range;
    return low + (rand() / div);
}

/* Generates a random matrix */
void rand_matrix(matrix *result, unsigned int seed, double low, double high) {
    srand(seed);
    for (int i = 0; i < result->rows; i++) {
        for (int j = 0; j < result->cols; j++) {
            set(result, i, j, rand_double(low, high));
        }
    }
}

/*
 * Allocates space for a matrix struct pointed to by the double pointer mat with
 * `rows` rows and `cols` columns. You should also allocate memory for the data array
 * and initialize all entries to be zeros. `parent` should be set to NULL to indicate that
 * this matrix is not a slice. You should also set `ref_cnt` to 1.
 * You should return -1 if either `rows` or `cols` or both have invalid values, or if any
 * call to allocate memory in this function fails. Return 0 upon success.
 */
int allocate_matrix(matrix **mat, int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    if ((rows <=0) || (cols<=0)){
      return -1;
    }
    (*mat)->data  = (double*) calloc(cols*row, sizeof(double));
    (*mat)->ref_cnt = 1;
    return 0;
}

/*
 * Allocates space for a matrix struct pointed to by `mat` with `rows` rows and `cols` columns.
 * Its data should point to the `offset`th entry of `from`'s data (you do not need to allocate memory)
 * for the data field. `parent` should be set to `from` to indicate this matrix is a slice of `from`.
 * You should return -1 if either `rows` or `cols` or both are non-positive or if any
 * call to allocate memory in this function fails. Return 0 upon success.
 */
int allocate_matrix_ref(matrix **mat, matrix *from, int offset, int rows, int cols) {
    /* TODO: YOUR CODE HERE */
    if ((rows <=0) || (cols<=0)){
      return -1;
    }
    *mat = (matrix*)malloc(sizeof(matrix));
    (*mat)->rows = rows;
    (*mat)->cols = cols;
    (*mat)->data = (from->data)[offset];
    (*mat)->parent = from;
    retun 0;

}

/*
 * You need to make sure that you only free `mat->data` if `mat` is not a slice and has no existing slices,
 * or if `mat` is the last existing slice of its parent matrix and its parent matrix has no other references
 * (including itself). You cannot assume that mat is not NULL.
 */
void deallocate_matrix(matrix *mat) {
    /* TODO: YOUR CODE HERE */
    while((mat->parent) == NULL){
      deallocate_matrix(mat->parent);
    }
    free(mat->data);
}

/*
 * Returns the double value of the matrix at the given row and column.
 * You may assume `row` and `col` are valid.
 */
double get(matrix *mat, int row, int col) {
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int step_ = (cols_ * row_)col;
    return (mat->data)[step_*(cols-1)+ (row-1)];
}

/*
 * Sets the value at the given row and column to val. You may assume `row` and
 * `col` are valid
 */
void set(matrix *mat, int row, int col, double val) {
    /* TODO: YOUR CODE HERE */
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int step_ = (cols_ * row_)col;
    (mat->data)[step_*(cols-1)+ (row-1)] = val;

}

/*
 * Sets all entries in mat to val
 */
void fill_matrix(matrix *mat, double val) {
    /* TODO: YOUR CODE HERE */
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int size = (cols_ * row_);
    int i = 0;
    for(i = 0 ; i < size; i++){
    (mat->data)[i] = val;
  }
}

/*
 * Store the result of adding mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int add_matrix(matrix *result, matrix *mat1, matrix *mat2) {
  int cols_ = mat->cols;
  int rows_ = mat->rows;
  int size = (cols_ * row_);
  int i = 0;
  for(i = 0 ; i < size; i++){
  (result->data)[i] = (mat1->data)[i] + (mat1->data)[i];
  }
  return 0
}

/*
 * Store the result of subtracting mat2 from mat1 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int sub_matrix(matrix *result, matrix *mat1, matrix *mat2) {
    /* TODO: YOUR CODE HERE */
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int size = (cols_ * row_);
    int i = 0;
    for(i = 0 ; i < size; i++){
    (result->data)[i] = (mat1->data)[i] - (mat1->data)[i];
    }
    return 0
  }
}

/*
 * Store the result of multiplying mat1 and mat2 to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that matrix multiplication is not the same as multiplying individual elements.
 */
int mul_matrix(matrix *result, matrix *mat1, matrix *mat2) {
    /* TODO: YOUR CODE HERE */
    double* mat1_data = mat1->data;
    double* mat2_data = mat2->data;
    double* result_data = result->data;
    int cols_1 = mat1->cols;
    int rows_1 = mat1->rows;
    int cols_2 = mat2->cols;
    int rows_2 = mat2->rows;
    int size = (cols_ * row_);
    int i ;
    int j ;
    int k ;
    if(cols_1 != rows_2){
      return -1;
    }
    for (int i = 0; i < rows_1; i++) {
        for (int j = 0; j < cols_2; j++) {
            double sum = 0.0;
            for (int k = 0; k < cols_2; k++) {
            sum = sum + mat1_data[i * cols_1 + k] * mat2_data[k * col2 + j];
            }
            result_data[i * col2 + j] = sum;
        }
    }
}

/*
 * Store the result of raising mat to the (pow)th power to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 * Remember that pow is defined with matrix multiplication, not element-wise multiplication.
 */
int pow_matrix(matrix *result, matrix *mat, int pow) {
      int times = pow;
      int cols_ = mat->cols;
      int rows_ = mat->rows;
      int size = cols_*rows_;
      int recols_ = reresult->cols;
      int rerows_ = reresult->rows;
      double* result_data = result->data;
      double* mat_data = mat->data;
      int i;
      int j;
      int k;
      if (pow < 0){
        return -1;
      }
      if (pow == 0){
        for(i =0; i < cols_; i++){
            for(j =0; j < rows_; j += rows_ ){
              result_data[cols_*i+ i] = 1.0;
              }
          }
      }
      if (pow== 1){
        for(k=0; i<size; k++){
          result_data[k] = mat_data[k];
        }
      }
      if(pow >1){
      while (times > 0) {
        mul_matrix(result, mat, mat);
        times--;
      }
    }
    return 0;
}

/*
 * Store the result of element-wise negating mat's entries to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int neg_matrix(matrix *result, matrix *mat) {
    /* TODO: YOUR CODE HERE */
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int size = cols_*rows_;
    int i = 0;
    for(i = 0 ; i < size; i++){
      (result->data)[i]= -(mat->data[i]);
}

/*
 * Store the result of taking the absolute value element-wise to `result`.
 * Return 0 upon success and a nonzero value upon failure.
 */
int abs_matrix(matrix *result, matrix *mat) {
    /* TODO: YOUR CODE HERE */
    int cols_ = mat->cols;
    int rows_ = mat->rows;
    int size = cols_*rows_;
    int i = 0;
    double check;
    for(i = 0 ; i < size; i++){
      check = mat->data[i]
      if (check >=0){
      (result->data)[i]= mat->data[i]);
    }
      else{
      (result->data)[i]= -(mat->data[i]);
    }
}
