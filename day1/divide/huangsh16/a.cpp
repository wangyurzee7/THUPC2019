#include <iostream>
using namespace std;

int n;
int main() {
	freopen("1.in", "r", stdin);
	while(cin >> n) 
		cout << (1 + n * (n - 1) / 2 + n * (n - 1) * (n - 2) * (n - 3) / 24) << endl;
	return 0;
}