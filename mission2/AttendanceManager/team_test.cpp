#include "gmock/gmock.h"
#include "team.h"

class AttendanceFixture : public ::testing::Test {
public:
	Team team;
protected:
	void SetUp() override {
		team.processAllRecords();
	}
};

TEST_F(AttendanceFixture, PointTest1) {
	EXPECT_EQ(team.getPlayer("Umar").getPoints(), 48);
}

TEST_F(AttendanceFixture, PointTest2) {
	EXPECT_EQ(team.getPlayer("Hannah").getPoints(), 127);
}

TEST_F(AttendanceFixture, PointTest3) {
	EXPECT_EQ(team.getPlayer("Bob").getPoints(), 8);
}

TEST_F(AttendanceFixture, GradeTestNormal) {
	EXPECT_EQ(team.getPlayer("Ian").getGrade(), "NORMAL");
}

TEST_F(AttendanceFixture, GradeTestSilver) {
	EXPECT_EQ(team.getPlayer("Will").getGrade(), "SILVER");
}

TEST_F(AttendanceFixture, GradeTestGold) {
	EXPECT_EQ(team.getPlayer("Charlie").getGrade(), "GOLD");
}

TEST_F(AttendanceFixture, RemovedPlayer) {
	EXPECT_EQ(team.getPlayer("Zane").isRemoved(), true);
}

TEST_F(AttendanceFixture, NotRemovedPlayer) {
	EXPECT_EQ(team.getPlayer("Xena").isRemoved(), false);
}