/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @file AppTasks.c
* @brief Implementation of common task primitives
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @author            Vasil Milev
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
* @revision{         1.0.1  , 2020.01.16, author Georgi Georgiev, Moved everything, except StartDefaultTask() to DefTasks.c }
* @endhistory
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* INCLUDES
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#include "AppTasks.h"
#include "system_manager.h"
#include "main.h"
#include "MCU_Init.h"
#include "User_types.h"
#include "version.h"
#include "Svc_RTC.h"
#include "FreeRTOS.h"
#include "task.h"
#include "core_cm4.h"
#include <stdint.h>
#include <stdio.h>

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* INTERNAL DEFINES
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
#define APP_LED_ON_TIME             (50)                                /* given time in ms */
#define APP_TASK_CALL_PERIOD        (1000)                              /* given time in ms */

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* INTERNAL ROUTINES DEFINITION
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifdef DEBUG_ENABLED
// Pass in a string for `name' to print the test name,
// or pass NULL to skip the name
static TestStatus_e RunTest(TestFunction_t t, const char* name)
{
	fprintf(DEBUG_COMM, "TEST: ~~ running test");
	if (name != NULL) fprintf(DEBUG_COMM, " %s", name);
	fprintf(DEBUG_COMM, "... \n");
	TestStatus_e testResult = t();
	if (testResult == TEST_PASS) fprintf(DEBUG_COMM, "PASS.\n");
	else fprintf(DEBUG_COMM, "FAIL with result %d!\n", testResult);
	return testResult;
}

static void Set_RunAllTests(const ModuleTestSet_t* ModuleTestSet)
{
    fprintf(DEBUG_COMM, "TEST: Running all tests in %s from %s...\n", ModuleTestSet->setName, ModuleTestSet->moduleName);
    for (uint32_t i = 0; i < ModuleTestSet->numTests; i++)
    {
        fprintf(DEBUG_COMM, "TEST: ~~ running test %s... ", ModuleTestSet->tests[i].testName);
        TestStatus_e testResult = ModuleTestSet->tests[i].test();
        if (testResult == TEST_PASS) fprintf(DEBUG_COMM, "PASS.\n");
        else fprintf(DEBUG_COMM, "FAIL with result %d!\n", testResult);
    }
}

static void Set_RunTestsUntilFail(const ModuleTestSet_t* ModuleTestSet)
{
    fprintf(DEBUG_COMM, "TEST: Running tests until first failure in %s from %s...\n", ModuleTestSet->setName, ModuleTestSet->moduleName);
    for (uint32_t i = 0; i < ModuleTestSet->numTests; i++)
    {
        fprintf(DEBUG_COMM, "TEST: ~~ running test %s... ", ModuleTestSet->tests[i].testName);
        TestStatus_e testResult = ModuleTestSet->tests[i].test();
        if (testResult == TEST_PASS) fprintf(DEBUG_COMM, "PASS.\n");
        else { fprintf(DEBUG_COMM, "FAIL with result %d!\n", testResult); return; }
    }
}

#endif

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* CODE TESTING
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/

#ifdef DEBUG_ENABLED
// If you want the default task to automatically run test sets, 
// uncomment the variable below and populate it with the test sets you want to run.
// (Don't forget to use the & operator in front of your test set name)

/*
static const ModuleTestSet_t* TO_TEST[] = {

};
*/
#endif

/*
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* EXTERNAL (NONE STATIC) ROUTINES DEFINITION
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
/*!
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @brief That is a task used as example to configure all sensors and actuators and blinks the green LED.
* That can be changed freely as needed depending on the project.
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
* @param[input]      argument - not used
* @param[output]     none
* @return            none
* @note              none
*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
*/
void StartDefaultTask(void * argument)
{
#ifdef DEBUG_ENABLED
    (void)RunTest; (void)Set_RunAllTests; (void)Set_RunTestsUntilFail;
    debug_L3("%s", "Default task started.");
#endif

#ifdef DEBUG_ENABLED
    /* If you want to automatically run test sets, uncomment this block. */
    /*
    for (uint32_t i = 0; i < sizeof(TO_TEST) / sizeof(TO_TEST[0]); i++)
        Set_RunAllTests(TO_TEST[i]);
    */
#endif

      for( ; ; )
      {
          
          //debug_L3("%s", "Default task loop.");

          /* blink the Green LED for 50ms to indicate the OBC is running */
          GREEN_LED_ON();
          vTaskDelay(pdMS_TO_TICKS(APP_LED_ON_TIME));
          GREEN_LED_OFF();

          vTaskDelay(pdMS_TO_TICKS(APP_TASK_CALL_PERIOD));    /* Give processing time for the other tasks */
      }

}
