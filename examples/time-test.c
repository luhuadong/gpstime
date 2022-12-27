/*
 * Copyright (c) 2022, RudyLo <luhuadong@163.com>
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2022-12-27     luhuadong    the first version
 */

#include <rtthread.h>
#include "GPSTime.h"

static void gpstime_sample(void)
{
    COMMONTIME pct  = {0};
    JULIANDAY  pjd  = {0};
    DayOfYear  pdoy = {0};
    GPSTIME    pgt  = {0};

    pct.year = 2022;
    pct.month = 12;
    pct.day = 12;
    pct.hour = 17;
    pct.minute = 38;
    pct.second = 45.26;
    rt_kprintf("转换之前的通用时（当地时间）：");
    rt_kprintf("%d-%d-%d %d:%d:%f\n", pct.year, pct.month, pct.day, pct.hour, pct.minute, pct.second);

    //通用时->儒略日的转换
    CommonTimeToJulianDay(&pct, &pjd);
    rt_kprintf("通用时->儒略日的转换:");
    rt_kprintf("%d, %d, %f\n", pjd.day, pjd.tod.seconds, pjd.tod.tos);

    //儒略日->通用时的转换
    JulianDayToCommonTime(&pjd, &pct);
    rt_kprintf("儒略日->通用时的转换:");
    rt_kprintf("%d-%d-%d %d:%d:%f\n", pct.year, pct.month, pct.day, pct.hour, pct.minute, pct.second);

    //儒略日->GPS时的转换
    JulianDayToGPSTime(&pjd, &pgt);
    rt_kprintf("儒略日->GPS时的转换:");
    rt_kprintf("%d, %d, %f\n", pgt.weeks, pgt.tow.seconds, pgt.tow.tos);

    //GPS时->儒略日的转换
    GPSTimeToJulianDay(&pgt, &pjd);
    rt_kprintf("GPS时->儒略日的转换:");
    rt_kprintf("%d, %d, %f\n", pjd.day, pjd.tod.seconds, pjd.tod.tos);

    //通用时->GPS时的转换
    CommonTimeToGPSTime(&pct, &pgt);
    rt_kprintf("通用时->GPS时的转换:");
    rt_kprintf("%d, %d, %f\n", pgt.weeks, pgt.tow.seconds, pgt.tow.tos);

    //GPS时->通用时的转换
    GPSTimeToCommonTime(&pgt, &pct);
    rt_kprintf("GPS时->通用时的转换:");
    rt_kprintf("%d-%d-%d %d:%d:%f\n", pct.year, pct.month, pct.day, pct.hour, pct.minute, pct.second);

    //通用时->年积日
    CommonTimeToDOY(&pct, &pdoy);
    rt_kprintf("通用时->年积日:");
    rt_kprintf("%d, %d, %d, %f\n", pdoy.year, pdoy.day, pdoy.tod.seconds, pdoy.tod.tos);

    //年积日->通用时
    DOYToCommonTime(&pdoy, &pct);
    rt_kprintf("年积日->通用时:");
    rt_kprintf("%d-%d-%d %d:%d:%f\n", pct.year, pct.month, pct.day, pct.hour, pct.minute, pct.second);

    //GPS时->年积日
    GPSTimeToDOY(&pgt, &pdoy);
    rt_kprintf("GPS时->年积日:");
    rt_kprintf("%d, %d, %d, %f\n", pdoy.year, pdoy.day, pdoy.tod.seconds, pdoy.tod.tos);

    //年积日->GPS时
    DOYToGPSTime(&pdoy, &pgt);
    rt_kprintf("年积日->GPS时:");
    rt_kprintf("%d, %d, %f\n", pgt.weeks, pgt.tow.seconds, pgt.tow.tos);

    //儒略日->年积日
    JulianDayToDOY(&pjd, &pdoy);
    rt_kprintf("儒略日->年积日:");
    rt_kprintf("%d, %d, %d, %f\n", pdoy.year, pdoy.day, pdoy.tod.seconds, pdoy.tod.tos);

    //年积日->儒略日
    DOYToJulianDay(&pdoy, &pjd);
    rt_kprintf("年积日->儒略日:");
    rt_kprintf("%d, %d, %f\n", pjd.day, pjd.tod.seconds, pjd.tod.tos);

    rt_kprintf("经过各种转换后还原得到的通用时:");
    rt_kprintf("%d-%d-%d %d:%d:%f\n", pct.year, pct.month, pct.day, pct.hour, pct.minute, pct.second);
}
#ifdef FINSH_USING_MSH
MSH_CMD_EXPORT(gpstime_sample, Test GPSTime conversion);
#endif