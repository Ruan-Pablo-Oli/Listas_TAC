#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    long long sum_A = 0;
    cin >> n;
    vector<int> A(n);

    for(int i=0;i<n;i++){
        cin >> A[i];
        sum_A += A[i];
    }
    sort(A.begin(), A.end());

    int m;
    long long sum_B = 0;
    cin >> m;
    vector<int> B(m);

    for(int i=0;i<m;i++){
        cin >> B[i];
        sum_B += B[i];
    }
    sort(B.begin(), B.end());

    if((sum_B-sum_A) % 2 != 0){
        cout << -1 << "\n";
        return 0;
    }

    long long d = (sum_B-sum_A)/2;

    bool find = false;
    int i = 0;
    int j = 0;
    while(i < n && j< m){
        long long diff = B[j]-A[i];

        if(diff == d){
            cout << A[i] << " " << B[j] << "\n";
            find = true;
            break;
        }
        else if (diff < d){
            j++;
        }
        else {
            i++;
        }
    }

    if(!find){
        cout << -1 << "\n";
    }


    return 0;
}

