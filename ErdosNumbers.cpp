#include <iostream>
#include <stdio.h>
#include <sstream>
#include <string>
#include <map>
#include <queue>
#include <vector>

using namespace std;

string erdos = "Erdos, P.";
string inf = "infinity";

vector<int> row;
vector<string> names;

vector< vector<int> > adjacency_matrix;
map<string, int> occurance;

void get_input(int P) {
    
    int n = 1;
    string line;

    getline(cin, line);
    while (P--) {
        int len, i = 0;
        vector<int> list;

        getline(cin, line);
        len = line.length();

        while (i < len) {
            string name;
            if(line[i] == ':')
                break;
            while (line[i] == ' ' && i < len) 
                i++;
            while (line[i] != ',') 
                name += line[i++];
            name += line[i++];
            while (line[i] != ',' && line[i] != ':') 
                name += line[i++];
            names.push_back(name);
            if (!occurance[name]) {
                list.push_back(n);
                occurance[name] = ++n;
                adjacency_matrix.push_back(row);
            }
            list.push_back(occurance[name]-1);
            if (i >= len || line[i]==':') 
                break;
            i++;
        }
        int list_size = list.size();
        for(int i = 0; i < list_size-1; i++){
            for(int j = i+1; j < list_size; j++){
                adjacency_matrix[list[i]].push_back(list[j]);
                adjacency_matrix[list[j]].push_back(list[i]); 
            }
        }
    }
}

int main() {
    int test_cases, P, N;
    string name;

    cin>>test_cases;

    for(int i = 1; i <= test_cases; i++) {
        cin >> P >>N;
        names.clear(); 
        names.push_back(erdos);
        adjacency_matrix.clear(); 
        adjacency_matrix.push_back(row);
        occurance.clear(); 
        occurance[erdos] = 1;
        get_input(P);
        cout<<"Scenario "<<i<<endl;
        while (N--) {
            vector<int> erdos_value(names.size(), -2);
            queue<int> update_erdos; 
            int erdos_number = -2;
            int curent_name_value;
            bool found = false;

            getline(cin, name);

            curent_name_value = occurance[name] - 1;
            erdos_value[curent_name_value] = 0;
            update_erdos.push(curent_name_value);

            if (curent_name_value == -1)
                found = true;
            while (update_erdos.size() && !found) {

                curent_name_value = update_erdos.front(); 
                int row_size = adjacency_matrix[curent_name_value].size();
        
                update_erdos.pop();
                for (int i = 0; i < row_size; i++) {
                    int temp = adjacency_matrix[curent_name_value][i];
                    if (erdos_value[temp] != -2) 
                        continue;
                    erdos_value[temp] = erdos_value[curent_name_value] + 1;
                    if (temp != 0) 
                        update_erdos.push(temp);
                    else{
                        erdos_number = erdos_value[temp];
                        found = true;
                        break;
                    }
                }
            }
            if(erdos_number == -2)
                cout<<name<<" "<<inf<<endl;
            else
                cout<<name<<" "<<erdos_number<<endl; 
        }
    }
    return 0;
}
