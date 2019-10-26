#include <string>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <tchar.h>
#include <stdlib.h>
#include <Windows.h>
#include <fstream>
#pragma warning(disable:4996)
using namespace std;
void Wchar_tToString(std::string& szDst, wchar_t* wchar)
{
	wchar_t* wText = wchar;
	DWORD dwNum = WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, NULL, 0, NULL, FALSE);
	char* psText;
	psText = new char[dwNum];
	WideCharToMultiByte(CP_OEMCP, NULL, wText, -1, psText, dwNum, NULL, FALSE);
	szDst = psText;
	delete[]psText;
}

int CheckReplace(string filename, string ReplaceContent, string ChangeContent) {
	ifstream file;
	int n = 0;//统计行数的变量
	string tmp;
	file.open(filename, ios::in);
	if (file.fail()) {
		return 0;
	}
	else {
		string TMP;//存放读取行内容的临时变量
		while (!file.eof()) {
			file >> TMP;
			if (TMP != ReplaceContent) {
				n++;
			}
			else {
				n++;
				break;
			}
		}
		file.close();
		ifstream fp;
		fp.open(filename);
		string strFileData = "";
		int line = 1;
		char tmpLineData[1024] = { 0 };
		while (fp.getline(tmpLineData, sizeof(tmpLineData))) {
			if (line == n) {
				system("pause");
				strFileData += ChangeContent;
				strFileData += "\n";
			}
			else {
				strFileData += tmpLineData;
				strFileData += "\n";
			}
			line++;
		}
		fp.close();
		//写入文件
		ofstream out;
		out.open(filename);
		out.flush();
		out << strFileData;
		out.close();
	}
}

int main()
{
	std::cout << "+——————————————————+\n";
	std::cout << "| 按下任意键检查DFA程序配置是否存在！|\n";
	std::cout << "+——————————————————+\n";
	system("pause");
	wchar_t buffer[MAX_PATH];
	DWORD code = GetEnvironmentVariable(L"APPDATA", buffer, MAX_PATH);
	string pathTMP = "\\DFAssist\\config.ini";
	string Buffer1;
	Wchar_tToString(Buffer1, buffer);
	string path = Buffer1 + pathTMP;
	ifstream _file(path, ios::in);
	if (!_file)
	{
		std::cout << "+————————————————————————————————+\n";
		cout << "| DFA配置文件读取失败，请确保您已经运行了一次DFA并正确彻底地关闭.|\n" << endl;
		std::cout << "+————————————————————————————————+\n";
		system("pause");
	}
	else
	{
		std::cout << "+——————————————————+\n";
		cout << "|   DFA数据确认完成，即将执行修改。  |\n";
		std::cout << "+——————————————————+\n";
		system("pause");
		string filename = path;
		string a = "crack=0";
		string b = "crack=1";
		CheckReplace(filename, a, b);
		std::cout << "+——————————————————+\n";
		std::cout << "+            DFA修改成功             +\n";
		std::cout << "+——————————————————+\n";
		system("pause");
	}
}