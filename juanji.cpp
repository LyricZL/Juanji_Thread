// juanji.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include<cstdlib>
#include<iostream>
#include<vector>
#include <windows.h>
using namespace std;
int const kernel = 3;
int const map = 8;
float A[map * map] =
{
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8,
1, 2, 3, 4, 5, 6, 7, 8
};

//定义卷积核矩阵（其实也是一个数组，数组元素的个数3*3）
float B[kernel * kernel] =

{
1, 1, 1,
1, 1, 1,
1, 1, 1
};

int const outm = map - kernel + 1; //被卷积矩阵的维数-卷积核的维数+1 即8-3+1=6
	//计算卷积过程中的被卷积矩阵的宽和高（就是把宽拉成和卷积核的高一样，这样才好对应相乘）
int const convAw = kernel * kernel;//3*3=9
int const convAh = map * map;//8*8=64
float A_convert[convAh * convAw] = { 0 };//定义一个卷积过程中的矩阵（也就是被拉长过后的矩阵）

DWORD WINAPI ThreadFunc1(LPVOID pParam)
{
	
	for (int i = 0; i < outm; i++)
	{
		for (int j = 0; j < outm; j++)
		{
			int wh = i * outm * convAw + j * convAw;
			int col1 = i * map + j;
			A_convert[wh] = A[col1]; //第一次循环时把A[0] 的值赋给 A_convert[0]
			A_convert[wh + 1] = A[col1 + 1];//第一次循环时把A[1] 的值赋给 A_convert[1]
			A_convert[wh + 2] = A[col1 + 2];//第一次循环时把A[2] 的值赋给 A_convert[2]
			int col2 = (i + 1) * map + j;
			A_convert[wh + 3] = A[col2]; //第一次循环时把A[8] 的值赋给 A_convert[3]
			A_convert[wh + 4] = A[col2 + 1];//第一次循环时把A[9] 的值赋给 A_convert[4]
			A_convert[wh + 5] = A[col2 + 2];//第一次循环时把A[10] 的值赋给 A_convert[5]
			int col3 = (i + 2) * map + j;
			A_convert[wh + 6] = A[col3]; //第一次循环时把A[16] 的值赋给 A_convert[6]
			A_convert[wh + 7] = A[col3 + 1]; //第一次循环时把A[17] 的值赋给 A_convert[7]
			A_convert[wh + 8] = A[col3 + 2]; //第一次循环时把A[18] 的值赋给 A_convert[8]
		}
	}
	return 0;
}

vector<int> C;
DWORD WINAPI ThreadFunc2(LPVOID pParam)
{
	
	for (int i = 0; i < outm; i++)
	{
		for (int j = 0; j < outm; j++)
		{
			int a = 0;
			int wh = i * outm * convAw + j * convAw;
			for (int m = 0; m < convAw; m++)
			{
				a += A_convert[wh + m] * B[m];
			}
			C.push_back(a); //在C中添加数据a
		}
	}
	return 0;
}

DWORD WINAPI ThreadFunc3(LPVOID pParam)
{
	cout << "被卷积矩阵 :" << endl;
	for (int i = 0; i < map; i++)
	{
		for (int j = 0; j < map; j++)
		{
			cout << A[i * map + j] << " ";
		}
		cout << endl;
	}

	cout << endl;
	//输出卷积核矩阵
	cout << "卷积核矩阵:" << endl;
	for (int i = 0; i < kernel; i++)
	{
		for (int j = 0; j < kernel; j++)
		{
			cout << B[i * kernel + j] << " ";
		}
		cout << endl;
	}
	cout << endl;
	//输出卷积后输出矩阵
	cout << "卷积后输出矩阵：" << endl;
	for (int i = 0; i < outm; i++)
	{
		for (int j = 0; j < outm; j++)
		{
			cout << C[i * outm + j] << " ";
		}
		cout << endl;
	}
	system("pause");
	return 0;
}

int main()
{
	HANDLE hthread1 = CreateThread(NULL, 0, ThreadFunc1, NULL, 0, NULL);
	Sleep(1000);
	HANDLE hthread2 = CreateThread(NULL, 0, ThreadFunc2, NULL, 0, NULL);
	Sleep(1000);
	HANDLE hthread3 = CreateThread(NULL, 0, ThreadFunc3, NULL, 0, NULL);
	Sleep(1000);
}
// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件
