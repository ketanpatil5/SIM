/*
 * gsm.c
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */
#include "main.h"
#include "sys_init.h"


char ATcommand[80];
uint8_t buffer[30] = {0};

void send_at_command(const char *cmd, char *response, int timeout_ms) {
//    uart_write_bytes(UART_NUM, cmd, strlen(cmd));
//    uart_write_bytes(UART_NUM, "\r\n", 2);

	sprintf(ATcommand,cmd);
	HAL_UART_Transmit(&huart1,(uint8_t *)ATcommand,strlen(ATcommand),1000);
	HAL_UART_Receive (&huart1, buffer, 30, 100);
    // Wait for response
	if(strstr((char *)buffer,"OK")){
//	   ATisOK = 1
	   char AT[30];
	   sprintf(AT,"OK\r\n");
	   HAL_UART_Transmit(&huart2,(uint8_t *)AT,strlen(AT),1000);

	}
	   HAL_Delay(1000);
	   memset(response,0,sizeof(buffer));
}

void mqtt_init(const char *broker, const char *accesstoken, const char *clientid) {
    char response[256];
//    generate_negative_pulse(GPIO_PIN, 10);
    send_at_command("AT\r\n",response,500);
    HAL_Delay(2000);// New
    send_at_command("AT+CFUN=1\r\n",response,500);
    send_at_command("AT+CREG=2\r\n",response,500);
    send_at_command("AT+CEREG=2\r\n",response,500);
    // send_at_command("AT+COPS?\r\n",response,1000);
    send_at_command("AT+CGDCONT=1,\"IP\",\"airtelgprs.com\"\r\n",response,500);
    send_at_command("AT+CGACT=0,1\r\n",response,500);
    send_at_command("AT+CNTP=\"asia.pool.ntp.org\",0\r\n",response,500);
    send_at_command("AT+CNTP\r\n",response,500);
    // send_at_command("AT+CCLK?\r\n",response,500);
    // send_at_command("AT+IPADDR\r\n",response,1000);
    send_at_command("AT+CGATT=1\r\n",response,500);
    send_at_command("AT+CGPADDR=1\r\n",response,500);
    // send_at_command("AT+CGACT?\r\n",response,1000);
    // send_at_command("AT+CEREG?\r\n",response,1000);
    send_at_command("AT+NETOPEN\r\n",response,500);
    // send_at_command("AT+NETOPEN?\r\n",response,1000);

    // send_at_command("AT+CSSLCFG=\"sslversion\",0,4\r\n",response,1000);
    send_at_command("AT+CSSLCFG=\"authmode\",0,1\r\n",response,500);
    send_at_command("AT+CSSLCFG=\"cacert\",0,\"ca_cert.pem\"\r\n",response,500);
    // send_at_command("AT+CSSLCFG=\"clientcert\",0,\"client_cert.pem\"\r\n",response,1000);
    // send_at_command("AT+CSSLCFG=\"clientkey\",0,\"client_key.pem\"\r\n",response,1000);
    // send_at_command("AT+CSSLCFG=\"password\",0,\"password.pem\"\r\n",response,1000);
    send_at_command("AT+CSSLCFG=\"enableSNI\",0,1\r\n",response,500);

    send_at_command("AT+CMQTTSTART\r\n", response, 500);
    send_at_command("AT+CCHSET=1,1\r\n", response, 500);
    send_at_command("AT+CCHMODE=1\r\n", response, 500);
    send_at_command("AT+CCHSTART\r\n", response, 500);
    send_at_command("AT+CCHADDR\r\n", response, 500);

    // send_at_command("AT+CCHOPEN\r\n", response, 500);
    send_at_command("AT+CCHCFG=\"sendtimeout\",0,60\r\n", response, 500);
    send_at_command("AT+CCHCFG=\"sslctx\",0,1\r\n", response, 500);
    // send_at_command("AT+CCERTMOVE=\"ca_cert.pem\"\r\n", response, 500);
    send_at_command("AT+CMQTTSSLCFG=0,1\r\n", response, 500);
    send_at_command("AT+CSSLCFG=0\r\n",response,500);

    //Set ID
    char mqtt_id[128];
    snprintf(mqtt_id, sizeof(mqtt_id), "AT+CMQTTACCQ=0,\"%s\",1\r\n",clientid);
    send_at_command(mqtt_id, response, 500);

    send_at_command("AT+CMQTTCFG=\"checkUTF8\",0,1\r\n",response,1000);
    send_at_command("AT+CMQTTCFG=\"optimeout\",0,60\r\n",response,1000);
    // send_at_command("AT+CMQTTCONNECT?\r\n",response,100);
    // send_at_command("AT+CCERTLIST", response, 1000);
    // send_at_command("AT+CCERTDELE=\"ca_cert.pem\"", response, 1000);

    for(int i=0;i<3;i++){
    char mqtt_conn[256];
    snprintf(mqtt_conn, sizeof(mqtt_conn), "AT+CMQTTCONNECT=0,\"tcp://%s\",300,1,\"%s\"\r\n",broker, accesstoken);
    send_at_command(mqtt_conn, response, 2500);
    }
    HAL_Delay(1500);
    // ESP_LOGI("MQTT", "MQTT connection response: %s", response);

}

void mqtt_publish(const char *topic, const char *data) {
    char response[256];

    // Set topic
    char mqtt_topic[128];
    int len;
    len=strlen(topic);
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTTOPIC=0,%d\r\n", len);
    send_at_command(mqtt_topic, response, 1000);
    send_at_command(topic,response,1000);

    // Send payload
    char mqtt_payload[512];
    len=strlen(data);
    snprintf(mqtt_payload, sizeof(mqtt_payload), "AT+CMQTTPAYLOAD=0,%d\r\n", len);
    send_at_command(mqtt_payload, response, 1000);
    send_at_command(data,response,1000);

    // Publish Data
    send_at_command("AT+CMQTTPUB=0,0,60,1\r\n",response,500);

    // send_at_command("AT+CMQTTDISC=0,60\r\n", response, 2000);
    // send_at_command("AT+CMQTTSTOP\r\n",response,1000);

    // ESP_LOGI("MQTT", "MQTT publish response: %s", response);
}

void mqtt_subscribe(const char *topic) {
    char response[256];

    //Set topic
    char mqtt_topic[128];
    int len;
    len=strlen(topic);
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTSUBTOPIC=0,%d,0\r\n", len);
    send_at_command(mqtt_topic, response, 1000);
    // send_at_command("AT+CMQTTSUBTOPIC=0,9,0\r\n",response,1000);
    send_at_command(topic,response,1000);

    //Subscribe
    snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTSUB=0,%d,0\r\n", len);
    // send_at_command(mqtt_topic, response, 1000);
    send_at_command("AT+CMQTTSUB=0\r\n",response,1000);
    // send_at_command(topic,response,1000);


    // Disconnect
    // len=strlen(topic);
    // snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTUNSUBTOPIC=0,%d", len);
    // send_at_command(mqtt_topic, response, 1000);
    // send_at_command(topic,response,1000);

    // Unsubcribe
        // len=strlen(topic);
    // snprintf(mqtt_topic, sizeof(mqtt_topic), "AT+CMQTTUNSUB==0,%d", len);
    // send_at_command(mqtt_topic, response, 1000);
    // send_at_command(topic,response,1000);

    // send_at_command("AT+CMQTTDISC=0,60\r\n", response, 2000);
    // send_at_command("AT+CMQTTSTOP\r\n",response,1000);


    // ESP_LOGI("MQTT", "MQTT Subscribe response: %s", response);
}
void gsm_init(){

    // Initialize MQTT
    const char *broker = "thingsboard.cloud:8883";
    const char *accesstoken = "399kawoa7g4y9ovt57p6";
    const char *clientid = "KP";

    mqtt_init(broker, accesstoken, clientid);
    char msg[30];
    sprintf(msg, "{\"temperature\":%d}", Data[0]);
//    mqtt_publish("v1/devices/me/telemetry", "{\"temperature\": 51, \"humidity\": 03, \"flowRate\": 4, \"energy\": 91, \"volume\": 563, \"totalVolume\": 64}");
     mqtt_publish("v1/devices/me/telemetry", msg);

    // mqtt_subscribe("v1/devices/me/telemetry");
}
