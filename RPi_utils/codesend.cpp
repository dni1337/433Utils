#include "../rc-switch/RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>
#include <fstream>
#include <unistd.h>

using namespace std;

int main(int argc, char *argv[]) {
        wiringPiSetup();
        int PIN = 0;
        RCSwitch mySwitch = RCSwitch();
        mySwitch.enableTransmit(PIN);
        string s, line;
        std::string code(argv[1]);
        ifstream file("codes.txt");
        while (getline(file, s)){
                std::size_t pos = s.find(code);
                if (pos!=std::string::npos){
                        line = s.substr(code.length()+1);
                        unsigned int arr[line.length()] = { 0 };
                        int j = 0, i;
                        string c = "";
                        for (i = 0; line[i] != '\0'; i++) {
                                if (line[i] == ',') {
                                        arr[j] = stoi(c);
                                        c = "";
                                        j++;
                                } else {
                                        c = c + line[i];
                                }
                        }
                        arr[j] = stoi(c);
                        printf("sending code[%s]\n", line.c_str());
                        mySwitch.send(arr);
                        usleep(500000);
                        mySwitch.send(arr);
                }
        }
        return 0;
}
