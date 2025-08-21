#pragma once

#include <string>
#include <memory>

class Grade {
public:
	virtual std::string getName() = 0;
	virtual int getCutoff() = 0;
};

class GoldGrade : public Grade {
public:
	std::string getName() override { return name; }
	int getCutoff() override { return cutoff; }
private:
	std::string name = "GOLD";
	int cutoff = 50;
};

class SilverGrade : public Grade {
public:
	std::string getName() override { return name; }
	int getCutoff() override { return cutoff; }
private:
	std::string name = "SILVER";
	int cutoff = 30;
};

class NormalGrade : public Grade {
public:
	std::string getName() override { return name; }
	int getCutoff() override { return cutoff; }
private:
	std::string name = "NORMAL";
	int cutoff = 0;
};

class GradeFactory {
public:
	static std::unique_ptr<Grade> create(int point) {
		if (point >= 50) {
			return std::make_unique<GoldGrade>();
		}
		if (point >= 30) {
			return std::make_unique<SilverGrade>();
		}
		return std::make_unique<NormalGrade>();
	}
};