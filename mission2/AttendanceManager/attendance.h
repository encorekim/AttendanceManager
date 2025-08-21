#pragma once

#include <string>
#include <unordered_map>

enum Grade {
	Normal = 0,
	Silver = 1,
	Gold = 2
};

class Player {
public:
	Player() = default;
	Player(const std::string& name) : name(name) {}
	~Player() = default;

	std::string getName() { return name; }
	void addPoints(int gainedPoints) { points += gainedPoints; }
	int getPoints() { return points; }
	void setGrades(int newGrade) { grade = newGrade; }
	int getGrade() { return grade; }
	void attendOnWednesday() { wendesnesdayAttendanceCount++; }
	void attendOnWeekend() { weekendAttendanceCount++; }
	int getWendnesdayAttendanceCount() {
		return wendesnesdayAttendanceCount;
	}
	int getWeekendAttendanceCount() {
		return weekendAttendanceCount;
	}

private:
	std::string name{ "" };
	int points{ 0 };
	int grade{ 0 };
	int wendesnesdayAttendanceCount{ 0 };
	int weekendAttendanceCount{ 0 };
};

class Team {
public:
	Team() = default;
	~Team() = default;
	void processAllRecords();
	Player& getPlayer(const std::string& playerName) { return members[playerName]; }
private:
	std::unordered_map<std::string, Player> members;
	void assignPlayer(const std::string& playerName);
	void giveAttendancePoints(const std::string& playerName, const std::string& attendedWeekday);
	void giveBonusPoints();
	void assignPlayerGrades();
	void showPlayerScoreAndGrades();
	void showRemovedPlayers();
};