#include "cJSON.h"
#include "sys_init.h"
#define SlaveID      0x01
#define FunctionCode 0x04


const char* Key[4] = {
    "Filter_plant_Tank",
    "Battery_Voltage_Slave_PLC",
    "EM_P1_WATT",
    "EM_P1_PF"
};

uint16_t Address[4] = {
    100, // Example Modbus address
    101,
    115,
    117
};
uint16_t Len[4] = {
    1, // Example Modbus address
    1,
    2,
    2
};



void data() {
    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return;

    cJSON_AddStringToObject(root, "ts", "1747143868");

    cJSON *values = cJSON_CreateObject();
    if (values == NULL) {
        cJSON_Delete(root);
        return;
    }


    for (int i = 0; i < 4; i++) {


        float val = modbus_int(SlaveID,FunctionCode,Address[i],Len[i]);
        cJSON_AddNumberToObject(values, Key[i], val);
    }

    cJSON_AddItemToObject(root, "values", values);

    char *json_str = cJSON_PrintUnformatted(root);  // or cJSON_Print() for pretty
    if (json_str) {
    	char Json[512];
//        printf("JSON: %s\n", json_str);  // For debugging
        sprintf(Json,"JSON: %s\n", json_str);
        HAL_UART_Transmit(&huart2,(uint8_t *)Json,strlen(Json),1000);
        // === Use this string to send over MQTT ===
        mqtt_publish("v1/devices/me/telemetry", json_str);

        free(json_str);
    }

    cJSON_Delete(root);
}
