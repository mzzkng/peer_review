#include <algorithm>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <memory>
#include <string>
#include <vector>

class HendlerProcess{
private:
    static const int MAXUSER_ = 10000001;
    static const int MAXPEGES_ = 1001;
    std::vector<int> person_;
    std::vector<int> page_;
public:
    HendlerProcess()
    :person_(MAXUSER_, -123)
    ,page_(MAXPEGES_, 0){}
    ~HendlerProcess(){
        page_.clear();
        person_.clear();
    }
    /**
     * @brief  - регистраци состояния
     * @param ID - читеталь
     * @param PEGE  - колличесво прочитых страниц
     */
    void processing(int& ID, int& PEGE);
    /**
     * @brief
     * @param ID - номер читателя
     * @return  долю читателей
     */
    double cheek(int& ID);
};

void HendlerProcess::processing(int& realID, int& realPAGE) {
    auto ID = 0;
    realID == 0 ? ID = 0 : ID = realID - 1;
    auto lastPage = person_[ID];
    lastPage < 0 ? lastPage = 0 : lastPage = person_[ID] + 1;
    person_[ID] = realPAGE;
    for(int i = lastPage; i <= realPAGE; ++i){++page_[i];}
}

double HendlerProcess::cheek(int& realID){
    auto result = -0.8;
    auto ID = 0;
    realID == 0 ? ID = 0 : ID = realID - 1;
    if(person_[ID] < 0 ){
        result = .0;
    } else if (page_[person_[ID] - 1] == 1 && page_[0] == 1){
        result = 1.0;
    } else {
        result = (page_[0] - page_[person_[ID]]) *1.0 / (page_[0] - 1)* 1.0;
    }
    return result;
}

int main(){
    using namespace std::literals;
    HendlerProcess manager;
    std::size_t query_count;
    std::cin >> query_count;
    for(std::size_t i = 0 ; i < query_count; ++i){
        std::string query;
        int ID;
        std::cin >> query >> ID;
        if(query == "READ"s){
            int PAGE;
            std::cin>>PAGE;
            manager.processing(ID,PAGE);
        } else if (query == "CHEER"s){
            std::cout<< std::setprecision(6) << manager.cheek(ID)<<std::endl;
        }
    }
    return 0;
}

/*
Аторское решение:
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>


using namespace std;

class ReadingManager {
public:
    ReadingManager()
        : user_page_counts_(MAX_USER_COUNT_ + 1, -1)
        ,  // -1 значит, что не случилось ни одного READ
        page_achieved_by_count_(MAX_PAGE_COUNT_ + 1, 0) {
    }

    void Read(int user_id, int page_count) {
        UpdatePageRange(user_page_counts_[user_id] + 1, page_count + 1);
        user_page_counts_[user_id] = page_count;
    }

    double Cheer(int user_id) const {
        const int pages_count = user_page_counts_[user_id];
        if (pages_count == -1) {
            return 0;
        }
        const int user_count = GetUserCount();
        if (user_count == 1) {
            return 1;
        }
        // По умолчанию деление целочисленное, поэтому
        // нужно привести числитель к типу double.
        // Один из простых способов сделать это — умножить его на 1.0.
        return 1.0 - (page_achieved_by_count_[pages_count] - 1.0) / (user_count - 1.0);
    }

private:
    static const int MAX_USER_COUNT_ = 100'000;
    static const int MAX_PAGE_COUNT_ = 1'000;

    // Номер страницы, до которой дочитал пользователь <ключ>
    vector<int> user_page_counts_;
    // Количество пользователей, дочитавших (как минимум) до страницы <индекс>
    vector<int> page_achieved_by_count_;

    int GetUserCount() const {
        return page_achieved_by_count_[0];
    }

    void UpdatePageRange(int lhs, int rhs) {
        for (int i = lhs; i < rhs; ++i) {
            ++page_achieved_by_count_[i];
        }
    }
};

int main() {
    ReadingManager manager;

    int query_count;
    cin >> query_count;

    for (int query_id = 0; query_id < query_count; query_id++) {
        string query_type;
        cin >> query_type;
        int user_id;
        cin >> user_id;

        if (query_type == "READ"s) {
            int page_count;
            cin >> page_count;
            manager.Read(user_id, page_count);
        } else if (query_type == "CHEER"s) {
            cout << setprecision(6) << manager.Cheer(user_id) << endl;
        }
    }
}

*/