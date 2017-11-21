#pragma once

# include <vector>
# include <cstdlib>
# include "TokenFact.class.hpp"
# include "Operator.class.hpp"
# include "Fact.class.hpp"

class Parser
{
private:
	std::vector< std::vector<Token *> *> *CVectorToken;
	std::vector<Fact *> FactTab;

	Parser(void);
	void	splitLineToken(std::vector<Token *> *tokenLine);
	std::vector<Token *> *ShuntingYardAlgo(std::vector<Token *> *Input);
	void buildGraph(std::vector<Token *> *input1, std::vector<Token *> *input2, Operator *middleToken);
	Link * buildNode(std::vector<Token *> *input1, WTF);
<<<<<<< HEAD
	Fact * getFact(Token * token);
=======
	Fact * getFact(Token *token);
>>>>>>> 323eaecc4158e014cd5fa79c09177c1dcf14768d

	void PrintMemory(std::vector<Token *> toto);

public:
	Parser(std::vector< std::vector<Token *> *> *, std::vector<Fact *>);
	~Parser(void) {};
};