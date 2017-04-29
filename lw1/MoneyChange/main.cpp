#include "stdafx.h"

namespace
{

const std::vector<size_t> BANKNOTES = { 1, 2, 5, 10, 50, 100, 500, 1000, 5000 };
const size_t TOTAL_MONEY = 8086;

void PrintChunks(const std::map<size_t, size_t> & chunks)
{
	for (const auto & chunk : chunks)
	{
		std::cout << chunk.first << " " << chunk.second << std::endl;
	}
}

}

int main(int, char * [])
{
	std::map<size_t, size_t> chunks;
	for (auto & banknote : BANKNOTES)
	{
		chunks[banknote] = 2;
	}
	size_t balance = TOTAL_MONEY;

	while (balance > 0)
	{
		auto bla = std::find_if(chunks.rbegin(), chunks.rend(), [=](const auto & chunk) {
			return ((chunk.second > 0) && (chunk.first <= balance));
		});
		if (bla == chunks.rend())
		{
			std::cout << "No roots" << std::endl;
			return 1;
		}
		else
		{
			balance -= (*bla).first;
			--chunks[(*bla).first];
		}
		if (balance == 0)
		{
			std::cout << "Hip-hip! Hooray!" << std::endl;
			for (const auto & chunk : chunks)
			{
				if (chunk.second != 2)
				{
					std::cout << "+ " << (2 - chunk.second) << "*" << chunk.first << " ";
				}
			}
			std::cout << std::endl;
		}
	}
	return 0;
}
