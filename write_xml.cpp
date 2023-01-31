#include <iostream>
#include <string.h>
#include <fstream> //filestream
#include <array>
#include <stdexcept>
#include <memory>
#include <cstdio>

using namespace std;

string exec(const char* cmd);

int main(){

    ofstream o;
    o.open("/var/www/html/qr_reader/message.xml");

    string dateTime = exec("date");

    dateTime = dateTime.substr(0, dateTime.size()-1);

    string itemInstanceId = "scanned id";
    string laneId = "some string";
    string zoneId = "some string";
    string scannerId = "some string";

    o << "<ItemIdentifierRead\n\tdateTime=\"" << dateTime << "\"" << endl;
    o << "\titemIstancedId=\"" << itemInstanceId << "\"" << endl;
    o << "\tlaneId=\"" << laneId << "\"" << endl;
    o << "\tzoneId=\"" << zoneId << "\"" << endl;
    o << "\tscannerId=\"" << scannerId << "\"" << endl;
    o << "/>" << endl;
    return 0;
}

    string exec(const char* cmd) {
    array<char, 128> buffer;
    string result;
    unique_ptr<FILE, decltype(&pclose)> pipe(popen(cmd, "r"), pclose);
    if (!pipe) {
        throw std::runtime_error("popen() failed!");
    }
    while (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result += buffer.data();
    }
    return result;
}