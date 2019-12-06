#include <iostream>
#include <ctime>
#include <random>
using namespace std;

typedef unsigned int uint;


struct c_mt {
	int w = 32;
	int n = 634;
	int m = 397;
	int r = 31;
	unsigned a = 0x9908B0DF;
	int u = 11;
	unsigned d = 4294967295;
	int s = 7;
	unsigned b = 0x9D2C5680;
	int t = 15;
	unsigned c = 0xEFC60000;
	int l = 18;
	unsigned f = 1812433253;
};

struct mani_bits {
	unsigned x;
	unsigned xA;
};

c_mt cmt;
mani_bits mb;

class mt{
public:

	unsigned mt_s(int seed){
		init_generator(seed);
		temp_preob();
		return y;
	}

	~mt(){
		delete(MT);
	}
	void twist() {
		for (int i = 0; i < cmt.n - 1; i++) {
			mb.x = (MT[i] & u_mask) + (MT[(i + 1) % cmt.n] & l_mask);
			mb.xA = mb.x >> 1;
			if ((mb.x % 2) != 0) {
				mb.xA = mb.xA ^ cmt.a;
			}
			MT[i] = MT[(i + cmt.m) % cmt.n] ^ mb.xA;
		}
		index = 0;
	}
	void init_generator(int seed) {
		int index = cmt.n;
		MT[0] = seed;
		for (int i = 1; i <= cmt.n - 1; i++) {
			MT[i] = cmt.f * (MT[i - 1] ^ (MT[i-1] >> (cmt.w-2))) + i;
			/*cout <<"mt = "<< MT[i] << endl;*/
		}

	}
	int temp_preob() {
			if (index >= cmt.n) {
				if (index > cmt.n) {
					cout << "problem init generator(seed)" << endl;
				}
				twist();
			}
			y = MT[index];
			y = y ^ ((y >> cmt.u) & cmt.d);
			y = y ^ ((y << cmt.s) & cmt.b);
			y = y ^ ((y >> cmt.t) & cmt.c);
			y = y ^ (y >> cmt.l);

			/*cout << "y = " << y << endl;
			cout << "mbx = " << mb.x << endl;
			cout << "cmt.w = " << cmt.w << endl;
			cout << "mt = " << MT[index] << endl;*/
			index += 1;

			return y;
	}

private:
	unsigned *MT = new unsigned[cmt.n];
	int index = cmt.n;
	const int l_mask = (1 << cmt.r) - 1;
	const int u_mask = cmt.w;
	unsigned y;

};