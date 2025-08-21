#pragma once

#include <string>
#include <unordered_map>
#include "player.h"

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
	void showPlayerScoreAndGrades();
	void showRemovedPlayers();
	void removeLazyPlayers();
};