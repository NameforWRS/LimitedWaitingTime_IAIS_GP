#include <string>
#include <vector>
#include "ExpressionMgr.h"

using namespace std;


class Object
{
public:
	Object();
	~Object();

	///����ָ�룬ͨ������������Ӧ�ĺ���
	string (*pp)(vector<string>&);
	ExpressionMgr expression;
	string value;

	Object(string(* _p)(vector<string>&));
	string get_value();
	ExpressionMgr get_expression();
	string apply(vector<string>&V);


private:

};
