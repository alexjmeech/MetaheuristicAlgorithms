#include "TSPAlgorithmDispatcher.h"
#include "FileIOUtil.hpp"
#include <iostream>
#include <chrono>
#include "TSP.h"

void TSP::Load(string directory)
{
	if (graph != nullptr)
	{
		delete[] graph;
	}

	FileIOUtil::readData(directory, string("graph.txt"), graph, size, &(Point3D::fromInput));
}

void TSP::Execute()
{
	if (algorithm == nullptr || graph == nullptr)
	{
		return;
	}

	summary = (*algorithm)(graph, size, algorithmConfig);
}

void TSP::Display()
{
	if (summary.getAlgorithm().empty())
	{
		return;
	}

	cout << "Path:" << '\n';

	for (unsigned long node : summary.getBestPath().getPath())
	{
		cout << " -> " << (node + 1);
	}

	cout << '\n' << '\n';

	cout.flush();
}

void TSP::Stats()
{
	if (summary.getAlgorithm().empty())
	{
		return;
	}

	OutputSummary(cout, summary, false);
	cout.flush();
}

void TSP::Select(int algorithmType)
{
	if (algorithmType < 0 || algorithmType >= TSPAlgorithmType::END_TSP)
	{
		return;
	}

	summary = AlgorithmSummary();
	algorithmConfig = 0;
	algorithm = TSPAlgorithmDispatcher::getAlgorithm((TSPAlgorithmType)algorithmType);
}

void TSP::Save()
{
	if (summary.getAlgorithm().empty())
	{
		return;
	}

	ostringstream buffer;

	OutputSummary(buffer, summary, true);

	FileIOUtil::writeBuffer("output", summary.getAlgorithm() + summary.getConfigurationId() + "_Summary.txt", buffer);
}

void TSP::Configure(unsigned long long config)
{
	summary = AlgorithmSummary();
	algorithmConfig = config;
}

void TSP::OutputSummary(ostream& output, AlgorithmSummary& summary, bool path)
{
	output << "Algorithm:" << '\n';
	output << summary.getAlgorithm() << '\n' << '\n';

	output << "Configuration:" << '\n';

	for (auto& config : summary.getConfiguration())
	{
		output << config.first << ": " << config.second << '\n';
	}

	output << '\n';

	if (path)
	{
		output << "Path:" << '\n';

		for (unsigned long node : summary.getBestPath().getPath())
		{
			output << " -> " << (node + 1);
		}

		output << '\n' << '\n';
	}

	output << "Nodes in Path:" << '\n';
	output << (summary.getBestPath().getPath().size() + 1) << '\n' << '\n';

	output << "Distance of Path:" << '\n';
	output << summary.getBestPath().getPathDistance() << '\n' << '\n';

	//output << "Execution Time:" << '\n';
	//output << execution << " nanoseconds" << '\n' << '\n' << '\n';
}

TSP::~TSP()
{
	if (graph != nullptr)
	{
		delete[] graph;
	}

	if (algorithm != nullptr)
	{
		algorithm = nullptr;
	}

	algorithmConfig = 0;
	summary = AlgorithmSummary();
}
