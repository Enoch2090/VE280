//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#include <iostream>
#include "course.h"

typedef struct task
{
    std::string type;
    int index; // Task index of type
    int due_month;
    int due_day;
} Task;
/*
 * Task is used to represent tasks in a course.
 * type could be "Lab", "Project" and etc., which specifies the type of the task,
 * index is the number of task of this type,
 * due_month and due_day specifies its due date
 */

// ----------TechnicalCourse--------------
const int MAXTASKS = 4; // default maximum number of tasks in a course at a time
class TechnicalCourse : public Course
{
protected:
    Task *tasks;
    int numTasks;
    int sizeTasks;
    std::string course_code;

public:
    TechnicalCourse(const std::string &course_code, int size = MAXTASKS);

    ~TechnicalCourse()
    {
        delete[] this->tasks;
    }

    void updateTask(const std::string &type, int index, int due_month, int due_day);

    void finishTask(const std::string &type, int index, int finish_month, int finish_day);
    void print();
};

TechnicalCourse::TechnicalCourse(const std::string &course_code, int size)
{
    this->course_code = course_code;
    this->sizeTasks = size;
    this->numTasks = 0;
    this->tasks = new Task[size];
}

void TechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: if Task index of type already exists in tasks, updates its due_month & due_day ;
//          otherwise, adds Task i of type at the end of tasks if tasks is not full,
//          throw an exception if tasks is full
{
    if (this->numTasks == this->sizeTasks)
    {
        tooManyTasks t;
        throw t;
    }
    bool taskExists = false;
    for (int taskid = 0; taskid < this->numTasks; taskid++)
    {
        if (this->tasks[taskid].type == type && this->tasks[taskid].index == index)
        {
            taskExists = true;
            this->tasks[taskid].due_month = due_month;
            this->tasks[taskid].due_day = due_day;
            break;
        }
    }
    if (!taskExists)
    {
        this->tasks[numTasks].type = type;
        this->tasks[numTasks].index = index;
        this->tasks[numTasks].due_month = due_month;
        this->tasks[numTasks].due_day = due_day;
        this->numTasks++;
        std::cout << this->course_code << " " << type << " " << index << " is released! Submit it via ";
        if (type == "Lab" || type == "Project")
        {
            std::cout << "oj!" << std::endl;
        }
        else
        {
            std::cout << "canvas!" << std::endl;
        }
    }
}

void TechnicalCourse::finishTask(const std::string &type, int index, int finish_month, int finish_day)
// REQUIRES: Task index of type is in tasks. finish_month and finish_day are in normal range.
// MODIFIES: this
// EFFECTS: removes Task index of type
{
    // std::cout << "Finish " << type << index << " " << finish_month << "." << finish_day << std::endl;
    int donetaskid = 0;
    bool overdue = false;
    for (int taskid = 0; taskid < this->numTasks; taskid++)
    {
        if (this->tasks[taskid].type == type && this->tasks[taskid].index == index)
        {
            donetaskid = taskid;
            break;
        }
    }
    if (finish_month > tasks[donetaskid].due_month)
    {
        overdue = true;
    }
    else if (finish_month == tasks[donetaskid].due_month)
    {
        if (finish_day > tasks[donetaskid].due_day)
        {
            overdue = true;
        }
    }
    if (overdue)
    {
        std::cout << this->course_code << " " << tasks[donetaskid].type << " " << tasks[donetaskid].index << " is overdue!" << std::endl;
    }
    else
    {
        std::cout << this->course_code << " " << tasks[donetaskid].type << " " << tasks[donetaskid].index << " is finished!" << std::endl;
    }
    for (int taskid = donetaskid; taskid < this->numTasks - 1; taskid++)
    {
        this->tasks[taskid].type = this->tasks[taskid + 1].type;
        this->tasks[taskid].index = this->tasks[taskid + 1].index;
        this->tasks[taskid].due_month = this->tasks[taskid + 1].due_month;
        this->tasks[taskid].due_day = this->tasks[taskid + 1].due_day;
    }
    this->numTasks--;
}
void TechnicalCourse::print()
{
    std::cout << course_code << std::endl;
    for (int i = 0; i < numTasks; ++i)
    {
        std::cout << tasks[i].type << " " << tasks[i].index << ": "
                  << tasks[i].due_month << "/" << tasks[i].due_day << std::endl;
    }
}

// ----------UpperlevelTechnicalCourse--------------
class UpperlevelTechnicalCourse : public TechnicalCourse
{
public:
    UpperlevelTechnicalCourse(const std::string &course_code, int size = MAXTASKS);

    ~UpperlevelTechnicalCourse() = default;

    void updateTask(const std::string &type, int index, int due_month, int due_day);
};

UpperlevelTechnicalCourse::UpperlevelTechnicalCourse(const std::string &course_code, int size) : TechnicalCourse(course_code, size) {}

void UpperlevelTechnicalCourse::updateTask(const std::string &type, int index, int due_month, int due_day)
// REQUIRES: due_month and due_day are in normal range.
// MODIFIES: this
// EFFECTS: If Task index of type does not exist in tasks,
//          adds Task i of type according to its due date if tasks is not full, throw an exception if tasks is full.
//          If Task index of type already exists in tasks,
//          updates its position in tasks & due_month & due_day if its due_month/due_day is changed,
//          do nothing if its due_month/due_day is unchanged.
{
    // std::cout << "Update " << type << index << " " << due_month << "." << due_day << std::endl;
    if (this->numTasks == this->sizeTasks)
    {
        tooManyTasks t;
        throw t;
    }
    bool taskExists = false;
    int original_index = numTasks;
    int insert_index = numTasks;
    for (int taskid = 0; taskid < this->numTasks; taskid++)
    {
        if (this->tasks[taskid].type == type && this->tasks[taskid].index == index)
        {
            taskExists = true;
            original_index = taskid;
            if (this->tasks[taskid].due_month == due_month && this->tasks[taskid].due_day == due_day)
            {
                return;
            }
            break;
        }
    }

    if (taskExists)
    {
        for (int taskid = original_index; taskid < this->numTasks - 1; taskid++)
        {
            this->tasks[taskid].type = this->tasks[taskid + 1].type;
            this->tasks[taskid].index = this->tasks[taskid + 1].index;
            this->tasks[taskid].due_month = this->tasks[taskid + 1].due_month;
            this->tasks[taskid].due_day = this->tasks[taskid + 1].due_day;
        }
        this->numTasks--;
        insert_index = this->numTasks;
    }

    for (int taskid = 0; taskid < this->numTasks; taskid++)
    {
        if ((this->tasks[taskid].due_month > due_month) || (this->tasks[taskid].due_month == due_month && this->tasks[taskid].due_day > due_day))
        {
            insert_index = taskid;
            break;
        }
    }

    for (int taskid = insert_index; taskid < this->numTasks; taskid++)
    {
        this->tasks[taskid + 1].type = this->tasks[taskid].type;
        this->tasks[taskid + 1].index = this->tasks[taskid].index;
        this->tasks[taskid + 1].due_month = this->tasks[taskid].due_month;
        this->tasks[taskid + 1].due_day = this->tasks[taskid].due_day;
    }
    this->tasks[insert_index].type = type;
    this->tasks[insert_index].index = index;
    this->tasks[insert_index].due_month = due_month;
    this->tasks[insert_index].due_day = due_day;
    this->numTasks++;

    if (!taskExists)
    {

        std::cout << this->course_code << " " << type << " " << index << " is released! Submit it via ";
        if (type == "Lab" || type == "Project")
        {
            std::cout << "oj!" << std::endl;
        }
        else if (type == "Team Project")
        {
            std::cout << "github!" << std::endl;
        }
        else
        {
            std::cout << "canvas!" << std::endl;
        }
    }
}

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size)
{
    if (class_type == "Technical")
    {
        if (assign_size)
        {
            return new TechnicalCourse(course_code, tasks_size);
        }
        else
        {
            return new TechnicalCourse(course_code);
        }
    }
    else if (class_type == "Upper Level Technical")
    {
        if (assign_size)
        {
            return new UpperlevelTechnicalCourse(course_code, tasks_size);
        }
        else
        {
            return new UpperlevelTechnicalCourse(course_code);
        }
    }
    else
    {
        return nullptr;
    }
}
