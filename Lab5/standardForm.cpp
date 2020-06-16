//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include <cmath>
#include "standardForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in)
{
    this->a = a_in;
    this->b = b_in;
    this->c = c_in;
}

float quadraticFunction::getA() const
{
    return a;
}

float quadraticFunction::getB() const
{
    return b;
}

float quadraticFunction::getC() const
{
    return c;
}

float quadraticFunction::evaluate(float x)
{
    return (a * x * x + b * x + c);
}

root quadraticFunction::getRoot()
{
    root_t root;
    float d_sq = b * b - 4 * a * c;
    complexNum r1, r2;
    if (d_sq > 0)
    {
        r1.imaginary = 0;
        r2.imaginary = 0;
        r1.real = (-b - sqrt(d_sq)) / (2 * a);
        r2.real = (-b + sqrt(d_sq)) / (2 * a);
        root.realRootNum = 2;
    }
    else if (d_sq == 0)
    {
        r1.imaginary = 0;
        r2.imaginary = 0;
        r1.real = (-b) / (2 * a);
        r2.real = (-b) / (2 * a);
        root.realRootNum = 1;
    }
    else if (d_sq < 0)
    {
        r1.imaginary = (-sqrt(-d_sq)) / (2 * a);
        r2.imaginary = (sqrt(-d_sq)) / (2 * a);
        r1.real = (-b) / (2 * a);
        r2.real = (-b) / (2 * a);
        root.realRootNum = 0;
    }
    root.roots[0] = r1;
    root.roots[1] = r2;
    return root;
}

int quadraticFunction::intersect(quadraticFunction g)
{
    if (g.getA() != this->a)
    {
        quadraticFunction inter_quad(this->a - g.getA(), this->b - g.getB(), this->c - g.getC());
        root_t roots = inter_quad.getRoot();
        return (roots.realRootNum > 0);
    }
    else
    {
        return 1;
    }
}