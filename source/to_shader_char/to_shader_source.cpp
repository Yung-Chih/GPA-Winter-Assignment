#include<iostream>
#include<string>
#include<fstream>
#include<vector>
#include<algorithm>
using namespace std;

vector<string> fs_line, vs_line;

int read_in(string, vector<string>&);
void output(string name, vector<string> data, int line);

int main(int argc, char* argv[] ){

    int vs_wid = read_in("vs_source.txt", vs_line);
    cout << vs_wid << endl;
    output("vs_source", vs_line, vs_wid );
    
    int fs_wid = read_in("fs_source.txt", fs_line);
    output("fs_source", fs_line, fs_wid );

    return 0;
}

int read_in(string name, vector<string>& data){
    ifstream fin(name);
    string line;
    int max_size = 0;
    data.clear();
    while( getline(fin, line) ){
        data.emplace_back(line);
        max_size = max( max_size, (int)line.size() );
    }
    return max_size;
}
void output(string name, vector<string> data, int width){
    ofstream fout(name);
    string space;

    fout << "static const char* " << name << "[] = {" << endl;
    for(string line : data ){
        space.clear();
        for(int i=0; i < width-line.size(); i++ ){
            space += " ";
        }

        fout << "\t\"" << line << space << "\t\\n\"" << endl;
    }
    fout << "};" << endl;
}