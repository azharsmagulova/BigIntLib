#include "BigInt.h"
#include <string>

using namespace std;

string Calculation::Add(string a, string b){

    int size_a, size_b = 0;

    if (a[0] == 45) {
        int size_a = a.length() -2;
    }
    else size_a = a.size() - 1;

    if (b[0] == 45) {
        int size_b = b.length() -2;
    }
    else size_b = b.size() - 1;
}

string Calculation::Subtract(string a, string b){

}

string Calculation::Multiply(string a, string b){

}

string Calculation::Divide(string a, string b){

}