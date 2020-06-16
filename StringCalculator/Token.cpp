#include "pch.h"
#include "Token.h"


CToken::CToken()
	: m_eType(eNull), m_eOperatorType(eOperatorsNull)
{
	// 연산 기호를 초기화합니다.
	m_vecOperatorSymbol.push_back("(");	// eLeftParenthesis
	m_vecOperatorSymbol.push_back(")");	// eRightParenthesis
	m_vecOperatorSymbol.push_back("+");	// ePlusSign
	m_vecOperatorSymbol.push_back("-");	// eMinusSign
	m_vecOperatorSymbol.push_back("*");	// eMultiplySign
	m_vecOperatorSymbol.push_back("/");	// eDivideSign
	m_vecOperatorSymbol.push_back(" ");	// eSpaceSign

	// 피연산자를 초기화합니다.
	m_vecOperandNumber.push_back("0");	// ZERO
	m_vecOperandNumber.push_back("1");	// ONE
	m_vecOperandNumber.push_back("2");	// TWO
	m_vecOperandNumber.push_back("3");	// THREE
	m_vecOperandNumber.push_back("4");	// FOUR
	m_vecOperandNumber.push_back("5");	// FIVE
	m_vecOperandNumber.push_back("6");	// SIX
	m_vecOperandNumber.push_back("7");	// SEVEN
	m_vecOperandNumber.push_back("8");	// EIGHT
	m_vecOperandNumber.push_back("9");	// NINE
	m_vecOperandNumber.push_back(".");	// DECIMAL_POINT
}


CToken::~CToken()
{
}

bool CToken::IsOperand(const std::string& strData) const
{
	for (size_t i = 0; i < m_vecOperandNumber.size(); ++i)
	{
		if (strData == m_vecOperandNumber[i])
		{
			return true;
		}
	}

	return false;
}

bool CToken::IsOperator(const std::string& strData) const
{
	for (size_t i = 0; i < m_vecOperatorSymbol.size(); ++i)
	{
		if (strData == m_vecOperatorSymbol[i])
		{
			return true;
		}
	}

	return false;
}

void CToken::ResetData(void)
{
	m_strData = "";
	m_eType = eNull;
	m_eOperatorType = eOperatorsNull;
}

bool CToken::Get(const std::string& strExpression, size_t& iRead)
{
	ResetData();

	for (size_t i = iRead; i < strExpression.size(); ++i)
	{
		std::string strTemp;
		strTemp = strExpression[i];


		if (IsOperand(strTemp) == true)
		{
			m_eType = eOperand;
			m_strData += strTemp;
			iRead++;

			std::string strTempEx;
			strTempEx = strExpression[i + 1];

			if (IsOperand(strTempEx) == false)
			{
				return true;
			}
		}
		else if (IsOperator(strTemp) == true)
		{
			m_eType = eOperator;
			m_strData = strTemp;
			iRead++;

			if (strTemp == "(")
				m_eOperatorType = eLeftParenthesis;
			else if (strTemp == ")")
				m_eOperatorType = eRightParenthesis;
			else if (strTemp == "+")
				m_eOperatorType = ePlusSign;
			else if (strTemp == "-")
				m_eOperatorType = eMinusSign;
			else if (strTemp == "*")
				m_eOperatorType = eMultiplySign;
			else if (strTemp == "/")
				m_eOperatorType = eDivideSign;
			else if (strTemp == " ")
				m_eOperatorType = eSpaceSign;
			else
			{
				assert(!"등록되지 않은 연산자입니다.");
				return false;
			}

			return true;
		}
		else
		{
			assert(!"문자열에 정의되지 않은 문자가 있습니다.");
			return false;
		}
	}

	return true;
}