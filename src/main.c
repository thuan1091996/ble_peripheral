/*
 * Copyright (c) 2012-2014 Wind River Systems, Inc.
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <zephyr.h>
#include <logging/log.h>

#include "ble/bluetoothle.h"
#define MODULE_NAME			main_module
#define MODULE_LOG_LEVEL	LOG_LEVEL_DBG

LOG_MODULE_REGISTER(MODULE_NAME, MODULE_LOG_LEVEL);




/* BLE callbacks*/
static struct bt_conn  *current_conn;
static ble_gatt_cb_t	my_srv_callbacks;


void on_connected(struct bt_conn *conn, uint8_t err)
{
	if(err) {
		LOG_ERR("connection err: %d", err);
		return;
	}
	LOG_INF("Connected.");
	current_conn = bt_conn_ref(conn);
}

void on_disconnected(struct bt_conn *conn, uint8_t reason)
{
	LOG_INF("Disconnected (reason: %d)", reason);
	if(current_conn) {
		bt_conn_unref(current_conn);
		current_conn = NULL;
	}
}

struct bt_conn_cb ble_cb = {
	.connected 		= &on_connected,
	.disconnected 	= &on_disconnected,
};

void main(void)
{
	LOG_INF("BLE sample demo using %s", CONFIG_BOARD);
	ble_init(&ble_cb, &my_srv_callbacks);
}
