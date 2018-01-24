#include <arm_neon.h>
#include <stdio.h>


void neon_float_matrix_vec_mul(const float *matrix, const float *vec, float *vec_ret, int row, int col) {
        float32x4_t sum, a, x;
        for (int i = 0; i < row; i++) {
                sum = vdupq_n_f32(0);
                for (int j = 0; j < col; j += 4) {
                        a = vld1q_f32(matrix + i*col + j);
                        x = vld1q_f32(vec + j);
                        sum = vmlaq_f32(sum, a, x);
                }
                vec_ret[i] = vgetq_lane_f32(sum, 0)
                        +vgetq_lane_f32(sum, 1)
                        +vgetq_lane_f32(sum, 2)
                        +vgetq_lane_f32(sum, 3);
        }
}


int main()
{
    const int MATRIX_SIZE = 16;
    float mat1[]={1.1,1.2,1.3,1.4,
                  1.5,1.6,1.7,1.8,
                  1.9,2.0,2.1,2.2,
                  2.3,2.4,2.5,2.6};
    float mat2[]={2.1,2.2,2.3,2.4,
                  2.5,2.6,2.7,2.8,
                  2.9,3.0,3.1,3.2,
                  3.3,3.4,3.5,3.6};
    float mat3[MATRIX_SIZE];
	neon_float_matrix_vec_mul(mat1,mat2,&mat3[0],4,4);
    for(int i=0;i<MATRIX_SIZE;i++){
        printf("%f\n",mat3[i]);
    }
    printf("end\n");
    return 0;
}
