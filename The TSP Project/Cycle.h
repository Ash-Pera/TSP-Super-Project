#pragma once
#include "Path.h"
class Cycle : public Path {
public:
	Cycle();
	Cycle(Path);
	double length() const override;
};

