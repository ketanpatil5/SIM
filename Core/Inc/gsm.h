/*
 * gsm.h
 *
 *  Created on: May 13, 2025
 *      Author: Admin
 */

#ifndef INC_GSM_H_
#define INC_GSM_H_

void gsm_init();
void send_at_command(const char *cmd, char *response, int timeout_ms);
void mqtt_subscribe(const char *topic);
void mqtt_publish(const char *topic, const char *data);
void gsm_set_clock();

#endif /* INC_GSM_H_ */
