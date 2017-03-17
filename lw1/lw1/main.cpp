#include "stdafx.h"

namespace
{

const std::set<std::string> FLAGS = { "-t", "-p", };

template <class T>
auto MeasureTime(T && fn)
{
	auto begin = std::chrono::high_resolution_clock::now();
	fn();
	auto end = std::chrono::high_resolution_clock::now();
	return (end - begin);
}

template <class T>
void GetPermutations(std::ostream & stream, T & objects, const std::set<std::string> & flags)
{
	const auto needPrint = (flags.find("-p") != flags.end());
	std::sort(objects.begin(), objects.end());
	do
	{
		if (needPrint)
		{
			stream << objects << std::endl;
		}
	} while (std::next_permutation(objects.begin(), objects.end()));
}

std::set<std::string> ParseFlags(int argc, char * argv[])
{
	if (!(2 <= argc) && (argc <= 4))
	{
		throw std::runtime_error("Invalid params. Use this:\n permutation.exe <string> [-t] [-p]\n");
	}
	std::set<std::string> flags;
	for (int i = 2; i < argc; ++i)
	{
		if (FLAGS.find(argv[i]) != FLAGS.end())
		{
			flags.insert(std::string(argv[i]));
		}
		else
		{
			throw std::runtime_error("Unknown flag " + std::string(argv[i]));
		}
	}
	return flags;
}

}

int main(int argc, char * argv[])
{
	try
	{
		auto flags = ParseFlags(argc, argv);
		auto t = MeasureTime([=] {
			GetPermutations(std::cout, std::string(argv[1]), flags);
		});
		if (flags.find("-t") != flags.end())
		{
			std::cout << "runtime = "
				<< std::chrono::duration_cast<std::chrono::milliseconds>(t).count()
				<< " ms" << std::endl;
		}
	}
	catch (std::exception & ex)
	{
		std::cerr << ex.what() << std::endl;
		return 1;
	}
	return 0;
}
