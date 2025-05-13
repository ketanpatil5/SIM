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


extern char ATcommand[80];
extern uint8_t buffer[30];

#endif /* INC_GSM_H_ */
