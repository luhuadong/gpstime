# gpstime

GPS time, UTC time, and Julian date conversion library


## 转换思想

各个时间系统都有严格的转换公式，其转换的主要思想是把通用时、GPS 时间、和年积日分别转换为儒略日，然后以儒略日为媒介，实现任意两个时间系统的相互转换。

![](https://static.getiot.tech/gps-time-conversion.png)
