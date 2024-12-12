#include "CSECourse.h" // CSECourse 클래스의 선언을 포함
#include "Utilities.h" // 유틸리티 함수를 사용하기 위해 포함

// CSECourse 클래스의 생성자 구현
// 모든 멤버 변수를 초기화하여 객체를 생성
CSECourse::CSECourse(const std::string& _name, const std::string& _code, const std::string& _dept,
                     int _credit, int _year, const std::string& _prereq,
                     const std::vector<std::pair<std::string, std::vector<int>>>& _times) {
    name = _name;           // 과목명 초기화
    code = _code;           // 과목 코드 초기화
    department = _dept;     // 학과명 초기화
    credit = _credit;       // 학점 초기화
    year = _year;           // 개설 학년 초기화
    prereq = _prereq;       // 선수과목 초기화
    times = _times;         // 강의 시간 초기화
}

// getName() 함수 구현: 과목명을 반환
std::string CSECourse::getName() const { 
    return name; 
}

// getCode() 함수 구현: 과목 코드를 반환
std::string CSECourse::getCode() const { 
    return code; 
}

// getYear() 함수 구현: 개설 학년을 반환
int CSECourse::getYear() const { 
    return year; 
}

// getCredit() 함수 구현: 학점을 반환
int CSECourse::getCredit() const { 
    return credit; 
}

// getPrerequisite() 함수 구현: 선수과목 정보를 반환
std::string CSECourse::getPrerequisite() const { 
    return prereq; 
}

// getTimes() 함수 구현: 강의 시간 정보를 반환
const std::vector<std::pair<std::string, std::vector<int>>>& CSECourse::getTimes() const { 
    return times; 
}

// checkPrerequisite() 함수 구현: 이수 조건을 만족하는지 검사
bool CSECourse::checkPrerequisite(const std::set<std::string>& completed) const {
    // 선수과목이 "없음"인 경우, 이수 조건을 자동으로 만족
    if (prereq == "없음") return true;
    
    std::stringstream ss(prereq); // 선수과목 문자열을 스트림으로 변환하여 파싱
    std::string token;
    
    // ';'를 구분자로 사용하여 선수과목을 하나씩 추출
    while (std::getline(ss, token, ';')) {
        trim(token); // 과목명 앞뒤의 공백을 제거
        if (token.empty()) continue; // 공백인 경우 건너뜀
        
        // 이수한 과목 집합에 선수과목이 포함되어 있지 않으면 false 반환
        if (completed.find(token) == completed.end()) return false;
    }
    
    // 모든 선수과목이 이수한 과목 집합에 포함되어 있으면 true 반환
    return true;
}
