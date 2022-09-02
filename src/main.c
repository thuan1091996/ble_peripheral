/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <logging/log.h>

#define MODULE_NAME			main_module
#define MODULE_LOG_LEVEL	LOG_LEVEL_DBG

LOG_MODULE_REGISTER(MODULE_NAME, MODULE_LOG_LEVEL);

void main(void)
{
	LOG_INF("BLE sample demo using %s", CONFIG_BOARD);
}
