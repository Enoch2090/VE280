## Usage
1. Put a for loop inside your `main()` function, but outside your other codes:
    ```cpp
    int main()
    {
        for (int r = 0; r < RUNTIME; r++)
        {
            //CODE HERE
        }
    }
    ```
    Note that `RUNTIME` equals to the number of cases.
2. Run in shell:
    ```bash
    $ g++ -Wall -Werror -pedantic --std=c++11 -g p1.cpp -o p1
    $ ./p1 < testcase.in >>t.out
    $ diff t.out testcase.out
    ```
3. For any difference in output located at line 2n, see for the testcase n.