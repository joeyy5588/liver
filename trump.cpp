#include "trump.h"
#include <fstream>
#include <iostream>

using namespace std;

int totalmoney=0;
int highscore=0;
int highdistance = 0;
int m1 =0;
int m2 =0;
int m3 =0;
int mis1 = 2000;
int mis2 = 100;
int mis3 = 100;
bool billionaire=false;
bool timemachine=false;
bool champion=false;
bool superman=false;
bool puzzle1=false;
bool puzzle2=false;
bool puzzle3=false;
bool puzzle4=false;
void savefile(){
    fstream file;
    file.open("temp.txt", ios::out);
    file<<totalmoney<<'\n'<<highscore<<'\n'<<highdistance<<'\n'<<m1<<'\n'<<m2<<'\n'<<m3<<'\n'<<mis1<<'\n'<<mis2<<'\n'<<mis3<<'\n'
    <<(int)billionaire<<'\n'<<(int)timemachine<<'\n'<<(int)champion<<'\n'<<(int)superman<<'\n'
    <<(int)puzzle1<<'\n'<<(int)puzzle2<<'\n'<<(int)puzzle3<<'\n'<<(int)puzzle4;
    file.close();
}
void loadfile(){
    fstream file2;
    file2.open("temp.txt", ios::in);
    int a;
    file2>>totalmoney>>highscore>>highdistance>>m1>>m2>>m3>>mis1>>mis2>>mis3>>
    billionaire>>timemachine>>champion>>superman>>puzzle1>>puzzle2>>puzzle3>>puzzle4;
    file2.close();
}
