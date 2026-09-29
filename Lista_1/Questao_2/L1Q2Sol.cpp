#include <iostream>
#include <queue>

using namespace std;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int alfabeto_r[26] = {0};
  int alfabeto_s[26] = {0};
  queue<char> s;
  int contador = 0;
  char c;
  bool flag = 1;

  while (cin.get(c) && !isspace(c)) {
    int pos = c - 'a';
    alfabeto_r[pos] += 1;
    contador++;
  }

  while (cin.get(c)) {
    if (isspace(c))
      continue;
    else {

      int pos = c - 'a';
      s.push(c);
      alfabeto_s[pos] += 1;

      if (s.size() > contador) {
        pos = s.front() - 'a';
        alfabeto_s[pos] -= 1;
        s.pop();
      }

      if (s.size() == contador) {
        for (int i = 0; i < 26; i++) {
          if (alfabeto_r[i] != alfabeto_s[i]) {
            flag = 0;
            break;
          } else {
            flag = 1;
          }
        }
        if (flag) {
          cout << "Sim\n";
          return 0;
        }
      }
    }
  }

  cout << "Nao\n";
  return 0;

  /*for(int i=0; i<26; i++){
      if(alfabeto_r[i] != alfabeto_s[i]) {flag=0; break;}
      else{
          flag=1;
      }
  }
  if(flag){
      cout << "Sim\n";
      return 0;
  }

  while(cin.get(c) && !isspace(c)){
      int pos = s.front() - 'a';
      alfabeto_s[pos] -= 1;
      pos = c - 'a';
      alfabeto_s[pos] += 1;
      s.pop();
      s.push(c);


      for(int i=0; i<26; i++){
          if(alfabeto_r[i] != alfabeto_s[i]) {flag=0; break;}
          else{
              flag=1;
          }
      }
      if(flag){
          cout << "Sim\n";
          return 0;
      }

  }*/

  /*

  //bool flag = 1;

      //string r, s;
      //cin >> r >> s;

      //int array[26] = {0};
      //int copia[26];

      for(char c : r){
          int pos = c - 'a';

          array[pos] += 1;

      }

      for(int i = 0; i<s.length(); i++){
          int pos = s[i] - 'a';

          std::copy(array, array + 26, copia);
          if(copia[pos] >= 1){
              flag = 1;

              for(int j = i; j<s.length(); j++){
                  int pos = s[j] - 'a';

                  if(copia[pos] >= 1){
                      copia[pos]--;
                  }else {
                      for(int i=0; i<26; i++){
                          if(copia[i]>0){
                              flag = 0;
                              break;
                          }
                      }
                      if(flag) {
                          cout << "Sim\n";
                          return 0;
                      }
                  }

                  if(!flag) break;
                  if(j==s.length() && flag){
                      cout << "Sim\n";
                      return 0;
                  }

              }
          }
      }


      cout << "Nao\n";
      return 0;
  */
}
