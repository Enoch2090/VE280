//
// VE280 Lab 7, SU2020
// Created by cyx on 20-5-22.
//

#ifndef COURSE_H
#define COURSE_H
#include <iostream>
// an exception class
class tooManyTasks
{
};

class Course
{
public:
    virtual ~Course(){};
    virtual void updateTask(const std::string &type, int index, int due_month, int due_day) = 0;
    virtual void finishTask(const std::string &type, int index, int finish_month, int finish_day) = 0;
    virtual void print() = 0;
};

Course *create(const std::string &class_type, const std::string &course_code, bool assign_size, int tasks_size);
// EFFECTS: returns a pointer according to class_type
//          If class_type is not "Technical" or "Upper Level Technical", returns a null pointer.
//          If assignSize is true, the maximum number of tasks is specified by tasksSize;
//          otherwise, the maximum number of tasks is the default value.

#endif //COURSE_H
