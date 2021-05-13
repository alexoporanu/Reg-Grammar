#include <iostream>
#include <fstream>
#include <unordered_map>
#include <vector>
#include <set>

using namespace std;

ifstream f("grammar.in");

string drum[10000];
int n;

unordered_map<string, vector<string>> p;
set<string> cuvinte;

string to_string(string x[], int k)
{
    string sol = "";

   for (int i = 0; i <= k; ++i)
        if (drum[i][0] != 'N' && drum[i][0] != '$')
            sol += drum[i][0];

    return sol;
}
int nrTerminale(int m)
{
    int cnt = 0;
    for (int i = 0; i <= m; ++i)
    {   if (drum[i][0] != 'N' )
            if (drum[i] != "$")
                cnt++;
    }

    return cnt;
}
bool valid (int k)
{   for (int i = 0; i < k; ++i)
        if (drum[i] == drum[k] && nrTerminale(k) == nrTerminale(i))
            return false;

    return true;
}

void Back(int k){
    if (drum[k - 1][0] == 'N' && nrTerminale(k - 1) <= n)
            for(int i = 0 ; i < p[drum[k - 1]].size() ; ++i)
            {

                drum[k] = p[drum[k - 1]][i];
                if(valid(k))
                        Back(k+1);

            }

    if (drum[k - 1].length() >= 3 && nrTerminale(k - 1) <= n)
            if (drum[k - 1][1] == 'N')
                for(int i = 0 ; i < p[drum[k - 1].substr(1,2)].size() ; ++i)
                {
                    drum[k] = p[drum[k - 1].substr(1,2)][i];
                    Back(k+1);
                }

    if (nrTerminale(k - 1) == n && drum[k - 1].find('N') == std::string::npos)
        {
            cuvinte.insert(to_string(drum, k - 1));
        }

}

int main()
{
    string a, b;

    while (f >> a >> b)
        p[a].push_back(b);

    cout << "Introduceti n: ";
    cin >> n;

    drum[0] = "NS";
    Back(1);

    if (!(cuvinte.empty())){
        cout << "Cuvintele de lungime " << n << " acceptate de gramatica sunt:\n";

        set<string> :: iterator itr;

        for (itr = cuvinte.begin(); itr != cuvinte.end(); itr++)
            cout << "   -" << (*itr) << "\n";
    }
    else{
        cout << "Gramatica nu accepta niciun cuvant de lungime " << n <<" !";
    }

    return 0;
}

