#include <iostream>
#include <fstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

ifstream f("grammar.in");

string x[10000];
int n;

unordered_map<string, vector<string>> p;
unordered_set<string> cuvinte;

string to_string(string x[], int k)
{
    string sol = "";

   for (int i = 0; i <= k; ++i)
        if (x[i][0] != 'N' && x[i][0] != '$')
            sol += x[i][0];

    return sol;
}
int nrTerminale(int m)
{
    int cnt = 0;
    for (int i = 0; i <= m; ++i)
    {   if (x[i][0] != 'N' )
            if (x[i] != "$")
                cnt++;
    }

    return cnt;
}
bool valid (int k)
{   for (int i = 0; i < k; ++i)
        if (x[i] == x[k] && nrTerminale(k) == nrTerminale(i))
            return false;

    return true;
}

void afisTerminale(int m)
{   for (int i = 0; i <= m; ++i)
        if (x[i][0] != 'N' && x[i][0] != '$')
            cout << x[i][0];
        cout << "\n";
}

void af(int k)
{   cout << " ";
    for (int i = 0; i <=k; ++i)
        cout << x[i] << " ";
}
void Back(int k){
    if (x[k - 1][0] == 'N' && nrTerminale(k - 1) <= n)
            for(int i = 0 ; i < p[x[k - 1]].size() ; ++i)
            {

                x[k] = p[x[k - 1]][i];
                if(valid(k))
                        Back(k+1);

            }
        if (x[k - 1].length() >= 3 && nrTerminale(k - 1) <= n)
            if (x[k - 1][1] == 'N')
                for(int i = 0 ; i < p[x[k - 1].substr(1,2)].size() ; ++i)
                {
                    x[k] = p[x[k - 1].substr(1,2)][i];
                    Back(k+1);
                }

    if (nrTerminale(k - 1) == n && x[k - 1].find('N') == std::string::npos)
        {
            cuvinte.insert(to_string(x, k - 1));
        }

}

int main()
{
    string a, b;

    while (f >> a >> b)
        p[a].push_back(b);

    cout << "Introduceti n: ";
    cin >> n;


    x[0] = "NS";
    Back(1);

    cout << "Cuvintele de lungime " << n << " acceptate de gramatica sunt:\n";

    unordered_set<string> :: iterator itr;
    for (itr = cuvinte.begin(); itr != cuvinte.end(); itr++)
        cout << "\t" << (*itr) << "\n";

    return 0;
}

