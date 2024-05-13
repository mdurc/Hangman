
#define DATA_FILE "user_data.txt"
#define CLEAR_CONSOLE std::cout << "\033[2J\033[H";

#include <bits/stdc++.h>
#include "User.cpp"
#include "Game.cpp"


void parse_user_data(const std::string& data_file,
                     std::unordered_map<std::string, User>& user_map) {
    std::ifstream user_data(data_file);
    if (!user_data.is_open()) {
        std::cerr << "File not found: " << data_file << std::endl;
        exit(1);
    }
    std::string name, pass;
    int hs, strk, pts, earliest_win, wins, losses;

    while (user_data >> name >> pass >> hs >> strk >> pts >> earliest_win >> wins >>
           losses) {
        user_map.insert(
            {name, User(name, pass, hs, strk, pts, earliest_win, wins, losses)});
    }
    user_data.close();
}

void add_to_user_data(const std::string& data_file, const User& u) {
    std::ofstream data_os;
    data_os.open(data_file, std::ios_base::app);
    data_os << u.get_name() << ' ' << u.get_pass() << ' ' << u.get_high() << std::endl;
    data_os.close();
}

void rewrite_user_data(const std::unordered_map<std::string, User>& user_map) {
    std::ofstream user_data(DATA_FILE);
    for (const std::pair<std::string, User>& u : user_map) {
        u.second.write_to_user_data(user_data);
    }
    user_data.close();
}

User& login(std::unordered_map<std::string, User>& user_map) {
    std::string name, password;

    std::cout << "Login\nUsername: ";
    std::cin >> name;
    std::cout << "Password: ";
    std::cin >> password;

    std::pair<std::unordered_map<std::string, User>::iterator, bool> ret;
    ret = user_map.insert({name, User(name, password)});
    if (ret.second) {
        std::cout << "\nCreated New Account.\nWelcome " << name << '!' << std::endl;
        add_to_user_data(DATA_FILE, ret.first->second);
    } else {
        while (password != ret.first->second.get_pass()) {
            std::cout << "Invalid Password. Try again." << std::endl;
            std::cout << "Password: ";
            std::cin >> password;
        }
        std::cout << "\nWelcome back " << name << '!' << std::endl;
    }
    return ret.first->second;
}

void display_leaderboard(const std::unordered_map<std::string, User>& user_map) {
    std::set<User> leaderboard;
    for (const std::pair<std::string, User>& u : user_map) {
        leaderboard.insert(u.second);
    }
    for (const User& u : leaderboard) {
        std::cout << u << std::endl;
    }
}

int display_menu() {
    std::cout << "======================\n";
    std::cout << "Menu:\n"
                 "1. Play\n"
                 "2. Add Word\n"
                 "3. Profile\n"
                 "4. View Leaderboard\n"
                 "5. Quit"
              << std::endl;

    std::string selection;
    while (true) {
        std::cout << "Enter [1-5]: ";
        std::cin >> selection;
        try {
            int val = std::stoi(selection);
            if (val >= 1 && val <= 5) {
                return val;
            }
        } catch (std::exception e) {
            std::cerr << "Try again" << std::endl;
        }
    }
}

int profile_options(User& user, std::unordered_map<std::string, User>& user_map) {
    int action;
    while (true) {
        std::cout << "1. Rename\n"
                     "2. Change Password\n"
                     "3. Logout\n"
                     "4. Clear Data\n"
                     "5. Delete Account\n"
                     "6. Back to Menu\n"
                     "\nEnter[1,6]: ";
        std::cin >> action;
        if (action == 1) {
            std::string new_name;
            while(true){
                std::cout << "What would you like your new username to be? ";
                std::cin >> new_name;
                if(user.get_name()==new_name || user_map.find(new_name)==user_map.end()){
                    user.set_name(new_name);
                    break;
                }else{
                    std::cout << "Name is already in use." << std::endl;
                }
            }
        }
        else if (action == 2) {
            while(true){
                std::string temp_pass;
                std::cout << "Confirm old password: ";
                std::cin >> temp_pass;
                if (temp_pass != user.get_pass()) {
                    std::cout << "Incorrect" << std::endl;
                    continue;
                }
                std::cout << "New password: ";
                std::cin >> temp_pass;
                user.set_pass(temp_pass);
                break;
            }
        } else if (action == 4 || action == 5) {
            char confirmation;
            std::cout << "Are you sure you want to do this? (y,n) ";
            std::cin >> confirmation;
            if (confirmation != 'y') { continue; }

            if (action == 4) { user.reset(); }
            else { user_map.erase(user.get_name()); }
        }
        return action;
    }
}

void add_new_word(std::vector<std::string>& categories) {
    // either add word to existing category's file, or create new file and word.
    std::cout << "======================\n";
    std::cout << "Would you like to add to an existing category or "
                 "create a new one?\n";
    int i = 0, z = categories.size();
    for (; i < z; ++i) {
        std::cout << i + 1 << ". " << categories[i] << '\n';
    }

    std::cout << z+1 << ". Create new category\nEnter [1," << z+1 << "]: ";
    std::cin >> i;

    if (i == z+1) {
        // new category
        std::string temp;

        std::cout << "New category: ";
        std::cin >> temp;
        categories.push_back(temp);

        std::cout << "New word: ";
        std::cin >> temp;

        std::ofstream os;
        os.open("word_bank/" + categories.back() + ".txt", std::ios_base::app);
        os << temp << std::endl;
        os.close();

        os.open("word_bank/categories.txt", std::ios_base::app);
        os << categories.back() << std::endl;
        os.close();
    } else {
        // open category file and append new word
        std::cout << "New word: ";
        std::string new_word;
        std::cin >> new_word;

        std::ofstream word_bank_os;
        word_bank_os.open("word_bank/" + categories[i-1] + ".txt", std::ios_base::app);
        word_bank_os << new_word << std::endl;
        word_bank_os.close();
    }
    std::cout << "Word Added!" << std::endl;
}

int main() {
    std::string line;

    // intro display
    CLEAR_CONSOLE
    std::ifstream title("art/title.txt");
    if (!title.is_open()) {
        std::cerr << "File not found: art/title.txt" << std::endl;
        exit(1);
    }
    while (std::getline(title, line)) {
        std::cout << line << std::endl;
    }
    title.close();

    // parse the different category_in for the words
    std::vector<std::string> categories;
    std::ifstream category_in("word_bank/categories.txt");
    if (!category_in.is_open()) {
        std::cerr << "File not found: word_bank/categories.txt" << std::endl;
        exit(1);
    }
    while (std::getline(category_in, line)) {
        categories.push_back(line);
    }
    category_in.close();

    // parse user data. create objects. store in set
    // we need to be able to access a user's information, given the name
    std::unordered_map<std::string, User> user_map;
    parse_user_data(DATA_FILE, user_map);

    bool run_game = true;
    while (run_game) {
        std::cout << std::endl;
        User& user = login(user_map);
        bool logged_in = true;
        while (logged_in) {
            int action = display_menu();
            if (action == 1) {
                // play
                Game round(categories);
                round.start_game(user);
            } else if (action == 2) {
                CLEAR_CONSOLE
                // new category?
                // add word
                // rewrite's word_bank data in function
                add_new_word(categories);
            } else if (action == 3) {
                CLEAR_CONSOLE
                // view personal stats. edit user information
                user.print_stats();
                int profile_action = profile_options(user, user_map);
                CLEAR_CONSOLE
                if (profile_action==3 || profile_action==5) {
                    //Account logout, or Account deleted
                    logged_in=false;
                }
            } else if (action == 4) {
                CLEAR_CONSOLE
                // view leaderboard
                display_leaderboard(user_map);
            } else {
                // exit game
                run_game = logged_in = false;
            }
            rewrite_user_data(user_map);
        }
    }

    return 0;
}
