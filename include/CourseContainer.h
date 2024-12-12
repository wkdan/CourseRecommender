#ifndef COURSECONTAINER_H
#define COURSECONTAINER_H

#include <vector>
#include <set>
#include <stdexcept>
#include "Course.h"

// 템플릿 클래스 CourseContainer
// 다양한 타입(T)의 과목 객체를 관리하고 추천할 수 있도록 구현
template <typename T>
class CourseContainer {
private:
    // 객체 포인터를 저장하는 벡터: 동적 할당된 과목 객체들을 관리
    std::vector<T*> courses;

public:
    // 소멸자: 모든 과목 객체를 삭제
    ~CourseContainer() {
        for (auto c : courses) delete c;
    }

    // 과목 추가 함수: 새로운 과목 객체를 컨테이너에 추가
    void addCourse(T* c) {
        courses.push_back(c);
    }

    // 모든 과목 객체를 반환하는 함수
    std::vector<T*> getAll() const {
        return courses;
    }

    // 함수 오버로딩: 학점 제한을 포함한 추천 과목 목록 생성
    std::vector<T*> recommendCourses(int year, const std::set<std::string>& completed, int targetCredit) {
        // 같은 학년과 다른 학년의 과목들을 분류하기 위한 벡터
        std::vector<T*> sameYear;
        std::vector<T*> diffYear;

        // 이수한 과목 및 자신의 학년보다 높은 학년의 과목 제외
        for (auto c : courses) {
            // 이수한 과목이면 제외
            if (completed.find(c->getName()) != completed.end()) continue;

            // 자신의 학년보다 높은 학년 과목 제외
            if (c->getYear() > year) continue;

            // 같은 학년이면 sameYear 벡터에 추가, 아니면 diffYear에 추가
            if (c->getYear() == year) sameYear.push_back(c);
            else diffYear.push_back(c);
        }

        // 선수과목을 충족하는 과목과 충족하지 않는 과목으로 분류
        std::vector<T*> primary;
        std::vector<T*> secondary;
        for (auto c : sameYear) {
            if (c->checkPrerequisite(completed)) primary.push_back(c);
            else secondary.push_back(c);
        }

        std::vector<T*> otherPrimary;
        std::vector<T*> otherSecondary;
        for (auto c : diffYear) {
            if (c->checkPrerequisite(completed)) otherPrimary.push_back(c);
            else otherSecondary.push_back(c);
        }

        // 추천 후보군을 하나의 벡터로 합침
        std::vector<T*> candidate;
        candidate.insert(candidate.end(), primary.begin(), primary.end());
        candidate.insert(candidate.end(), secondary.begin(), secondary.end());
        candidate.insert(candidate.end(), otherPrimary.begin(), otherPrimary.end());
        candidate.insert(candidate.end(), otherSecondary.begin(), otherSecondary.end());

        // 최종 추천 과목 목록을 저장할 벡터
        std::vector<T*> result;
        int currentCredit = 0;

        // 후보군을 순회하며 시간 충돌 없이 학점 제한 내에서 과목을 선택
        for (auto c : candidate) {
            bool conflict = false;

            // 이미 선택된 과목들과 시간 충돌이 있는지 확인
            for (auto chosen : result) {
                if (Course::timeConflict(chosen, c)) {
                    conflict = true;
                    break;
                }
            }

            // 시간 충돌이 없고 학점 제한을 넘지 않으면 과목을 추천 목록에 추가
            if (!conflict && currentCredit + c->getCredit() <= targetCredit) {
                result.push_back(c);
                currentCredit += c->getCredit();
            }
        }

        // 추천 가능한 과목이 없으면 예외 발생
        if (result.empty()) {
            throw std::runtime_error("추천 가능한 과목이 없습니다!");
        }

        return result;
    }

 
    std::vector<T*> recommendCourses(int year, const std::set<std::string>& completed) {
        return recommendCourses(year, completed, 9999);
    }
};

#endif
