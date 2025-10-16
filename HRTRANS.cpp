#include "HRTRANS.h"

Captain::Captain(){

}
Soldier::Soldier(){ 

}
Soldier::Soldier(int id){ 
    this->id = id;
}
string Captain::to_binary(int bits, string time){
    string res = "";
    int int_time = stoi(time);
    for(int i = 0; i < bits; i++){
        res = to_string(int_time % 2) + res;
        int_time /= 2;
    }
    return res;
}
string Captain::to_hamming(string s){
    int r; //find r
    for(int i = 0; i <= 100; i++){
        if(pow(2, i) - i - s.size() - 1 >= 0){
            r = i;
            break;
        }
    }
    int n = s.size() + int(r); //total of bit hamming
    int *pArr;
    pArr = new int[n + 1];
    for(int i = 0; pow(2, i) <= n; i++){
        int x = int(pow(2, i));
        if(x < n + 1){
            pArr[x] = -1;
        }
        else break;
    }
    int j = 0; // idx of s
    for (int i = 1; i <= n; i++) {
        if (pArr[i] != -1) { 
            pArr[i] = s[j] - '0';
            j++;
        }
    }
    for(int i = 0; i < r; i++){
        int pos = int(pow(2, i));
        int sum = 0;
        for(int j = 1; j <= n; j++){
            if(j & pos){
                if(j != pos){
                    sum += pArr[j];
                }
            }
        }
        pArr[pos] = sum % 2;
    }
     string result = "";
    for (int i = 1; i <= n; i++) {
        result += char(pArr[i] + '0');
    }

    delete[] pArr;
    return result;
}
string Captain::encode(string s){
    string hour = s.substr(0, 2);
    string minute = s.substr(3, 2);
    string second = s.substr(6, 2);
    string res = to_binary(5, hour) + to_binary(6, minute) + to_binary(6, second);
    return to_hamming(res);
}

string Soldier::to_decimal(string s){
    int result = 0;
    for(char ch : s){
        result = result * 2 + (ch == '1' ? 1 : 0);
    }
    return to_string(result);
}
string Soldier::to_binary(string s){
     int r = 0;
     int n = s.size();
    while (pow(2, r) <= n) r++;
    int *pArr = new int[s.size() + 1];
    int j = 0; // idx of s
    for (int i = 1; i <= n; i++) {
        pArr[i] = s[j] - '0';
        j++; 
    }
    int errorPos = 0;
    for (int i = 0; i < r; i++) {
        int pos = int(pow(2, i));
        int sum = 0;
        for (int j = 1; j <= n; j++) {
            if (j & pos) sum += pArr[j];
        }
        if (sum % 2 != 0)  // parity chẵn
            errorPos += pos;
    }
    if (errorPos != 0 && errorPos <= n) {
        pArr[errorPos] = 1 - pArr[errorPos];
    }
    string result = "";
    for (int i = 1; i <= n; i++) {
        bool isParity = false;
        for (int k = 0; k < r; k++) {
            if (i == int(pow(2, k))) {
                isParity = true;
                break;
            }
        }
        if (!isParity) result.push_back(char(pArr[i] + '0'));
    }

    delete[] pArr;
    return result;
}

string Soldier::decode(string s){
    string binary = to_binary(s);
    string hour = to_decimal(binary.substr(0, 5));
    string minute = to_decimal(binary.substr(5, 6));
    string second = to_decimal(binary.substr(11, 6));
    if(hour.size() != 2) hour = "0" + hour;
    if(minute.size() != 2) minute = "0" + minute;
    if(second.size() != 2)  second = "0" + second;
    return hour + ":" + minute + ":" + second;
}

