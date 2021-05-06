#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/module.h>
#include <linux/init.h>

static struct task_struct *test_task;

int threadfuc(void* data)
{
    int i = 0;
    while(1)
    {
        if (kthread_should_stop()) break;
        if (1)
        {
            printk(KERN_INFO "i = %d\n", i);
            i++;
        }
        schedule_timeout(HZ);
    }

    return 0;
}

static int test_init(void)
{
    test_task = kthread_run(threadfuc, NULL, "test_task");
    printk(KERN_INFO"module enter");
    return 0;
}

static void test_cleanup(void)
{
    if(test_task)
    {
        kthread_stop(test_task);
        test_task = NULL;
        printk(KERN_INFO"module remove");
    }
}

module_init(test_init);
module_exit(test_cleanup);