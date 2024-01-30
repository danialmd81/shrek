#include<iostream>
#include<fstream>
#include<string>
#include<sstream>
#include<vector>

using namespace std;

int main()

{
    ifstream input1("input1.txt"), input2("input2.txt");
    string in1, in2, world1, world2;
    int i, j;
    cin >> i >> j;
    while (i > 0)
    {
        getline(input1, in1);
        i--;
    }
    while (j > 0)
    {
        getline(input2, in2);
        j--;
    }
    stringstream i1(in1), i2(in2);
    vector <string>comp1, comp2;
    while (i1 >> world1)
    {
        comp1.push_back(world1);
    }
    while (i2 >> world2)
    {
        comp2.push_back(world2);
    }
    for (auto&& c1 : comp1)
    {
        for (auto&& c2 : comp2)
        {
            if (c1 == c2)
            {
                cout << c1 << " ";
            }

        }

    }


    input1.close();
    input2.close();

}