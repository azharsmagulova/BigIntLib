#include "BigInt.h"
#include <string>

using namespace std;

// Checks if the string is a number or other invalid characters were used. 
// If the first char is '-' then check starting from 1st char
// Otherwise from the 0th
bool IsNumber(string num, int num_len) {

    bool answer;

    int i = -1; 

    i = (num[0] == '-') ? 1 : 0;

    for(i; i < num_len; i++) {
        if ((num[i] < '0') || (num[i] > '9'))
            answer = false;
        else                
            answer = true;
    }
    return answer; 
}



string Pos_to_Neg (string num, int num_len) {

    num.resize(num_len + 1);

    for (int i = num_len; i > 0; i--) 
        num[i] = num[i-1];

    num[0] = '-';
    return num;
}


string Neg_to_Pos (string num, int num_len) {

    for (int i = num_len - 1; i > 0; i--)
        num[i-1] = num[i];

    num.resize(num_len - 1);
    return num;
}



char getMaxMagnitude(string num_1, string num_2, int len_1, int len_2, bool sign_1, bool sign_2){

    char answer;

    if (!(sign_1 ^ sign_2)) {

        int difference = len_1 - len_2;

        if (difference == 0) {
            bool checker = 0;
            int i = 0;
            while (checker && i < len_1) {
                if (num_1[i] == num_2[i]) {
                    i++;
                }
                else if (num_1[i] > num_2[i]) {
                    checker = false;
                    answer = '1';
                }
                else if (num_2[i] > num_1[i]) {
                    checker = false;
                    answer = '2';
                }
            }
            
            if (checker) 
                answer = '0';
        }
        else 
            answer = (difference > 0) ? '1' : '2';
    }

    else if (sign_1 && !sign_2) {
        int difference = len_1 - (len_2 - 1);

        if (difference == 0) {
            bool checker = 0;
            int i = 0;
            while (checker && i < len_1) {
                if (num_1[i] == num_2[i+1]) {
                    i++;
                }
                else if (num_1[i] > num_2[i+1]) {
                    checker = false;
                    answer = '1';
                }
                else if (num_2[i] > num_1[i+1]) {
                    checker = false;
                    answer = '2';
                }
            }
            
            if (checker) 
                answer = '0';
        }
        else 
            answer = (difference > 0) ? '1' : '2';
    }

    else if (!sign_1 && sign_2) {
        int difference = (len_1 - 1) - len_2;

        if (difference == 0) {
            bool checker = 0;
            int i = 0;
            while (checker && i < len_2) {
                if (num_1[i+1] == num_2[i]) {
                    i++;
                }
                else if (num_1[i+1] > num_2[i]) {
                    checker = false;
                    answer = '1';
                }
                else if (num_2[i+1] > num_1[i]) {
                    checker = false;
                    answer = '2';
                }
            }
            
            if (checker) 
                answer = '0';
        }
        else 
            answer = (difference > 0) ? '1' : '2';

    }
    
}
string DeleteLeadZeroes(string num, int num_len) {
    int i = (num[0] == '-') ? 1 : 0;
    int j = i;
    bool checker = true;

    while (checker) {
        if (num[i] == '0') i++;
        else checker = false;
    }

    for (i; i < num_len; i++) {
        num[j] = num[i];
        j++; 
    }
    num.resize(j);
    return num;
}


// Helping function that performs addition between numbers of the same sign.
// Creates string "answer" that is 1 byte longer than biggest of the numbers.
// Sets ending index int at 0 if numbers are positive and 1 otherwise.
// answer[0] = NULL if both numbers are positive and '-' otherwise.

// i and j are set to c_len-1 and d_len-1; and because c >= d
// the loop goes from the end of each strings until j hits end_index first.
// Loop performs addition, keeps track of carryover, writes result in answer.
// Once j < 0, another loop continues the same until i hits end_index too.

// After finihshing, another for loop gets rid of any NULLs in answer.
string Addition(string c, string d, int c_len, int d_len, bool signs){
    
    string answer = "";
    answer.resize(c_len + 1); 

    int end_index = (signs == true) ? 0 : 1;
    answer[0] = (signs == true) ? 0 : '-';

    bool carryover = false;  
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


    for (i; i >= end_index; i--) {
        if (carryover && (c[i] == 9)) {
            carryover = true;
            answer[i+1] = '0';
        }
        else if (carryover) {
            carryover = false;
            answer[i+1] = c[i] + 1;
        }
        else {
            answer[i+1] = c[i];
        }    
    }


    for (int i = 0; i < answer.length(); i++) 
        if (!answer[i]) 
            answer[i] = answer[i+1];

    return answer;

}



string Subtraction(string c, string d, int c_len, int d_len) {
    string answer = c;

    bool carryover = false;  
    int i = c_len - 1;
    int j = d_len - 1;

    for (j; j >= 0; j--) {

        char temp = c[i] - d[j];

        if ((carryover == false) && (temp >= 0)) {
            answer[i] = temp + 48;
            carryover = false;
        }
        else if ((carryover == false) && (temp < 0)) {
            answer[i] = temp + 58;
            carryover = true;
        }
        else if ((carryover == true) && (temp >= 1)) {
            answer[i] = temp + 47;
            carryover = true;
        }
        else if ((carryover == true) && (temp < 1)) {
            answer[i] = temp + 57;
            carryover = false;
        }

        i--;
    }

    for (i; i >= 0; i--) {

        if (carryover && (c[i] == '0')){
            carryover = true;
            answer[i] = '9';
        }
        else if (carryover) {
            carryover = false;
            answer[i] = c[i] - 1;
        }
        else {   
            answer[i] = c[i];
        }
    }

    //insert check for if leading zero
    answer = DeleteLeadZeroes(answer, c_len);
    return answer;
}



// The addition function.
// Checks whether inputs are numbers and if so then proceeds.
// Checks whether inputs are negative.
// If both numbers' have the same sign, call Addition function.
// The number with the biggest absolute magnitude is passed first.
string BigIntCalc::Add(string a, string b){

    string answer;
    int a_len = a.length();
    int b_len = b.length();

    if (!IsNumber(a, a_len) || !IsNumber(b, b_len)) {
        answer = "Error: invalid symbols";
        return answer;
    }

    bool sign_a = (a[0] == '-') ? false : true;
    bool sign_b = (b[0] == '-') ? false : true; 

    char which_bigger = getMaxMagnitude(a, b, a_len, b_len, sign_a, sign_b);

    if(!(sign_a ^ sign_b)) {

        if (sign_a && sign_b) {
            if (which_bigger == '1' || which_bigger == '0') 
                answer = Addition(a, b, a_len, b_len, true);
            else if (which_bigger == '2')
                answer = Addition(b, a, b_len, a_len, true);
        }

        else if (!sign_a  && !sign_b) {
            if (which_bigger == '1' || which_bigger == '0') 
                answer = Addition(a, b, a_len, b_len, false);
            else if (which_bigger == '2')
                answer = Addition(b, a, b_len, a_len, false);
        }
    }

    else {
        if (which_bigger == '0') {
            answer = "0";
            return answer;
        }

        if (sign_a & !sign_b) {
            b = Neg_to_Pos(b, b_len);
            b_len = b_len - 1;

            if (which_bigger == '1') {
                answer = Subtraction(a, b, a_len, b_len);
            }
            else if (which_bigger == '2') {
                answer = Subtraction(b, a, b_len, a_len);
                answer = Pos_to_Neg(answer, answer.length());
            }
        }
        else if (!sign_a && sign_b) {  
            a = Neg_to_Pos(a, a_len);
            a_len = a_len - 1;

            if (which_bigger == '1') {
                answer = Subtraction(a, b, a_len, b_len);
                answer = Pos_to_Neg(answer, answer.length());
            }
            else if (which_bigger == '2') {
                answer = Subtraction(b, a, b_len, a_len);
            }
        }
    }

    return answer;
}


// The substraction function
// Checks whether inputs are numbers and if so then proceeds.
// Checks numbers' signs and if they are different 
// Changes second to match first and calls Addition function

string BigIntCalc::Subtract(string a, string b) {

    string answer;
    int a_len = a.length();
    int b_len = b.length();

    if (!IsNumber(a, a_len) || !IsNumber(b, b_len)) {
        answer = "Error: invalid symbols";
        return answer;
    }

    bool sign_a = (a[0] == '-') ? false : true;
    bool sign_b = (b[0] == '-') ? false : true; 

    if (sign_a ^ sign_b) {

        if (sign_a && !sign_b) {

            b = Neg_to_Pos(b, b_len);
            char which_bigger = getMaxMagnitude(a, b, a_len, b_len - 1, sign_a, sign_b);

            if (which_bigger == '1' || which_bigger == '0') 
                answer = Addition(a, b, a_len, b_len - 1, true);
            else if (which_bigger == '2')
                answer = Addition(b, a, b_len - 1, a_len, true);
        }

        else if (!sign_a && sign_b) {
            b = Pos_to_Neg(b, b_len);
            char which_bigger = getMaxMagnitude(a, b, a_len, b_len + 1, sign_a, sign_b);

            if (which_bigger == '1' || which_bigger == '0')
                answer = Addition(a, b, a_len, b_len + 1, false);
            else if (which_bigger == '2')
                answer = Addition(b, a, b_len + 1, a_len, false);
        }
    }

    else {

        char which_bigger = getMaxMagnitude(a, b, a_len, b_len, sign_a, sign_b);

        if (which_bigger == '0') {
            answer = "0";
            return answer;
        }

        if (sign_a && sign_b) {
            if (which_bigger == '1') {
                answer = Subtraction(a, b, a_len, b_len);
            }
            else if (which_bigger == '2') {
                answer = Subtraction(b, a, b_len, a_len);
                answer = Pos_to_Neg(answer, answer.length());
            }
        }

        else if (!sign_a && !sign_b) {

            a = Neg_to_Pos(a, a_len);
            b = Neg_to_Pos(b, b_len);
            a_len =- 1;
            b_len =- 1;

            if (which_bigger == '1') {
                answer = Subtraction(a, b, a_len, b_len);
                answer = Pos_to_Neg(answer, answer.length());
            }
            else if (which_bigger == '2') {
                answer = Subtraction(b, a, b_len, a_len);
            }
        }
    }

    return answer;
}



string BigIntCalc::Multiply(string a, string b){

}



string BigIntCalc::Divide(string a, string b){

}