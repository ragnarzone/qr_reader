#include <iostream>
#include <string.h>

using namespace std;

int main(){

    string dateTime = "2000-02-02T10:53:12.+01:00";

    cout << "<ItemIdentifierRead\n\tdateTime=\"" << dateTime << "\"" << endl;
    return 0;
}