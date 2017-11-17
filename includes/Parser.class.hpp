#pragma once

# include <vector>
# include "TokenFact.class.hpp"
# include "Operator.class.hpp"

class Parser
{
private:
	std::vector< std::vector<Token *> *> *CVectorToken;
	std::vector<std::string> *Link;

	Parser(void);
	void	buildGraph(std::vector<Token *> *tokenLine);

	void PrintMemory();

public:
	Parser(std::vector< std::vector<Token *> *> *, std::vector<std::string> *);
	~Parser(void) {};
};