#include "calendar.h"
#include "datetime.h"

#include "log.h"


/******************************************************************************
 * @brief clock_gettime
 * @���ص�ǰʱ�̵�ʱ���
 *****************************************************************************/
extern uint32_t clock_gettime(void);

/******************************************************************************
 * @brief clock_settime
 * @����ʱ���set_timestamp
 *****************************************************************************/
extern void clock_settime(const uint32_t set_timestamp);

/*******************************************************************************
 * @brief calendar_sync_from_inner_rtc
 ******************************************************************************/
void calendar_sync_from_inner_rtc(void)
{
    UTCTimeStruct utc_time;
    time_union_t time_union;

    //��ȡ��ǰϵͳʱ��
    get_wall_clock_time(&utc_time, false);

    time_union.time.year   = utc_time.year - 2000;
    time_union.time.month  = utc_time.month;
    time_union.time.day    = utc_time.day;
    time_union.time.hour   = utc_time.hour;
    time_union.time.minute = utc_time.minute;
    time_union.time.second = utc_time.second;

    //��������������ʱ��
    calendar_set_system_clock(time_union, true);
}

/******************************************************************************
 * @brief set_system_clock
 *****************************************************************************/
void set_system_clock(time_union_t time, bool need_update)
{
    //�����ı���:����ϵͳʱ����need_update

    uint32_t set_timestamp = 0;

    set_timestamp = linux_mktime(time.time.year + BEGYEAR, time.time.month, time.time.day,
                                 time.time.hour, time.time.minute, time.time.second,
                                 0);

    clock_settime(set_timestamp);

    UTCTimeStruct utc_time;
    get_wall_clock_time(&utc_time, false);

    LOG(LEVEL_DEBUG, "set system clock: [%d/%02d/%02d %02d:%02d:%02d]\n",utc_time.year,utc_time.month,utc_time.day,utc_time.hour,utc_time.minute,utc_time.second);

    //��������������ʱ��
    calendar_set_system_clock(time, need_update);
}

/******************************************************************************
 * @brief get_wall_clock_time
 *****************************************************************************/
void get_wall_clock_time(UTCTimeStruct * utc_time, bool extern_src)
{
    if (NULL == utc_time)
        return;

    //�����ı���:���ⲿʱ��оƬ����ʱ����extern_src

    utc_time->year = BEGYEAR;
    utc_time->month = 0;
    utc_time->day = 0;
    utc_time->hour = 0;
    utc_time->minute = 0;
    utc_time->second = 0;

    ConvertToUTCTime(utc_time, clock_gettime());
    utc_time->month += 1; //calibration
    utc_time->day += 1; //calibration
    utc_time->year -= 30;
}
