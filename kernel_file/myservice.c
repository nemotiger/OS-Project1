#include <linux/linkage.h>
#include <linux/kernel.h>
#include <uapi/linux/time.h>
#include <linux/time.h>
#include <linux/ktime.h>
#include <linux/timekeeping.h>
#include <linux/uaccess.h>
#include <linux/sched.h>
#include <asm/current.h>

asmlinkage void sys_get_nstime(struct timespec *time) {
    struct timespec64 ts64;
    getnstimeofday64(&ts64);

    struct timespec ts;
    ts = timespec64_to_timespec(ts64);

    copy_to_user(time, &ts, sizeof(ts));
}

asmlinkage void sys_log_pslifetime(struct timespec start) {
    struct timespec64 end;
    getnstimeofday64(&end);
    printk("[Project1] %d %ld.%ld %ld.%ld\n", current->pid, start.tv_sec, start.tv_nsec, end.tv_sec, end.tv_nsec);
}
