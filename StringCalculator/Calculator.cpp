#include "pch.h"
#include "Calculator.h"


CCalculator::CCalculator()
{
}


CCalculator::~CCalculator()
{
}

double	CCalculator::Calculate(const std::string& strPostfixExpression)
{
	std::stack<std::string> tempStack;
	CToken					Token;
	double					dResult = 0.0;
	size_t					iRead = 0;


	// 후위표기법 문자열의 길이만큼 구간을 돌며 계산을 합니다.
	while (iRead < strPostfixExpression.size())
	{
		// 후위연산 변수에서 값을 받아와 토큰에 저장, 현재 토큰의 타입도 받아온다.		
		Token.Get(strPostfixExpression, iRead);


		// SPACE면 continue
		if (Token.GetOperator() == CToken::eSpaceSign)
			continue;


		// 토큰이 피연산자이면, 스택에 토큰을 담는다.
		if (Token.GetType() == CToken::eOperand)
		{
			tempStack.push(Token.GetData());
		}
		// 토큰이 연산자이면...
		else if (Token.GetType() == CToken::eOperator)
		{
			// 피연산자를 담는 변수입니다.
			double dOperandLeft = 0.0;
			double dOperandRight = 0.0;
			double dTempResult = 0.0;

			// 최상단의 피연산자 데이터를 받아옵니다.
			dOperandRight = atof(tempStack.top().c_str());
			tempStack.pop();

			// 다음 피연산자의 데이터를 받아옵니다.
			dOperandLeft = atof(tempStack.top().c_str());
			tempStack.pop();

			switch (Token.GetOperator())
			{
			case CToken::ePlusSign:
				dTempResult = dOperandLeft + dOperandRight;
				break;
			case CToken::eMinusSign:
				dTempResult = dOperandLeft - dOperandRight;
				break;
			case CToken::eMultiplySign:
				dTempResult = dOperandLeft * dOperandRight;
				break;
			case CToken::eDivideSign:
				dTempResult = dOperandLeft / dOperandRight;
				break;
			default:
				assert(!"지원되지 않는 연산자가 있습니다.");
				break;
			}


			// 소수로 되어 있는 계산 결과를 문자열로 변환합니다.
			char szResult[32];
			_gcvt_s(szResult, dTempResult, 10);

			// 계산 결과를 스택에 담습니다.
			tempStack.push(szResult);
		}
		else
		{
			assert(!"입력된 문자열에 연산할수 없는 문자가 포함되어 있습니다.");
		}
	}

	// 문자열로 되어 있는 계산 결과를 소수로 변환합니다.
	std::string strResult;
	strResult = tempStack.top();
	dResult = atof(strResult.c_str());

	return dResult;
}

std::string CCalculator::GetPostfix(const std::string& strInfixExpression)
{
	std::string				strPostfix;
	std::stack<CToken>		tempStack;
	size_t					dwPos = 0;
	CToken					tokenInfix;

	while (dwPos < strInfixExpression.size())
	{
		// 중위표기법 문자열에서 토큰을 받아옵니다.
		tokenInfix.Get(strInfixExpression, dwPos);



		// 토큰이 피연산자이면, 후위표기법 문자열에 등록합니다.
		if (tokenInfix.GetType() == CToken::eOperand)
		{
			strPostfix += tokenInfix.GetData();
			strPostfix += " ";
		}
		else if (tokenInfix.GetOperator() == CToken::eRightParenthesis)
		{
			// 스택이 빌때까지 검색을 합니다.
			while (!tempStack.empty())
			{
				CToken	tempToken;
				tempToken = tempStack.top();
				tempStack.pop();

				if (tempToken.GetOperator() == CToken::eLeftParenthesis)
				{
					break;
				}
				else
				{
					strPostfix += tempToken.GetData();
				}
			}
		}
		else	// 우측괄호 연산자를 제외한 연산자들입니다.
		{
			while ((!tempStack.empty())
				&& (!IsPrior(tempStack.top(), tokenInfix))
				)
			{
				CToken	tempToken;
				tempToken = tempStack.top();
				tempStack.pop();

				if (tempToken.GetOperator() != CToken::eLeftParenthesis)
					strPostfix += tempToken.GetData();

			}

			tempStack.push(tokenInfix);
		}

	}

	while (!tempStack.empty())
	{
		CToken	tempToken;
		tempToken = tempStack.top();
		tempStack.pop();

		if (tempToken.GetOperator() != CToken::eLeftParenthesis)
			strPostfix += tempToken.GetData();
	}

	return strPostfix;
}

bool CCalculator::IsPrior(CToken& tokenStack, CToken& tokenExpression)
{
	return (GetPriority(tokenStack.GetOperator(), true) > GetPriority(tokenExpression.GetOperator(), false));
}

int CCalculator::GetPriority(const CToken::Operators eOperator, const bool bInStack)
{
	int iPriority = -1;

	switch (eOperator)
	{
	case CToken::eLeftParenthesis:
	{
		if (bInStack)
			iPriority = 3;
		else
			iPriority = 0;
	}
	break;
	case CToken::eMultiplySign:
	case CToken::eDivideSign:
	{
		iPriority = 1;
	}
	break;
	case CToken::ePlusSign:
	case CToken::eMinusSign:
	{
		iPriority = 2;
	}
	break;
	}

	return iPriority;
}