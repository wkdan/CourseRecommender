#include "Utilities.h" 
#include <cctype>    
#include <sstream>    
#include <algorithm>  


// 문자열의 앞뒤 공백을 제거하는 함수
void trim(std::string &s) {
    // 문자열이 비어있지 않고, 첫 문자가 공백일 경우 제거
    while(!s.empty() && std::isspace((unsigned char)s.front())) 
        s.erase(s.begin());
    
    // 문자열이 비어있지 않고, 마지막 문자가 공백일 경우 제거
    while(!s.empty() && std::isspace((unsigned char)s.back())) 
        s.pop_back();
}

// 문자열이 숫자로만 구성되어 있는지 확인하는 함수
bool isNumber(const std::string &s) {
    for (char ch : s) {
        // 각 문자가 숫자가 아닌 경우 false 반환
        if(!std::isdigit((unsigned char)ch)) 
            return false;
    }
    // 문자열이 비어있지 않고, 모든 문자가 숫자인 경우 true 반환
    return !s.empty();
}

// 문자열이 요일을 나타내는지 확인하는 함수 (월, 화, 수, 목, 금)
bool isDay(const std::string &d) {
    return d == "월" || d == "화" || d == "수" || d == "목" || d == "금";
}

// 강의 시간 문자열을 파싱하여 요일과 시간대를 벡터로 반환하는 함수
std::vector<std::pair<std::string, std::vector<int>>> parseTimes(const std::string& timeStr) {
    std::vector<std::pair<std::string, std::vector<int>>> res; // 결과를 저장할 벡터
    std::stringstream ss(timeStr); // 입력 문자열을 스트림으로 변환
    std::string token;              // 토큰을 저장할 변수
    std::string currentDay;         // 현재 처리 중인 요일
    std::vector<int> currentPeriods; // 현재 요일의 시간대를 저장할 벡터

    // 스트림에서 공백을 기준으로 토큰을 추출
    while (ss >> token) {
        trim(token); // 추출한 토큰의 앞뒤 공백 제거

        if (isDay(token)) { // 토큰이 요일인 경우
            if (!currentDay.empty()) { // 이전에 처리한 요일이 있다면
                res.push_back({currentDay, currentPeriods}); // 결과 벡터에 추가
            }
            currentDay = token;       // 현재 요일 업데이트
            currentPeriods.clear();   // 이전 시간대 초기화
        } else { // 토큰이 시간대인 경우
            if (isNumber(token)) { // 토큰이 숫자인지 확인
                int period = std::stoi(token); // 문자열을 정수로 변환
                currentPeriods.push_back(period); // 시간대 벡터에 추가
            }
        }
    }

    // 마지막으로 처리한 요일과 시간대를 결과 벡터에 추가
    if (!currentDay.empty()) {
        res.push_back({currentDay, currentPeriods});
    }

    return res; // 파싱된 결과 반환
}
