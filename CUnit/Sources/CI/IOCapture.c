#include <stdio.h>
#include "CUnit/MessageHandlers.h"
#include "CUnit/AutomatedJUnitXml.h"
#include "CUnit/IOCapture.h"

#ifdef _WIN32
#pragma warning(disable : 4996)
#include <io.h>
#else
#include <unistd.h>
#include <assert.h>

#endif

static CU_BOOL capture_enabled = CU_FALSE;

struct redirected_stream {
    FILE *original;
    FILE *redirect;
    unsigned written; /* how many bytes have been written to *redirect */
};

struct redirected_stream redir_stdout = {0};
struct redirected_stream redir_stderr = {0};


CU_EXPORT CU_BOOL CUnit_IOCapture_get_enabled(void) {
  return capture_enabled && CU_automated_get_junit_xml_enabled();
}

/* return a filename to use to save the stdio stream to */
static char *redir_stdout_filename;
static char *redir_stderr_filename;

static void set_stdio_filenames(void) {
  if (CUnit_IOCapture_get_enabled() != CU_TRUE) return;

  if (!redir_stdout_filename) {
    const char *junit_filename = CU_automated_get_junit_filename();
    size_t namelen = 6 + strlen(junit_filename);

    redir_stderr_filename = malloc(namelen);
    assert(redir_stderr_filename && "could not allocate filename for stderr!");
    redir_stdout_filename = malloc(namelen);
    assert(redir_stdout_filename && "could not allocate filename for stdout!");

    snprintf(redir_stderr_filename, namelen, "%s.err", junit_filename);
    snprintf(redir_stdout_filename, namelen, "%s.out", junit_filename);
  }
}

static void free_stdio_filenames(void) {
  if (redir_stderr_filename && redir_stdout_filename) {
    free(redir_stderr_filename);
    free(redir_stderr_filename);
  }
}

static void CUnit_Begin_CaptureStdio(const CU_pSuite pSuite) {
  if (!CUnit_IOCapture_get_enabled()) return;
  /* make a temporary file for stdout and stderr, redirect to them */
  set_stdio_filenames();

}

static void CUnit_Finish_CaptureStdio(const CU_pSuite pSuite, const CU_pFailureRecord pFailure) {
  if (!CUnit_IOCapture_get_enabled()) return;
  /* close temporary stout/stderr, restore original, consume files */
}

/* called just before and every assert so we can print to the original stdio early */
static void CUnit_IOCapture_Pump(const CU_pTest pTest, const CU_pSuite pSuite) {

}

CU_EXPORT void CUnit_IOCapture_disable(void) {
  capture_enabled = CU_FALSE;
}

CU_EXPORT void CUnit_IOCapture_enable(void) {
  capture_enabled = CU_TRUE;

  if (CUnit_IOCapture_get_enabled() == CU_TRUE) {
    CCU_MessageHandler begin = {0};
    CCU_MessageHandler end = {0};
    CCU_MessageHandler pump = {0};

    begin.type = CUMSG_SUITE_STARTED;
    begin.func.suite_start = CUnit_Begin_CaptureStdio;
    CCU_MessageHandler_Insert(begin.type, &begin);

    end.type = CUMSG_SUITE_COMPLETED;
    end.func.suite_completed = CUnit_Finish_CaptureStdio;
    CCU_MessageHandler_Add(end.type, &end);

    pump.type = CUMSG_BEFORE_CU_ASSERT;
    pump.func.before_cu_assert = CUnit_IOCapture_Pump;
    CCU_MessageHandler_Add(pump.type, &pump);

    pump.type = CUMSG_AFTER_CU_ASSERT;
    pump.func.after_cu_assert = CUnit_IOCapture_Pump;
    CCU_MessageHandler_Add(pump.type, &pump);
  }
}

