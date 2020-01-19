#include "AlgorithmSummary.h"

AlgorithmSummary::AlgorithmSummary(string algorithm)
{
	algorithmName = algorithm;
}

const string& AlgorithmSummary::getAlgorithm() const
{
	return algorithmName;
}

string AlgorithmSummary::getConfigurationId() const
{
	string s;

	for (auto& config : configuration)
	{
		s += '_';
		s += to_string(config.second);
	}

	return s;
}

const PathSummary& AlgorithmSummary::getBestPath() const
{
	return bestPath;
}

const map<long long, double>& AlgorithmSummary::getSnapshots() const
{
	return snapshots;
}

const unordered_map<string, unsigned short>& AlgorithmSummary::getConfiguration() const
{
	return configuration;
}

void AlgorithmSummary::setBestPath(const PathSummary& summary)
{
	bestPath = summary;
}

void AlgorithmSummary::addSnapshot(long long epoch, double bestDistance)
{
	snapshots.emplace(epoch, bestDistance);
}

void AlgorithmSummary::addConfiguration(string configurationType, unsigned short configurationValue)
{
	configuration[configurationType] = configurationValue;
}
