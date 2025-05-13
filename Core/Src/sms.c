/*
 * sms.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */
#include "main.h"
#include "sys_init.h"


void send_sms(const char *phone_number, const char *message) {
	char response[256];
    send_at_command("AT\r\n",response,500);
    send_at_command("AT+CSMP?\r\n",response,500);
    send_at_command("AT+CMGF=1\r\n",response,500);
    send_at_command("AT+CSMP=17,167,0,0\r\n",response,500);

    //Set Number
    char mqtt_id[128];
    snprintf(mqtt_id, sizeof(mqtt_id), "AT+CMGS=\"%s\"\r\n",phone_number);
    send_at_command(mqtt_id, response, 500);
    send_at_command(message, response, 500);

}

// Task to read SMS
void read_sms() {

	char response[256];
    send_at_command("AT\r\n",response,500);
    send_at_command("AT+CMGF=1\r\n",response,500);
    send_at_command("AT+CMGD=,1\r\n",response,500);
    send_at_command("AT+CMGL=\"ALL\"\r\n",response,500);

}

