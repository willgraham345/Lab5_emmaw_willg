extern void sleep_main(void);
extern void kernel_main(void);
//extern void rtc_main(void);
extern void interrupt_main(void);
extern void busy_main(void);

void main(void)
{
#ifdef SLEEP_ACTIVITY
    sleep_main();
#endif

#ifdef KERNEL_ACTIVITY
    kernel_main();
#endif

#ifdef RTC_ACTIVITY
    //rtc_main();
    kernel_main();
#endif

#ifdef INTERRUPT_ACTIVITY
    interrupt_main();
#endif

#ifdef BUSY_ACTIVITY
    busy_main();
#endif
}
