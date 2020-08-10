#include <iostream>
using namespace std;

class father
{
private:
    int *p;

public:
    father()
    {
        cout << "father::ctor" << endl;
        this->p = new int(5);
    }
    ~father()
    {
        cout << "father::dtor" << endl;
        delete this->p;
    }
};

class son : public father
{
private:
    int *q;
    int i;
    int j;

public:
    son(int s, int t) : father(), i(s), j(t)
    {
        cout << "son::ctor" << endl;
        cout << this->i << this->j;
        this->q = new int(500);
    }
    ~son()
    {
        cout << "son::dtor" << endl;
        delete this->q;
    }
    int *qv()
    {
        return this->q;
    }
};

int main()
{
    son *s = new son(2, 3);
    father *f = s;
    int *a = s->qv();
    delete f;
    cout << *a << endl;
    delete a;
    return 0;
}
