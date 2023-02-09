#include <iostream>
#include <string.h>
#include <fstream>

using namespace std;

string generateRandomString(int length){
    static string charset = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890";
    string result;
    result.resize(length);

    srand(time(NULL));
    for (int i = 0; i < length; i++)
        result[i] = charset[rand() % charset.length()];

    return result;
}

int main(){
    ofstream out("/var/www/html/qr_reader/tested_code/out.txt");

    string result = generateRandomString(5);
    out << result;
    out.close();
    return 0;
}