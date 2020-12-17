#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

void show_usage();
void add(string);
void ls();
void del(int);
void done(int);
void report();

int main(int argc, char* argv[])
{
    string arg1="",arg2="";
    if(argc>1) arg1=argv[1];
    if(argc>2) arg2=argv[2];
    if(argc==1 || arg1=="help") show_usage();
    // if(arg1=="add") add(arg2);
    // if(arg1=="ls") ls();
    // if(arg1=="del") del(stoi(arg2));
    // if(arg1=="done") done(stoi(arg2));
    // if(arg1=="report") report();
    return 0;
}

void show_usage(){
      cout<<"Usage :-"<<endl;
      cout<<"$ ./todo add \"todo item\"  # Add a new todo"<<endl;
      cout<<"$ ./todo ls               # Show remaining todos"<<endl;
      cout<<"$ ./todo del NUMBER       # Delete a todo"<<endl;
      cout<<"$ ./todo done NUMBER      # Complete a todo"<<endl;
      cout<<"$ ./todo help             # Show usage"<<endl;
      cout<<"$ ./todo report           # Statistics"<<endl;
}

void add(string s){

}
