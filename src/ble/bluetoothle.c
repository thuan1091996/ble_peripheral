/*******************************************************************************
* Title                 :   Bluetooth LE 
* Filename              :   bluetoothle.c
* Author                :   Itachi
* Origin Date           :   2022/09/04
* Version               :   0.0.0
* Compiler              :   NCS toolchain v2.0.0
* Target                :   nRF52840dk
* Notes                 :   None
*******************************************************************************/

/*************** MODULE REVISION LOG ******************************************
*
*    Date       Software Version	Initials	Description
*  2022/09/04       0.0.0	         Itachi      Module Created.
*
*******************************************************************************/

/** \file bluetoothle.c
 * \brief This module contains the
 */
/******************************************************************************
* Includes
*******************************************************************************/
#include "bluetoothle.h"
#include "bluetooth/gatt.h"
#include "logging/log.h"
/******************************************************************************
* Module Preprocessor Constants
*******************************************************************************/
#define MODULE_NAME			        ble
#define MODULE_LOG_LEVEL	        LOG_LEVEL_DBG
#define DEVICE_NAME		            "Itachi"
#define DEVICE_NAME_LEN		        (sizeof(DEVICE_NAME) - 1) // Ignore null terminated
#define BT_KEYBOARD_APPEARANCE       0x03C1  /* More on: https://specificationrefs.bluetooth.com/assigned-values/Appearance%20Values.pdf */
LOG_MODULE_REGISTER(MODULE_NAME, MODULE_LOG_LEVEL);

/******************************************************************************
* Module Typedefs
*******************************************************************************/

/******************************************************************************
* Module Variable Definitions
*******************************************************************************/
static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN),
    BT_DATA(BT_DATA_GAP_APPEARANCE, ((uint16_t []) {BT_KEYBOARD_APPEARANCE}), sizeof(uint16_t))
};

static ble_gatt_cb_t	my_srv_callbacks;

ssize_t bt_gatt_att_read_callbacks(struct bt_conn *conn, const struct bt_gatt_attr *attr, void *buf, uint16_t len, uint16_t offset)
{
    LOG_INF(" Attribute handle %d read callback", attr->handle);
    return bt_gatt_attr_read(conn, attr, buf, len, offset, (uint16_t []) {0xFAFA},2);
}
ssize_t bt_gatt_att_write_callbacks(struct bt_conn *conn, const struct bt_gatt_attr *attr, const void *buf, uint16_t len, uint16_t offset, uint8_t flags)
{
    LOG_INF(" Attribute handle %d write callback", attr->handle);
} 

ssize_t bt_gatt_att_notify_callbacks(const struct bt_gatt_attr *attr, uint16_t value)
{
    LOG_INF(" Notify %s callback", value? "enable": "disable");
} 


/******************************************************************************
* Module Preprocessor Macros
*******************************************************************************/

/* GATT service declaration */
BT_GATT_SERVICE_DEFINE(my_custom_service,
    BT_GATT_PRIMARY_SERVICE(BT_UUID_CTS),
    BT_GATT_CHARACTERISTIC( BT_UUID_CTS_CURRENT_TIME, 
                            BT_GATT_CHRC_READ | BT_GATT_CHRC_NOTIFY | BT_GATT_CHRC_WRITE,
                            BT_GATT_PERM_READ | BT_GATT_PERM_WRITE,
                            &bt_gatt_att_read_callbacks,
                            &bt_gatt_att_write_callbacks,
                            NULL),
    BT_GATT_CCC(bt_gatt_att_notify_callbacks, BT_GATT_PERM_READ | BT_GATT_PERM_WRITE),
);
/******************************************************************************
* Function Prototypes
*******************************************************************************/

/******************************************************************************
* Function Definitions
*******************************************************************************/
static void ble_init_callback(int err)
{
    __ASSERT(0 == err, "Init BLE failed with error: %d", err);
    LOG_INF("BLE init succesfully");
}


int ble_init(struct bt_conn_cb *ble_callbacks, ble_gatt_cb_t* gatt_cb)
{
    int errorcode=0;
    LOG_INF("BLE initializing \n\r");

    /* Assign callbacks for connection events */
    __ASSERT(ble_callbacks != NULL, "Null connection callbacks");
    bt_conn_cb_register(ble_callbacks);

    __ASSERT(gatt_cb != NULL, "Null GATT callbacks");


    /* GATT inits */

    /* BLE initialization */
    errorcode = bt_enable(&ble_init_callback);
    if(errorcode)
    {
        LOG_ERR("bt_enable return err %d \r\n", errorcode);
        return errorcode;
    }

    /* Advertising */
    errorcode = bt_le_adv_start(BT_LE_ADV_PARAM((BT_LE_ADV_OPT_CONNECTABLE | BT_LE_ADV_OPT_ONE_TIME ), 0x20, 0x20, NULL),
                                 ad, ARRAY_SIZE(ad), NULL, 0);
    if (errorcode) {
        LOG_ERR("Couldn't start advertising (err = %d)", errorcode);
        return errorcode;
    }

}