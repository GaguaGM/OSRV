//============================================================================
// Name        : lab.cpp
// Author      :
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================
#include <iostream>
#include <pthread.h>

using namespace std;

struct data{

	int zero;
	int a;
	int b;
	int c;
	int N;
};


class LKG
{
public:
	LKG(data par) : tid(0), param(par){}
	~LKG(){}

private:

	static void* calc(void *temp)
	{
		LKG* cur = (LKG*) temp;
		return cur->calculation(cur);
	}

	void* calculation(LKG* cur)
        {
		data curPar = cur->getParam();
                int *rez = new int [curPar.N];
                rez[0] = curPar.zero;
                for (int i = 1; i < curPar.N; i++)
                {
                        rez[i] = (curPar.a*curPar.zero + curPar.b) % curPar.c;
                	curPar.zero = rez[i];
		}

                return rez;
        };

public:
	int* start_thread()
	{
		void *per;
		int *sum;
		pthread_create(&tid, NULL, calc, this);
		int buf;
		buf = pthread_join(tid, &per);

		cout << "potok vernulsya: " << buf << endl;

		sum = (int*)per;

		return sum;
	};

	data getParam()
	{
		return param;
	}



private:
	pthread_t tid;
	data param;

};


int main()
{
	cout << "enter zero, a, b, c, N" << endl;

	data dt;

	dt.zero = 7;
	dt.a = 7;
	dt.b = 7;
	dt.c = 10;
	dt.N = 15;


	LKG lkg(dt);
	int* res = lkg.start_thread();

	for(int i=0; i<dt.N; i++)
		cout << res[i] << " ";
	cout << endl;
	return 0;
}
