#include "test_me.h"

START_TEST(strerror_1) { ck_assert_str_eq(strerror(2), s21_strerror(2)); }
END_TEST

START_TEST(strerror_2) {
  int n = 5;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST
START_TEST(strerror_3) {
  int n = 8;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST
START_TEST(strerror_4) {
  int n = 15;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST
START_TEST(strerror_5) {
  int n = 16;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST
START_TEST(strerror_6) {
  int n = 23;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST
START_TEST(strerror_7) {
  int n = 42;
  ck_assert_str_eq(strerror(n), s21_strerror(n));
}
END_TEST

Suite *test_strerror(void) {
  Suite *s = suite_create("\033[45m-=S21_STRERROR=-\033[0m");
  TCase *tc = tcase_create("strerror_tc");

  suite_add_tcase(s, tc);
  tcase_add_test(tc, strerror_1);
  tcase_add_test(tc, strerror_2);
  tcase_add_test(tc, strerror_3);
  tcase_add_test(tc, strerror_4);
  tcase_add_test(tc, strerror_5);
  tcase_add_test(tc, strerror_6);
  tcase_add_test(tc, strerror_7);

  suite_add_tcase(s, tc);
  return s;
}