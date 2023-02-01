#include <iostream>
#include <vector>
#include <sstream>

using namespace std;

vector<string> get_candidates(int no_of_candidates){
    vector<string> candidates(no_of_candidates);
    for (int i = 0; i < no_of_candidates; i++)
        getline(cin, candidates[i]);
    return candidates;
}

vector<vector<int> > get_votes(int no_of_candidates){
    vector<vector<int> > votes;
    string temp;
    getline(cin, temp);
    while (temp != "")
    {
        stringstream temp_ss;
        temp_ss << temp;
        vector<int> temp_votes(no_of_candidates);
        
        for (int i = 0; i < no_of_candidates; i++)
        {
            temp_ss >> temp_votes[i];
            temp_votes[i]--;
        }
        votes.push_back(temp_votes);
        if (cin.eof())
            break;
        getline(cin, temp);
    }
    return votes;
}

void get_winner(int no_of_candidates){
    int total_votes, mx, mn;
    int winner = -1;
    bool changed = false;
    
    vector<bool> is_eliminated(no_of_candidates, false);
    vector<int> count(no_of_candidates, 0);
    cin.ignore();
    vector<string> candidates = get_candidates(no_of_candidates);
    vector<vector<int> > votes = get_votes(no_of_candidates);

    total_votes = votes.size();
    vector<int> candidate_rank(total_votes, 0);
    
    for (int i = 0; i < total_votes; i++)
        count[votes[i][0]]++;
    
    while (winner == -1)
    {
        mx = 0;
        mn = total_votes;
        for (int i = 0; i < total_votes; i++)
        {
            changed = false;
            while (is_eliminated[votes[i][candidate_rank[i]]])
            {
                candidate_rank[i]++;
                changed = true;
            }
            if (changed)
                count[votes[i][candidate_rank[i]]]++;
        }

        for (int i = 0; i < no_of_candidates; i++)
        {
            if (is_eliminated[i])
                continue;
            if (count[i] > mx)
                mx = count[i];
            if (count[i] < mn)
                mn = count[i];
        }
        
        if(mx > total_votes/2){
            for (int i = 0; i < no_of_candidates; i++)
                if (count[i] == mx && !is_eliminated[i]){       
                    cout << candidates[i] << endl;
                    break;
                }
            break;
        }
        if (mx == mn)
            winner = mx;  
        else
        {
            for (int i = 0; i < no_of_candidates; i++)
                if (count[i] == mn)
                    is_eliminated[i] = true;
        }
    }

    for (int i = 0; i < no_of_candidates; i++)
        if (count[i] == winner && !is_eliminated[i])         
            cout << candidates[i] << endl;
}


int main()
{
    int test_cases, no_of_candidates;
    cin >> test_cases;
   
    while (test_cases--)
    {
        cin >> no_of_candidates;
        get_winner(no_of_candidates);
        if(test_cases != 0)
            cout << endl;
    }

}
