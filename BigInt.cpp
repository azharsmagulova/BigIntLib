#include "BigInt.h"
#include <string>

using namespace std;


// Checks if the string is a number or other invalid characters were used. 
// If the first char is '-' then check starting from 1st char
// Otherwise from the 0th
bool IsNumber(string number, int size_n) {

    bool answer;

    int i = -1; 

    i = (number[0] == '-') ? 1 : 0;

    for(i; i < size_n; i++) {
        if ((number[i] < '0') || (number[i] > '9'))
            answer = false;
        else                
            answer = true;
    }
    return answer; 
}



// Helping function that performs addition between numbers of the same sign.
// Creates string "answer" that is 1 byte longer than biggest of the numbers.
// Sets ending index int at 0 if numbers are positive and 1 otherwise.
// answer[0] = NULL if both numbers are positive and '-' otherwise.

// i and j are set to c_len-1 and d_len-1, and because c >= d
// the loop goes from the end of each strings until j hits end_index first.
// Loop performs addition, keeps track of carryover, writes result in answer.
// Once j < 0, another loop continues until i hits end_index.

// After finihshing, for loop gets rid of any NULLs in final answer string.
string Add_Same_Sign(string c, string d, int c_len, int d_len, bool signs){
    
    string answer = "";
    answer.resize(c_len + 1); 

    int end_index = (signs == true) ? 0 : 1;
    answer[0] = (signs == true) ? 0 : '-';

    bool carryover = false; 
    int difference = c_len - d_len;  
    
    int i = c_len - 1;
    int j = d_len - 1;

    for (j; j >= end_index; j--) {

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

        i--;
    }

    if ( i >= end_index && carryover) {
        answer[i+1] += c[i] + 1;
        carryover = false;
        i--;
    }
    for (i; i >= end_index; i--) {
        answer[i+1] = c[i];
    }



    for (int i = 0; i < answer.length(); i++) 
        if (!answer[i]) 
            answer[i] = answer[i+1];

    return answer;

}

string Add_Diff_Sign(string a, string b) {

}

// The addition function.
// Checks whether inputs are numbers and if so then proceeds.
// Checks whether inputs are negative.
// If both numbers' have the same sign, call Add_Same_Sign function.
// The biggest magnitute of two numbers is passed first.
string BigIngCalc::Add(string a, string b){

    string answer;
    int a_len = a.length();
    int b_len = b.length();

    if (!IsNumber(a, a_len) || !IsNumber(b, b_len)) {
        answer = "Error: invalid symbols";
        return answer;
    }

    int aBigger = a_len - b_len;

    bool sign_a = (a[0] == '-') ? false : true;
    bool sign_b = (b[0] == '-') ? false : true; 

    if (sign_a && sign_b) {
        if (aBigger >= 0) 
            answer = Add_Same_Sign(a, b, a_len, b_len, true);
        else
            answer = Add_Same_Sign(b, a, b_len, a_len, true);
    }

    else if (!sign_a  && !sign_b) {
        if (aBigger >= 0) 
            answer = Add_Same_Sign(a, b, a_len, b_len, false);
        else
            answer = Add_Same_Sign(b, a, b_len, a_len, false);
    }
    return answer;
}

string BigIngCalc::Subtract(string a, string b){

}

string BigIngCalc::Multiply(string a, string b){

}

string BigIngCalc::Divide(string a, string b){

}