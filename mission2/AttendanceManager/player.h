#pragma once

#include <string>
#include <memory>
#include "grade.h"

class Player {
public:
	Player() = default;
	Player(const std::string& name) : name(name) {}
	~Player() = default;
	Player(Player&&) noexcept = default;
	Player& operator=(Player&&) noexcept = default;
	Player(const Player&) = delete;
	Player& operator=(const Player&) = delete;

	std::string getName() { return name; }
	void addPoints(int gainedPoints) { points += gainedPoints; }
	int getPoints() { return points; }
	void setGradesByPoints() { grade = GradeFactory::create(points); }
	std::string getGrade() { return grade->getName(); }
	void attendOnWednesday() { wendesnesdayAttendanceCount++; }
	void attendOnWeekend() { weekendAttendanceCount++; }
	int getWendnesdayAttendanceCount() {
		return wendesnesdayAttendanceCount;
	}
	int getWeekendAttendanceCount() {
		return weekendAttendanceCount;
	}
	void remove() { removed = true; }
	bool isRemoved() { return removed; }

private:
	std::string name{ "" };
	int points{ 0 };
	std::unique_ptr<Grade> grade = nullptr;
	int wendesnesdayAttendanceCount{ 0 };
	int weekendAttendanceCount{ 0 };
	bool removed = false;
};
