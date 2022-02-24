#pragma once
#include <vector>
#include <string>
#include <Windows.h>
class UndeadBaseclass
{
	friend class AsylumHandler;
public:
	UndeadBaseclass();
	~UndeadBaseclass();
	double getScore() { return score; };
	std::wstring getName();
	void setScore(double value) { score = value; };
	void addScore(double value) { score += value; };
	void setName(std::wstring new_name) { name = new_name; };
	bool getSex() { return sex; };
private:
	std::wstring name;
	bool sex = 0;
	double score;
	unsigned int daysSpent = 0;
};
