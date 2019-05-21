#include <QCoreApplication>
#include <iostream>
#include <QTextStream>

using namespace std;

int main()
{
    QTextStream qtin(stdin);
    QTextStream qtout(stdout);

    // INIT
    bool *ok=NULL;

    int RGB_in1,RGB_in2,RGB_out;
    int or7b,and7b,RGB_sum,mask_satrtd,sum_satrtd;

    QString RGB1,RGB2,Yes_No;

    do
    {
        qtout << endl;

        Yes_No.clear();

        qtout << "Input hex RGB1: "<<endl;
        qtin >> RGB1;
        RGB_in1 = RGB1.toInt(ok,16);

        qtout << "Input hex RGB2: "<<endl;
        qtin >> RGB2;
        RGB_in2 = RGB2.toInt(ok,16);

// saturated sum
        or7b   = RGB_in1 | RGB_in2;
        or7b  &= 0x00808080;

        and7b  = RGB_in1 & RGB_in2;
        and7b &= 0x00808080;

        RGB_in1 &= 0x007f7f7f;
        RGB_in2 &= 0x007f7f7f;

        RGB_sum = RGB_in1 + RGB_in2;

        mask_satrtd   = RGB_sum & 0x00808080;
        mask_satrtd  &= or7b;
        mask_satrtd  |= and7b;
        mask_satrtd >>= 7;

        sum_satrtd    = mask_satrtd * 0xff;
        RGB_out       = sum_satrtd | RGB_sum | or7b;

// print
        qtout << "Output saturated sum RGB1 + RGB2: "
              << endl << hex << RGB_out <<endl;

        qtout << "Continue? (y/n): " << endl;
        qtin >> Yes_No;

    }while(Yes_No.at(0) == 'y');

    return 0;
}
