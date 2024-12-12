#ifndef CSECOURSE_H
#define CSECOURSE_H

#include "Course.h" // 추상 클래스 Course를 상속받기 위해 포함

// Course 클래스의 구체적인 구현
class CSECourse : public Course {
public:
    // 생성자: 과목의 모든 속성을 초기화
    CSECourse(const std::string& _name, const std::string& _code, const std::string& _dept,
              int _credit, int _year, const std::string& _prereq,
              const std::vector<std::pair<std::string, std::vector<int>>>& _times);

    // 가상 함수들: Course 클래스에서 선언된 가상 함수들을 재정의
    virtual std::string getName() const override;
    virtual std::string getCode() const override;
    virtual int getYear() const override;
    virtual int getCredit() const override;
    virtual std::string getPrerequisite() const override;
    virtual const std::vector<std::pair<std::string, std::vector<int>>>& getTimes() const override;
    virtual bool checkPrerequisite(const std::set<std::string>& completed) const override;
};

#endif
