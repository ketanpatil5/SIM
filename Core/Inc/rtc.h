/*
 * rtc.h
 *
 *  Created on: May 15, 2025
 *      Author: Admin
 */

#ifndef INC_RTC_H_
#define INC_RTC_H_

void rtc_int(void);
uint64_t RTC_Get_Epoch(void);
int is_leap_year(int year);
void SetRTCFromCCLK(char *buffer);

#endif /* INC_RTC_H_ */
