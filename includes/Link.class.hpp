#pragma once

# include "Instr.class.hpp"
# include "vector"

class Link
{
private:
	std::vector<Instr> tabLink;

public:
	Link();
	~Link(void) {};

};