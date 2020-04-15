/**
 * Simple XUnit style CICD example with setup and teardown functions failing
 *
 * CU_SUITE_SETUP, CU_SUITE_TEARDOWN, CU_TEST_SETUP and CU_TEST_TEARDOWN
 * are automatically added to the suite.
 *
 *  CUnit - A Unit testing framework library for C.
 *  Copyright (C) 2001       Anil Kumar
 *  Copyright (C) 2004-2006  Anil Kumar, Jerry St.Clair
 *  Copyright (C) 2018       Ian Norton
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 */
#include <assert.h>
#include "CUnit/CUnitCI.h"

static int suite_setup_count = 0;
static int suite_teardown_count = 0;
static int test_setup_count = 0;
static int test_teardown_count = 0;

/* run at the start of each suite */
CU_SUITE_SETUP() {
    fprintf(stdout, "\n+++ setting up suite\n");
    suite_setup_count++;
    return CUE_SUCCESS;
}

/* run at the end of the suite */
CU_SUITE_TEARDOWN() {
    fprintf(stdout, "\n+++ cleaning up suite and then failing\n");
    suite_teardown_count++;
    return CUE_SCLEAN_FAILED;
}

/* run at the start of each test */
CU_TEST_SETUP() {
    test_setup_count++;
}

/* run at the end of each test */
CU_TEST_TEARDOWN() {
    test_teardown_count++;
}

static void test_simple_pass1(void) {
    CU_ASSERT_FATAL(suite_setup_count == 1);
    CU_ASSERT_FATAL(suite_teardown_count == 0);
    CU_ASSERT_FATAL(test_setup_count == 1);
    CU_ASSERT_FATAL(test_teardown_count == 0);
}

static void test_simple_pass2(void) {
    CU_ASSERT_FATAL(suite_setup_count == 1);
    CU_ASSERT_FATAL(suite_teardown_count == 0);
    CU_ASSERT_FATAL(test_setup_count == 2);
    CU_ASSERT_FATAL(test_teardown_count == 1);
}

int main(int argc, char** argv) {
  int exitstatus;

  CU_CI_add_suite(CU_MAIN_EXE_NAME,
            __cu_suite_setup,
            __cu_suite_teardown,
            __cu_test_setup,
            __cu_test_teardown);
  CUNIT_CI_TEST(test_simple_pass1);
  CUNIT_CI_TEST(test_simple_pass2);
  exitstatus =  CU_CI_main(argc, argv);

  if (!exitstatus) {
    fprintf(stderr, "CU_CI_main did not fail as expected!\n");
    return 1;
  }

  return 0;
}
