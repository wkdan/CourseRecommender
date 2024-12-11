#include "Course.h"

// 두 과목의 강의 시간이 겹치는지 확인하는 정적 함수
bool Course::timeConflict(const Course* a, const Course* b) {
    // 첫 번째 과목(a)의 모든 강의 시간 정보를 순회
    for (auto &t1 : a->getTimes()) {
        // 두 번째 과목(b)의 모든 강의 시간 정보를 순회
        for (auto &t2 : b->getTimes()) {
            // 두 과목의 강의 요일이 같은지 확인
            if (t1.first == t2.first) {
                // 같은 요일 내에서 시간대가 겹치는지 확인
                for (auto c1 : t1.second) {
                    for (auto c2 : t2.second) {
                        // 시간대가 겹치면 충돌(true)을 반환
                        if (c1 == c2) return true;
                    }
                }
            }
        }
    }
    // 모든 시간대를 확인했지만 충돌이 없으면 false 반환
    return false;
}

// Course 객체를 출력 스트림에 쉽게 출력할 수 있도록 하는 연산자 오버로딩
std::ostream& operator<<(std::ostream& os, const Course& c) {
    // 과목명, 코드, 학점, 학년, 선수과목, 시간 정보를 출력 형식에 맞게 구성
    os << c.getName() << " (" << c.getCode() << ", "
       << c.getCredit() << "학점, " << c.getYear() << "학년, 선수: "
       << c.getPrerequisite() << ", 시간: ";
    
    // 강의 시간 정보를 순회하여 출력
    for (auto &t : c.getTimes()) {
        os << t.first << " "; // 요일 출력
        for (auto cno : t.second) os << cno << " "; // 시간대 출력
    }
    return os;
}
