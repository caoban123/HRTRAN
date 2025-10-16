#include <bits/stdc++.h>
#include "HRTRANS.h"
using namespace std;

int main() {
    Captain cpt;
    Soldier sld;

    string time;
    cout << "Nhap thoi gian (dang HH:MM:SS): ";
    cin >> time;

    // B1: Captain mã hóa thời gian
    string encoded = cpt.encode(time);
    cout << "Ma Hamming sau khi ma hoa: " << encoded << endl;

    // (Tuỳ chọn) Giả lập lỗi trong dữ liệu truyền
    cout << "Ban co muon tao loi trong du lieu truyen? (y/n): ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y') {
        int pos;
        cout << "Nhap vi tri bit muon dao (1 -> " << encoded.size() << "): ";
        cin >> pos;
        if (pos >= 1 && pos <= encoded.size()) {
            encoded[pos - 1] = (encoded[pos - 1] == '0' ? '1' : '0');
            cout << "Du lieu bi loi: " << encoded << endl;
        }
    }

    // B2: Soldier nhận và giải mã
    string decoded = sld.decode(encoded);
    cout << "Thoi gian sau khi giai ma: " << decoded << endl;

    return 0;
}
