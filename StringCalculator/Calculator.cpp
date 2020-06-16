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


	// ����ǥ��� ���ڿ��� ���̸�ŭ ������ ���� ����� �մϴ�.
	while (iRead < strPostfixExpression.size())
	{
		// �������� �������� ���� �޾ƿ� ��ū�� ����, ���� ��ū�� Ÿ�Ե� �޾ƿ´�.		
		Token.Get(strPostfixExpression, iRead);


		// SPACE�� continue
		if (Token.GetOperator() == CToken::eSpaceSign)
			continue;


		// ��ū�� �ǿ������̸�, ���ÿ� ��ū�� ��´�.
		if (Token.GetType() == CToken::eOperand)
		{
			tempStack.push(Token.GetData());
		}
		// ��ū�� �������̸�...
		else if (Token.GetType() == CToken::eOperator)
		{
			// �ǿ����ڸ� ��� �����Դϴ�.
			double dOperandLeft = 0.0;
			double dOperandRight = 0.0;
			double dTempResult = 0.0;

			// �ֻ���� �ǿ����� �����͸� �޾ƿɴϴ�.
			dOperandRight = atof(tempStack.top().c_str());
			tempStack.pop();

			// ���� �ǿ������� �����͸� �޾ƿɴϴ�.
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
				assert(!"�������� �ʴ� �����ڰ� �ֽ��ϴ�.");
				break;
			}


			// �Ҽ��� �Ǿ� �ִ� ��� ����� ���ڿ��� ��ȯ�մϴ�.
			char szResult[32];
			_gcvt_s(szResult, dTempResult, 10);

			// ��� ����� ���ÿ� ����ϴ�.
			tempStack.push(szResult);
		}
		else
		{
			assert(!"�Էµ� ���ڿ��� �����Ҽ� ���� ���ڰ� ���ԵǾ� �ֽ��ϴ�.");
		}
	}

	// ���ڿ��� �Ǿ� �ִ� ��� ����� �Ҽ��� ��ȯ�մϴ�.
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
		// ����ǥ��� ���ڿ����� ��ū�� �޾ƿɴϴ�.
		tokenInfix.Get(strInfixExpression, dwPos);



		// ��ū�� �ǿ������̸�, ����ǥ��� ���ڿ��� ����մϴ�.
		if (tokenInfix.GetType() == CToken::eOperand)
		{
			strPostfix += tokenInfix.GetData();
			strPostfix += " ";
		}
		else if (tokenInfix.GetOperator() == CToken::eRightParenthesis)
		{
			// ������ �������� �˻��� �մϴ�.
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
		else	// ������ȣ �����ڸ� ������ �����ڵ��Դϴ�.
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