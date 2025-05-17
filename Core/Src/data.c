
#include "main.h"
#include "sys_init.h"



void data() {
    // Create a JSON object
    cJSON *root = cJSON_CreateObject();
    if (root == NULL) return;

    uint64_t epoch = RTC_Get_Epoch();


    cJSON_AddNumberToObject(root, "ts", epoch);

    cJSON *values = cJSON_CreateObject();
    if (values == NULL) {
        cJSON_Delete(root);
        return;
    }


    for (int i = 0; i < 4; i++) {
    	if (registers[i].length == 2) {
    	    float val = modbus_float(registers[i].SlaveID, registers[i].Functioncode, registers[i].address, registers[i].length);
    	    cJSON_AddNumberToObject(values, registers[i].key, val);
    	}
    	    int val = modbus_int(registers[i].SlaveID, registers[i].Functioncode, registers[i].address, registers[i].length);
    	    cJSON_AddNumberToObject(values, registers[i].key, val);

    }

    cJSON_AddItemToObject(root, "values", values);

    char *json_str = cJSON_PrintUnformatted(root);  // or cJSON_Print() for pretty
//    char *json_str = cJSON_Print(root);

    if (json_str) {
    	char Json[4096];
        sprintf(Json,"JSON: \n%s\r\n", json_str);
        HAL_UART_Transmit(&huart2,(uint8_t *)Json,strlen(Json),1000);
        // === Use this string to send over MQTT ===
        mqtt_publish("v1/devices/me/telemetry", json_str);
        process_sensor_data(json_str);

        free(json_str);
    }

    cJSON_Delete(root);
}

void process_sensor_data(const char *json_string) {
    // Parse the JSON string
    cJSON *root = cJSON_Parse(json_string);
    if (root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            fprintf(stderr, "Error before: %s\n", error_ptr);
        }
        return;
    }

    // Extract timestamp
    cJSON *timestamp = cJSON_GetObjectItemCaseSensitive(root, "ts");
    if (cJSON_IsNumber(timestamp)) {
        printf("Timestamp: %lld\n", (long long)timestamp->valueint);
    }

    // Extract values object
        cJSON *values = cJSON_GetObjectItemCaseSensitive(root, "values");
        if (cJSON_IsObject(values)) {
            // Get first child of values object
            cJSON *child = values->child;

            while (child != NULL) {
                // Search for this key in our Modbus register structure
                for (size_t i = 0; i < 4; i++) {
                    if (strcmp(child->string, registers[i].key) == 0) {
                        if (cJSON_IsNumber(child)) {
                            printf("Found register match:\r\n");
                            printf("  Function Code: %d\r\n", registers[i].Functioncode);
                            printf("  Address: %d\r\n", registers[i].address);
                            printf("  Value: %.2f\n", child->valuedouble);
                            printf("  Value: %d\n", child->valueint);

//                            if ((registers[i].length == 2)&&(registers[i].Functioncode==3)) {
//                            	write_Multiple_Reg(registers[i].SlaveID, 16, registers[i].address, registers[i].length,child->valuedouble);
//                            }
//                            if ((registers[i].length == 1)&&(registers[i].Functioncode==3)) {
//                            	write_Single_Reg(registers[i].SlaveID, 6, registers[i].address, registers[i].length,child->valueint);
//                            }
//                            if (registers[i].Functioncode==1){
//                            	write_Single_coil(registers[i].SlaveID, 5, registers[i].address, registers[i].length,child->valueint);
//                            }
                            sprintf(command,"Subscribe :%d\r\n",registers[i].address);
                            HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);

                        }
                        break; // Found match, move to next JSON child
                    }
                }
                child = child->next;
            }
        }


    // Clean up
    cJSON_Delete(root);
}

