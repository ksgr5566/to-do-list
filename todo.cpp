#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>
using namespace std;

void show_usage();
void add(string,string);
void ls(string);
void del(int,string);
void done(int,string);
void report(string);

int main(int argc, char* argv[])
{
    string arg1="",arg2="";
    if(argc>1) arg1=argv[1];
    if(argc>2) arg2=argv[2];
    if(argc==1 || arg1=="help") show_usage();
    if(arg1=="add") add(arg2,argv[0]);
    if(arg1=="ls") ls(argv[0]);
    if(arg1=="del") del(stoi(arg2),argv[0]);
    if(arg1=="done") done(stoi(arg2),argv[0]);
    if(arg1=="report") report(argv[0]);
    return 0;
}

void report(string cwd){
    string directory = cwd;
    directory.erase(directory.find_last_of('\\')+1);
    string file1= directory+"todo.txt";
    string file2= directory+"done.txt";
    fstream todo,done;
    todo.open(directory+"todo.txt",ios::in);
    int i=0,j=0;
    string line;
    if(todo.is_open()) while(getline(todo,line)) ++i;
    todo.close();
    string line2;
    done.open(directory+"done.txt",ios::in);
    if(done.is_open()) while(getline(done,line2)) ++j;
    const int MAXLEN = 80;
    char s[MAXLEN];
    time_t t = time(0);
    strftime(s, MAXLEN, "%d/%m/%Y", localtime(&t));
    cout << s << " Pending . " << i << " Completed . " << j << endl;
}

void del(int i,string cwd){
    string directory = cwd;
    directory.erase(directory.find_last_of('\\')+1);
    string file1= directory+"todo.txt";
    string file2= directory+"temp.txt";
    ifstream is(file1);
    ofstream temp_file;
    temp_file.open(file2, ofstream::out);
    char c;
    if(i!=1){
        int line_no = 1;
        while (is.get(c)){
            if (c == '\n') line_no++;
            if (line_no != i) temp_file << c;
        }
    }else{
         while (is.get(c)) if(c=='\n') break;
         while (is.get(c)) temp_file << c;
    }
    temp_file.close();
    is.close();
    remove((file1).c_str()); 
    rename((file2).c_str(), (file1).c_str());
    cout << "Deleted todo #" << i << endl;
}

void ls(string cwd){
    string directory = cwd;
    directory.erase(directory.find_last_of('\\')+1);
    fstream list;
    list.open(directory+"todo.txt",ios::in);
    vector<string> lines;
    string line;
    while (std::getline(list, line))
        lines.push_back(line);
    list.close();
    for(int i=lines.size()-1;i>=0;i--){
        cout << "["<< i+1 << "] " << lines[i] << endl;
    }
}

void done(int i,string cwd){
    string directory = cwd;
    directory.erase(directory.find_last_of('\\')+1);
    string file1= directory+"todo.txt";
    string file2= directory+"temp.txt";
    ifstream is(directory+"todo.txt");
    ofstream temp_file;
    temp_file.open(directory+"temp.txt", ofstream::out);
    fstream done;
    done.open(directory+"done.txt",ios::in | ios::app );
    char c;
    if(i!=1){
        int line_no = 1;
        while (is.get(c)){
            if (c == '\n') line_no++;
            if (line_no != i) temp_file << c;
            else done << c;
        }
    }else{
         done << '\n';
         while (is.get(c)){
             if(c=='\n') break;
             done << c;
         }
         while (is.get(c)) temp_file << c;
    }
    done.close();
    temp_file.close();
    is.close();
    remove((file1).c_str()); 
    rename((file2).c_str(), (file1).c_str());
    cout << "Marked todo #" << i << " as done." << endl;
}

void add(string s,string cwd){
    string directory = cwd;
    directory.erase(directory.find_last_of('\\')+1);
    fstream todo;
    todo.open(directory+"todo.txt",ios::in | ios::app );
    int lines= 0;
    string line;
    if(todo.is_open()) while(getline(todo,line)) ++lines;
    todo.close();
    todo.open(directory+"todo.txt",ios::in | ios::app );
    if(lines==0) todo << s;
    else todo << "\n" << s;
    cout << "Added todo: \"" << s << "\"" << endl;
    todo.close();
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
