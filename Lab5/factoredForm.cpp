//
// Created by Zhuoer Zhu on 10/06/2020.
//

#include "factoredForm.h"

quadraticFunction::quadraticFunction(float a_in, float b_in, float c_in)
{
    this->a = a_in;
    float b = b_in;
    float c = c_in;
    float d_sq = b * b - 4 * a * c;
    complexNum r1, r2;
    if (d_sq > 0)
    {
        r1.imaginary = 0;
        r2.imaginary = 0;
        r1.real = (-b - sqrt(d_sq)) / (2 * a);
        r2.real = (-b + sqrt(d_sq)) / (2 * a);
    }
    else if (d_sq == 0)
    {
        r1.imaginary = 0;
        r2.imaginary = 0;
        r1.real = (-b) / (2 * a);
        r2.real = (-b) / (2 * a);
    }
    else if (d_sq < 0)
    {
        r1.imaginary = (-sqrt(-d_sq)) / (2 * a);
        r2.imaginary = (sqrt(-d_sq)) / (2 * a);
        r1.real = (-b) / (2 * a);
        r2.real = (-b) / (2 * a);
    }
    this->r1 = r1;
    this->r2 = r2;
}

float quadraticFunction::getA() const
{
    return a;
}

float quadraticFunction::getB() const
{
    return -(this->a * (this->r1.real + this->r2.real));
}

float quadraticFunction::getC() const
{
    return this->a * (this->r1.real * this->r2.real - this->r1.imaginary * this->r2.imaginary);
}

float quadraticFunction::evaluate(float x)
{
    return (a * x * x + this->getB() * x + this->getC());
}
root quadraticFunction::getRoot()
{
    root_t root;
    root.roots[0] = this->r1;
    root.roots[1] = this->r2;
    if (r1.imaginary == 0 && r2.imaginary == 0 && r1.real != r2.real)
    {
        root.realRootNum = 2;
    }
    else if (r1.imaginary == 0 && r2.imaginary == 0 && r1.real == r2.real)
    {
        root.realRootNum = 1;
    }
    else
    {
        root.realRootNum = 0;
    }
    return root;
}

int quadraticFunction::intersect(quadraticFunction g)
{
    float b = this->getB();
    float c = this->getC();
    if (g.getA() != this->a)
    {
        quadraticFunction inter_quad(this->a - g.getA(), b - g.getB(), c - g.getC());
        root_t roots = inter_quad.getRoot();
        return (roots.realRootNum > 0);
    }
    else
    {
        return 1;
    }
}