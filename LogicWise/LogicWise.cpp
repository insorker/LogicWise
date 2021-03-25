#include "LogicalOperation.h"
#include "CyclicCode.h"
using std::cin;
using std::getline;

#if 0
void test1() {
	CyclicCode cc(4);
	while (cc.next()) {
		for (int i = 0; i < 4; i++)
			cout << cc[i] << ' ';
		cout << '\n';
	}
}
#endif

int main()
{
	unsigned int size;
	string exp;
	char c1 = 'y';
	char c2 = 'n';
	cout << "Welcome To LogicWise~~ Have a good time~~" << '\n';
	cout << "-----------------------------------------" << '\n';
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
			LogicalOperation lo(size, exp, LogicalOperation::KARNO);
			lo.showTrueTable();
			lo.showPostfixExpression();
		}
		else if (c2 == 'n') {
			LogicalOperation lo(size, exp);
			lo.showTrueTable();
			lo.showPostfixExpression();
		}

		cout << '\n';
		do {
			cout << "是否继续？（y/n)" << '\n';
			cin >> c1;
		} while (c1 != 'y' && c1 != 'n');
		cout << "-----------------------------------------" << '\n';
	}

	return 0;
}