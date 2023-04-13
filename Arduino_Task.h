#ifndef ARDUINO_TASK_H
#define ARDUINO_TASK_H

#include "Arduino.h"
#include "LOGO.h"

typedef void (*fun)(void *); /*定义函数指针*/

/*任务结构体*/
struct Task_data
{
    uint16_t Time;      // 任务间隔时间
    uint64_t Time_data; // 任务时间戳存储
    fun Task;           // 回调函数
    void *parameter;    // 回调函数参数
    Task_data(uint16_t Time_t, fun Task_t, void *parameter_t)
    {
        Time = Time_t;
        Time_data = millis();
        Task = Task_t;
        parameter = parameter_t;
    }
};

/*链表节点结构体*/
struct Linked_List
{
    void *Data;        // 数据域
    Linked_List *next; // 链表指针
    Linked_List(void *data)
    {
        Data = data;
        next = nullptr;
    }
};

typedef Linked_List *Task_handle;

/**
 * @brief 创建任务
 * @param Time 任务循环间隔时间
 * @param Task 任务执行函数
 * @param parameter 任务函数自定义参数
 * @return 任务句柄
 */
Task_handle Arduino_TaskCreate(uint16_t Time, void *parameter, fun Task);

/**
 * @brief 删除任务
 * @param Handle 任务句柄
 */
bool Arduino_TaskDelete(Task_handle Handle);

/**
 * @brief 任务循环
 */
void Arduino_TaskLoop();

#endif