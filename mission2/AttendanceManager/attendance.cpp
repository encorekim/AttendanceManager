#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "gmock/gmock.h"
#include "attendance.h"

using std::string;
using std::unordered_map;
using std::ifstream;

void Team::assignPlayer(const string& playerName) {
	if (members.find(playerName) == members.end()) {
		members[playerName] = Player(playerName);
	}
}

void Team::giveAttendancePoints(const string& playerName, const string& attendedWeekday) {
	if (attendedWeekday == "wednesday") {
		members[playerName].addPoints(3);
		members[playerName].attendOnWednesday();
	}
	else  if (attendedWeekday == "saturday" || attendedWeekday == "sunday") {
		members[playerName].addPoints(2);
		members[playerName].attendOnWeekend();
	}
	else {
		members[playerName].addPoints(1);
	}
}

void Team::giveBonusPoints() {
	for (auto& pair : members) {
		Player& player = pair.second;
		if (player.getWendnesdayAttendanceCount() > 9) {
			player.addPoints(10);
		}
		if (player.getWeekendAttendanceCount() > 9) {
			player.addPoints(10);
		}
	}
}

void Team::assignPlayerGrades() {
	for (auto& pair : members) {
		Player& player = pair.second;
		if (player.getPoints() >= 50) {
			player.setGrades(2);
		}
		else if (player.getPoints() >= 30) {
			player.setGrades(1);
		}
		else {
			player.setGrades(0);
		}

	}
}

void Team::showPlayerScoreAndGrades() {
	for (auto& pair : members) {
		Player& player = pair.second;
		std::cout << "NAME : " << player.getName() << ", ";
		std::cout << "POINT : " << player.getPoints() << ", ";
		std::cout << "GRADE : ";

		if (player.getGrade() == 2) {
			std::cout << "GOLD" << "\n";
		}
		else if (player.getGrade() == 1) {
			std::cout << "SILVER" << "\n";
		}
		else {
			std::cout << "NORMAL" << "\n";
		}
	}
}

void Team::removeLazyPlayers() {
	for (auto& pair : members) {
		Player& player = pair.second;
		if (player.getGrade() != 1 && player.getGrade() != 2 && player.getWendnesdayAttendanceCount() == 0 && player.getWeekendAttendanceCount() == 0) {
			player.remove();
		}
	}
}

void Team::showRemovedPlayers()
{
	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (auto& pair : members) {
		Player& player = pair.second;
		if (player.isRemoved()) {
			std::cout << player.getName() << "\n";
		}
	}
}

void Team::processAllRecords() {
	ifstream fin{ "attendance_weekday_500.txt" };
	for (int i = 0; i < 500; i++) {
		string playerName, attendedWeekday;
		fin >> playerName >> attendedWeekday;
		assignPlayer(playerName);
		giveAttendancePoints(playerName, attendedWeekday);
	}

	giveBonusPoints();

	assignPlayerGrades();

	showPlayerScoreAndGrades();

	removeLazyPlayers();

	showRemovedPlayers();
}
