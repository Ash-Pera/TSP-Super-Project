#pragma once
#include "path.h"
class Cycle :
	public Path {
public:
	Cycle();
	Cycle(Path);
	double length() const;

};

