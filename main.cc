#include <iostream>
#include <stdexcept>
#include <fstream>
#include "floorDisplay.h"
#include "chamber.h"
#include "floor.h"
#include <ncurses.h>
#include <unistd.h>

using namespace std;

string getStr(){ // two char
    string ss{};
    ss += getch();
    ss += getch();
    return ss;
}

int main(int argc, char* argv[]) {
    unique_ptr<ifstream> map;
    try{
        if (argc < 2 || argv[1][0] == '-') {
            map = make_unique<ifstream>("cc3kfloor.txt");
        }
        else map = make_unique<ifstream>(argv[1]);
        shared_ptr<Floor> floor = make_shared<Floor>(Floor{});
        floor->init(move(map));

        initscr(); // ncurses
        
        keypad(stdscr, true);

        printw("Choose Character: \n");
        printw(" 's' for Shade, 'd' for Drow, 'v' for Vampire, 'g' for Goblin, 't' for Troll.\n");
        printw("Your choice: ");

        char c = getch();
        floor->generatePC(c);

        // floorDisplay.h
        FloorDisplay display {floor};
        floor->generate();
        usleep(1500000);
        noecho();
        display.display();
        refresh();

        wchar_t command;
        char cm;
        char mode = 'm'; // m is default mode, m for move, u for potion, a for attack, q for quit

        while ((mode != 'q') && (!floor->getEnd())) {
            char * ss;
            string str{};
            command = getch();
            move(8, 30); //move the cursor to the right place

            switch(command){
                case 'w':
                case KEY_UP:
                    if (mode == 'm')
                    floor->PCAction('m', "no");
                    else if (mode == 'a'){
                        floor->PCAction('a', "no");
                    }
                    else floor->PCAction('u', "no");
                    mode = 'm';
                    break;

                case 's':
                case KEY_DOWN:
                    if (mode == 'm')
                    floor->PCAction('m', "so");
                    else if (mode == 'a'){
                        floor->PCAction('a', "so");
                    }
                    else floor->PCAction('u', "so");
                    mode = 'm';
                    break;

                case 'A':
                case KEY_LEFT:
                    if (mode == 'm')
                    floor->PCAction('m', "we");
                    else if (mode == 'a'){
                        floor->PCAction('a', "we");
                    }
                    else floor->PCAction('u', "we");
                    mode = 'm';
                    break;

                case 'd':
                case KEY_RIGHT:
                    if (mode == 'm')
                    floor->PCAction('m', "ea");
                    else if (mode == 'a'){
                        floor->PCAction('a', "ea");
                    }
                    else floor->PCAction('u', "ea");
                    mode = 'm';
                    break;
                case KEY_EXIT:
                case 'q':
                    clear(); // clears the screen
                    mvprintw(30, 30, "You lose!\n"); // cursor move to (x, y) and print
                    endwin();
                    mode = 'q';
                    break;

                case 'r':
                    clear();
                    display.display();
                    echo();
                    printw("Choose Character: \n");
                    printw(" 's' for Shade, 'd' for Drow, 'v' for Vampire, 'g' for Goblin, 't' for Troll.\n");
                    printw("Your choice: ");
                    noecho();
                    refresh();
                    c = getch();
                    floor->reset(1);
                    floor->generatePC(c);
                    floor->generate();
                    display.display();
                    mode = 'm';
                    break;

                case 'u':
                    /*
                    str = getStr();
                    if (str == "no" || str == "so" || str == "ea" || str == "we" || str == "nw" || str == "se" || str == "sw" || str == "ne"){
                        floor->PCAction('u', ss);
                        display.display();
                    }
                    */
                    mode = 'u';
                    break;

                case 'a':
                    /*
                    str = getStr();
                    if (str == "no" || str == "so" || str == "ea" || str == "we" || str == "nw" || str == "se" || str == "sw" || str == "ne"){
                        floor->PCAction('a', ss);
                    }
                    display.display();
                    */
                    mode = 'a';
                    break;
                                
                case 'f':
                    floor->setEnemyStop();
                    display.display();
                    mode = 'm';
                    break;

            }
            refresh();
            noecho();
            display.display();
            refresh();
        }

        endwin();

    }
    catch(ifstream::failure){
        cerr << "infile not readable " << endl;
    }
    catch(exception e){
        cerr << e.what() << endl;
    }

}

