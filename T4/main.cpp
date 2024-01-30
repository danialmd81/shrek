#include <iostream>
#include <fstream>
#include <sstream>
#include <bitset>
#include <string>

using namespace std;

unsigned long hex2int(char ch)
{
    if (ch >= '0' && ch <= '9')
        return ch - '0';
    if (ch >= 'A' && ch <= 'F')
        return ch - 'A' + 10;
    if (ch >= 'a' && ch <= 'f')
        return ch - 'a' + 10;
    return -1;
}

void I_Format_Build(int ins, int op)
{
    string name;
    int rs, rt, imm;
    rs = (ins >> 21) & 31;
    rt = (ins >> 16) & 31;
    imm = ins & 32767;
    if ((ins & 32768) > 0)
    {
        imm = imm ^ 32767;
        imm++;
        imm *= -1;
    }
    switch (op)
    {
    case 8:
        name = "addi ";
        cout << name << "$" << rt << ", "
             << "$" << rs << ", " << imm << endl;
        break;
    case 12:
        name = "andi ";
        cout << name << "$" << rt << ", "
             << "$" << rs << ", " << imm << endl;
        break;
    case 13:
        name = "ori ";
        cout << name << "$" << rt << ", "
             << "$" << rs << ", " << imm << endl;
        break;
    case 35:
        name = "lw ";
        cout << name << "$" << rt << ", " << imm << "("
             << "$" << rs << ")" << endl;
        break;
    case 32:
        name = "lb ";
        cout << name << "$" << rt << ", " << imm << "("
             << "$" << rs << ")" << endl;
        break;
    case 43:
        name = "sw ";
        cout << name << "$" << rt << ", " << imm << "("
             << "$" << rs << ")" << endl;
        break;
    case 40:
        name = "sb ";
        cout << name << "$" << rt << ", " << imm << "("
             << "$" << rs << ")" << endl;
        break;
    default:
        break;
    }
}

void J_Format_Build(int ins, int op)
{
    int jump_address = ins & 67108863;
    string name;
    switch (op)
    {
    case 2:
        name = "j";
        printf("%s %X\n", name.c_str(), jump_address);
        break;
    case 3:
        name = "jal";
        printf("%s %X\n", name.c_str(), jump_address);
        break;
    default:
        break;
    }
}

void R_Format_Build(int ins, int op)
{
    string name;
    int rs, rt, rd, shamt, func;
    func = ins & 63;
    shamt = (ins >> 6) & 31;
    rs = (ins >> 21) & 31;
    rt = (ins >> 16) & 31;
    rd = (ins >> 11) & 31;
    switch (func)
    {
    case 0:
        name = "sll ";
        cout << name << "$" << rd << ", "
             << "$" << rt << ", " << shamt << endl;
        break;
    case 2:
        name = "srl ";
        cout << name << "$" << rd << ", "
             << "$" << rt << ", " << shamt << endl;
        break;
    case 32:
        name = "add ";
        cout << name << "$" << rd << ", "
             << "$" << rs << ", "
             << "$" << rt << endl;
        break;
    case 34:
        name = "sub ";
        cout << name << "$" << rd << ", "
             << "$" << rs << ", "
             << "$" << rt << endl;
        break;
    case 37:
        name = "or ";
        cout << name << "$" << rd << ", "
             << "$" << rs << ", "
             << "$" << rt << endl;
        break;
    case 38:
        name = "xor ";
        cout << name << "$" << rd << ", "
             << "$" << rs << ", "
             << "$" << rt << endl;
        break;

    default:
        break;
    }
}

void read_op(int ins)
{
    int op = (ins >> 26) & 63;
    if (op == 0)
    {
        R_Format_Build(ins, op);
    }
    else if (op == 2 || op == 3)
    {
        J_Format_Build(ins, op);
    }
    else
    {
        I_Format_Build(ins, op);
    }
}

void assembly2bin(string str)
{
    stringstream ssr(str);
    char inp;
    int ins = 0, op, rt, rs, imm;
    int func, shamt, rd;
    string name;
    ssr >> inp;
    if (inp == 'j')
    {
        string jump;
        ssr >> inp;
        if (inp >= 'A' && inp <= 'Z')
        {
            op = 2;
            op = op << 26;
            ssr >> jump;
            jump = inp + jump;
            for (auto &&i : jump)
                tolower(i);
            unsigned int x;
            std::stringstream ss;
            ss << std::hex << jump.c_str();
            ss >> x;
            ins += op + x;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else
        {
            op = 3;
            op = op << 26;
            ssr >> jump;
            jump = inp + jump;
            for (auto &&i : jump)
                tolower(i);
            unsigned int x;
            std::stringstream ss;
            ss << std::hex << jump.c_str();
            ss >> x;
            ins += op + x;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
    }
    else
    {
        while (inp != '$')
        {
            name.push_back(inp);
            ssr >> inp;
        }
        if (name == "addi")
        {
            op = 8;
            ssr >> rt;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> imm;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "andi")
        {
            op = 12;
            ssr >> rt;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> imm;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "ori")
        {
            op = 13;
            ssr >> rt;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> imm;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "lw")
        {
            op = 35;
            ssr >> rt;
            ssr >> inp;
            ssr >> imm;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "lb")
        {
            op = 32;
            ssr >> rt;
            ssr >> inp;
            ssr >> imm;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "sw")
        {
            op = 43;
            ssr >> rt;
            ssr >> inp;
            ssr >> imm;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "sb")
        {
            op = 40;
            ssr >> rt;
            ssr >> inp;
            ssr >> imm;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            op = op << 26;
            rs = rs << 21;
            rt = rt << 16;
            ins = op + rs + rt + imm;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "sll")
        {
            op = 0;
            func = 0;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            ssr >> inp;
            ssr >> shamt;
            rs = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "srl")
        {
            op = 0;
            func = 2;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            ssr >> inp;
            ssr >> shamt;
            rs = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "add")
        {
            op = 0;
            func = 32;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            shamt = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "sub")
        {
            op = 0;
            func = 34;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            shamt = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "or")
        {
            op = 0;
            func = 37;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            shamt = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
        else if (name == "xor")
        {
            op = 0;
            func = 38;
            ssr >> rd;
            ssr >> inp;
            ssr >> inp;
            ssr >> rs;
            ssr >> inp;
            ssr >> inp;
            ssr >> rt;
            shamt = 0;
            shamt = shamt << 6;
            rd = rd << 11;
            rt = rt << 16;
            rs = rs << 21;
            ins = op + rs + rt + rd + shamt + func;
            bitset<32> bits(ins);
            cout << bits << endl;
        }
    }
}

int main(int argc, char const *argv[])
{
    ifstream ifile(argv[1]);
    while (ifile.good())
    {
        string in, string;
        for (int i = 0; i < 4; i++)
        {
            ifile >> in;
            string += in;
            if (in.find('(') != -1)
            {
                i++;
            }
            if (in.find('j') != -1)
            {
                i += 2;
            }
        }
        if (string.size() != 8)
        {
            assembly2bin(string);
        }
        else
        {
            int ans = 0;
            for (int i = 0; i < string.size() - 1; i++)
            {
                ans += hex2int(string[i]);
                ans = ans << 4;
            }
            ans += hex2int(string[7]);
            read_op(ans);
        }
    }
}
