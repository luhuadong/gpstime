/*
 * Copyright (c) 2022, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-27     luhuadong    the first version
 */

#ifndef __GPS_TIME_H__
#define __GPS_TIME_H__

/* 通用时 */
typedef struct tagCOMMONTIME
{
    int   year;
    int   month;
    int   day;
    int   hour;
    int   minute;
    double   second;
}COMMONTIME;
typedef COMMONTIME *PCOMMONTIME;

typedef struct tagTimeOfDay
{
    long seconds;   //秒数的整数部分
    double tos;     //秒数的小数部分
}TimeOfDay;
typedef TimeOfDay *PTimeOfDay;

/* 儒略日 */
typedef struct
{
    long day; 		//整数天数
    TimeOfDay tod;  //一天内的秒数
}JULIANDAY;
typedef JULIANDAY *PJULIANDAY;

/* 新儒略日 */
typedef struct tagMJULIANDAY
{
    long day;
    TimeOfDay  tod;
}MJULIANDAY;
typedef MJULIANDAY *PMJIANDAY;

typedef struct tagTimeOfWeek
{
    long seconds;	//秒整数部分
    double tos;	    //秒小数部分
}TimeOfWeek;
typedef TimeOfWeek *PTimeOfWeek;

/* GPS时 */
typedef struct tagGPSTIME
{
    int weeks; 		//周数
    TimeOfWeek tow;	//一周内的秒数
}GPSTIME;
typedef GPSTIME *PGPSTIME;

/* 年积日 */
typedef struct tagDayOfYear
{
    unsigned short year;
    unsigned short day;
    TimeOfDay tod;
}DayOfYear;
typedef DayOfYear *PDayOfYear;

#ifdef __cplusplus
extern "C" {
#endif

/* 通用时到儒略日的转换 */
void CommonTimeToJulianDay(const PCOMMONTIME pct, PJULIANDAY pjd);

/* 儒略日到通用时的转换 */
void JulianDayToCommonTime(const PJULIANDAY pjd, PCOMMONTIME pct);

/* 儒略日到GPS时的转换 */
void JulianDayToGPSTime(const PJULIANDAY pjd, PGPSTIME pgt);

/* GPS时到儒略日的转换 */
void GPSTimeToJulianDay(const PGPSTIME pgt, PJULIANDAY pjd);

/* 通用时到GPS时的转换 */
void CommonTimeToGPSTime(const PCOMMONTIME pct, PGPSTIME pgt);

/* GPS时到通用时的转换 */
void GPSTimeToCommonTime(const PGPSTIME pgt, PCOMMONTIME pct);

/* 通用时到年内天 */
void CommonTimeToDOY(const PCOMMONTIME pct, PDayOfYear pdoy);

/* 年内天到普通时 */
void DOYToCommonTime(const PDayOfYear pdoy, PCOMMONTIME pct);

void GPSTimeToDOY(const PGPSTIME pgt, PDayOfYear pdoy);

void DOYToGPSTime(const PDayOfYear pdoy, PGPSTIME pgt);

void JulianDayToDOY(const PJULIANDAY pjd, PDayOfYear pdoy);

void DOYToJulianDay(const PDayOfYear pdoy, PJULIANDAY pjd);

#ifdef __cplusplus
}
#endif

#endif /* __GPS_TIME_H__ */