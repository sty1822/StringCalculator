// StringCalculator.cpp : 이 파일에는 'main' 함수가 포함됩니다. 거기서 프로그램 실행이 시작되고 종료됩니다.
//

#include "pch.h"
#include <iostream>

#include "Calculator.h"

int main()
{
	std::string strInfix;
	std::string strPostfix;
	double dResult = 0.0;
	
	CCalculator calc;

	while (true)
	{
		std::cout << "수식을 입력하세요." << std::endl;
		std::cin >> strInfix;

		strPostfix = calc.GetPostfix(strInfix);

		dResult = calc.Calculate(strPostfix);

		std::cout << " = " << dResult << std::endl << std::endl;
	}

	
}
