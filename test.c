#include <check.h>

#include "s21_decimal.h"

START_TEST(test_s21_add_1) {
  s21_decimal test_value_1 = {{1899999, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{100001, 0, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};

  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 2000000);
}
END_TEST

START_TEST(test_s21_add_2) {
  s21_decimal test_value_1 = {{199421, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{4433, 0, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  setsign(&test_value_2, 1);
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 199421 + (-4433));
}
END_TEST

START_TEST(test_s21_add_3) {
  s21_decimal test_value_1 = {{199421, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{4433, 0, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  setsign(&test_value_1, 1);
  s21_add(test_value_1, test_value_2, &result_dec);

  ck_assert_int_eq(result_dec.bits[0], 194988);
  ck_assert_int_eq(getsign(result_dec), 1);
}
END_TEST

START_TEST(test_s21_add_4) {
  s21_decimal test_value_1 = {{199421, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{4433, 0, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  setsign(&test_value_1, 1);
  setsign(&test_value_2, 1);
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 203854);
  ck_assert_int_eq(getsign(result_dec), 1);
}
END_TEST

START_TEST(test_s21_add_5) {
  s21_decimal test_value_1 = {{10000, 3, 10, 0}, 0};
  s21_decimal test_value_2 = {{5000, 2, 500, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 10000 + 5000);
  ck_assert_uint_eq(result_dec.bits[1], 3 + 2);
  ck_assert_uint_eq(result_dec.bits[2], 10 + 500);
}
END_TEST

START_TEST(test_s21_add_6) {
  s21_decimal test_value_1 = {{4294967295, 10, 10, 0}, 0};
  s21_decimal test_value_2 = {{1, 2, 20, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 0);
  ck_assert_uint_eq(result_dec.bits[1], 13);
  ck_assert_uint_eq(result_dec.bits[2], 30);
}
END_TEST

START_TEST(test_s21_add_7) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal test_value_2 = {{1, 1, 1, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  int result = s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result, 1);
}
END_TEST

START_TEST(test_s21_add_8) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal test_value_2 = {{1, 1, 1, 0}, 0};
  setsign(&test_value_2, 1);
  setsign(&test_value_1, 1);
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  int result = s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result, 2);
}
END_TEST

START_TEST(test_s21_add_9) {
  s21_decimal test_value_1 = {{123, 0, 0, 262144}, 0};
  s21_decimal test_value_2 = {{37, 0, 0, 196608}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 493);
  ck_assert_uint_eq(result_dec.bits[3], 262144);
}
END_TEST

START_TEST(test_s21_add_11) {
  s21_decimal src1 = {{1234, 0, 0, 0}, 0};
  s21_decimal src2 = {{1234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src2, 3);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 1232766);
  ck_assert_uint_eq(getexp(result), 3);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_12) {
  s21_decimal src1 = {{1234, 0, 0, 0}, 0};
  s21_decimal src2 = {{1234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setsign(&src2, 1);
  setexp(&src2, 3);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 1235234);
  ck_assert_uint_eq(getexp(result), 3);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_13) {
  s21_decimal src1 = {{1234, 0, 0, 0}, 0};
  s21_decimal src2 = {{221234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setsign(&src2, 1);
  setexp(&src2, 3);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 1455234);
  ck_assert_uint_eq(getexp(result), 3);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_14) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src2, 5);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 940299766);
  ck_assert_uint_eq(getexp(result), 5);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_15) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src1, 1);
  setexp(&src2, 6);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 940299766);
  ck_assert_uint_eq(getexp(result), 6);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_16) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src1, 4);
  setexp(&src2, 6);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 940066);
  ck_assert_uint_eq(getexp(result), 6);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_17) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{20234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src1, 4);
  setexp(&src2, 4);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 10831);
  ck_assert_uint_eq(getexp(result), 4);
  ck_assert_uint_eq(getsign(result), 0);
}
END_TEST

START_TEST(test_s21_add_18) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{1120234, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setsign(&src2, 1);
  setexp(&src1, 4);
  setexp(&src2, 4);
  s21_add(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 1129637);
  ck_assert_uint_eq(getexp(result), 4);
  ck_assert_uint_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_add_19) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  src1.bits[3] = 0x30000;
  src1.bits[2] = 0;
  src1.bits[1] = 0xFF;
  src1.bits[0] = 0x67E4F;
  src2.bits[3] = 0x60000;
  src2.bits[2] = 0;
  src2.bits[1] = 0xEA;
  src2.bits[0] = 0x67E4F;

  s21_decimal result_origin;
  result_origin.bits[3] = 0x60000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0x3E502;
  result_origin.bits[0] = 0x1963E2E7;
  s21_add(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_add_20) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}, 0};
  s21_decimal test_value_2 = {{100, 0, 0, 131072}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 0);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_21) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}, 0};
  s21_decimal test_value_2 = {{5, 1, 0, 131072}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 42949672);
  ck_assert_int_eq(result_dec.bits[1], 0);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
}
END_TEST

START_TEST(test_s21_add_22) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}, 0};
  s21_decimal test_value_2 = {{5, 0, 1, 131072}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  int error = s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4123168603);
  ck_assert_int_eq(result_dec.bits[1], 42949672);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_add_23) {
  s21_decimal test_value_1 = {{4294967295, 4294967295, 4294967290, 0}, 0};
  s21_decimal test_value_2 = {{165, 0, 1, 131072}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  int error = s21_add(test_value_1, test_value_2, &result_dec);
  ck_assert_int_eq(result_dec.bits[0], 4123168604);
  ck_assert_int_eq(result_dec.bits[1], 42949672);
  ck_assert_int_eq(result_dec.bits[2], 4294967291);
  ck_assert_int_eq(result_dec.bits[3], 0);
  ck_assert_int_eq(error, 0);
}
END_TEST

START_TEST(test_s21_sub_1) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{202, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 9201);
}
END_TEST

START_TEST(test_s21_sub_2) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{202098, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src2, 3);
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 9200902);
  ck_assert_int_eq(getexp(result), 3);
}
END_TEST

START_TEST(test_s21_sub_3) {
  s21_decimal src1 = {{9403, 0, 0, 0}, 0};
  s21_decimal src2 = {{202098, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src2, 3);
  setsign(&src1, 1);
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 9605098);
  ck_assert_int_eq(getexp(result), 3);
  ck_assert_int_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_4) {
  s21_decimal src1 = {{94030, 0, 0, 0}, 0};
  s21_decimal src2 = {{2020900000, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src1, 1);
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2020890597);
  ck_assert_int_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_5) {
  s21_decimal src1 = {{940300, 0, 0, 0}, 0};
  s21_decimal src2 = {{3029130816, 4, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 3028190516);
  ck_assert_int_eq(result.bits[1], 4);
  ck_assert_int_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_6) {
  s21_decimal src1 = {{940300, 0, 0, 0}, 0};
  s21_decimal src2 = {{202, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setsign(&src2, 2);
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 940098);
  ck_assert_int_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_sub_7) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  src1.bits[3] = 0b00000000000000010000000000000000;
  src1.bits[2] = 0;
  src1.bits[1] = 0;
  src1.bits[0] = 0b00000000000000000110011011110000;
  src2.bits[3] = 0b00000000000000110000000000000000;
  src2.bits[2] = 0;
  src2.bits[1] = 0;
  src2.bits[0] = 0b00000000000001000101000111010110;
  s21_decimal result_origin;
  result_origin.bits[3] = 0b00000000000000110000000000000000;
  result_origin.bits[2] = 0;
  result_origin.bits[1] = 0;
  result_origin.bits[0] = 0b00000000001000111110001111101010;
  s21_sub(src1, src2, &result);
  ck_assert_int_eq(result_origin.bits[3], result.bits[3]);
  ck_assert_int_eq(result_origin.bits[2], result.bits[2]);
  ck_assert_int_eq(result_origin.bits[1], result.bits[1]);
  ck_assert_int_eq(result_origin.bits[0], result.bits[0]);
}
END_TEST

START_TEST(test_s21_sub_8) {
  s21_decimal test_value_1 = {{1, 10, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4);
  ck_assert_uint_eq(result_dec.bits[2], 0);
}
END_TEST

START_TEST(test_s21_sub_9) {
  s21_decimal test_value_1 = {{1, 4, 5, 0}, 0};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967294);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(test_s21_sub_10) {
  s21_decimal test_value_1 = {{1, 0, 5, 0}, 0};
  s21_decimal test_value_2 = {{5000, 5, 0, 0}, 0};
  s21_decimal result_dec = {{0, 0, 0, 0}, 0};
  s21_sub(test_value_1, test_value_2, &result_dec);
  ck_assert_uint_eq(result_dec.bits[0], 4294962297);
  ck_assert_uint_eq(result_dec.bits[1], 4294967290);
  ck_assert_uint_eq(result_dec.bits[2], 4);
}
END_TEST

START_TEST(test_s21_mul_1) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float a = 9403.0e2;
  int b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_int_to_decimal(b, &src2);
  float res_origin = 189940600;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_2) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float a = 9403.0e2;
  float b = 9403.0e2;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  s21_mul(src1, src2, &result);
  ck_assert_float_eq(result.bits[0], 212244544);
  ck_assert_float_eq(result.bits[1], 20586);
  ck_assert_float_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_mul_3) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float a = 9403;
  float b = 202;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = 1899406;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_4) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float a = -32768;
  float b = 2;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -65536;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_5) {
  s21_decimal src1 = {{0, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float a = -32768;
  float b = 32768;
  float res_our_dec = 0.0;
  s21_from_float_to_decimal(a, &src1);
  s21_from_float_to_decimal(b, &src2);
  float res_origin = -1073741824;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_6) {
  s21_decimal src1 = {{0, 1, 0, 0}, 0};
  s21_decimal src2 = {{1, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  float res_our_dec = 0.0;
  float res_origin = 4294967296;
  s21_mul(src1, src2, &result);
  s21_from_decimal_to_float(result, &res_our_dec);
  ck_assert_float_eq(res_our_dec, res_origin);
}
END_TEST

START_TEST(test_s21_mul_7) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal src2 = {{2, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_mul_8) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 2147483648}, 0};
  s21_decimal src2 = {{2, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  int res = s21_mul(src1, src2, &result);
  ck_assert_int_eq(res, 2);
}
END_TEST

START_TEST(test_s21_div_1) {
  s21_decimal src1 = {{25, 0, 0, 0}, 0};
  s21_decimal src2 = {{5, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 5);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_2) {
  s21_decimal src1 = {{25, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  int res = s21_div(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_s21_div_3) {
  s21_decimal src1 = {{0, 1, 0, 0}, 0};
  s21_decimal src2 = {{2, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_4) {
  s21_decimal src1 = {{1000, 0, 0, 65536}, 0};
  s21_decimal src2 = {{2, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 50);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_5) {
  s21_decimal src1 = {{1000, 0, 0, 0}, 0};
  s21_decimal src2 = {{5, 0, 0, 65536}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_div_6) {
  s21_decimal src1 = {{1000, 0, 0, 0}, 0};
  s21_decimal src2 = {{5, 0, 0, 65536}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  s21_div(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 2000);
  ck_assert_int_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_div_7) {
  s21_decimal src1 = {{312768, 98785618, 312659, 0}, 0};
  s21_decimal src2 = {{582180, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src1, 3);

  s21_div(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 3316150127);
  ck_assert_uint_eq(result.bits[1], 2619555446);
  ck_assert_uint_eq(result.bits[2], 537048718);
  ck_assert_uint_eq(getsign(result), 1);
  ck_assert_uint_eq(getexp(result), 12);
}
END_TEST

START_TEST(test_s21_div_8) {
  s21_decimal src1 = {{478268, 9174998, 1391990, 0}, 0};
  s21_decimal src2 = {{76788, 3424, 12, 65536}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src1, 24);
  setexp(&src2, 1);
  s21_div(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 3009981321);
  ck_assert_uint_eq(result.bits[1], 2);
  ck_assert_uint_eq(result.bits[2], 0);
  ck_assert_uint_eq(getsign(result), 0);
  ck_assert_uint_eq(getexp(result), 28);
}
END_TEST

START_TEST(test_s21_div_9) {
  s21_decimal src1 = {{478268, 9174998, 1391990, 0}, 0};
  s21_decimal src2 = {{76788, 3424, 12, 65536}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src1, 1);
  setexp(&src2, 20);
  s21_div(src1, src2, &result);
  ck_assert_uint_eq(result.bits[0], 2304396071);
  ck_assert_uint_eq(result.bits[1], 3098785200);
  ck_assert_uint_eq(result.bits[2], 628832701);
  ck_assert_uint_eq(getsign(result), 0);
  ck_assert_uint_eq(getexp(result), 4);
}
END_TEST

START_TEST(test_s21_div_10) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal src2 = {{1, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src2, 1);
  int res = s21_div(src1, src2, &result);
  ck_assert_uint_eq(res, 1);
}
END_TEST

START_TEST(test_s21_div_11) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal src2 = {{1, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&src2, 1);
  setsign(&src1, 1);
  int res = s21_div(src1, src2, &result);
  ck_assert_uint_eq(res, 2);
}
END_TEST

START_TEST(test_s21_mod_1) {
  s21_decimal src1 = {{1, 0, 0, 0}, 0};
  s21_decimal src2 = {{2, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mod_2) {
  s21_decimal src1 = {{1, 0, 0, 0}, 0};
  s21_decimal src2 = {{0, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  int res = s21_mod(src1, src2, &result);
  ck_assert_int_eq(res, 3);
}
END_TEST

START_TEST(test_s21_mod_3) {
  s21_decimal src1 = {{1010, 0, 0, 65536}, 0};
  s21_decimal src2 = {{10, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mod_4) {
  s21_decimal src1 = {{101, 0, 0, 0}, 0};
  s21_decimal src2 = {{100, 0, 0, 65536}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 1);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
}
END_TEST

START_TEST(test_s21_mod_5) {
  s21_decimal src1 = {{12345, 0, 0, 0}, 0};
  s21_decimal src2 = {{12, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setsign(&src1, 1);
  setexp(&src1, 3);
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 345);
  ck_assert_int_eq(getsign(result), 1);
  ck_assert_int_eq(getexp(result), 3);
}
END_TEST

START_TEST(test_s21_mod_6) {
  s21_decimal src1 = {{12345, 0, 0, 0}, 0};
  s21_decimal src2 = {{1, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(getsign(result), 0);
  ck_assert_int_eq(getexp(result), 0);
}
END_TEST

START_TEST(test_s21_mod_7) {
  s21_decimal src1 = {{10, 0, 0, 0}, 0};
  s21_decimal src2 = {{15, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 10);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(getsign(result), 0);
  ck_assert_int_eq(getexp(result), 0);
}
END_TEST

START_TEST(test_s21_mod_8) {
  s21_decimal src1 = {{4294967295, 4294967295, 4294967295, 0}, 0};
  s21_decimal src2 = {{1, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_mod(src1, src2, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(getsign(result), 0);
  ck_assert_int_eq(getexp(result), 0);
}
END_TEST

START_TEST(test_s21_is_less_1) {
  s21_decimal test_value_1 = {{10, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{15, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_2) {
  s21_decimal test_value_1 = {{6739, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_3) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{6739, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_4) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{6739, 0, 0, 2147483648}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_5) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_6) {
  s21_decimal test_value_1 = {{19993, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{19993, 0, 0, 131072}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_7) {
  s21_decimal test_value_1 = {{0, 1, 0, 0}, 0};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_8) {
  s21_decimal test_value_1 = {{19993, 1, 0, 2147483648}, 0};
  s21_decimal test_value_2 = {{19993, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}, 0};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}, 0};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_less_or_equal_5) {
  s21_decimal test_value_1 = {{0, 1, 0, 0}, 0};
  s21_decimal test_value_2 = {{0, 1, 0, 0}, 0};
  ck_assert_int_eq(s21_is_less_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_1) {
  s21_decimal dst1 = {{12345, 0, 0, 0}, 0};
  s21_decimal dst2 = {{12, 0, 0, 0}, 0};
  setexp(&dst1, 4);
  setexp(&dst2, 1);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_2) {
  s21_decimal dst1 = {{12345, 0, 0, 0}, 0};
  s21_decimal dst2 = {{12, 0, 0, 0}, 0};
  setexp(&dst1, 4);
  setexp(&dst2, 1);
  setsign(&dst1, 1);
  setsign(&dst2, 1);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 1);
}
END_TEST

START_TEST(test_s21_is_greater_3) {
  s21_decimal dst1 = {{12345, 0, 0, 0}, 0};
  s21_decimal dst2 = {{12, 0, 0, 0}, 0};
  setexp(&dst1, 4);
  setexp(&dst2, 1);
  setsign(&dst2, 1);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 1);
  ck_assert_int_eq(s21_is_greater(dst2, dst1), 0);
}
END_TEST

START_TEST(test_s21_is_greater_4) {
  s21_decimal dst1 = {{0, 0, 0, 0}, 0};
  s21_decimal dst2 = {{0, 0, 0, 0}, 0};
  setexp(&dst1, 1);
  setexp(&dst2, 1);
  ck_assert_int_eq(s21_is_greater(dst1, dst2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_greater_or_equal_5) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_greater_or_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}, 0};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}, 0};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_equal_5) {
  s21_decimal test_value_1 = {{5000, 1, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 2, 0}, 0};
  ck_assert_int_eq(s21_is_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_1) {
  s21_decimal test_value_1 = {{0, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{0, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 0);
}
END_TEST

START_TEST(test_s21_is_not_equal_2) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5001, 0, 0, 0}, 0};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_3) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 2147483648}, 0};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_4) {
  s21_decimal test_value_1 = {{5000, 0, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 0, 131072}, 0};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_is_not_equal_5) {
  s21_decimal test_value_1 = {{5000, 1, 0, 0}, 0};
  s21_decimal test_value_2 = {{5000, 0, 2, 0}, 0};
  ck_assert_int_eq(s21_is_not_equal(test_value_1, test_value_2), 1);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_1) {
  s21_decimal result;
  s21_from_int_to_decimal(0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_2) {
  s21_decimal result;
  s21_from_int_to_decimal(-128, &result);
  ck_assert_int_eq(result.bits[0], 128);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_3) {
  s21_decimal result;
  s21_from_int_to_decimal(5000, &result);
  ck_assert_int_eq(result.bits[0], 5000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_4) {
  s21_decimal result;
  s21_from_int_to_decimal(-2147483648, &result);
  ck_assert_int_eq(result.bits[0], 2147483648);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_form_int_to_decimal_5) {
  s21_decimal result;
  s21_from_int_to_decimal(2147483647, &result);
  ck_assert_int_eq(result.bits[0], 2147483647);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_1) {
  s21_decimal result;
  float fres = 0;
  s21_from_float_to_decimal(0.03, &result);
  s21_from_decimal_to_float(result, &fres);
  ck_assert_int_eq(fres, 0.03);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_2) {
  s21_decimal result;
  s21_from_float_to_decimal(127.1234, &result);
  ck_assert_int_eq(result.bits[0], 1271234);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 262144);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_3) {
  s21_decimal result;
  float fres = 0;
  s21_from_float_to_decimal(-128.023, &result);
  s21_from_decimal_to_float(result, &fres);
  ck_assert_int_eq(fres, -128.023);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_4) {
  s21_decimal result;
  s21_from_float_to_decimal(22.14836E+03, &result);
  ck_assert_int_eq(result.bits[0], 2214836);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 131072);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_5) {
  s21_decimal result;
  s21_from_float_to_decimal(1.02E+09, &result);
  ck_assert_int_eq(result.bits[0], 1020000000);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_6) {
  s21_decimal result;
  s21_from_float_to_decimal(-333.2222, &result);
  ck_assert_int_eq(result.bits[0], 3332222);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 2147745792);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_7) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_8) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(-1.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_form_float_to_decimal_9) {
  s21_decimal result;
  int res = s21_from_float_to_decimal(0.0 / 0.0, &result);
  ck_assert_int_eq(result.bits[0], 0);
  ck_assert_int_eq(result.bits[1], 0);
  ck_assert_int_eq(result.bits[2], 0);
  ck_assert_int_eq(result.bits[3], 0);
  ck_assert_int_eq(res, 1);
}
END_TEST

START_TEST(test_s21_decimal_to_int_1) {
  int number = 0;
  s21_decimal src = {{2147483647, 0, 0, 0}, 0};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 2147483647);
}
END_TEST

START_TEST(test_s21_decimal_to_int_2) {
  int number = 0;
  s21_decimal src = {{0, 0, 0, 0}, 0};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, 0);
}
END_TEST

START_TEST(test_s21_decimal_to_int_3) {
  int number = 0;
  s21_decimal src = {{5000, 0, 0, 2147483648}, 0};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -5000);
}
END_TEST

START_TEST(test_s21_decimal_to_int_4) {
  int number = 0;
  s21_decimal src = {{2147483648, 0, 0, 2147483648}, 0};
  s21_from_decimal_to_int(src, &number);
  ck_assert_int_eq(number, -2147483648);
}
END_TEST

START_TEST(test_s21_decimal_to_float_1) {
  float number = 0.0;
  s21_decimal src = {{18122, 0, 0, 2147680256}, 0};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -18.122);
}
END_TEST

START_TEST(test_s21_decimal_to_float_2) {
  float number = 0.0;
  s21_decimal src = {{1812, 0, 0, 2147483648}, 0};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -1812);
}
END_TEST

START_TEST(test_s21_decimal_to_float_3) {
  float number = 0.0;
  s21_decimal src = {{23450987, 0, 0, 2147745792}, 0};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, -2345.0987);
}
END_TEST

START_TEST(test_s21_decimal_to_float_4) {
  float number = 0.0;
  s21_decimal src = {{4294967295, 4294967295, 0, 0}, 0};
  s21_from_decimal_to_float(src, &number);
  ck_assert_float_eq(number, 0xFFFFFFFFFFFFFFFF);
}
END_TEST

START_TEST(test_s21_floor_1) {
  s21_decimal value_1 = {{673988, 0, 0, 262144}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_2) {
  s21_decimal value_1 = {{679988, 0, 0, 262144}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_3) {
  s21_decimal value_1 = {{679988, 0, 0, 2147745796}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 68);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_floor_4) {
  s21_decimal value_1 = {{4294967295, 4294967295, 4294967295, 131072}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 687194767);
  ck_assert_float_eq(result.bits[1], 4123168604);
  ck_assert_float_eq(result.bits[2], 42949672);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_5) {
  s21_decimal value_1 = {{5, 1, 0, 131072}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 42949673);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_6) {
  s21_decimal value_1 = {{4294967295, 0, 1, 131072}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118277);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_floor_7) {
  s21_decimal value_1 = {{115, 0, 1, 2147483648}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168606);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_floor_8) {
  s21_decimal value_1 = {{5, 0, 1, 0}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_floor(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168604);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_1) {
  s21_decimal value_1 = {{5, 0, 1, 0}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4123168604);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_2) {
  s21_decimal value_1 = {{5, 1, 1, 0}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118277);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_3) {
  s21_decimal value_1 = {{155, 1, 1, 0}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118279);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_round_4) {
  s21_decimal value_1 = {{155, 1, 1, 2147483648}, 0};
  setexp(&value_1, 2);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 4166118279);
  ck_assert_float_eq(result.bits[1], 42949672);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_round_5) {
  s21_decimal value_1 = {{0, 1, 0, 0}, 0};
  setexp(&value_1, 1);
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_round(value_1, &result);
  ck_assert_float_eq(result.bits[0], 429496730);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_negate_1) {
  s21_decimal value_1 = {{155, 1, 1, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_negate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 2147483648);
}
END_TEST

START_TEST(test_s21_negate_2) {
  s21_decimal value_1 = {{155, 1, 1, 2147483648}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_negate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 155);
  ck_assert_float_eq(result.bits[1], 1);
  ck_assert_float_eq(result.bits[2], 1);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_1) {
  s21_decimal value_1 = {{673988, 0, 0, 262144}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  s21_truncate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 67);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

START_TEST(test_s21_truncate_2) {
  s21_decimal value_1 = {{2744406, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&value_1, 4);
  setsign(&value_1, 1);
  s21_truncate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 274);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(getsign(result), 1);
}
END_TEST

START_TEST(test_s21_truncate_3) {
  s21_decimal value_1 = {{123, 0, 0, 0}, 0};
  s21_decimal result = {{0, 0, 0, 0}, 0};
  setexp(&value_1, 4);

  s21_truncate(value_1, &result);
  ck_assert_float_eq(result.bits[0], 0);
  ck_assert_float_eq(result.bits[1], 0);
  ck_assert_float_eq(result.bits[2], 0);
  ck_assert_float_eq(result.bits[3], 0);
}
END_TEST

int main() {
  Suite *s1 = suite_create("s21_decimal: ");
  TCase *tc1_1 = tcase_create("s21_decimal: ");
  SRunner *sr = srunner_create(s1);
  int result;
  suite_add_tcase(s1, tc1_1);

  // tests_add
  tcase_add_test(tc1_1, test_s21_add_1);
  tcase_add_test(tc1_1, test_s21_add_2);
  tcase_add_test(tc1_1, test_s21_add_3);
  tcase_add_test(tc1_1, test_s21_add_4);
  tcase_add_test(tc1_1, test_s21_add_5);
  tcase_add_test(tc1_1, test_s21_add_6);
  tcase_add_test(tc1_1, test_s21_add_7);
  tcase_add_test(tc1_1, test_s21_add_8);
  tcase_add_test(tc1_1, test_s21_add_8);
  tcase_add_test(tc1_1, test_s21_add_9);
  tcase_add_test(tc1_1, test_s21_add_11);
  tcase_add_test(tc1_1, test_s21_add_12);
  tcase_add_test(tc1_1, test_s21_add_13);
  tcase_add_test(tc1_1, test_s21_add_14);
  tcase_add_test(tc1_1, test_s21_add_15);
  tcase_add_test(tc1_1, test_s21_add_16);
  tcase_add_test(tc1_1, test_s21_add_17);

  tcase_add_test(tc1_1, test_s21_add_18);
  tcase_add_test(tc1_1, test_s21_add_19);
  tcase_add_test(tc1_1, test_s21_add_20);
  tcase_add_test(tc1_1, test_s21_add_21);
  tcase_add_test(tc1_1, test_s21_add_22);
  tcase_add_test(tc1_1, test_s21_add_23);

  // tests_sub
  tcase_add_test(tc1_1, test_s21_sub_1);
  tcase_add_test(tc1_1, test_s21_sub_2);
  tcase_add_test(tc1_1, test_s21_sub_3);
  tcase_add_test(tc1_1, test_s21_sub_4);
  tcase_add_test(tc1_1, test_s21_sub_5);
  tcase_add_test(tc1_1, test_s21_sub_6);
  tcase_add_test(tc1_1, test_s21_sub_7);
  tcase_add_test(tc1_1, test_s21_sub_8);
  tcase_add_test(tc1_1, test_s21_sub_9);
  tcase_add_test(tc1_1, test_s21_sub_10);

  // tests_mul
  tcase_add_test(tc1_1, test_s21_mul_1);
  tcase_add_test(tc1_1, test_s21_mul_2);
  tcase_add_test(tc1_1, test_s21_mul_3);
  tcase_add_test(tc1_1, test_s21_mul_4);
  tcase_add_test(tc1_1, test_s21_mul_5);
  tcase_add_test(tc1_1, test_s21_mul_6);
  tcase_add_test(tc1_1, test_s21_mul_7);
  tcase_add_test(tc1_1, test_s21_mul_8);

  // tests_div
  tcase_add_test(tc1_1, test_s21_div_1);
  tcase_add_test(tc1_1, test_s21_div_2);
  tcase_add_test(tc1_1, test_s21_div_3);
  tcase_add_test(tc1_1, test_s21_div_4);
  tcase_add_test(tc1_1, test_s21_div_5);
  tcase_add_test(tc1_1, test_s21_div_6);
  tcase_add_test(tc1_1, test_s21_div_7);
  tcase_add_test(tc1_1, test_s21_div_8);
  tcase_add_test(tc1_1, test_s21_div_9);
  tcase_add_test(tc1_1, test_s21_div_10);
  tcase_add_test(tc1_1, test_s21_div_11);

  // tests_mod
  tcase_add_test(tc1_1, test_s21_mod_1);
  tcase_add_test(tc1_1, test_s21_mod_2);
  tcase_add_test(tc1_1, test_s21_mod_3);
  tcase_add_test(tc1_1, test_s21_mod_4);
  tcase_add_test(tc1_1, test_s21_mod_5);
  tcase_add_test(tc1_1, test_s21_mod_6);
  tcase_add_test(tc1_1, test_s21_mod_7);
  tcase_add_test(tc1_1, test_s21_mod_8);

  // tests_is_less
  tcase_add_test(tc1_1, test_s21_is_less_1);
  tcase_add_test(tc1_1, test_s21_is_less_2);
  tcase_add_test(tc1_1, test_s21_is_less_3);
  tcase_add_test(tc1_1, test_s21_is_less_4);
  tcase_add_test(tc1_1, test_s21_is_less_5);
  tcase_add_test(tc1_1, test_s21_is_less_6);
  tcase_add_test(tc1_1, test_s21_is_less_7);
  tcase_add_test(tc1_1, test_s21_is_less_8);

  // tests_is_less_or_equal
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_less_or_equal_5);

  // tests_is_greater
  tcase_add_test(tc1_1, test_s21_is_greater_1);
  tcase_add_test(tc1_1, test_s21_is_greater_2);
  tcase_add_test(tc1_1, test_s21_is_greater_3);
  tcase_add_test(tc1_1, test_s21_is_greater_4);

  // tests_is_greater_or_equal
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_1);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_2);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_3);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_4);
  tcase_add_test(tc1_1, test_s21_is_greater_or_equal_5);

  // tests_is_equal
  tcase_add_test(tc1_1, test_s21_is_equal_1);
  tcase_add_test(tc1_1, test_s21_is_equal_2);
  tcase_add_test(tc1_1, test_s21_is_equal_3);
  tcase_add_test(tc1_1, test_s21_is_equal_4);
  tcase_add_test(tc1_1, test_s21_is_equal_5);

  // tests_is_not_equal
  tcase_add_test(tc1_1, test_s21_is_not_equal_1);
  tcase_add_test(tc1_1, test_s21_is_not_equal_2);
  tcase_add_test(tc1_1, test_s21_is_not_equal_3);
  tcase_add_test(tc1_1, test_s21_is_not_equal_4);
  tcase_add_test(tc1_1, test_s21_is_not_equal_5);

  // tests_from_int_to_decimal
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_1);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_2);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_int_to_decimal_5);

  // tests_from_float_to_decimal
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_1);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_2);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_3);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_4);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_5);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_6);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_7);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_8);
  tcase_add_test(tc1_1, test_s21_form_float_to_decimal_9);

  // tests_from_decimal_to_int
  tcase_add_test(tc1_1, test_s21_decimal_to_int_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_3);
  tcase_add_test(tc1_1, test_s21_decimal_to_int_4);

  // tests_from_decimal_to_float
  tcase_add_test(tc1_1, test_s21_decimal_to_float_1);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_2);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_3);
  tcase_add_test(tc1_1, test_s21_decimal_to_float_4);

  //  test_floor
  tcase_add_test(tc1_1, test_s21_floor_1);
  tcase_add_test(tc1_1, test_s21_floor_2);
  tcase_add_test(tc1_1, test_s21_floor_3);
  tcase_add_test(tc1_1, test_s21_floor_4);
  tcase_add_test(tc1_1, test_s21_floor_5);
  tcase_add_test(tc1_1, test_s21_floor_6);
  tcase_add_test(tc1_1, test_s21_floor_7);
  tcase_add_test(tc1_1, test_s21_floor_8);

  // tests_round
  tcase_add_test(tc1_1, test_s21_round_1);
  tcase_add_test(tc1_1, test_s21_round_2);
  tcase_add_test(tc1_1, test_s21_round_3);
  tcase_add_test(tc1_1, test_s21_round_4);
  tcase_add_test(tc1_1, test_s21_round_5);

  // tests_negate
  tcase_add_test(tc1_1, test_s21_negate_1);
  tcase_add_test(tc1_1, test_s21_negate_2);

  // tests_truncate
  tcase_add_test(tc1_1, test_s21_truncate_1);
  tcase_add_test(tc1_1, test_s21_truncate_2);
  tcase_add_test(tc1_1, test_s21_truncate_3);

  srunner_run_all(sr, CK_ENV);
  result = srunner_ntests_failed(sr);
  srunner_free(sr);
  return result == 0 ? 0 : 1;
}
