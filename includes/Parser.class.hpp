#pragma once

# include <vector>
# include <cstdlib>
# include "TokenFact.class.hpp"
# include "Operator.class.hpp"
# include "Fact.class.hpp"
# include "TokenMixed.class.hpp"

class Parser
{
private:
	std::vector< std::vector<Token *> *> *CVectorToken;
	std::vector<Fact *> FactTab;

	Parser(void);
	void	splitLineToken(std::vector<Token *> *tokenLine);
	std::vector<Token *> *ShuntingYardAlgo(std::vector<Token *> *Input);
	void buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Operator *middleToken);
	Fact * buildNode(std::vector<Token *> *input1, int way);
	Fact * getFact(Token * token);

	void PrintMemory(std::vector<Token *> toto);
	void PrintFactTab();
	void PrintNode(Fact * fact, Instr * instr);

public:
	void PrintGraph();
	Parser(std::vector< std::vector<Token *> *> *, std::vector<Fact *>);
	~Parser(void) {};
};