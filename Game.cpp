
#include <bits/stdc++.h>
#define STAGE_0 "art/stage_0.txt"

class Game{
public:
    Game(const std::vector<std::string>& categories): stage(STAGE_0){
        srand(time(0));

        category = categories[rand() % categories.size()];
        std::string fname = "word_bank/"+category+".txt";

        std::ifstream word_options(fname);
        if(!word_options.is_open()){
            std::cerr << "File not found: " << fname << std::endl;
            exit(1);
        }

        std::vector<std::string> words;
        while(word_options >> filled){
            words.push_back(filled);
        }
        word_options.close();
        filled = words[rand() % words.size()];

        int z=filled.size();
        for(int i=0;i<z*2;++i){
            unfilled.push_back((i%2==0)?'_':' ');
            if(i<z){
                char_indices[std::tolower(filled[i])].push_back(i);
            }
        }
        game_points = 100*char_indices.size();
        // for rarer letters, add more value:
        std::vector<char> rare = {'q', 'z', 'x', 'j', 'k', 'v', 'p', 'y', 'g'};
        for(char& c: rare){
            game_points+=50 * (char_indices.find(c)!=char_indices.end());
        }
    }

    // when stage 6 is reached. User loses
    bool next_stage(){
        int x = stage[10]-'0'+1;
        stage[10]=x+'0';
        return x!=6;
    }

    void start_game(User& user);
    void game_lost(User& user)const{
        CLEAR_CONSOLE
        user.lose();
        std::cout << *this << "YOU LOSE! THE WORD WAS -> " << filled << std::endl;
        std::cout << "Highest Streak -> " << user.get_high() << std::endl;
    }
    void game_won(User& user)const{
        CLEAR_CONSOLE
        user.win(game_points,stage[10]-'0');
        std::cout << *this << filled << "\nYOU WON!" << std::endl;
        std::cout << user.get_name() << ", your streak is -> " << user.get_streak() << std::endl;
        std::cout << "Points earned: " << game_points << ", total points -> " << user.get_points() << std::endl;
    }


    friend std::ostream& operator<<(std::ostream& os, const Game& g);
private:
    std::string filled, unfilled, category;
    std::unordered_map<char,std::vector<int>> char_indices;
    std::unordered_set<char> guessed_letters;
    std::unordered_set<std::string> guessed_words;
    std::string stage;
    int game_points;
};

bool compare(const std::string& a, const std::string& b){
    int z=a.size();
    if(z!=b.size()) return false;
    for(int i=0;i<z;++i){
        if(a[i]!=std::tolower(b[i])){
            return false;
        }
    }
    return true;
}

void str_to_lower(std::string& a){
    int z=a.size();
    for(int i=0;i<z;++i){ a[i]=std::tolower(a[i]); }
}

void print_guesses(const std::unordered_set<char>& l,
        const std::unordered_set<std::string>& w){
    std::cout << "Guessed letters:";
    for(const char& c: l){ std::cout << ' ' << c; }
    std::cout << std::endl;
    std::cout << "Guessed words:";
    for(const std::string& s: w){ std::cout << ' ' << s; }
    std::cout << std::endl;
}

void Game::start_game(User& user){
    while(!char_indices.empty()){
        CLEAR_CONSOLE
        std::cout << "FOR DEBUGGING: " << filled << ", curr points: " << game_points << std::endl;
        std::cout << *this << '\n';

        print_guesses(guessed_letters, guessed_words);

        std::cout << unfilled << '\n';

        std::string guess;
        while(true){
            std::cout << "Guess letter or entire word(EXIT to leave): ";

            std::cin >> guess;
            if(guess=="EXIT"){ return; }

            int gsize=guess.size();
            str_to_lower(guess);

            if(gsize==1 && !guessed_letters.insert(guess[0]).second){
                // already guessed this letter
                std::cout << "Already guessed this letter!" << std::endl;
                continue;
            }else if(gsize>1 && !guessed_words.insert(guess).second){
                std::cout << "Already guessed this word!" << std::endl;
                continue;
            }
            break;
        }


        if(guess.size()!=1){
            // makes guess fully lowercase
            if(compare(guess,filled)){
                this->game_won(user);
                return;
            }else if(!this->next_stage()){
                this->game_lost(user);
                return;
            }
            // continue. For harder version, return false, or: return guess==filled
            game_points=std::max(0,game_points-100);
            continue;
        }

        // Search for the lowercase of the word.
        // "char_indices" will have lowercase versions of the word in the word bank.
        std::unordered_map<char,std::vector<int>>::iterator itr;
        itr=char_indices.find(guess[0]);
        if(itr==char_indices.end()){
            if(!this->next_stage()){
                this->game_lost(user);
                return;
            }
            game_points=std::max(0,game_points-((game_points>200) ? 50 : 25));

        }else{
            int z=itr->second.size();
            for(int i=0;i<z;++i){
                unfilled[itr->second[i]*2] = filled[itr->second[i]];
            }
            char_indices.erase(itr);
        }
    }
    this->game_won(user);
}


std::ostream& operator<<(std::ostream& os, const Game& g){
    os << "======================\n";
    os << "Category: " << g.category << '\n';

    std::ifstream file_stream(g.stage);
    if(!file_stream.is_open()){
        std::cerr << "File not found: " << g.stage << std::endl;
        exit(1);
    }

    std::string ascii_stage((std::istreambuf_iterator<char>(file_stream)), std::istreambuf_iterator<char>());
    os << ascii_stage;
    return os;
}
