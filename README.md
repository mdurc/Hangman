


# Hangman



Game function:
- Guess single characters.
    - If guessing the entire word, if it is incorrect, it counts as a character that does not exist in the word.
    - Potentially a "hard" mode could exist where after one incorrect word guess, it is an immediate loss. This is not implemented.
- Game user data is stored in `user_data.txt`
- Game word data is stored in `word_bank/` with the categories in `categories.txt`, which holds the file name of the category, which contains all choosable words.


**Plan:**
- Bank of words
- Ascii art for the visual
- Leaderboard
    - local txt file that is used to fill the initial data structure, updated locally
        - user data file
    - Start with x number of points. Lose points every miss.
        - Starting point value will change based on # of unique characters in the word.
    - Highscore determined by streak of wins
- Login feature. Ask user at the start for a username. Used to keep track of individual highscores
    - If the username exists a separate local data file, ask for a password (which will be held in the data file)
        - Else ask them to create a password for their new account, add their information to the data file, along with a user's **high score**
    - Allow for logging out of their account, and logging back in, to the same, or different.
    - Allow account deletion
- add custom word



### Outcome
```
Login
Username: John
Password: 1234

Created New Account.
Welcome John!
======================
Menu:
1. Play
2. Add Word
3. Profile
4. View Leaderboard
5. Quit
Enter [1-5]:
```
- Where 1: Begin playing with a random category and random word from category
- Where 2: Add a word to an existing category or create a new category and word.
- Where 3: Shows user's statistics: highest streak, current streak, points, earliest stage win, total games, wins, losses, and win percentage
    - 3: Prompts options to rename your username, change your password, logout, clear data, or delete your account
- Where 4: Displays a leaderboard, ranking all users in the `user_data.txt` file by points.
