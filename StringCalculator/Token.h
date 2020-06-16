#pragma once

class CToken
{
public:
	enum Type
	{
		eNull,		// �⺻��
		eOperand,	// �ǿ�����
		eOperator,	// ������
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
	std::string			m_strData;			// ��ū�� ��� ���� �������Դϴ�.
	Type				m_eType;			// ��ū�� ��� ������ Ÿ���Դϴ�.
	Operators			m_eOperatorType;	// ���� Ÿ���� ������ �� ��, ��� ������������ ��Ÿ���ϴ�.
	std::vector<std::string>		m_vecOperatorSymbol;	// ���� ��ȣ�� ���� �����̳��Դϴ�.
	std::vector<std::string>		m_vecOperandNumber;		// �ǿ����ڸ� ���� �����̳��Դϴ�.
};

