/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2023 Comcast Cable Communications Management, LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <rbus/rbus.h>
#include <stdlib.h>
#include <ifaddrs.h>
#include <CUnit/Basic.h>
#include <sys/stat.h>
#include "../src/mqttcm_connect.h"
#include "../src/mqttcm_generic.h"
#include "../src/mqttcm_generic.h"
#include "../src/mqttcm_log.h"
#include "../src/mqttcm_privilege.h"
#include "../src/mqttcm_webcfg.h"

rbusHandle_t handle;

/*----------------------------------------------------------------------------*/
/*                             Test Functions                             */
/*----------------------------------------------------------------------------*/

//Test function for webcfgMqttSubscribeHandler
void test_webcfgMqttSubscribeHandler()
{
	rbusError_t ret = RBUS_ERROR_BUS_ERROR;
	
	ret = webcfgMqttSubscribeHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_SUBSCRIBE_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
	
	ret = webcfgMqttSubscribeHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_ONMESSAGE_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
}

//Test function for webcfgMqttOnMessageHandler
void test_webcfgMqttOnMessageHandler()
{
	rbusError_t ret = RBUS_ERROR_BUS_ERROR;
	
	ret = webcfgMqttOnMessageHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_ONMESSAGE_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
	
	ret = webcfgMqttOnMessageHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_SUBSCRIBE_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
}

//Test function for webcfgMqttOnPublishHandler
void test_webcfgMqttOnPublishHandler()
{
	rbusError_t ret = RBUS_ERROR_BUS_ERROR;
	
	ret = webcfgMqttOnPublishHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_ONPUBLISH_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
	
	ret = webcfgMqttOnPublishHandler(handle, RBUS_EVENT_ACTION_SUBSCRIBE , WEBCFG_MQTT_ONMESSAGE_CALLBACK, NULL, 0, false);
	CU_ASSERT_EQUAL(ret, 0);
}

// Test suite initialization function
int init_suite(void) 
{
    // Initialize any necessary resources or setups
    return 0;
}

// Test suite cleanup function
int clean_suite(void) 
{
    // Clean up any allocated resources or memory
    return 0;
}
void add_suites( CU_pSuite *suite )
{
    *suite = CU_add_suite( "tests", NULL, NULL );
    CU_add_test( *suite, "test webcfgMqttSubscribeHandler", test_webcfgMqttSubscribeHandler);
    CU_add_test( *suite, "test webcfgMqttOnMessageHandler", test_webcfgMqttOnMessageHandler);
    CU_add_test( *suite, "test webcfgMqttOnPublishHandler", test_webcfgMqttOnPublishHandler);    
}

int main( int argc, char *argv[] )
{
    unsigned rv = 1;
    CU_pSuite suite = NULL;

    (void ) argc;
    (void ) argv;

    if( CUE_SUCCESS == CU_initialize_registry() ) {
        add_suites( &suite );

        if( NULL != suite ) {
            CU_basic_set_mode( CU_BRM_VERBOSE );
            CU_basic_run_tests();
            printf( "\n" );
            CU_basic_show_failures( CU_get_failure_list() );
            printf( "\n\n" );
            rv = CU_get_number_of_tests_failed();
        }

        CU_cleanup_registry();

    }
    return rv;
}
