#define SIGNBIT 0x80000000
#include <math.h>
#include <stdio.h>

typedef enum {
  s21_NORMAL_VALUE = 0,
  s21_INFINITY = 1,
  s21_NEGATIVE_INFINITY = 2,
  s21_NAN = 3,
} value_type_t;

typedef struct {
  unsigned int bits[4];
  value_type_t value_type;
} s21_decimal;

typedef union {
  unsigned int ui;
  float fl;
} floatbits;

void normal_result(s21_decimal *value_1);
int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
void setexp(s21_decimal *src, unsigned int exp);
unsigned int gotmask(int bit);
int getbit(s21_decimal src, int bit);
void setbit(s21_decimal *dst, int bit, int znach);
void setsign(s21_decimal *src, int sign);
unsigned int getexp(s21_decimal src);
int multi10(s21_decimal *val1);
int plus(s21_decimal val1, s21_decimal val2, s21_decimal *result);
int upscale(s21_decimal *src);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int dicrement(s21_decimal *src);

int s21_is_less(s21_decimal src, s21_decimal dst);
int s21_is_equal(s21_decimal src, s21_decimal dst);
int s21_is_not_equal(s21_decimal src, s21_decimal dst);
int getsign(s21_decimal src);
int see_bit(s21_decimal x, int mode);
int s21_is_greater(s21_decimal src, s21_decimal dst);
int s21_is_less_or_equal(s21_decimal src, s21_decimal dst);
int s21_is_greater_or_equal(s21_decimal src, s21_decimal dst);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int dop_code(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div_ost(s21_decimal ost, s21_decimal value_2, s21_decimal *result);
int s21_div_int(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int down_scale(s21_decimal *src);
void normal_scale(s21_decimal *value_1, s21_decimal *value_2);
int s21_truncate(s21_decimal value, s21_decimal *result);
int s21_negate(s21_decimal value, s21_decimal *result);
int s21_floor(s21_decimal value, s21_decimal *result);
int s21_round(s21_decimal value, s21_decimal *result);

void shift_div(s21_decimal *value, int shear);
void reverse_shift_div(s21_decimal *value, int shear);
int getbit_div(s21_decimal src, int bit);
void setbit_div(s21_decimal *dst, int bit, int znach);
int s21_add_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int div_div(s21_decimal value_1, s21_decimal *value_2, s21_decimal *result,
            s21_decimal *res, s21_decimal *res2, int *shear);
int s21_from_decimal_to_float(s21_decimal src, float *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);

int s21_shift(s21_decimal *number);
void set_1_bit(unsigned int *value, int BitNumber);
void set_0_bit(unsigned int *value, int BitNumber);
int s21_addiction_logic(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result);
int s21_10_conv(s21_decimal value);
int test_bit(unsigned int value, int BitNumber);
void s21_rev_10_conv(s21_decimal *value, int result);
void s21_init_decimal(s21_decimal *dst);