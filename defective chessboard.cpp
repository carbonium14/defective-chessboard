#include<iostream>
#include<cstdio>
using namespace std;
int** m, ** ans, * a, k, now;
bool** b;
void solve(int sx, int sy, int x, int y, int size)    // �������̸���
{
	if (size & 1) return;
	int nowt = now++;
	int nowsize = size >> 1;
	// ���� 
	if (x < sx + nowsize && y < sy + nowsize) solve(sx, sy, x, y, size >> 1);
	else {
		m[sx + nowsize - 1][sy + nowsize - 1] = nowt;
		solve(sx, sy, sx + nowsize - 1, sy + nowsize - 1, size >> 1);
	}
	// ����  �� 
	if (x >= sx + nowsize && y < sy + nowsize) solve(sx + nowsize, sy, x, y, size >> 1);
	else {
		m[sx + nowsize][sy + nowsize - 1] = nowt;
		solve(sx + nowsize, sy, sx + nowsize, sy + nowsize - 1, size >> 1);
	}
	// ���� 
	if (x < sx + nowsize && y >= sy + nowsize) solve(sx, sy + nowsize, x, y, size >> 1);
	else {
		m[sx + nowsize - 1][sy + nowsize] = nowt;
		solve(sx, sy + nowsize, sx + nowsize - 1, sy + nowsize, size >> 1);
	}
	// ���� 
	if (x >= sx + nowsize && y >= sy + nowsize) solve(sx + nowsize, sy + nowsize, x, y, size >> 1);
	else {
		m[sx + nowsize][sy + nowsize] = nowt;
		solve(sx + nowsize, sy + nowsize, sx + nowsize, sy + nowsize, size >> 1);
	}
	return;
}
void work(int size)  // �������ǰ��Ž���Ⱦɫ
{
	//	int color[4] = {0,1,2,3};   ������ɫ�����õ���ɫ��һ�� < = 4
	int tot = (size * size - 1) / 3;
	bool vis[4];
	ans = new int* [tot];
	a = new int[tot];
	b = new bool* [tot];
	for (int i = 0; i < tot; i++) ans[i] = new int[tot], b[i] = new bool[tot], a[i] = -1;
	for (int i = 0; i < tot; i++)
		for (int j = 0; j < tot; j++)
			b[i][j] = false;
	// ��ͼ����Ϊ���ǰ� ��Ϊ�����ڵ����ǰ�ı�
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
		{
			int x = m[i][j];
			if (i >= 1 && !b[x][m[i - 1][j]])
			{
				b[x][m[i - 1][j]] = b[m[i - 1][j]][x] = true;
			}
			if (j >= 1 && !b[x][m[i][j - 1]])
			{
				b[x][m[i][j - 1]] = b[m[i][j - 1]][x] = true;
			}
		}
	for (int i = 0; i < tot; i++)
	{
		int x = 0;
		for (int k = 0; k < 4; k++) vis[k] = true;
		for (int j = 0; j < tot; j++)
			if (b[i][j] && i != j && a[j] !=-1) vis[a[j]] = false;
		for (int k = 0; k < 4; k++) {
			if (vis[k]) {
				x = k; break;
			}
		}
		a[i] = x;
	}
	return;
}
void print(int size)   // GUI����
{
	for (int i = 0; i < size; i ++)
	{	//������
		for (int j = 0; j < size; j++)
		{
			printf("%3d ",m[i][j]);
		}
		cout<<endl;
    }
	for (int i = 0; i < size; i ++)
	{	//������
		for (int j = 0; j < size; j++)
		{
			printf("%3d ",ans[i][j]);
		}
		cout<<endl;
	}
}
int main()
{
	int x, y;
	scanf("%d%d%d", &k, &x, &y);
	int size = 1 << k;
	m = new int* [size];
	for (int i = 0; i < size; i++)
		m[i] = new int[size];
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			m[i][j] = 0;
	solve(0, 0, x, y, size);
	work(size);
	for (int i = 0; i < size; i++)
		for (int j = 0; j < size; j++)
			ans[i][j] = a[m[i][j]];
	print(size);
	return 0;
}
