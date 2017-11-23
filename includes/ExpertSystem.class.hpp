#pragma once

class ExpertSystem
{

private:

	std::vector<Fact *> * tabFact;
	std::vector<std::string> * tabQuery;

	ExpertSystem();

public:
	ExpertSystem(std::vector<Fact *> *, std::vector<std::string> *);
	~ExpertSystem() {} ;

	int backWardChaining(Fact *);

};