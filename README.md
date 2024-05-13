


# Hangman


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
- 1v1
- add custom word


Game function:
- Lives. Start with game over after one loss. After three correct games without a game over, earn a life.
- Guess single characters.
    - If guessing the entire word, if it is incorrect, it counts as a character that does not exist in the word.
    - Potentially a "hard" mode could exist where after one incorrect word guess, it is an immediate loss. This is not implemented.


Login
Username: 

then. (highscore is based on the login, user's data)

Highscore: null

Menu:
1. Play
2. 1v1
3. Add Word
4. View Leaderboard


