#if 1
#define TEST_TTB_IO 0
#define TEST_TTB_CC 0
#define TEST_LD		1
#endif

#if TEST_TTB_IO
#include "TrueTable/TTB_InOrder.h"
#include <iostream>
using namespace std;
void test_ttb_inorder() {
	unsigned int size = 3;
	TTB_InOrder ttb_io(size);
	while (ttb_io.next()) {
		for (unsigned int i = 0; i < size; ++i) {
			cout << ttb_io[i] << ' ';
		}
		cout << endl;
	}
}
#endif

#if TEST_TTB_CC
#include "TrueTable/TTB_CyclicCode.h"
#include <iostream>
using namespace std;
void test_ttb_cc() {
	unsigned int size = 3;
	TTB_CyclicCode ttb_io(size);
	while (ttb_io.next()) {
		for (unsigned int i = 0; i < size; ++i) {
			cout << ttb_io[i] << ' ';
		}
		cout << endl;
	}
}
#endif

#if TEST_LD
#include "LogicalWise/LogicalDraw.h"
using std::cin;

void test_LD() {
	unsigned int size;
	string exp;
	char c1 = 'y';
	char c2 = 'n';
	cout << "Welcome To LogicWise~~ Have a good time~~" << endl;
	cout << "-----------------------------------------" << endl;
	while (c1 == 'y') {
		cout << "请输入变量个数：" << '\n';
		cin >> size;
		cout << "请输入表达式：" << '\n';
		cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
		getline(cin, exp);
		do {
			cout << "是否使用卡诺图形式输出真值表？（y/n)" << '\n';
			cin >> c2;
		} while (c2 != 'y' && c2 != 'n');

		if (c2 == 'y') {
			LogicalDraw ld(size, exp, LogicalParser::KARNO);
			ld.showTrueTable();
			ld.showPostfixExpression();
		}
		else if (c2 == 'n') {
			LogicalDraw ld(size, exp);
			ld.showTrueTable();
			ld.showPostfixExpression();
		}

		cout << '\n';
		do {
			cout << "是否继续？（y/n)" << '\n';
			cin >> c1;
		} while (c1 != 'y' && c1 != 'n');
		cout << "-----------------------------------------" << '\n';
	}
}
#endif

int main()
{
	test_LD();
	return 0;
}