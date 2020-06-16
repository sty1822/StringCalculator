#pragma once

class CToken
{
public:
	enum Type
	{
		eNull,		// 기본값
		eOperand,	// 피연산자
		eOperator,	// 연산자
	};

	enum Operators
	{
		eOperatorsNull,
		eLeftParenthesis	= '(',
		eRightParenthesis	= ')',
		ePlusSign			= '+',
		eMinusSign			= '-',
		eMultiplySign		= '*',
		eDivideSign			= '/',
		eSpaceSign			= ' ',
	};



public:
	CToken();
	~CToken();

public:
	bool Get(const std::string& strExpression, size_t& iRead);

	std::string GetData(void) const
	{
		return m_strData;
	}

	Type GetType(void) const
	{
		return m_eType;
	}

	Operators GetOperator(void) const
	{
		return m_eOperatorType;
	}

private:
	void ResetData(void);
	bool IsOperand(const std::string& strData) const;
	bool IsOperator(const std::string& strData) const;

private:
	std::string			m_strData;			// 토큰에 담긴 문자 데이터입니다.
	Type				m_eType;			// 토큰에 담긴 문자의 타입입니다.
	Operators			m_eOperatorType;	// 문자 타입이 연산자 일 때, 어떠한 연산자인지를 나타냅니다.
	std::vector<std::string>		m_vecOperatorSymbol;	// 연산 기호를 담은 컨테이너입니다.
	std::vector<std::string>		m_vecOperandNumber;		// 피연산자를 담은 컨테이너입니다.
};

