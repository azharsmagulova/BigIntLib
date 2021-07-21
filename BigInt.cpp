#include "BigInt.h"
#include <string>

using namespace std;


//Checks if the string is a number or other invalid characters were used. 
bool IsNumber(string number, int size_n) {

    bool answer;
    int i = -1; 

    i = (number[0] == 45) ? 1 : 0;

    for(i; i < size_n; i++) {
        if ((number[i] < 48) || (number[i] > 57))
            answer = false;
        else                
            answer = true;
    }
    return answer; 
}


string Add_Same_Sign(string c, string d, int size_c, int size_d, bool signs){
    
    //create a string one byte larger than the 
    string answer = "";
    answer.resize(size_c + 1); 

    int end_index = (signs == true) ? 0 : 1;
    bool carryover = false; 
    int difference = size_c - size_d;  
 
    for (int i = size_c; i > end_index - 1; i--) {
         
        int j = i - difference;

        while ( j>= 0) {

            char temp = c[i] + d[j];

            if ((carryover == false) && (temp >= 106)) {
                answer[i+1] = temp - 58;
                carryover = true;
            }
            else if ((carryover == false) && (temp < 106)) {
                answer[i+1] = temp - 48;
                carryover = false;
            }
            else if ((carryover == true) && (temp >= 106)) {
                answer[i+1] = temp - 57;
                carryover = true;
            }
            else if ((carryover == true) && (temp < 106)) {
                answer[i+1] = temp - 47;
                carryover = false;
            }
        }

        if (carryover = true) {
            answer[i+1] += c[i] + 1;
            carryover = false;
            continue;
        }
        answer[i+1] = c[i];
    }
    
    answer[0] = (signs == true) ? 0 : 45;

    for (int i = 0; i < answer.length(); i++) 
        if (!answer[i]) 
            answer[i] = answer[i+1];

    return answer;

}

string Add_Diff_Sign(string a, string b) {

}

string Calculation::Add(string a, string b){

    string answer;
    int end_a = a.length() - 1;
    int end_b = b.length() - 1;
    int ifBigger = end_a - end_b;

    if ((IsNumber(a, end_a) == false) || (IsNumber(b, end_b) == false)) {
        answer = "Error: invalid symbols";
        return answer;
    }

    bool sign_a = (a[0] == 45) ? false : true;
    bool sign_b = (b[0] == 45) ? false : true; 

    if ((sign_a == true) && (sign_b == true)) {
        if (ifBigger >= 0) 
            answer = Add_Same_Sign(a, b, end_a, end_b, true);
        else
            answer = Add_Same_Sign(b, a, end_b, end_a, true);
    }

    else if ((sign_a == false) && (sign_b == false)) {
        if (ifBigger >= 0) 
            answer = Add_Same_Sign(a, b, end_a, end_b, false);
        else
            answer = Add_Same_Sign(b, a, end_b, end_a, false);
    }
    return answer;
}

string Calculation::Subtract(string a, string b){

}

string Calculation::Multiply(string a, string b){

}

string Calculation::Divide(string a, string b){

}