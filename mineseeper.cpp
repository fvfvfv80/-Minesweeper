#include<iostream>
#include<vector>
#include<ctime>
#include<Windows.h>
#include<iomanip>
#include<cstdlib>
#include<conio.h>



using namespace std;
struct sTile
{
	bool isMine;
	int mineAround;
	bool isCheck;
	bool isCursor;
	bool isFlag;
	bool isLook;
};

void Spread(vector<vector<sTile*>> *vtile, int x, int y, int max, bool isfirst);
void CheckMine(vector<vector<sTile*>> *vtile, int max);
void Rendering(vector<vector<sTile*>> *vtile, int max,int mine,int flag);


void testfunc(int i, bool first)
{
	cout << "시작" << endl;
	if (i == 100)return;
	else if (first)
	{
		cout << i << endl;
		Sleep(250);
		return testfunc(i + 1, true);
	}
	cout << "2번째" << i << endl;
	Sleep(250);
	//if (i == 1)return;
	//else
	//{
	//	cout << "2번째"<<i << endl;
	//	Sleep(50);
	//	testfunc(i-1,false);
	//	cout << "3번째?"<<i << endl;
	//	Sleep(250);
	//}
}

void main()
{
	srand(time(NULL));
	int maxTile;
	int maxMine;
	int cursorX = 0;
	int cursorY = 0;
	int flagNum = 0;
	int answer = 0;
	clock_t begin, end;
	vector<vector<sTile*>> vvTile;




	while (1)
	{
		cout << "몇 곱하기 몇?: ";
		cin >> maxTile;
		if (!cin)
		{
			cin.clear();
			while (cin.get() != '\n');
			cout << "숫자만 입력해주세요." << endl;
		}
		else
		{
			if (maxTile > 30 || 0 > maxTile)
			{
				cout << "다시입력해주세요" << endl;
			}
			else break;
		}
	}

	while (1)
	{
		cout << "지뢰 개수: ";
		cin >> maxMine;
		if (!cin)
		{
			cin.clear();
			while (cin.get() != '\n');

			cout << "숫자만 입력해주세요." << endl;
		}
		else
		{
			if (maxMine > maxTile*maxTile || 0 > maxMine)
			{
				cout << "다시입력해주세요" << endl;
			}
			else break;
		}
	}
#pragma region Init
	for (int i = 0;i < maxTile;i++)
	{
		vector<sTile*> vtile;
		for (int j = 0;j < maxTile;j++)
		{

			sTile *tile = new sTile;
			(*tile).isCheck = false;
			(*tile).isMine = false;
			(*tile).mineAround = 0;
			(*tile).isCursor = false;
			(*tile).isFlag = false;
			(*tile).isLook = false;
			vtile.push_back(tile);
		}
		vvTile.push_back(vtile);
		//vector<sTile*>::iterator it = vtile.begin();
		//delete(&it);
		//it = vtile.erase(it);
	}
	for (int i = 0;i < maxMine;)
	{
		int garo = rand() % maxTile;
		int sero = rand() % maxTile;
		if (!vvTile[garo][sero]->isMine)
		{
			vvTile[garo][sero]->isMine = true;
			vvTile[garo][sero]->mineAround = -1;
			i++;
		}
	}
	CheckMine((&vvTile), maxTile);
	vvTile[cursorX][cursorY]->isCursor = true;
	system("cls");
	Rendering(&vvTile, maxTile,maxMine,flagNum);
	begin = clock();
#pragma endregion
#pragma region Update

	int key;
	while (answer!=maxMine)
	{
		key = _getch();
		vvTile[cursorY][cursorX]->isCursor = false;
		if (key == 75&& cursorX>0)cursorX--;
		else if (key == 77&& cursorX<maxTile-1)cursorX++;
		else if (key == 72 && cursorY > 0)cursorY--;
		else if (key == 80 && cursorY < maxTile-1)cursorY++;
		else if (key == 13)
		{
			if (!vvTile[cursorY][cursorX]->isCheck&&!vvTile[cursorY][cursorX]->isFlag)vvTile[cursorY][cursorX]->isCheck = true;
			if (vvTile[cursorY][cursorX]->isMine)break;
			else if (vvTile[cursorY][cursorX]->mineAround == 0 && !vvTile[cursorY][cursorX]->isFlag)Spread(&vvTile, cursorX, cursorY, maxTile, true);
		}
		else if (key == 115)
		{
			int xMask[] = { -1,0,1,-1,0,1,-1,0,1 };
			int yMask[] = { -1,-1,-1,0,0,0,1,1,1 };
			for (int i = 0;i < 9;i++)
			{
				if (cursorY + yMask[i] < 0 || cursorY + yMask[i] >= maxMine)continue;
				if (cursorX + xMask[i] < 0 || cursorX + xMask[i] >= maxMine)continue;
				if (!vvTile[cursorY + yMask[i]][cursorX + xMask[i]]->isCheck)
				{
					vvTile[cursorY + yMask[i]][cursorX + xMask[i]]->isLook = true;
				}
			}
						/*if(!vvTile[cursorY][cursorX]->isCheck)vvTile[cursorY][cursorX]->isLook = true;
						if (cursorX == 0 && cursorY == 0)
						{

							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX + 1]->isCheck)vvTile[cursorY+1][cursorX+1]->isLook = true;
						}
						else if (cursorX == maxTile - 1 && cursorY == 0)
						{
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX - 1]->isCheck)vvTile[cursorY+1][cursorX-1]->isLook = true;
						}
						else if (cursorX == 0 && cursorY == maxTile - 1)
						{
							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX + 1]->isCheck)vvTile[cursorY-1][cursorX+1]->isLook = true;
						}
						else if (cursorX == maxTile - 1 && cursorY == maxTile - 1)
						{
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX - 1]->isCheck)vvTile[cursorY-1][cursorX-1]->isLook = true;
						}
						else if (cursorY == 0)
						{
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX - 1]->isCheck)vvTile[cursorY+1][cursorX-1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX + 1]->isCheck)vvTile[cursorY+1][cursorX+1]->isLook = true;
						}
						else if (cursorY == maxTile - 1)
						{
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX - 1]->isCheck)vvTile[cursorY-1][cursorX-1]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX + 1]->isCheck)vvTile[cursorY-1][cursorX+1]->isLook = true;
						}
						else if (cursorX == 0)
						{
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX + 1]->isCheck)vvTile[cursorY-1][cursorX+1]->isLook = true;
							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX + 1]->isCheck)vvTile[cursorY+1][cursorX+1]->isLook = true;
						}
						else if (cursorX == maxTile - 1)
						{
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX - 1]->isCheck)vvTile[cursorY-1][cursorX-1]->isLook = true;
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX - 1]->isCheck)vvTile[cursorY+1][cursorX-1]->isLook = true;
						}
						else
						{
							if (!vvTile[cursorY - 1][cursorX - 1]->isCheck)vvTile[cursorY-1][cursorX-1]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX]->isCheck)vvTile[cursorY-1][cursorX]->isLook = true;
							if (!vvTile[cursorY - 1][cursorX + 1]->isCheck)vvTile[cursorY-1][cursorX+1]->isLook = true;
							if (!vvTile[cursorY][cursorX - 1]->isCheck)vvTile[cursorY][cursorX-1]->isLook = true;
							if (!vvTile[cursorY][cursorX]->isCheck)vvTile[cursorY][cursorX]->isLook = true;
							if (!vvTile[cursorY][cursorX + 1]->isCheck)vvTile[cursorY][cursorX+1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX - 1]->isCheck)vvTile[cursorY+1][cursorX-1]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX]->isCheck)vvTile[cursorY+1][cursorX]->isLook = true;
							if (!vvTile[cursorY + 1][cursorX + 1]->isCheck)vvTile[cursorY+1][cursorX+1]->isLook = true;
						}*/
				system("cls");
				Rendering(&vvTile, maxTile, maxMine, flagNum);
				Sleep(50);	
		}
		else if (key == 97)
		{
			if (!vvTile[cursorY][cursorX]->isCheck&&flagNum < maxMine)
			{
				vvTile[cursorY][cursorX]->isFlag = (vvTile[cursorY][cursorX]->isFlag + 1) % 2;
				vvTile[cursorY][cursorX]->isFlag ? flagNum++ : flagNum--;
				if (vvTile[cursorY][cursorX]->isFlag&&vvTile[cursorY][cursorX]->isMine)answer++;
				else if (answer > 0&&vvTile[cursorY][cursorX]->isMine)answer--;
			}
		}
		else
		{
			cout << "다시" << endl;
			continue;
		}
		for (int i = 0;i < maxTile;i++)
		{
			for (int j = 0;j < maxTile;j++)
			{
				if (vvTile[i][j]->isLook)vvTile[i][j]->isLook = false;
			}
		}	
		vvTile[cursorY][cursorX]->isCursor = true;
		system("cls");
		Rendering(&vvTile, maxTile, maxMine, flagNum);
		vvTile[cursorY][cursorX]->isLook = false;
		cout << answer << endl;
	}
#pragma endregion


#pragma region End
	cout << endl;
	system("cls");
	for (int i = 0;i < maxTile;i++)
	{
		for (int j = 0;j < maxTile;j++)
		{
			if (vvTile[i][j]->isMine)cout << setw(4) << "◎";
			else if (vvTile[i][j]->isCheck)
			{
				if (vvTile[i][j]->mineAround == 0)cout << setw(4) << " ";
				else cout << setw(4) << vvTile[i][j]->mineAround;
			}
			else cout << setw(4)<<"■";
		}
		cout << endl << endl;
	}
	end = clock();
	cout <<"\t\t\t"<<setw(10)<< (end - begin)/CLOCKS_PER_SEC<<"."<<(end - begin)%CLOCKS_PER_SEC<<"초"<< endl;
	cout << "끝!!" << endl;

	/*
	vector 메모리 10이었던거에서 하나더 입력하면 11이되는게 아니라 20이 된다
	clear하면 데이터는 사라지지만 메모리는 20으로 계속 남음
	swap을 사용해서 빈 벡터를 넣어주면 메모리 청소도 됨
	*/


	//백터도 초기화
	for (int i = 0;i < vvTile.size();i++)
	{
		for (int j = 0;j < vvTile[i].size();j++)
		{
			sTile *temp = vvTile[i][j];
			delete temp;
		}
	}
	

	/*vector<vector<sTile*>> temp;
	vvTile.clear();
	vvTile.swap(temp);*/
#pragma endregion
}



void CheckMine(vector<vector<sTile*>> *vtile, int max)
{
	int xMask[] = { -1,0,1,-1,1,-1,0,1 };
	int yMask[] = { -1,-1,-1,0,0,1,1,1 };
	for (int i = 0;i < max;i++)
	{
		for (int j = 0;j < max;j++)
		{
			int minenum = 0;
			if ((*vtile)[i][j]->isMine)continue;
			for (int k = 0;k < 8;k++)
			{	
				if (i + yMask[k] < 0|| i + yMask[k] >= max)continue;
				if (j + xMask[k] < 0|| j + xMask[k] >= max)continue;
				if ((*vtile)[i+ yMask[k]][j + xMask[k]]->isMine)minenum++;
			}
			(*vtile)[i][j]->mineAround = minenum;
		}
	}
	//for (int i = 0;i < max;i++)
	//{
	//	for (int j = 0;j < max;j++)
	//	{
	//		int minenum = 0;
	//		if ((*vtile)[i][j]->isMine)continue;
	//		if (j == 0 && i == 0)
	//		{

	//			if ((*vtile)[i][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j + 1]->isMine)minenum++;
	//		}
	//		else if (j == max - 1 && i == 0)
	//		{
	//			if ((*vtile)[i][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j - 1]->isMine)minenum++;
	//		}
	//		else if (j == 0 && i == max - 1)
	//		{
	//			if ((*vtile)[i][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j + 1]->isMine)minenum++;
	//		}
	//		else if (j == max - 1 && i == max - 1)
	//		{
	//			if ((*vtile)[i][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j - 1]->isMine)minenum++;
	//		}
	//		else if (i == 0)
	//		{
	//			if ((*vtile)[i][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j + 1]->isMine)minenum++;
	//		}
	//		else if (i == max - 1)
	//		{
	//			if ((*vtile)[i][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j + 1]->isMine)minenum++;
	//		}
	//		else if (j == 0)
	//		{
	//			if ((*vtile)[i - 1][j]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i][j + 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j + 1]->isMine)minenum++;
	//		}
	//		else if (j == max - 1)
	//		{
	//			if ((*vtile)[i - 1][j]->isMine)minenum++;
	//			if ((*vtile)[i - 1][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i][j - 1]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j]->isMine)minenum++;
	//			if ((*vtile)[i + 1][j - 1]->isMine)minenum++;
	//		}
	//		else
	//		{

	//		
	//			for (int p = i - 1;p <= i + 1;p++)
	//			{
	//				for (int k = j - 1;k <=j+1;k++)
	//				{
	//					if (p == i&&k == j)continue;
	//					if ((*vtile)[p][k]->isMine)minenum++;
	//				}
	//			}
	//		}

	//		(*vtile)[i][j]->mineAround = minenum;
	//	}
	//}
}

void Rendering(vector<vector<sTile*>> *vtile, int max,int mine,int flag)
{
	cout << endl;
	for (int i = 0;i < max;i++)
	{
		for (int j = 0;j < max;j++)
		{
			if ((*vtile)[i][j]->isCursor) cout << setw(4)<<"□";
			else if ((*vtile)[i][j]->isCheck)
			{
				if ((*vtile)[i][j]->mineAround == 0)cout << setw(4) << " ";
				else cout << setw(4) << (*vtile)[i][j]->mineAround;
			}
			else
			{
				if((*vtile)[i][j]->isLook)cout << setw(4) << "▣";
				else if((*vtile)[i][j]->isFlag)cout << setw(4) << "★";
				else if(!(*vtile)[i][j]->isLook) cout << setw(4) << "■";
			}
		}
		cout << endl << endl;
	}
	cout << "\t\t\t\t\b"<< setw(4)<<"깃발여분:" << mine - flag << endl;
}



void Spread(vector<vector<sTile*>> *vtile, int x, int y, int max, bool isfirst)
{

	int xMask[] = { -1,0,1,-1,1,-1,0,1 };
	int yMask[] = { -1,-1,-1,0,0,1,1,1 };
	for (int i = 0;i < 8;i++)
	{
		if (y + yMask[i] < 0 || y + yMask[i] >= max)continue;
		if (x + xMask[i] < 0 || x + xMask[i] >= max)continue;
		if (!(*vtile)[y + yMask[i]][x +xMask[i]]->isCheck)
		{
			if (!(*vtile)[y + yMask[i]][x+ xMask[i]]->isFlag)
			{
				(*vtile)[y + yMask[i]][x + xMask[i]]->isCheck = true;
				if ((*vtile)[y + yMask[i]][x + xMask[i]]->mineAround == 0)
				{

					Spread(vtile, x +xMask[i], y  +yMask[i], max, false);
				}
			}
		}
	}
	return;
	/*if (y - 1 >= 0)
	{
		if (x - 1 >= 0)
		{
			if (!(*vtile)[y - 1][x - 1]->isCheck)
			{
				if (!(*vtile)[y - 1][x - 1]->isFlag)
				{
					(*vtile)[y - 1][x - 1]->isCheck = true;
					if ((*vtile)[y - 1][x - 1]->mineAround == 0)
					{

						Spread(vtile, x - 1, y - 1, max, false);
					}
				}
			}
		}
		if (x + 1 != max)
		{
			if (!(*vtile)[y - 1][x + 1]->isCheck)
			{
				if (!(*vtile)[y - 1][x + 1]->isFlag)
				{
					(*vtile)[y - 1][x + 1]->isCheck = true;
					if ((*vtile)[y - 1][x + 1]->mineAround == 0)
					{

						Spread(vtile, x + 1, y - 1, max, false);
					}
				}
			}
		}


		if (!(*vtile)[y - 1][x]->isCheck)
		{
			if (!(*vtile)[y - 1][x]->isFlag)
			{
				(*vtile)[y - 1][x]->isCheck = true;
				if ((*vtile)[y - 1][x]->mineAround == 0)
				{

					Spread(vtile, x, y - 1, max, false);
				}
			}
		}
	}
	if (x - 1 >= 0)
	{
		if (!(*vtile)[y][x - 1]->isCheck)
		{
			if (!(*vtile)[y][x - 1]->isFlag)
			{
				(*vtile)[y][x - 1]->isCheck = true;
				if ((*vtile)[y][x - 1]->mineAround == 0)
				{
					Spread(vtile, x - 1, y, max, false);
				}
			}
		}
	}
	if (x + 1 != max)
	{
		if (!(*vtile)[y][x + 1]->isCheck)
		{
			if (!(*vtile)[y][x + 1]->isFlag)
			{
				(*vtile)[y][x + 1]->isCheck = true;
				if ((*vtile)[y][x + 1]->mineAround == 0)
				{
					Spread(vtile, x + 1, y, max, false);
				}
			}
		}
	}
	if (y + 1 != max)
	{
		if (x - 1 >= 0)
		{
			if (!(*vtile)[y + 1][x - 1]->isCheck)
			{
				if (!(*vtile)[y + 1][x - 1]->isFlag)
				{
					(*vtile)[y + 1][x - 1]->isCheck = true;
					if ((*vtile)[y + 1][x - 1]->mineAround == 0)
					{
						Spread(vtile, x - 1, y + 1, max, false);
					}
				}
			}
		}
		if (x + 1 != max)
		{
			if (!(*vtile)[y + 1][x + 1]->isCheck)
			{
				if (!(*vtile)[y + 1][x + 1]->isFlag)
				{
					(*vtile)[y + 1][x + 1]->isCheck = true;
					if ((*vtile)[y + 1][x + 1]->mineAround == 0)
					{
						Spread(vtile, x + 1, y + 1, max, false);
					}
				}
			}
		}
		if (!(*vtile)[y + 1][x]->isCheck)
		{
			if (!(*vtile)[y + 1][x]->isFlag)
			{
				(*vtile)[y + 1][x]->isCheck = true;
				if ((*vtile)[y + 1][x]->mineAround == 0)
				{
					Spread(vtile, x, y + 1, max, false);
				}
			}
		}
	}*/
	
}


/*
힘들었던점
vector2중배열
check
spread
*/