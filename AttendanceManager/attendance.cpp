#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

map<string, int> nameToId;
int idCount = 0;

int attendanceRecord[100][100]; // [id][weekday]
int playerPoints[100]; // [id]
int playerGrades[100]; // [id]
string playerNames[100]; // [id]

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

	int point = 0;
	int weekdayIndex = 0;
	if (attendedWeekday == "monday") {
		weekdayIndex = 0;
		point++;
	}
	if (attendedWeekday == "tuesday") {
		weekdayIndex = 1;
		point++;
	}
	if (attendedWeekday == "wednesday") {
		weekdayIndex = 2;
		point += 3;
		wednesdayAttendenceCount[playerId] += 1;
	}
	if (attendedWeekday == "thursday") {
		weekdayIndex = 3;
		point++;
	}
	if (attendedWeekday == "friday") {
		weekdayIndex = 4;
		point++;
	}
	if (attendedWeekday == "saturday") {
		weekdayIndex = 5;
		point += 2;
		weekendAttendenceCount[playerId] += 1;
	}
	if (attendedWeekday == "sunday") {
		weekdayIndex = 6;
		point += 2;
		weekendAttendenceCount[playerId] += 1;
	}

	//사용자ID별 요일 데이터에 1씩 증가
	attendanceRecord[playerId][weekdayIndex] += 1;
	playerPoints[playerId] += point;
}

void processAllRecords() {
	ifstream fin{ "attendance_weekday_500.txt" }; //500개 데이터 입력
	for (int i = 0; i < 500; i++) {
		string playerName, attendedWeekday;
		fin >> playerName >> attendedWeekday;
		processRecord(playerName, attendedWeekday);
	}

	for (int i = 1; i <= idCount; i++) {
		if (attendanceRecord[i][2] > 9) {
			playerPoints[i] += 10;
		}
		
		if (attendanceRecord[i][5] + attendanceRecord[i][6] > 9) {
			playerPoints[i] += 10;
		}

		if (playerPoints[i] >= 50) {
			playerGrades[i] = 1;
		}
		else if (playerPoints[i] >= 30) {
			playerGrades[i] = 2;
		}
		else {
			playerGrades[i] = 0;
		}

		cout << "NAME : " << playerNames[i] << ", ";
		cout << "POINT : " << playerPoints[i] << ", ";
		cout << "GRADE : ";

		if (playerGrades[i] == 1) {
			cout << "GOLD" << "\n";
		}
		else if (playerGrades[i] == 2) {
			cout << "SILVER" << "\n";
		}
		else {
			cout << "NORMAL" << "\n";
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

int main() {
	processAllRecords();
}