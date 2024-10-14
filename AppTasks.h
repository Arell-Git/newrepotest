/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @file AppTasks.h
* @brief Header of AppTasks.c
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author            Vasil MIlev
* @version           1.0.0
* @date              2018.07.04
*
* @copyright         (C) Copyright Endurosat
*
*                    Contents and presentations are protected world-wide.
*                    Any kind of using, copying etc. is prohibited without prior permission.
*                    All rights - incl. industrial property rights - are reserved.
*
* @history
* @revision{         1.0.0  , 2018.07.04, author Vasil Milev, Initial revision }
* @endhistory
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifndef APPTASKS_H
#define APPTASKS_H

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* INCLUDES
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "main.h"
#include "MCU_Init.h"
#include <stdint.h>
#include <stdlib.h>

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* EXTERNAL DEFINES
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#ifdef DEBUG_ENABLED
/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @brief Print an error message to debug serial and permanently halt execution
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @param[input]      format - message format
* @param[input]      ... - variadic parameters for message formatting
* @note				 Noreturn
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#define panic(format, ...)                                                      \
{                                                                               \
    __disable_interrupt();                                                      \
    fprintf(DEBUG_COMM, "!!!CRITICAL: Panic from %s:%d: " format "\n",          \
            __FILE__, __LINE__, __VA_ARGS__);                                   \
    exit(0);                                                                    \
}

#endif
/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* EXTERNAL TYPES DECLARATIONS
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifdef DEBUG_ENABLED // Testing-related types


typedef enum {
	TEST_PASS = 0,
	TEST_FAIL = 1,
} TestStatus_e;

// All test functions should have this type
typedef TestStatus_e (*TestFunction_t)(void);

typedef struct {
	TestFunction_t test;
	const char* const testName; // Human-readable test name. Should probably be similar to the name of the test function
} Test_t;

// This is the type used by the default task when executing tests.
typedef struct {
	const char* const moduleName; 
	const char* const setName; 
	const Test_t* const tests; // Pointer to an array of `Test_t'
	const uint32_t numTests; // Number of elements in `tests'
} ModuleTestSet_t;

#define DeclareTestSet(set_name) extern const ModuleTestSet_t set_name
#define DefineTestSet(set_name, module_name, tests_array)				\
	const ModuleTestSet_t set_name = {									\
		.moduleName = #module_name,										\
		.setName = #set_name,											\
		.numTests = sizeof(tests_array) / sizeof(tests_array[0]),		\
		.tests = tests_array											\
	}

#define test_assert(expr) if (!(expr)) { debug_msg("%s", "test assertion failed"); return TEST_FAIL; }
#define test_assert_cleanup(expr, cleanup_lbl) if (!(expr)) { debug_msg("%s", "test assertion failed"); goto cleanup_lbl; }
#define use_test_fixture(fixture) test_assert(fixture() == TEST_PASS)

#endif



/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* EXTERNAL VARIABLES DECLARATIONS
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
extern uint8_t  up_sec, up_min, up_hrs;
extern uint32_t up_day;
extern uint16_t UptimePeriod;

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* EXTERNAL ROUTINES DECLARATIONS 
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
void StartDefaultTask(void * argument);
void Process_Sensors(void const * argument);
void ServicesTask(void * argument);
void S_X_BAND_Task(void const * argument);

#endif    /* APPTASKS_H */
/* ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ */
