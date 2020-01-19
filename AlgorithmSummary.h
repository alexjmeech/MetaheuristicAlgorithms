#ifndef ALGORITHMSUMMARY_H_
#define ALGORITHMSUMMARY_H_

#include <string>
#include <map>
#include <unordered_map>
#include "PathSummary.h"
using namespace std;

class AlgorithmSummary
{
private:
	string algorithmName;
	unordered_map<string, unsigned short> configuration;
	PathSummary bestPath;
	map<long long, double> snapshots;
public:
	AlgorithmSummary() {}

	AlgorithmSummary(string);

	const string& getAlgorithm() const;

	string getConfigurationId() const;

	const PathSummary& getBestPath() const;

	const map<long long, double>& getSnapshots() const;

	const unordered_map<string, unsigned short>& getConfiguration() const;

	void setBestPath(const PathSummary&);

	void addSnapshot(long long, double);

	void addConfiguration(string, unsigned short);
};

#endif /* ALGORITHMSUMMARY_H_ */
