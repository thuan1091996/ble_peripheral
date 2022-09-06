/****************************************************************************
* Title                 :   bluetooth le interface
* Filename              :   bluetoothle.h
* Author                :   Itachi
* Origin Date           :   2022/09/04
* Version               :   v0.0.0
* Compiler              :   NCS toolchain v2.0.0
* Target                :   nRF52840dk
* Notes                 :   None
*****************************************************************************/

/*************** INTERFACE CHANGE LIST **************************************
*
*    Date    	Software Version    Initials   	Description
*  2022/09/04    v0.0.0         	Itachi      Interface Created.
*
*****************************************************************************/

/** \file bluetoothle.h
 *  \brief This module contains interface for ble with Zephyr RTOS using nRF52840dk
 *
 *  This is the header file for 
 */
#ifndef BLE_BLUETOOTHLE_H_
#define BLE_BLUETOOTHLE_H_

/******************************************************************************
* Includes
*******************************************************************************/
#include <zephyr.h>
#include <logging/log.h>

#include <bluetooth/bluetooth.h>
#include <bluetooth/uuid.h>
#include <bluetooth/gatt.h>
#include <bluetooth/hci.h>
/******************************************************************************
* Preprocessor Constants
*******************************************************************************/


/******************************************************************************
* Configuration Constants
*******************************************************************************/


/******************************************************************************
* Macros
*******************************************************************************/


/******************************************************************************
* Typedefs
*******************************************************************************/
typedef struct ble_gatt_cb
{
	ssize_t (*bt_gatt_read_cb)(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset);
	ssize_t (*bt_gatt_write_cb)(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags);
}ble_gatt_cb_t;

/******************************************************************************
* Variables
*******************************************************************************/


/******************************************************************************
* Function Prototypes
*******************************************************************************/
int ble_init(struct bt_conn_cb *ble_callbacks, ble_gatt_cb_t* gatt_callbacks);

#ifdef __cplusplus
extern "C"{
#endif


#ifdef __cplusplus
} // extern "C"
#endif

#endif // BLE_BLUETOOTHLE_H_

/*** End of File **************************************************************/