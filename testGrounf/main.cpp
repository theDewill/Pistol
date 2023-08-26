//
//  main.cpp
//  testGrounf
//
//  Created by Nomin Sendinu on 2023-07-09.
//

#include <iostream>
#include <ncurses.h>
using namespace std;

int main() {
    initscr();
    cbreak();  // Disable line buffering
    noecho();  // Disable echoing of typed characters

    // Enable keypad to capture function keys
    keypad(stdscr, TRUE);

    // Set non-blocking mode for getch()
    nodelay(stdscr, TRUE);

    // Loop to listen for keyboard events
    int ch;
    while (true) {
        ch = getch();
        if (ch == 'q' || ch == 'Q')
            break;

        // Process the key event
        // Example: Print the ASCII code of the pressed key
        printw("Key pressed: %d\n", ch);
        refresh();
    }

    // Clean up ncurses
    endwin();
    
}
