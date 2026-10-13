#include<iostream>
#include<vector>

using namespace std;

int main(){

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    int k;
    long long max = 0;
    long long min = 0;
    cin >> n;
    cin >> k;
    vector<int> A(n);

    for(int i=0;i<n;i++){
        cin >> A[i];
        max += A[i];
        if(A[i] > min){
            min = A[i];
        }
    }

    long long m;
    while(min < max){
        m = min + (max-min)/2;
        int c_k = 1;
        long long count = A[0];
        for(int i=0; i<n-1; i++){
            if(count + A[i+1] <= m){
                count += A[i+1];
            }
            else{
                count = A[i+1];
                c_k++;
            }
        }
        if(c_k > k){
            min = m+1;
        }
        else{
            max = m;
        }

        if(min == max){
            break;
        }
    }

    if(min == max){
        cout << min << "\n";
    }

    return 0;
}