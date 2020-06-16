#pragma once
#include "Token.h"

class CCalculator
{
public:
	double	Calculate(const std::string& strPostfixExpression);
	std::string GetPostfix(const std::string& strInfixExpression);
	bool IsPrior(CToken& tokenStack, CToken& tokenExpression);
	int GetPriority(const CToken::Operators eOperator, const bool bInStack);


public:
	CCalculator();
	~CCalculator();
};

