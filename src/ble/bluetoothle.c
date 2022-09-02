#include "bluetoothle.h"

#define MODULE_NAME			ble
#define MODULE_LOG_LEVEL	LOG_LEVEL_DBG
LOG_MODULE_REGISTER(MODULE_NAME, MODULE_LOG_LEVEL);
#define DEVICE_NAME		    CONFIG_BT_DEVICE_NAME
#define DEVICE_NAME_LEN		(sizeof(DEVICE_NAME) - 1)
#define UNKNOWN_APPEARANCE	0x0000

static const struct bt_data ad[] = {
    BT_DATA_BYTES(BT_DATA_FLAGS, (BT_LE_AD_GENERAL | BT_LE_AD_NO_BREDR)),
    BT_DATA(BT_DATA_NAME_COMPLETE, DEVICE_NAME, DEVICE_NAME_LEN)
};

static const struct bt_data sd[] = {
    BT_DATA_BYTES(BT_DATA_UUID128_ALL, BT_UUID_REMOTE_SERV_VAL),
};

static void ble_init_callback(int err)
{
    __ASSERT(0 == err, "Init BLE failed with error: %d", err);
    LOG_INF("BLE init succesfully");
}


int ble_init(struct bt_conn_cb *ble_callbacks)
{
    int errorcode=0;
    LOG_INF("BLE initializing \n\r");
    __ASSERT(ble_callbacks != NULL, "Null callbacks");
    bt_conn_cb_register(ble_callbacks);

    errorcode = bt_enable(&ble_init_callback);
    if(errorcode)
    {
        LOG_ERR("bt_enable return err %d \r\n", errorcode);
        return errorcode;
    }
    errorcode = bt_le_adv_start(BT_LE_ADV_CONN, ad, ARRAY_SIZE(ad), sd, ARRAY_SIZE(sd));
    if (errorcode) {
        LOG_ERR("Couldn't start advertising (err = %d)", errorcode);
        return errorcode;
    }

}
