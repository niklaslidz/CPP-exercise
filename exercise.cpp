/*c++程序
 */
#include <iostream>//输入输出流
#include <math.h>
#include <string.h>
#include <vector>

//判断输入三个数哪个最大

#if 0
using namespace std;
int main()
{
	int a,b,c;
	cin >> a >> b >> c;
	int max = a > b ? (a>c?a:c):(b>c?b:c);

	cout << "max number is " << max <<'\n';
}
#endif


//输出金字塔

#if 0
using namespace std;
int main(){
	int rows;
	cout << "input rows:" <<std::endl;
	cin >> rows;
	for(int i = 1; i <= rows; i++)
	{
		for(int space = 1; space <= rows-1; space++)
		{
			cout << " ";
                }
		for(int k = 1; k <= 2*i-1; k++)
		{
			cout << "*";
		}
		
		cout << endl;
	}
	return 0;
}
#endif


//输入一个数,判断是否为质数
#if 0
using namespace std;
int main(){
	int n,flag;
	cout << "input a number:"<< endl;
	cin >> n;
	for (int m = 2; m <= sqrt(n); m++){
		if(n % m == 0){
			flag = 0;
		        break;
		}
		else{
			flag = 1;
		}
	}
	if(flag == 0)
		cout << n << " is not a 质数\n";
	else if (flag == 1)
		cout << n << " is a 质数\n";
	return 0;
}
#endif

#if 0
using namespace std;
int main(){
	vector<int> iv;
	iv.push_back(1);
	iv.push_back(2);
        iv.push_back(3);
	for (int i = 0; i != iv.size(); i++)
		cout << iv[i] << endl;

	vector<char> cv(5);
	cv[2] = 'A';
	cout << cv[0] << endl << cv[2] << endl;


}
#endif

//计算n的阶乘
#if 1
using namespace std;
int main(){
	int n, i{1},factorial{1};
	cout << "input a int number:";
	cin >> n;

	while(i <= n){
		factorial *= i;
		++i;
	}

	cout << n << "的阶乘是:" << factorial<<endl;
	return 0;
}

#endif 
