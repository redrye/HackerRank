
#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
#include <utility>
#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Neighbor;
typedef long long int _W64;

class disjointset {
public:
  disjointset(int &n) {
    size = n;
    rank = vector<int>(n, 1);
    arr = vector<int>(n, 0);
    createSet();
    setcount = n;
  }
 void createSet() {
    for (int i = 0; i < size; i++) {
      arr[i] = i;
    }
  }

  int find(int &a) {
    if (arr[a] != a) {
      return find(arr[a]);
    }
    return arr[a];
  }

  void join(Neighbor &a) {
    int arep = find(a.first);
    int brep = find(a.second);

    if (find(a.first) != find(a.second)) {
        if (rank[a.first] < rank[a.second]) {
            arr[brep] = arep;
            rank[arep] += rank[brep];
            rank[brep] = 0;
        } else {
            arr[arep] = brep;
            rank[brep] += rank[arep];
            rank[arep] = 0;
        }
    }
  }

  int getRank(int &a) { return rank[a]; }

private:
  int size;
  int setcount;
  vector<int> arr;
  vector<int> rank;
};

int main() {
  /* Enter your code here. Read input from STDIN. Print output to STDOUT */
  int n;
  cin >> n;

  disjointset ds(n);

  int numoflines = n - 1, a, b;
  Neighbor c;
  char ch;
  for (; numoflines; --numoflines) {
    cin >> a >> b >> ch;
    a--;
    b--;
    if (ch == 'b') {
      ds.join(c = make_pair(a, b));
    }
  }

  vector<long long int> vec;
  for (int i = 0; i < n; i++) {
    if (ds.getRank(i) > 1)
      vec.push_back((_W64)ds.getRank(i));
  }

  _W64 mod = 1000000007;
  _W64 result = 0;
  _W64 nCom3 = (((LT)n * (n - 1) * (n - 2)) / 6);
  _W64 binom2 = 0, binom3 = 0;

  for (auto &elem : vec) {
    binom3 = 0;
    binom2 = 0;

    if (elem > 2)
      binom3 += ((_W64)elem * (elem - 1) * (elem - 2)) / 6;

    binom2 = ((_W64)elem * (elem - 1)) / 2;
    result += (binom3 + binom2 * ((_W64)n - elem));
  }

  cout << (nCom3 - result) % mod << endl;

  return 0;
}
