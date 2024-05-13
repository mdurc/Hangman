#include <bits/stdc++.h>

class User{
public:
    // data file format:
    // name password highest streak streak points earliest_win win_count loss_count
    User(const std::string& name, const std::string& pass, int hs=0, int strk=0, int pts=0,
         int earliest_win=0, int wins=0, int losses=0)
        : m_name(name),
          m_password(pass),
          m_highest_streak(hs),
          m_streak(strk),
          m_points(pts),
          m_earliest_win(earliest_win),
          win_count(wins),
          loss_count(losses) {}

    void set_name(const std::string& new_name){ m_name=new_name; }
    void set_pass(const std::string& new_pass){ m_password=new_pass; }
    const std::string& get_name()const{ return m_name; }
    const std::string& get_pass()const{ return m_password; }
    int get_high()const{ return m_highest_streak; }
    int get_streak()const{ return m_streak; }
    int get_points()const{ return m_points; }

    void print_stats()const{
        std::cout << "======================\n";
        std::cout<< "User: " << m_name << '\n';
        std::cout<< "\tHighest Streak: " << m_highest_streak << '\n';
        std::cout<< "\tCurrent Streak: " << m_streak << '\n';
        std::cout<< "\tPoints: " << m_points << '\n';
        std::cout<< "\tEarliest Stage Win: " << m_earliest_win << '\n';
        std::cout<< "\tTotal Games: " << win_count+loss_count <<
                    "\n\tWins: " << win_count << "\n\tLosses: " << loss_count << '\n';
        std::cout<< "\tWin Percentage: " << (100*win_count)/(win_count+loss_count) << "%\n";
    }
    
    void win(int points, int misses){
        m_highest_streak = std::max(m_highest_streak, ++m_streak);
        m_points+=points;
        m_earliest_win = std::min(m_earliest_win, misses);
        ++win_count;
    }
    void lose(){ m_streak=0; ++loss_count; }

    void reset(){
        m_points=m_highest_streak=m_streak=m_earliest_win=win_count=loss_count=0;
    }

    std::ostream& write_to_user_data(std::ostream& os)const;

    friend bool operator<(const User& a, const User& b);
    friend std::ostream& operator<<(std::ostream& os, const User& user);
private:
    std::string m_name, m_password;
    int m_points, m_highest_streak, m_streak, m_earliest_win;
    int win_count, loss_count;
};


std::ostream& User::write_to_user_data(std::ostream& os)const{
    os<<m_name<<' '<<m_password<<' '<<m_highest_streak<<' '<<m_streak<<' '<<m_points<<
        ' '<<m_earliest_win<<' '<<win_count<<' '<<loss_count<<std::endl;
    return os;
}

bool operator<(const User& a, const User& b){
    if(a.m_highest_streak!=b.m_highest_streak){
        return a.m_highest_streak > b.m_highest_streak;
    }
    return a.m_name < b.m_name;
}

std::ostream& operator<<(std::ostream& os, const User& user){
    os << "======================\n";
    os << "Name: " << user.m_name << '\n';
    os << "Highest Streak: " << user.m_highest_streak << '\n';
    os << "======================" << std::endl;
    return os;
}

