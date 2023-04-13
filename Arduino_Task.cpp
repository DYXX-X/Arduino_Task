#include "Arduino_Task.h"

Linked_List *Head_Pointer = new Linked_List(nullptr); // 任务链表头指针->指向头节点(头节点数据域存放当前链表长度)

/**
 *
 *
 *
 * Arduino简单任务栈 成员函数
 *
 *
 *
 */

Task_handle Arduino_TaskCreate(uint16_t Time, void *parameter, fun Task)
{
    logo.println("创建任务");
    Linked_List *List = nullptr;
    for (List = Head_Pointer; List->next != nullptr; List = List->next) // 循环找到最后一个节点
        ;
    Head_Pointer->Data = (void *)(((int)Head_Pointer->Data) + 1);              // 链表长度+1
    return List->next = new Linked_List(new Task_data(Time, Task, parameter)); // new一个空间，链接链表，返回指针
}

bool Arduino_TaskDelete(Task_handle Handle)
{
    if (Handle == nullptr)
    {
        return false;
    }

    if (Handle == Head_Pointer) // 如果句柄等于头节点
    {
        logo.print("删除头节点"), logo.println((int)Handle);
        Head_Pointer = Head_Pointer->next; // 头节点等于下一个节点
        delete Handle;                     // 删除句柄
        return true;
    }

    for (Linked_List *List = Head_Pointer; List != nullptr; List = List->next) // 轮询链表
    {
        if (List->next == Handle) // 如果节点等于句柄
        {
            if (List->next->next == nullptr) // 如果节点指针域为空，则为尾节点
            {
                logo.print("删除尾节点"), logo.println((int)Handle);
                List->next = nullptr;
                delete Handle;
                return true;
            }
            else
            {
                logo.println();
                logo.println();
                logo.print("找到目标任务"), logo.println((int)List->next);
                logo.print("目标下一个节点"), logo.println((int)List->next->next);
                Linked_List *X = List->next->next; // 保存目标下一个节点
                List->next = X;                    // 重新链接链表
                logo.print("删除任务"), logo.println((int)Handle);
                delete Handle;
                return true;
            }
        }
        // delay(1000);
    }
    logo.println("句柄不存在！");
    return false;
}

void Arduino_TaskLoop()
{
    for (Linked_List *List = Head_Pointer->next; List != nullptr; List = List->next)
    {
        // logo.print("链表"), logo.println((int)List);
        // logo.print("节点"), logo.println((int)List);
        Task_data *Task = ((Task_data *)(List->Data));
        if (millis() - Task->Time_data >= Task->Time)
        {
            Task->Time_data = millis();
            Task->Task(Task->parameter);
        }
    }
}