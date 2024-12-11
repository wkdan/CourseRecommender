#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <vector>
#include <set>
#include <iostream>

// 추상 클래스 Course
class Course {
protected:
    // 과목명
    std::string name;
    // 과목 코드 (예: T043585)
    std::string code;
    // 학과명
    std::string department;
    // 학점
    int credit;
    // 개설 학년
    int year;
    // 선수과목 (prerequisite)
    std::string prereq;
    // 강의 시간 정보: 요일과 해당 요일의 시간대
    std::vector<std::pair<std::string, std::vector<int>>> times;

public:
    // 가상 소멸자: 상속받은 클래스의 소멸자가 제대로 호출되도록 보장
    virtual ~Course() {}

    // 가상 함수
    virtual std::string getName() const = 0;
    virtual std::string getCode() const = 0;
    virtual int getYear() const = 0;
    virtual int getCredit() const = 0;
    virtual std::string getPrerequisite() const = 0;
    virtual const std::vector<std::pair<std::string, std::vector<int>>>& getTimes() const = 0;
    virtual bool checkPrerequisite(const std::set<std::string>& completed) const = 0;

    // 정적 함수: 두 과목의 강의 시간이 겹치는지 확인
    static bool timeConflict(const Course* a, const Course* b);

    // 연산자 오버로딩: Course 객체를 출력 스트림에 쉽게 출력할 수 있도록 함
    friend std::ostream& operator<<(std::ostream& os, const Course& c);
};

#endif
