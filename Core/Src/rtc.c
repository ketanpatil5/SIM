/*
 * rtc.c
 *
 *  Created on: May 15, 2025
 *      Author: Admin
 */
#include "main.h"
#include "sys_init.h"

RTC_DateTypeDef Date;
RTC_TimeTypeDef Time;

void rtc_int(void)
{

	  HAL_RTC_GetTime(&hrtc, &Time, RTC_FORMAT_BIN);
	  HAL_RTC_GetDate(&hrtc, &Date, RTC_FORMAT_BIN);


	  sprintf(command,"%02d-%02d-%2d, ", Date.Date, Date.Month, 2000+ Date.Year);
	  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);

	  sprintf(command,"%02d:%02d:%02d\r\n", Time.Hours, Time.Minutes, Time.Seconds);
	  HAL_UART_Transmit(&huart2,(uint8_t *)command,strlen(command),1000);


//	  uint64_t Rtc = RTC_Get_Epoch();
//	  sprintf(rtc,"Epoch: %lu\r\n", Rtc);
//	  HAL_UART_Transmit(&huart2,(uint8_t *)rtc,strlen(rtc),1000);
//	  HAL_Delay(500);


}


// Helper function to determine leap year
int is_leap_year(int year) {
    return ((year % 4 == 0 && year % 100 != 0) || (year % 400 == 0));
}

// Convert RTC time to Epoch
uint64_t RTC_Get_Epoch(void) {
    RTC_TimeTypeDef sTime;
    RTC_DateTypeDef sDate;

    HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
    HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN); // MUST be called after GetTime

    struct tm t;
    t.tm_year = 2000 + sDate.Year - 1900;  // RTC returns year offset from 2000
    t.tm_mon  = sDate.Month - 1;           // tm_mon: 0 = Jan
    t.tm_mday = sDate.Date;
    t.tm_hour = sTime.Hours;
    t.tm_min  = sTime.Minutes;
    t.tm_sec  = sTime.Seconds;
    t.tm_isdst = 0;

    // Calculate Epoch manually
    const int days_in_month[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    uint32_t days = 0;
    for (int year = 1970; year < t.tm_year + 1900; year++) {
        days += is_leap_year(year) ? 366 : 365;
    }

    for (int month = 0; month < t.tm_mon; month++) {
        if (month == 1 && is_leap_year(t.tm_year + 1900)) {
            days += 29;
        } else {
            days += days_in_month[month];
        }
    }

    days += t.tm_mday - 1;

//    return (days * 86400) + (t.tm_hour * 3600) + (t.tm_min * 60) + t.tm_sec;
    time_t epoch_sec = mktime(&t);  // Converts struct tm to epoch seconds
    return ((uint64_t)epoch_sec * 1000UL);  // Convert to milliseconds
}

void SetRTCFromCCLK(char *response) {
    int yy, MM, dd, hh, mm, ss;

    // Example: +CCLK: "25/05/15,11:27:40+00"
    char *start = strstr(response, "+CCLK: ");
    if (start) {
        if (sscanf(start, "+CCLK: \"%2d/%2d/%2d,%2d:%2d:%2d",
                   &yy, &MM, &dd, &hh, &mm, &ss) == 6) {
            RTC_DateTypeDef sDate = {0};
            RTC_TimeTypeDef sTime = {0};



            // Add 5 hours and 30 minutes (UTC+5:30)
//            mm += 30;
//            hh += 5;
//
//            if (mm >= 60) {
//                mm -= 60;
//                hh += 1;
//            }
//
//            if (hh >= 24) {
//                hh -= 24;
//                dd += 1;
//                // You can optionally handle month/year rollover here if needed
//            }

            sDate.Year = yy;
            sDate.Month = MM;
            sDate.Date = dd;
            sDate.WeekDay = RTC_WEEKDAY_MONDAY; // Optional: calculate real weekday if needed

            sTime.Hours = hh;
            sTime.Minutes = mm;
            sTime.Seconds = ss;


            HAL_RTC_SetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
            HAL_RTC_SetDate(&hrtc, &sDate, RTC_FORMAT_BIN);
        } else {
            HAL_UART_Transmit(&huart2, (uint8_t *)"Failed to parse time\r\n", 23, 100);
        }
    } else {
        HAL_UART_Transmit(&huart2, (uint8_t *)"CCLK not found in response\r\n", 29, 100);
    }
}
