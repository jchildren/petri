#pragma once

struct position {
	int x;
	int y;

	bool operator==(const position& rhs) const
	{
		return (x == rhs.x) && (y == rhs.y);
	}

};
