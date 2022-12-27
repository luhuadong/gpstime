/*
 * Copyright (c) 2022, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-27     luhuadong    the first version
 */

#include <stdint.h>
#include "GPSTime.h"

/* 取小数部分 */
static double FRAC(double morigin)
{
    return morigin - (long)(morigin);
}

/* 通用时到儒略日的转换 */
void CommonTimeToJulianDay(const PCOMMONTIME pct, PJULIANDAY pjd) 
{
    if (pct->year<1900)
    {
        if (pct->year<80)
            pct->year += 2000;
        else pct->year += 1900;
    }
    double ut = pct->hour + pct->minute / 60.0 + pct->second / 3600.0;
    if (pct->month <= 2)
    {
        pct->year -= 1;
        pct->month += 12;
    }
    pjd->day = (int)(365.25*pct->year) + (int)(30.6001*(pct->month + 1)) + pct->day + (int)(ut / 24 + 1720981.5);
    pjd->tod.seconds = ((pct->hour + 12) % 24) * 3600 + pct->minute * 60 + (int)pct->second;//秒的整数部分
    pjd->tod.tos = pct->second - (int)pct->second;//秒的小数部分
}

/* 儒略日到通用时的转换 */
void JulianDayToCommonTime(const PJULIANDAY pjd, PCOMMONTIME pct)
{
    double x = pjd->day + (pjd->tod.seconds + pjd->tod.tos) / (60.0*60.0 * 24);
    int a = (int)(x + 0.5);
    int b = a + 1537;
    int c = (int)((b - 122.1) / 365.25);
    int d = (int)(365.25*c);
    int e = (int)((b - d) / 30.6001);
    pct->day = b - d - (int)(30.6001*e);
    pct->month = e - 1 - 12 * (int)(e / 14);
    pct->year = c - 4715 - (int)((7 + pct->month) / 10);
    pct->hour = (pjd->tod.seconds / 3600 + 12) % 24;
    pct->minute = (pjd->tod.seconds % 3600) / 60;
    pct->second = pjd->tod.seconds % 60 + pjd->tod.tos;
    int N = a % 7;
}

/* 儒略日到GPS时的转换 */
void JulianDayToGPSTime(const PJULIANDAY pjd, PGPSTIME pgt)
{
    double x = pjd->day + (pjd->tod.seconds + pjd->tod.tos) / (60.0*60.0 * 24);
    pgt->weeks = (int)((x - 2444244.5) / 7);
    pgt->tow.seconds = (int)(((pjd->day - 2444244) % 7 + (pjd->tod.seconds / (60.0*60.0 * 24) - 0.5)) * 86400);
    pgt->tow.tos = pjd->tod.tos;
}

/* GPS时到儒略日的转换 */
void GPSTimeToJulianDay(const PGPSTIME pgt, PJULIANDAY pjd)
{
    pjd->day = (int)(pgt->weeks * 7 + (double)(pgt->tow.seconds) / 86400.0 + 2444244.5);
    pjd->tod.seconds = (pgt->tow.seconds + 43200) % 86400;
    pjd->tod.tos = pgt->tow.tos;
}

/* 通用时到GPS时的转换 */
void CommonTimeToGPSTime(const PCOMMONTIME pct, PGPSTIME pgt)
{
    JULIANDAY pjd = {0};
    CommonTimeToJulianDay(pct, &pjd);
    JulianDayToGPSTime(&pjd, pgt);
}

/* GPS时到通用时的转换 */
void GPSTimeToCommonTime(const PGPSTIME pgt, PCOMMONTIME pct)
{
    JULIANDAY pjd = {0};
    GPSTimeToJulianDay(pgt, &pjd);
    JulianDayToCommonTime(&pjd, pct);
}

/* 通用时到年内天 */
void CommonTimeToDOY(const PCOMMONTIME pct, PDayOfYear pdoy)
{
    COMMONTIME pcto = {0};
    pcto.year = pct->year;
    pcto.month = 1;
    pcto.day = 1;
    pcto.hour = 0;
    pcto.minute = 0;
    pcto.second = 0;

    JULIANDAY pjdo = {0};

    double JD, JDO;
    CommonTimeToJulianDay(&pcto, &pjdo);
    JDO = pjdo.day + (pjdo.tod.seconds + pjdo.tod.tos) / 86400;

    JULIANDAY pjd = {0};
    CommonTimeToJulianDay(pct, &pjd);

    JD = pjd.day + (pjd.tod.seconds + pjd.tod.tos) / 86400;

    pdoy->day = (short)(JD - JDO + 1);
    pdoy->year = pct->year;

    pdoy->tod.seconds = (long)(pct->hour * 3600 + pct->minute * 60 + pct->second);

    /*pct->hour*3600+pct->minute*60+pct->second-pdoy->tod.seconds;*/
    pdoy->tod.tos = pct->second - (int)(pct->second);
}

/* 年内天到普通时 */
void DOYToCommonTime(const PDayOfYear pdoy, PCOMMONTIME pct)
{
    COMMONTIME pcto = {0};
    pcto.year = pdoy->year;
    pcto.month = 1;
    pcto.day = 1;
    pcto.hour = 0;
    pcto.minute = 0;
    pcto.second = 0;
    JULIANDAY pjdo = {0};
    double JD, JDO;
    CommonTimeToJulianDay(&pcto, &pjdo);
    JDO = pjdo.day + (pjdo.tod.seconds + pjdo.tod.tos) / 86400;
    JD = JDO + pdoy->day + (pdoy->tod.seconds + pdoy->tod.tos) / 86400 - 1;
    long a, b, c, d, e;
    a = (long)(JD + 0.5);
    b = a + 1537;
    c = (long)((b - 122.1) / 365.25);
    d = (long)(365.25*c);
    e = (long)((b - d) / 30.6001);
    pct->day = (short)(b - d - (long)(30.6001*e) + FRAC(JD + 0.5));
    pct->month = (short)(e - 1 - 12 * (long)(e / 14));
    pct->year = (short)(c - 4715 - (long)((7 + pct->month) / 10));
    pct->hour = (short)((pdoy->tod.seconds + pdoy->tod.tos) / 3600);
    pct->minute = (short)((pdoy->tod.seconds + pdoy->tod.tos - pct->hour * 3600) / 60);
    pct->second = pdoy->tod.seconds + pdoy->tod.tos - pct->hour * 3600 - pct->minute * 60;
}

void GPSTimeToDOY(const PGPSTIME pgt, PDayOfYear pdoy)
{
    JULIANDAY pjd = {0};
    GPSTimeToJulianDay(pgt, &pjd);
    COMMONTIME pct = {0};
    JulianDayToCommonTime(&pjd, &pct);
    CommonTimeToDOY(&pct, pdoy);
}

void DOYToGPSTime(const PDayOfYear pdoy, PGPSTIME pgt)
{
    COMMONTIME pct = {0};
    DOYToCommonTime(pdoy, &pct);
    CommonTimeToGPSTime(&pct, pgt);
}

void JulianDayToDOY(const PJULIANDAY pjd, PDayOfYear pdoy)
{
    COMMONTIME pct = {0};
    JulianDayToCommonTime(pjd, &pct);
    CommonTimeToDOY(&pct, pdoy);
}

void DOYToJulianDay(const PDayOfYear pdoy, PJULIANDAY pjd)
{
    COMMONTIME pct = {0};
    DOYToCommonTime(pdoy, &pct);
    CommonTimeToJulianDay(&pct, pjd);
}