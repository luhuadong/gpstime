/*
 * Copyright (c) 2022, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-27     luhuadong    the first version
 */

#include <iostream>
#include "GPSTime.h"

using namespace std;

int main(void)
{
    PCOMMONTIME pct = new COMMONTIME;
    PJULIANDAY pjd = new JULIANDAY;
    PDayOfYear pdoy = new DayOfYear;
    PGPSTIME pgt = new GPSTIME;
    pct->year = 2022;
    pct->month = 12;
    pct->day = 12;
    pct->hour = 17;
    pct->minute = 38;
    pct->second = 45.26;
    cout << "转换之前的通用时（当地时间）：";
    cout << pct->year << "-" << pct->month << "-" << pct->day << "-" << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
    CommonTimeToJulianDay(pct, pjd);//通用时->儒略日的转换
    cout << "通用时->儒略日的转换:";
    cout << pjd->day << ", " << pjd->tod.seconds << ", " << pjd->tod.tos << endl;
    cout << endl;
    JulianDayToCommonTime(pjd, pct);//儒略日->通用时的转换
    cout << "儒略日->通用时的转换:";
    cout << pct->year << "-" << pct->month << "-" << pct->day << " " << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
    JulianDayToGPSTime(pjd, pgt);//儒略日->GPS时的转换
    cout << "儒略日->GPS时的转换:";
    cout << pgt->weeks << ", " << pgt->tow.seconds << ", " << pgt->tow.tos << endl;
    cout << endl;
    GPSTimeToJulianDay(pgt, pjd);//GPS时->儒略日的转换
    cout << "GPS时->儒略日的转换:";
    cout << pjd->day << ", " << pjd->tod.seconds << ", " << pjd->tod.tos << endl;
    cout << endl;
    CommonTimeToGPSTime(pct, pgt);//通用时->GPS时的转换
    cout << "通用时->GPS时的转换:";
    cout << pgt->weeks << ", " << pgt->tow.seconds << ", " << pgt->tow.tos << endl;
    cout << endl;
    GPSTimeToCommonTime(pgt, pct);//GPS时->通用时的转换
    cout << "GPS时->通用时的转换:";
    cout << pct->year << "-" << pct->month << "-" << pct->day << " " << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
    CommonTimeToDOY(pct, pdoy);//通用时->年积日
    cout << "通用时->年积日:";
    cout << pdoy->year << ", " << pdoy->day << ", " << pdoy->tod.seconds << ", " << pdoy->tod.tos << endl;
    cout << endl;
    DOYToCommonTime(pdoy, pct);//年积日->通用时
    cout << "年积日->通用时:";
    cout << pct->year << "-" << pct->month << "-" << pct->day << " " << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
    GPSTimeToDOY(pgt, pdoy);//GPS时->年积日
    cout << "GPS时->年积日:";
    cout << pdoy->year << ", " << pdoy->day << ", " << pdoy->tod.seconds << ", " << pdoy->tod.tos << endl;
    cout << endl;
    DOYToGPSTime(pdoy, pgt);//年积日->GPS时
    cout << "年积日->GPS时:";
    cout << pgt->weeks << ", " << pgt->tow.seconds << ", " << pgt->tow.tos << endl;
    cout << endl;
    JulianDayToDOY(pjd, pdoy);//儒略日->年积日
    cout << "儒略日->年积日:";
    cout << pdoy->year << ", " << pdoy->day << ", " << pdoy->tod.seconds << ", " << pdoy->tod.tos << endl;
    cout << endl;
    DOYToJulianDay(pdoy, pjd);//年积日->儒略日
    cout << "年积日->儒略日:";
    cout << pjd->day << ", " << pjd->tod.seconds << ", " << pjd->tod.tos << endl;
    cout << endl;
    cout << "经过各种转换后还原得到的通用时:";
    cout << pct->year << "-" << pct->month << "-" << pct->day << " " << pct->hour << ":" << pct->minute << ":" << pct->second << endl;
    cout << endl;
}
