#include "s21_decimal.h"

#include <math.h>

char bitexp(float src) {
  floatbits a = {.fl = src};
  char sca = (a.ui >> 23) - 127;
  return sca;
}

void normal_result(s21_decimal *value_1) {
  s21_decimal dec = {{10, 0, 0, 0}, 0};
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  s21_decimal result = *value_1;
  s21_decimal value_2 = {{0, 0, 0, 0}, 0};
  int exp = getexp(*value_1);
  int sign = getsign(*value_1);
  for (int i = 0; i < exp; i++) {
    value_2 = nool;
    s21_div_int(*value_1, dec, &value_2);
    setexp(&value_2, exp - i - 1);
    if (s21_is_equal(*value_1, value_2)) {
      result = nool;
      result = value_2;
    } else {
      i = 100;
    }
  }
  *value_1 = nool;
  *value_1 = result;
  setsign(value_1, sign);
}

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal res2 = {{0, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};
  s21_decimal one = {{1, 0, 0, 0}, 0};
  s21_decimal ost = {{0, 0, 0, 0}, 0};
  int shear = 0, chek, error = 0;
  int exp1, exp2, max_exp = 0, sign = 0;

  if (getsign(value_1)) sign = 1;
  exp1 = getexp(value_1);
  exp2 = getexp(value_2);
  if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) error = 3;
  if (!error) {
    if (exp1 || exp2) {
      if (exp1 > exp2)
        max_exp = exp1;
      else
        max_exp = exp2;
      normal_scale(&value_1, &value_2);
    }
    setsign(&value_1, 0);
    setsign(&value_2, 0);
    if (!s21_is_less(value_2, one)) {
      chek = div_div(value_1, &value_2, result, &res, &res2, &shear);
      if (chek == 0) {
        s21_add_div(res2, value_2, &ost);
      } else {
        ost = res2;
      }
      reverse_shift_div(&ost, shear);
      if (shear < 0) ost = value_1;
      *result = ost;
      if (result->bits[0] || result->bits[1] || result->bits[2])
        setexp(result, max_exp);
      normal_result(result);
      setsign(result, sign);
    }
  } else {
    *result = value_2;
  }
  return error;
}

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init_decimal(result);
  s21_decimal dop_value_2 = value_2;
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};
  s21_decimal res2 = {{0, 0, 0, 0}, 0};
  s21_decimal ost = {{0, 0, 0, 0}, 0};
  int shear, chek = 1, exp, error = 0, sign = 0;
  int exp_shift = getexp(value_1) - getexp(value_2);
  if (!value_2.bits[0] && !value_2.bits[1] && !value_2.bits[2]) error = 3;

  if (!error) {
    if (getsign(value_1) != getsign(value_2)) sign = 1;

    chek = div_div(value_1, &value_2, result, &res, &res2, &shear);

    if (chek == 0) {
      s21_add_div(res2, value_2, &ost);
    } else {
      ost = res2;
    }
    if (shear < 0) {
      ost = res;
    }

    reverse_shift_div(&ost, shear);
    if (ost.bits[0] != 0 || ost.bits[1] != 0 || ost.bits[2] != 0)
      s21_div_ost(ost, dop_value_2, result);
    exp = getexp(*result);

    if (exp_shift > 0) {
      if (exp_shift + exp <= 28) {
        setexp(result, exp + exp_shift);
      } else {
        exp_shift = (exp_shift + exp) - 28;
        for (int i = 0; i < exp_shift; i++) {
          setexp(result, 1);
          down_scale(result);
          res = nool;
          s21_truncate(*result, &res);
          *result = res;
        }
        setexp(result, 28);
      }
    } else if (exp_shift < 0) {
      if (exp_shift + exp >= 0) {
        setexp(result, exp + exp_shift);
      } else {
        exp_shift = exp_shift + exp;
        exp_shift = exp_shift * -1;
        setexp(result, 0);
        for (int i = 0; i < exp_shift; i++) {
          if (multi10(result)) error = 1;
        }
      }
    }
    normal_result(result);
    setsign(result, sign);
  }
  if (error == 1 && sign) error = 2;
  return error;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  double result = 0;
  int status = 0;
  int off = 0;
  for (int i = 0; i < 96; i++) {
    int x = 0;
    if ((src.bits[i / 32] & (x = pow(2, i % 32))) != 0) {
      result += pow(2, i);
    }
  }
  if ((off = (src.bits[3] & ~0x80000000) >> 16) > 0) {
    for (int i = off; i > 0; i--) {
      result /= 10.0;
    }
  }
  *dst = (float)result;
  if (*dst < result) {
    status = 1;
  }
  *dst *= src.bits[3] >> 31 ? -1 : 1;
  return status;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int status = 0;
  for (unsigned int i = 0; i < getexp(src); i++) {
    down_scale(&src);
  }
  s21_decimal res = {{0, 0, 0, 0}, 0};
  s21_truncate(src, &res);
  if (res.bits[1] || res.bits[2]) {
    status = 1;
  }
  if (dst) {
    int sign = (getsign(res) ? -1 : 1);
    *dst = res.bits[0] * sign;
  } else {
    status = 1;
  }
  return status;
}

int s21_div_ost(s21_decimal ost, s21_decimal value_2, s21_decimal *result) {
  s21_decimal dop_value_2 = value_2;
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};
  s21_decimal res2 = {{0, 0, 0, 0}, 0};
  s21_decimal res_ost = {{0, 0, 0, 0}, 0};
  s21_decimal dop_res = {{0, 0, 0, 0}, 0};
  s21_decimal dop_res2 = {{0, 0, 0, 0}, 0};
  s21_decimal one = {{1, 0, 0, 0}, 0};
  static int res_exp = 0;
  int shear, chek = 1, flag = 0;

  multi10(&ost);
  chek = div_div(ost, &value_2, &res_ost, &res, &res2, &shear);

  if (shear >= 0) ost = nool;
  if (chek == 0) {
    s21_add_div(res2, value_2, &ost);
  } else {
    ost = res2;
  }
  if (shear < 0) {
    ost = res;
  }
  reverse_shift_div(&ost, shear);
  dop_res = *result;
  if (multi10(&dop_res) == 0 && res_exp != 28) {
    dop_res2 = dop_res;
    dop_res = nool;
    if (s21_add(dop_res2, res_ost, &dop_res) == 0) {
      *result = dop_res;
    } else {
      flag = 1;
    }
  } else {
    flag = 1;
  }
  if (!flag && res_exp != 28) {
    res_exp++;
    if (ost.bits[0] != 0 || ost.bits[1] != 0 || ost.bits[2] != 0) {
      if (res_exp < 29) {
        s21_div_ost(ost, dop_value_2, result);
      }
    }
  } else {
    dop_res = nool;
    if (res_ost.bits[0] > 4) {
      if (s21_add(*result, one, &dop_res) == 0) {
        *result = dop_res;
      }
    }
  }

  setexp(result, res_exp);
  return 0;
}

int div_div(s21_decimal value_1, s21_decimal *value_2, s21_decimal *result,
            s21_decimal *res, s21_decimal *res2, int *shear) {
  s21_decimal dop_value = {{0, 0, 0, 0}, 0};
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  int chek = 1;
  *shear = dop_code(value_1, *value_2, &dop_value);
  shift_div(value_2, *shear);
  *res = value_1;

  for (int i = 0; i < *shear + 1; i++) {
    if (i) {
      shift_div(res2, 1);
      *res = *res2;
    }
    *res2 = nool;
    if (chek == 1) {
      s21_add_div(*res, dop_value, res2);
      if (getbit_div(*res2, 98) == 0) {
        chek = 1;
        setbit_div(result, *shear + 1 - i, 1);
      } else {
        chek = 0;
        setbit_div(result, *shear + 1 - i, 0);
      }
    } else {
      s21_add_div(*res, *value_2, res2);
      if (getbit_div(*res2, 98) == 1) {
        chek = 0;
        setbit_div(result, *shear + 1 - i, 0);
      } else {
        chek = 1;
        setbit_div(result, *shear + 1 - i, 1);
      }
    }
  }

  return chek;
}

int s21_div_int(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal res2 = {{0, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};
  int shear;
  div_div(value_1, &value_2, result, &res, &res2, &shear);
  return 0;
}

void shift_div(s21_decimal *value, int shear) {
  for (int i = 0; i < shear; i++) {
    value->bits[3] <<= 1;
    if (getbit_div(*value, 96)) setbit_div(value, 97, 1);
    value->bits[2] <<= 1;
    if (getbit_div(*value, 64)) setbit_div(value, 65, 1);
    value->bits[1] <<= 1;
    if (getbit_div(*value, 32)) setbit_div(value, 33, 1);
    value->bits[0] <<= 1;
  }
}

void reverse_shift_div(s21_decimal *value, int shear) {
  for (int i = 0; i < shear; i++) {
    value->bits[0] >>= 1;
    if (getbit_div(*value, 33)) setbit_div(value, 32, 1);
    value->bits[1] >>= 1;
    if (getbit_div(*value, 65)) setbit_div(value, 64, 1);
    value->bits[2] >>= 1;
    if (getbit_div(*value, 97)) setbit_div(value, 96, 1);
    value->bits[3] >>= 1;
  }
}

int dop_code(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_decimal one = {{1, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};
  int pos1 = 0, pos2 = 0, shear;

  for (int i = 1; i < 99; i++) {
    int bit1 = getbit_div(value_1, i);
    int bit2 = getbit_div(value_2, i);
    if (bit1) pos1 = i;
    if (bit2) pos2 = i;
  }

  shear = pos1 - pos2;
  shift_div(&value_2, shear);

  for (int i = 1; i < 99; i++) {
    int bit2 = getbit_div(value_2, i);
    if (bit2)
      setbit_div(&res, i, 0);
    else
      setbit_div(&res, i, 1);
  }

  s21_add_div(res, one, result);

  return shear;
}
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int bit_1;
  int sign_1 = getsign(value_1);
  int sign_2 = getsign(value_2);
  s21_init_decimal(result);
  s21_decimal adder = value_1;
  int exp1;
  int exp2;
  int error = 0;
  exp1 = s21_10_conv(value_1);
  exp2 = s21_10_conv(value_2);
  // printf("%d\n", exp1);
  // printf("%d\n", exp2);
  s21_rev_10_conv(result, exp1 + exp2);
  set_0_bit(&adder.bits[3], 31);  // модуль копии вал_1
  for (int i = 0; i < 3; i++) {  // проходимся по всей мантисе
    for (int j = 0; j < 32; j++) {
      bit_1 = test_bit(value_2.bits[i], j);
      if (bit_1) {
        s21_addiction_logic(*result, adder, result);  // ---?
      }
      error = s21_shift(&adder);
    }
  }
  if (sign_1 != sign_2)
    setsign(result, 1);
  else
    setsign(result, 0);
  if (error != 0) {
    if (sign_1 != sign_2)
      error = 2;
    else
      error = 1;
  }
  return error;
}

int s21_shift(s21_decimal *number) {
  int vault_1 = 0;  // Хранит значение предыдущего бита
  int vault_2 = 0;  // Сохраняет нынешний бит
  int error = test_bit(number->bits[2], 31);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 32; j++) {
      vault_2 = test_bit((number->bits[i]), j);
      if (vault_1)
        set_1_bit(&number->bits[i], j);
      else
        set_0_bit(&number->bits[i], j);
      vault_1 = vault_2;
    }
  }
  return error;
}

void set_1_bit(unsigned int *value, int BitNumber) {
  *value |= (1 << BitNumber);
}

void set_0_bit(unsigned int *value, int BitNumber) {
  *value &= ~(1 << BitNumber);
}

int s21_addiction_logic(s21_decimal value_1, s21_decimal value_2,
                        s21_decimal *result) {
  int a = 0;
  int b = 0;
  int prev = 0;
  int next = 0;
  int res;

  int error = 0;
  a = test_bit(value_1.bits[2], 31);
  b = test_bit(value_2.bits[2], 31);

  for (int j = 0; j < 3; j++) {
    for (int i = 0; i < 32; i++) {
      a = test_bit(value_1.bits[j], i);
      b = test_bit(value_2.bits[j], i);
      if (a == 0) {
        if (b == 0 && prev == 0) {
          res = 0;
          next = 0;
        } else if (b == 0 || prev == 0) {
          res = 1;
          next = 0;
        } else {
          res = 0;
          next = 1;
        }
      } else {
        if (b == 0 && prev == 0) {
          res = 1;
          next = 0;
        } else if (b == 0 || prev == 0) {
          res = 0;
          next = 1;
        } else {
          res = 1;
          next = 1;
        }
      }
      prev = next;

      if (res) {
        set_1_bit(&(result->bits[j]), i);
      } else {
        set_0_bit(&(result->bits[j]), i);
      }
    }
  }
  return error;
}

int s21_10_conv(s21_decimal value) {
  int result = 0;
  int power = 1;
  for (int i = 16; i < 21; i++, power = power * 2)
    if (test_bit(value.bits[3], i)) {
      result = result + power;
    }
  return result;
}

int test_bit(unsigned int value, int BitNumber) {
  return value & (1 << BitNumber);
}

void s21_rev_10_conv(s21_decimal *value, int result) {
  int power = 16;
  for (int i = 20; i > 15; i--, power /= 2)
    if (result >= power) {
      result -= power;
      set_1_bit(&value->bits[3], i);
    } else {
      set_0_bit(&value->bits[3], i);
    }
}

void s21_init_decimal(s21_decimal *dst) {
  dst->bits[0] = 0;
  dst->bits[1] = 0;
  dst->bits[2] = 0;
  dst->bits[3] = 0;
}

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  s21_init_decimal(dst);
  if (src < 0) {
    dst->bits[3] = SIGNBIT;
    src = -src;
  }
  dst->bits[0] = src;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  s21_init_decimal(dst);
  if ((src == 1.0 / 0.0) || (src == -1.0 / 0.0) || (src != src)) {
    return 1;
  }
  if (src < 0) {
    setsign(dst, 1);
    src *= -1;
  }
  unsigned int scale = 0;
  for (; !((int)src); src *= 10, scale++) {
  }
  for (; src / 1000000 < 1; src *= 10, scale++) {
  }
  char exp = bitexp(src);
  setbit(dst, (int)exp + 1, 1);
  unsigned int srcu = *(unsigned int *)&src;
  unsigned int mask = 0x400000;
  for (int i = (int)exp; i > 0; i--) {
    setbit(dst, i, !!(srcu & mask));
    mask >>= 1;
  }
  setexp(dst, scale);
  return 0;
}

unsigned int getexp(s21_decimal src) {
  src.bits[3] &= ~SIGNBIT;
  return src.bits[3] >> 16;
}

int plus(s21_decimal val1, s21_decimal val2, s21_decimal *result) {
  int res = 0;
  int nextraz = 0;
  for (int i = 1; i < 97; i++) {
    int bit1 = getbit(val1, i);
    int bit2 = getbit(val2, i);
    if (bit1 || bit2) {
      if (bit1 && bit2) {
        if (nextraz) setbit(result, i, 1);
        nextraz = 1;
      } else {
        if (!nextraz) {
          setbit(result, i, 1);
        }
      }
    } else {
      if (nextraz) {
        setbit(result, i, 1);
        nextraz = 0;
      }
    }
  }
  if (nextraz) {
    res = 1;
  }
  return res;
}

void setexp(s21_decimal *src, unsigned int exp) {
  unsigned int mask = 0;
  mask = exp;
  mask <<= 16;
  if (src->bits[3] >> 31) {
    mask |= SIGNBIT;
  }
  src->bits[3] = src->bits[3] & 0;
  src->bits[3] = src->bits[3] | mask;
}

void setsign(s21_decimal *src, int sign) {
  if (sign) {
    src->bits[3] |= SIGNBIT;
  } else {
    src->bits[3] &= ~SIGNBIT;
  }
}

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  s21_init_decimal(result);
  int res = 0;
  int nextraz = 0;
  int mininf = 0;
  if (getexp(value_1) != getexp(value_2)) {
    normal_scale(&value_1, &value_2);
    setexp(result, getexp(value_1));
  }
  setexp(result, getexp(value_1));
  if (getsign(value_1) != getsign(value_2)) {
    if (s21_is_less(value_2, value_1)) {
      setsign(&value_1, 0);
      setsign(&value_2, 0);
      s21_sub(value_1, value_2, result);
    } else {
      setsign(&value_1, 0);
      setsign(&value_2, 0);
      s21_sub(value_2, value_1, result);
    }

  } else {
    for (int i = 1; i < 97; i++) {
      int bit1 = getbit(value_1, i);
      int bit2 = getbit(value_2, i);
      if (bit1 || bit2) {
        if (bit1 && bit2) {
          if (nextraz) setbit(result, i, 1);
          nextraz = 1;
        } else {
          if (!nextraz) {
            setbit(result, i, 1);
          }
        }
      } else {
        if (nextraz) {
          setbit(result, i, 1);
          nextraz = 0;
        }
      }
    }
  }
  if (getsign(value_1) && getsign(value_2)) {
    mininf = 1;
    setsign(result, 1);
  }
  if (nextraz) {
    if (mininf) {
      res = 2;
    } else {
      res = 1;
    }
  }
  return res;
}

void setbit(s21_decimal *dst, int bit, int znach) {
  int numbits = 0;
  if (bit <= 32) {
    numbits = 0;
  } else if (bit > 32 && bit <= 64) {
    bit = bit - 32;
    numbits = 1;
  } else if (bit > 64 && bit <= 96) {
    bit = bit - 64;
    numbits = 2;
  }
  unsigned int mask = gotmask(bit);
  if (znach) {
    dst->bits[numbits] |= mask;
  } else {
    mask = ~mask;
    dst->bits[numbits] &= mask;
  }
}

int getbit(s21_decimal src, int bit) {
  int numbits = 0;
  if (bit <= 32) {
    numbits = 0;
  } else if (bit > 32 && bit <= 64) {
    bit = bit - 32;
    numbits = 1;
  } else if (bit > 64 && bit <= 96) {
    bit = bit - 64;
    numbits = 2;
  }
  unsigned int mask = gotmask(bit);
  return !!(src.bits[numbits] & mask);
}

unsigned int gotmask(int bit) {
  if (bit == 0) bit = 1;
  unsigned int mask = 1;
  for (; bit - 1; bit--) {
    mask <<= 1;
  }
  return mask;
}

int s21_is_less(s21_decimal src, s21_decimal dst) {
  unsigned int exp_src, exp_dst, sign_src, sign_dst;
  int result = 2;

  sign_src = getsign(src);
  sign_dst = getsign(dst);
  if (sign_src == 1 && sign_dst == 0)
    result = 1;
  else if (sign_src == 0 && sign_dst == 1)
    result = 0;
  if (result == 2) {
    exp_src = getexp(src);
    exp_dst = getexp(dst);
    if (exp_src != exp_dst) normal_scale(&src, &dst);

    if (src.bits[2] < dst.bits[2])
      result = 1;
    else if (src.bits[2] > dst.bits[2])
      result = 0;
    if (result == 2 && src.bits[1] < dst.bits[1])
      result = 1;
    else if (result == 2 && src.bits[1] > dst.bits[1])
      result = 0;
    if (result == 2 && src.bits[0] < dst.bits[0])
      result = 1;
    else if (result == 2 && src.bits[0] > dst.bits[0])
      result = 0;
    if (result == 1 && sign_dst == 1 && sign_src == 1)
      result = 0;
    else if (result == 0 && sign_dst == 1 && sign_src == 1)
      result = 1;
    if (result == 2) result = 0;
  }
  return result;
}

int s21_is_greater(s21_decimal src, s21_decimal dst) {
  int result = 0;
  if (s21_is_less(src, dst) == 0 && s21_is_equal(src, dst) == 0) result = 1;
  return result;
}

int s21_is_less_or_equal(s21_decimal src, s21_decimal dst) {
  int result = 0;
  if (s21_is_greater(src, dst) == 0) result = 1;
  return result;
}

int s21_is_greater_or_equal(s21_decimal src, s21_decimal dst) {
  int result = 0;
  if (s21_is_less(src, dst) == 0) result = 1;
  return result;
}

int s21_is_equal(s21_decimal src, s21_decimal dst) {
  int result = 1;
  unsigned int exp_src, exp_dst;

  exp_src = getexp(src);
  exp_dst = getexp(dst);
  if (exp_src != exp_dst) normal_scale(&src, &dst);

  for (int j = 3; j >= 0 && result != 0; j--) {
    if (src.bits[j] == (dst.bits[j]))
      result = 1;
    else
      result = 0;
  }
  return result;
}

int s21_is_not_equal(s21_decimal src, s21_decimal dst) {
  int result = 0;
  if (s21_is_equal(src, dst) == 0) result = 1;
  return result;
}

int getsign(s21_decimal src) {
  unsigned int mask = gotmask(32);
  return !!(src.bits[3] & mask);
}

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int loan = 0;
  s21_decimal swap;
  unsigned int sign_1, sign_2, exp_1, exp_2, max_exp;
  normal_result(&value_1);
  normal_result(&value_2);
  exp_1 = getexp(value_1);
  exp_2 = getexp(value_2);
  sign_1 = getsign(value_1);
  sign_2 = getsign(value_2);
  max_exp = exp_1;
  if (max_exp < exp_2) max_exp = exp_2;

  if (exp_1 != exp_2) normal_scale(&value_1, &value_2);

  if (sign_1 != sign_2) {
    setsign(&value_1, 0);
    setsign(&value_2, 0);

    s21_add(value_1, value_2, result);
    if (sign_1) setsign(result, 1);
  } else {
    if (sign_1 && sign_2) {
      setsign(&value_1, 0);
      setsign(&value_2, 0);
      swap = value_1;
      value_1 = value_2;
      value_2 = swap;
    }
    if (s21_is_less(value_1, value_2)) {
      swap = value_1;
      value_1 = value_2;
      value_2 = swap;
      setsign(result, 1);
    }

    for (int i = 1; i < 97; i++) {
      int bit1 = getbit(value_1, i);
      int bit2 = getbit(value_2, i);
      if (bit1 == bit2) {
        if (loan) {
          setbit(result, i, 1);
          loan = 1;
        } else {
          setbit(result, i, 0);
        }
      } else if (bit1 > bit2) {
        if (loan) {
          setbit(result, i, 0);
          loan = 0;
        } else {
          setbit(result, i, 1);
        }
      } else if (bit1 < bit2) {
        if (loan) {
          setbit(result, i, 0);
          loan = 1;
        } else {
          setbit(result, i, 1);
          loan = 1;
        }
      }
    }
  }
  setexp(result, max_exp);
  normal_result(result);
  return 0;
}

void normal_scale(s21_decimal *value_1, s21_decimal *value_2) {
  unsigned int exp1, exp2, max_exp, odds_exp, flag = 0;
  int sign1 = getsign(*value_1);
  int sign2 = getsign(*value_2);

  exp1 = getexp(*value_1);
  exp2 = getexp(*value_2);
  if (exp1 > exp2) {
    max_exp = 1;
    odds_exp = exp1 - exp2;
  } else {
    max_exp = 2;
    odds_exp = exp2 - exp1;
  }
  for (unsigned int i = 0; i < odds_exp; i++) {
    if (flag == 0) {
      if (max_exp == 1) {
        if (upscale(value_2) == 1) flag = 1;
      } else {
        if (upscale(value_1) == 1) flag = 1;
      }
    }
    if (flag == 1) {
      if (max_exp == 1)
        down_scale(value_1);
      else
        down_scale(value_2);
    }
  }
  setsign(value_1, sign1);
  setsign(value_2, sign2);
}

int down_scale(s21_decimal *src) {
  unsigned int exp = getexp(*src);
  s21_decimal dec = {{10, 0, 0, 0}, 0};
  s21_decimal res = {{0, 0, 0, 0}, 0};

  s21_div_int(*src, dec, &res);
  *src = res;
  setexp(src, exp - 1);
  return 0;
}

int upscale(s21_decimal *src) {
  unsigned int exp, res_up;
  s21_decimal res = *src;
  exp = getexp(*src);
  res_up = multi10(&res);
  if (res_up == 0) {
    *src = res;
    setexp(src, exp + 1);
    res_up = 0;
  } else {
    res_up = 1;
  }
  return res_up;
}

int multi10(s21_decimal *val1) {
  s21_decimal res = *val1;
  unsigned int res_mul;
  for (int i = 0; i < 9; i++) {
    s21_decimal res2 = {{0, 0, 0, 0}, 0};
    if (plus(*val1, res, &res2) == 1) {
      i = 10;
      res_mul = 1;
    } else {
      res_mul = 0;
    }
    res = res2;
  }
  if (res_mul == 0) *val1 = res;
  return res_mul;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  unsigned int exp = getexp(value);
  int sign = getsign(value);
  *result = value;
  for (unsigned int i = 0; i < exp; i++) {
    down_scale(result);
  }
  setsign(result, sign);
  return 0;
}

int s21_negate(s21_decimal value, s21_decimal *result) {
  int sign = getsign(value);
  *result = value;
  if (sign)
    setsign(result, 0);
  else
    setsign(result, 1);
  return 0;
}

int s21_floor(s21_decimal value, s21_decimal *result) {
  s21_decimal one = {{1, 0, 0, 0}, 0};
  s21_decimal dop_res = {{0, 0, 0, 0}, 0};
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  int sign = getsign(value);

  s21_truncate(value, result);
  if (sign) {
    setsign(result, 0);
    dop_res = *result;
    *result = nool;
    s21_add(dop_res, one, result);
    setsign(result, 1);
  }
  return 0;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  unsigned int exp = getexp(value);
  int sign = getsign(value);
  s21_decimal ost = {{0, 0, 0, 0}, 0};
  s21_decimal nool = {{0, 0, 0, 0}, 0};
  s21_decimal one = {{0, 0, 0, 0}, 0};
  s21_decimal dop_res = {{0, 0, 0, 0}, 0};
  s21_decimal dec = {{10, 0, 0, 0}, 0};

  *result = value;
  for (unsigned int i = 0; i < exp - 1; i++) {
    down_scale(result);
  }
  s21_mod(*result, dec, &ost);
  down_scale(result);
  if (ost.bits[0] > 5) {
    dop_res = *result;
    *result = nool;
    s21_sub(dop_res, one, result);
    setsign(result, sign);
  }
  return 0;
}

int getbit_div(s21_decimal src, int bit) {
  int numbits = 0;
  if (bit <= 32) {
    numbits = 0;
  } else if (bit > 32 && bit <= 64) {
    bit = bit - 32;
    numbits = 1;
  } else if (bit > 64 && bit <= 96) {
    bit = bit - 64;
    numbits = 2;
  } else if (bit > 96 && bit <= 100) {
    bit = bit - 96;
    numbits = 3;
  }
  unsigned int mask = gotmask(bit);
  return !!(src.bits[numbits] & mask);
}

void setbit_div(s21_decimal *dst, int bit, int znach) {
  int numbits = 0;
  if (bit <= 32) {
    numbits = 0;
  } else if (bit > 32 && bit <= 64) {
    bit = bit - 32;
    numbits = 1;
  } else if (bit > 64 && bit <= 96) {
    bit = bit - 64;
    numbits = 2;
  } else if (bit > 96 && bit <= 100) {
    bit = bit - 96;
    numbits = 3;
  }
  unsigned int mask = gotmask(bit);
  if (znach) {
    dst->bits[numbits] |= mask;
  } else {
    mask = ~mask;
    dst->bits[numbits] &= mask;
  }
}

int s21_add_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int res = 0;
  int nextraz = 0;

  for (int i = 1; i < 99; i++) {
    int bit1 = getbit_div(value_1, i);
    int bit2 = getbit_div(value_2, i);
    if (bit1 || bit2) {
      if (bit1 && bit2) {
        if (nextraz) setbit_div(result, i, 1);
        nextraz = 1;
      } else {
        if (!nextraz) {
          setbit_div(result, i, 1);
        }
      }
    } else {
      if (nextraz) {
        setbit_div(result, i, 1);
        nextraz = 0;
      }
    }
  }

  if (nextraz) {
    res = 1;
  }

  return res;
}
