/*
 * Lab2 Ex2 VE280 20SU
 * Created by: Yiqing Fan
 * Last update: May 25, 2020
 */

#include <cstdlib>
#include <iostream>
#include <string>
using namespace std;
typedef struct
{
    string name;
    int ChineseScore;
    int MathScore;
    int EnglishScore;
} Student;

int compare(const void *p1, const void *p2)
{
    Student s1 = *static_cast<const Student *>(p1);
    Student s2 = *static_cast<const Student *>(p2);
    return (s1.ChineseScore + s1.MathScore + s1.EnglishScore) >= (s2.ChineseScore + s2.MathScore + s2.EnglishScore) ? -1 : 1;
}

int main()
{
    unsigned int NAMELEN = 16;
    int n = 0;
    cin >> n;
    Student *data = new Student[n];
    for (int i = 0; i < n; i++)
    {
        string name;
        int CScore, MScore, EScore;
        cin >> name >> CScore >> MScore >> EScore;
        unsigned int namel = name.length();
        if (namel < NAMELEN)
        {
            for (unsigned int k = 0; k < NAMELEN - namel; k++)
            {
                name += ' ';
            }
        }

        data[i] = {name,
                   CScore,
                   MScore,
                   EScore};
    }

    std::qsort(data, n, sizeof(data[0]), compare);

    for (int i = 0; i < n; i++)
    {
        cout << data[i].name << data[i].ChineseScore << ' ' << data[i].MathScore << ' ' << data[i].EnglishScore << endl;
    }

    return 0;
}