#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include "gmock/gmock.h"

using std::string;
using std::map;
using std::ifstream;

map<string, int> nameToId;
int idCount = 0;

int playerPoints[100];
int playerGrades[100];
string playerNames[100];

int wednesdayAttendenceCount[100];
int weekendAttendenceCount[100];

void processRecord(string playerName, string attendedWeekday) {
	if (playerName == "Daisy") {
		int debug = 1;
	}
	if (nameToId.count(playerName) == 0) {
		nameToId.insert({ playerName, ++idCount });
		playerNames[idCount] = playerName;
	}
	int playerId = nameToId[playerName];

	if (attendedWeekday == "wednesday") {
		playerPoints[playerId] += 3;
		wednesdayAttendenceCount[playerId] += 1;
	}
	else  if (attendedWeekday == "saturday" || attendedWeekday == "sunday") {
		playerPoints[playerId] += 2;
		weekendAttendenceCount[playerId] += 1;
	}
	else {
		playerPoints[playerId] += 1;
	}
}

void processAllRecords() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string playerName, attendedWeekday;
		fin >> playerName >> attendedWeekday;
		processRecord(playerName, attendedWeekday);
	}

	for (int id = 1; id <= idCount; id++) {
		if (wednesdayAttendenceCount[id] > 9) {
			playerPoints[id] += 10;
		}
		
		if (weekendAttendenceCount[id] > 9) {
			playerPoints[id] += 10;
		}

		if (playerPoints[id] >= 50) {
			playerGrades[id] = 1;
		}
		else if (playerPoints[id] >= 30) {
			playerGrades[id] = 2;
		}
		else {
			playerGrades[id] = 0;
		}

		std::cout << "NAME : " << playerNames[id] << ", ";
		std::cout << "POINT : " << playerPoints[id] << ", ";
		std::cout << "GRADE : ";

		if (playerGrades[id] == 1) {
			std::cout << "GOLD" << "\n";
		}
		else if (playerGrades[id] == 2) {
			std::cout << "SILVER" << "\n";
		}
		else {
			std::cout << "NORMAL" << "\n";
		}
	}

	std::cout << "\n";
	std::cout << "Removed player\n";
	std::cout << "==============\n";
	for (int i = 1; i <= idCount; i++) {

		if (playerGrades[i] != 1 && playerGrades[i] != 2 && wednesdayAttendenceCount[i] == 0 && weekendAttendenceCount[i] == 0) {
			std::cout << playerNames[i] << "\n";
		}
	}
}

TEST(AttendenaceTest, PointTest1) {
	EXPECT_EQ(playerPoints[nameToId["Umar"]], 48);
}

TEST(AttendenaceTest, PointTest2) {
	EXPECT_EQ(playerPoints[nameToId["Hannah"]], 127);
}

TEST(AttendenaceTest, PointTest3) {
	EXPECT_EQ(playerPoints[nameToId["Bob"]], 8);
}

TEST(AttendenaceTest, GradeTestNormal) {
	EXPECT_EQ(playerGrades[nameToId["Ian"]], 0);
}

TEST(AttendenaceTest, GradeTestSilver) {
	EXPECT_EQ(playerGrades[nameToId["Will"]], 2);
}

TEST(AttendenaceTest, GradeTestGold) {
	EXPECT_EQ(playerGrades[nameToId["Charlie"]], 1);
}

int main() {
	processAllRecords();
	::testing::InitGoogleTest();
	return RUN_ALL_TESTS();
}