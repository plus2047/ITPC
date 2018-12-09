// POJ1001 Long Exponentiation
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void int_mul(vector<int> &a_r, int b){
    for(int i=0;i<(int)a_r.size();i++) a_r[i] *= b;
    for(int i=0;i<(int)a_r.size();i++) {
        if(a_r[i]>=10){
            if(i == (int) a_r.size() - 1) a_r.push_back(0);
            a_r[i+1] += a_r[i] / 10;
            a_r[i] %= 10;
        }
    }
}

int main(){
    string s; int n;
    while(cin >> s >> n){
        int point_count = 0, a = 0; vector<int> a_r;
        for(int i=0;i<(int)s.size();i++){
            if(s[i]!='.'){
                a_r.push_back(s[i]-'0');
                a *= 10;
                a += s[i] - '0';
            }
            else point_count = (int)s.size() - 1 - i;
        }
        if(a == 0){
            cout << '0' << endl;
            continue;
        }

        reverse(a_r.begin(), a_r.end());
        for(int i=1;i<n;i++) int_mul(a_r, a);
        point_count *= n;

        bool begin_output = false, begin_point = false;
        s = "";

        int f_zero = point_count - (int)a_r.size();
        if(f_zero > 0){
            cout << '.' << string((size_t)f_zero, '0');
            begin_point = true;
        }
        for(int i=(int)a_r.size()-1;i>=0;i--){
            if(i+1==point_count){
                cout << s; s = ".";
                begin_point = true;
            }
            if(a_r[i]!=0){
                cout << s << a_r[i]; s = "";
                begin_output = true;
            }
            else{
                s += '0';
            }
        }
        if(begin_output && !begin_point) cout << s;
        cout << endl;
    }
}
