#include "stdafx.h"

namespace
{

// NOTE: BANKNOTES need to be sorted for optimization!
const std::vector<size_t> BANKNOTES = { 1, 2, 5, 10, 50, 100 };
const size_t BANKNOTE_COUNT = 2;
const size_t TOTAL_MONEY = 337;

bool FindSolve(std::map<size_t, size_t> & chunks, size_t balance) noexcept
{
	for (const auto & banknote : BANKNOTES)
	{
		if (chunks[banknote] > 0)
		{
			if (balance - banknote == 0)
			{
				return true;
			}
			else if (balance - banknote > 0)
			{
				auto clone(chunks);
				--clone[banknote];
				if (FindSolve(clone, balance - banknote))
				{
					return true;
				}
			}
			else
			{
				return false;
			}
		}
	}
	return false;
}

}

int main(int, char * [])
{
	size_t balance = TOTAL_MONEY;
	std::map<size_t, size_t> chunks;
	for (auto & banknote : BANKNOTES)
	{
		chunks[banknote] = BANKNOTE_COUNT;
	}

	if (FindSolve(chunks, balance))
	{
		std::cout << "Solve!" << std::endl;
	}
	else
	{
		std::cout << "There is no decision" << std::endl;
	}

	return 0;
}
