#ifndef UTILITIES_H
#define UTILITIES_H

#include <string>
#include <cctype>
#include <algorithm>
#include <sstream>
#include <vector>
#include <iostream>

// 문자열의 앞뒤 공백을 제거하는 함수
void trim(std::string &s);

// 문자열이 숫자로만 구성되어 있는지 확인하는 함수
bool isNumber(const std::string &s);

// 문자열이 요일을 나타내는지 확인하는 함수 (월, 화, 수, 목, 금)
bool isDay(const std::string &d);

// 강의 시간 문자열을 파싱하여 요일과 시간대를 벡터로 반환하는 함수
std::vector<std::pair<std::string, std::vector<int>>> parseTimes(const std::string& timeStr);

#endif