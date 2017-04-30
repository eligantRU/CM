#include "stdafx.h"

namespace
{

// NOTE: BANKNOTES need to be sorted! [for optimization]
const std::vector<size_t> BANKNOTES = { 1, 2, 5, 10, 50, 100, 500 };
const size_t BANKNOTE_COUNT = 2;
const size_t TOTAL_MONEY = 1336;

std::map<size_t, size_t> GetChunks()
{
	std::map<size_t, size_t> chunks;
	for (const auto & banknote : BANKNOTES)
	{
		chunks[banknote] = BANKNOTE_COUNT;
	}
	return chunks;
}

bool CanSolve(std::map<size_t, size_t> & chunks, size_t balance) noexcept
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
				if (CanSolve(clone, balance - banknote))
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

bool CanExchange(const std::map<size_t, size_t> & chunks, size_t balance)
{
	if (balance == 0)
	{
		return true;
	}

	const auto doubleMax = BANKNOTE_COUNT * std::accumulate(BANKNOTES.cbegin(), BANKNOTES.cend(), size_t());
	if (!((0 < TOTAL_MONEY) && (TOTAL_MONEY <= doubleMax)))
	{
		return false;
	}

	auto clone(chunks);
	return CanSolve(clone, balance);
}

}

int main(int, char * [])
{
	if (CanExchange(GetChunks(), TOTAL_MONEY))
	{
		std::cout << "Solved!" << std::endl;
	}
	else
	{
		std::cout << "There is no decision" << std::endl;
	}
}
