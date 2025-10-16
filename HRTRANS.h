#ifndef HR_H_
#define HR_H_
#include <bits/stdc++.h>
using namespace std;
class Captain{
    private:
    public:
        Captain();
        string encode(string);
        string to_binary(int , string);
        string to_hamming(string);
};
class Soldier{
    private: int id;
    public:
        Soldier();
        Soldier(int);
        string decode(string);
        string to_decimal(string);
        string to_binary(string);
};



#endif