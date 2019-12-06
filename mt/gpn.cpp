#include "mt.h"

int main(int argc, char* argv[]) {
	mt mers;
	mt19937 mt_r(20);
	for (int i = 0; i < 10; i++) {
		cout <<"my " << mers.mt_s(20) << endl;
		cout << "mtorig " << mt_r() << endl;
	}
	system("pause");
	return 0;
}