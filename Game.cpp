#include <iostream>
#include <string>
#include <cstdlib>
#include <limits> // for numeric_limits
#include <algorithm> // for transform

#ifdef _WIN32
#include <windows.h>
#define CLEAR_COMMAND "cls"
#else
#define CLEAR_COMMAND "clear"
#endif

// Function to set console text color (cross-platform)
void setConsoleColor(int color) {
#ifdef _WIN32
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
#else
    std::cout << "\033[" << color << "m";
#endif
}

// Function to reset console text color (cross-platform)
void resetConsoleColor() {
#ifdef _WIN32
    setConsoleColor(7); // Reset to default color
#else
    std::cout << "\033[0m";
#endif
}

// Function to display the introduction and ASCII art
void displayIntroduction() {
    // Detective ASCII art
    setConsoleColor(14); // Cyan color
    std::cout << "  DDD    EEEEE  TTTTT  EEEEE  CCCCC  TTTTT  IIIII  V   V  EEEEE\n";
    std::cout << "  D   D  E        T    E      C        T      I    V   V  E    \n";
    std::cout << "  D   D  EEEE     T    EEEE   C        T      I    V   V  EEEE \n";
    std::cout << "  D   D  E        T    E      C        T      I     V V   E    \n";
    std::cout << "  DDD    EEEEE    T    EEEEE  CCCCC    T    IIIII    V    EEEEE\n";
    resetConsoleColor();

    std::cout << "\nWelcome Detective!\n";
    std::cout << "You are on a mission to solve a murder mystery.\n";
    std::cout << "To unveil the truth, you must answer a series of riddles.\n";
    std::cout << "Be careful! You only have 3 chances (hearts) to answer incorrectly.\n\n";
}

// Function to check if two strings are close enough (ignoring case and spaces)
bool isCloseEnough(const std::string& userAnswer, const std::string& correctAnswer) {
    // Convert both answers to lowercase for case-insensitive comparison
    std::string userLower = userAnswer;
    std::transform(userLower.begin(), userLower.end(), userLower.begin(), ::tolower);

    std::string correctLower = correctAnswer;
    std::transform(correctLower.begin(), correctLower.end(), correctLower.begin(), ::tolower);

    // Check if the user's answer contains the correct answer or vice versa
    return userLower.find(correctLower) != std::string::npos || correctLower.find(userLower) != std::string::npos;
}

// Function to ask a riddle, receive user input, and check the answer
bool askRiddle(const std::string& question, const std::string& correctAnswer, int& hearts) {
    setConsoleColor(11); // Set color for the riddle question
    std::cout << "Riddle: " << question << "\n";
    resetConsoleColor();

    std::cout << "Hearts: ";
    setConsoleColor(12); // Set color for the hearts (red)
    for (int i = 0; i < hearts; ++i) {
        std::cout << "<3 "; // ASCII heart symbol
    }
    resetConsoleColor();
    std::cout << "\nYour answer: ";

    std::string userAnswer;
    std::getline(std::cin, userAnswer);

    // Remove spaces from the user's answer and the correct answer
    std::string strippedUserAnswer = userAnswer;
    strippedUserAnswer.erase(std::remove_if(strippedUserAnswer.begin(), strippedUserAnswer.end(), ::isspace), strippedUserAnswer.end());

    std::string strippedCorrectAnswer = correctAnswer;
    strippedCorrectAnswer.erase(std::remove_if(strippedCorrectAnswer.begin(), strippedCorrectAnswer.end(), ::isspace), strippedCorrectAnswer.end());

    bool isCorrect = strippedUserAnswer == strippedCorrectAnswer;

    if (!isCorrect && isCloseEnough(strippedUserAnswer, strippedCorrectAnswer)) {
        // Provide a hint or correct the answer
        std::cout << "Close! The answer is: " << correctAnswer << "\n";
    }

    // Clear the console
    system(CLEAR_COMMAND);

    // Re-print ASCII art
    displayIntroduction();

    return isCorrect;
}

// Main function
int main() {
    const int maxHearts = 3;
    int hearts = maxHearts;

    std::string riddles[] = {
        "I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?",
        "The more you take, the more you leave behind. What am I?",
        "I am taken from a mine, and shut up in a wooden case, from which I am never released, and yet I am used by almost every person. What am I?",
        "The person who makes it, sells it. The person who buys it never uses it. What is it?",
        "I fly without wings. I cry without eyes. Wherever I go, darkness follows me. What am I?",
        "The more fragile, the more it is used. What is it?",
        "I have keys but no locks. I have space but no room. You can enter, but you can't go inside. What am I?",
        "I am always hungry. I must always be fed. The finger I touch will soon turn red. What am I?",
        "I can be cracked, made, told, and played. What am I?",
        "I speak without a mouth and hear without ears. I have no body, but I come alive with the wind. What am I?"
    };

    std::string answers[] = {
        "an echo",
        "footsteps",
        "pencil lead",
        "a coffin",
        "a cloud",
        "an egg",
        "a keyboard",
        "fire",
        "a joke",
        "an echo"
    };

    displayIntroduction();

    for (int i = 0; i < sizeof(riddles) / sizeof(riddles[0]); ++i) {
        if (hearts == 0) {
            std::cout << "\nGame Over! You ran out of hearts. The murderer remains at large.\n";
            break;
        }

        if (askRiddle(riddles[i], answers[i], hearts)) {
            std::cout << "Correct! You are one step closer to solving the mystery.\n";
        }
        else {
            std::cout << "Incorrect! The murderer remains elusive.\n";
            --hearts;
            --i; // Repeat the same riddle
        }
    }

    if (hearts > 0) {
        std::cout << "\nCongratulations, Detective! You solved the murder mystery.\n";
    }

    return 0;
}
