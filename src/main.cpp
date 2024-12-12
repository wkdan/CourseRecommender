/*
컴퓨터 프로그래밍 및 실습 평가과제 (배점 25점)
학과 : 컴퓨터공학과
학번 : 202104330
이름 : 장무영
과제 주제 : 미래의 수강신청 추천 시스템 (개인별 맞춤 자동화)
*/


#include <iostream>    
#include <fstream>  
#include <sstream>     
#include <string> 
#include <set>        
#include <stdexcept>    
#include <limits>        
#include "CourseContainer.h"
#include "CSECourse.h"    
#include "Utilities.h"     

using namespace std;

int main() {
    // C++ 표준 입출력과 C 입출력의 동기화를 비활성화하여 입출력 속도 향상(구글 참고)
    ios::sync_with_stdio(false);
    // cin과 cout의 연결을 해제하여 입출력 속도 향상 (구글 참고)
    cin.tie(NULL);

    // courses.txt 파일을 읽기 모드로 열기
    ifstream fin("../data/courses.txt");
    if(!fin.is_open()) { // 파일 열기에 실패한 경우
        cerr << "courses.txt 파일을 열 수 없습니다.\n"; // 오류 메시지 출력
        return 1; // 프로그램 종료
    }

    // CourseContainer 객체 생성 (Course 타입을 관리)
    CourseContainer<Course> container;

    {
        string line; // 파일에서 한 줄씩 읽어올 변수
        while (true) {
            if(!getline(fin, line)) break; // 파일의 끝에 도달하면 루프 종료
            if(line.empty()) continue; // 빈 줄은 건너뜀

            string name, code, dept, prereq, timeStr; // 각 필드를 저장할 변수
            string creditStr, yearStr; // 학점과 학년을 문자열로 저장할 변수

            {
                stringstream ss(line); // 현재 줄을 스트링 스트림으로 변환하여 필드 추출 준비

                // 콤마(',')를 기준으로 필드 추출 및 공백 제거
                if(!getline(ss, name, ',')) continue; trim(name);
                if(!getline(ss, code, ',')) continue; trim(code);
                if(!getline(ss, dept, ',')) continue; trim(dept);
                if(!getline(ss, creditStr, ',')) continue; trim(creditStr);

                // 학점이 숫자인지 확인
                if(!isNumber(creditStr)) {
                    cerr << "학점 숫자 오류: [" << creditStr << "]\n"; // 오류 메시지 출력
                    continue; 
                }
                int credit = stoi(creditStr); // 학점을 정수로 변환

                if(!getline(ss, yearStr, ',')) continue; trim(yearStr);
                // 학년이 숫자인지 확인
                if(!isNumber(yearStr)) {
                    cerr << "학년 숫자 오류: [" << yearStr << "]\n"; // 오류 메시지 출력
                    continue; 
                }
                int courseYear = stoi(yearStr); // 학년을 정수로 변환

                if(!getline(ss, prereq, ',')) continue; trim(prereq); // 선수과목 추출 및 공백 제거
                if(!getline(ss, timeStr, '\n')) continue; trim(timeStr); // 강의 시간 추출 및 공백 제거

                // 강의 시간 문자열을 파싱하여 구조화된 데이터로 변환
                auto times = parseTimes(timeStr);

                // CSECourse 객체 동적 할당 및 초기화
                Course *c = new CSECourse(name, code, dept, credit, courseYear, prereq, times);
                container.addCourse(c); // CourseContainer에 과목 추가
            }
        }
    }
    fin.close(); // 파일 스트림 닫기

    // 학년 입력 받기
    int inputYear;
    while (true) {
        cout << "추천받을 학년을 입력하세요: " << flush; // 사용자에게 입력 요청 및 버퍼 플러시
        string yearInput; // 사용자 입력을 저장할 변수
        getline(cin, yearInput); // 한 줄 입력받기
        trim(yearInput); // 입력된 문자열의 앞뒤 공백 제거

        if(!isNumber(yearInput)) { // 입력이 숫자가 아닌 경우
            cout << "학년을 숫자로 입력하세요.\n"; // 오류 메시지 출력
            continue; // 다시 입력받기
        }
        inputYear = stoi(yearInput); // 입력을 정수로 변환
        break; // 유효한 입력이므로 루프 종료
    }

    // 이수한 과목 입력 받기
    cout << "이수한 과목명을 ','로 구분하여 입력하세요(없으면 엔터): " << flush; // 사용자에게 입력 요청
    string completedStr; // 사용자 입력을 저장할 변수
    getline(cin, completedStr); // 한 줄 입력받기
    set<string> completedSet; // 이수한 과목을 저장할 집합

    if (!completedStr.empty()) { // 입력이 비어있지 않은 경우
        stringstream ss(completedStr); // 입력 문자열을 스트링 스트림으로 변환
        string token; // 과목명을 저장할 변수

        while (getline(ss, token, ',')) { // 콤마(',')를 기준으로 과목명 추출
            trim(token); // 과목명 앞뒤 공백 제거
            if(!token.empty()) completedSet.insert(token); // 공백이 아닌 경우 집합에 추가
        }
    }

    // 학점 입력 받기
    int targetCredit;
    while (true) {
        cout << "수강하고 싶은 총 학점을 입력하세요: " << flush; // 사용자에게 입력 요청
        string creditInput; // 사용자 입력을 저장할 변수
        getline(cin, creditInput); // 한 줄 입력받기
        trim(creditInput); // 입력된 문자열의 앞뒤 공백 제거

        if(!isNumber(creditInput)) { // 입력이 숫자가 아닌 경우
            cout << "학점을 숫자로 입력하세요.\n"; // 오류 메시지 출력
            continue; // 다시 입력받기
        }
        targetCredit = stoi(creditInput); // 입력을 정수로 변환
        break; // 유효한 입력이므로 루프 종료
    }

    try {
        // 추천 과목 목록 생성: 입력된 학년, 이수한 과목, 목표 학점을 기반으로 추천
        auto recommended = container.recommendCourses(inputYear, completedSet, targetCredit);

        cout << "\n추천 과목 목록:\n"; // 추천 과목 목록 출력 시작 메시지
        for (auto c : recommended) { // 추천 과목들을 순회
            cout << *c << "\n"; // 각 과목 정보를 출력 (operator<< 오버로딩 활용)
        }

        // 추천 과목 목록을 recommended.txt 파일에 저장
        ofstream fout("recommended.txt");
        if(!fout.is_open()) { // 파일 열기에 실패한 경우
            throw runtime_error("recommended.txt 파일을 열 수 없습니다."); // 예외 발생
        }

        fout << "추천 과목 목록:\n"; // 파일에 출력 시작 메시지
        for (auto c : recommended) { // 추천 과목들을 순회
            fout << c->getName() << " (" << c->getCode() << ", "
                 << c->getCredit() << "학점, " << c->getYear() << "학년)\n"; // 과목 정보 형식화하여 파일에 저장
        }
        fout.close(); // 파일 스트림 닫기
        cout << "\n추천 결과가 recommended.txt에 저장되었습니다.\n"; // 성공 메시지 출력

    } catch (exception &e) { // 예외가 발생한 경우
        cerr << "\n오류 발생: " << e.what() << "\n"; // 오류 메시지 출력
    }

    // 프로그램 종료 전에 사용자 입력을 기다림
    cout << "프로그램을 종료하려면 엔터 키를 누르세요..." << endl; // 종료 메시지 출력 및 버퍼 플러시
    cin.get(); // 사용자로부터 엔터 키 입력을 기다림

    return 0; // 프로그램 정상 종료
}
