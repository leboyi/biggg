#include "Game.h"
#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

void Game::start() {
    int playMode;
    cout << "玩法(代碼)1：兩人分開猜密碼，兩者猜密碼次數較小者獲勝" << endl;
    cout << "玩法(代碼)2：兩人同時猜密碼，猜中者獲勝(不計算猜的次數)" << endl;
    cout << "請輸入模式代碼：";
    cin >> playMode;

    if (playMode == 1)
        play1();
    else if (playMode == 2)
        play2();
    else
        cout << "偵測輸入的值為1或2以外的值，無法開始遊戲" << endl;

    cout << "Game over" << endl;
}

void Game::whoWin(Player& p1, Player& p2) {
    if (p1.isFailed() || p2.isFailed()) {
        if (p1.isFailed() && p2.isFailed()) cout << "Draw" << endl;
        else if (p1.isFailed()) cout << "Player2 win" << endl;
        else cout << "Player1 win" << endl;
    }
    else {
        if (p1.getGuessTimes() < p2.getGuessTimes()) cout << "Player1 win" << endl;
        else if (p1.getGuessTimes() > p2.getGuessTimes()) cout << "Player2 win" << endl;
        else cout << "Draw" << endl;
    }
}

void Game::playFunction1(Player& player, int playerNumber) {
    srand(time(0));
    bool isFinish = false;
    int max = 100, min = 0;
    int guessNumber = rand() % 101;
    int playerGuessNumber = -1;

    while (!isFinish) {
        while (!(playerGuessNumber == guessNumber)) {
            cout << "Player" << playerNumber << " enter your guess number(range in " << min << "~" << max << "): ";
            cin >> playerGuessNumber;
            if (playerGuessNumber < min || playerGuessNumber > max) {
                cout << "Out of range, please enter again" << endl;
            }
            else {
                if (playerGuessNumber < guessNumber) {
                    min = playerGuessNumber + 1;
                    if (min == max) {
                        cout << "Ultimate password is " << min << ", you failed." << endl;
                        isFinish = true;
                        player.setFailed(true);
                        player.plusGuessTimes();
                        break;
                    }
                    else {
                        cout << "Not ultimate password , please try again." << endl;
                        player.plusGuessTimes();
                    }
                }
                else if (playerGuessNumber > guessNumber) {
                    max = playerGuessNumber - 1;
                    if (min == max) {
                        cout << "Ultimate password is " << max << ", so you failed." << endl;
                        isFinish = true;
                        player.plusGuessTimes();
                        player.setFailed(true);
                        break;
                    }
                    else {
                        cout << "Not ultimate password , please try again." << endl;
                        player.plusGuessTimes();
                    }
                }
                else {
                    cout << "Congratulations! ultimate password is " << guessNumber << endl;
                    isFinish = true;
                    player.plusGuessTimes();
                }
            }
        }
    }
}

void Game::playFunction2(Player& player1, Player& player2) {
    srand(time(0));
    bool isFinish = false;
    int max = 100, min = 0;
    int guessNumber = rand() % 101;
    int playerGuessNumber = -1;
    Player playerArray[2] = { player1, player2 };

    while (!isFinish) {
        for (int i = 0; !(playerGuessNumber == guessNumber); i++) {
            cout << "Player" << i % 2 + 1 << " please enter your guess number(range in " << min << "~" << max << ") : ";
            cin >> playerGuessNumber;
            if (playerGuessNumber < min || playerGuessNumber > max) {
                cout << "Out of range, please enter again" << endl;
            }
            else {
                if (playerGuessNumber < guessNumber) {
                    min = playerGuessNumber + 1;
                    if (min == max) {
                        cout << "Ultimate password is " << min << ", so you failed." << endl;
                        isFinish = true;
                        playerArray[i % 2].setFailed(true);
                        break;
                    }
                    else {
                        cout << "Not ultimate password , please try again." << endl;
                    }
                }
                else if (playerGuessNumber > guessNumber) {
                    max = playerGuessNumber - 1;
                    if (min == max) {
                        cout << "Ultimate password is " << max << ", so you failed." << endl;
                        isFinish = true;
                        playerArray[i % 2].setFailed(true);
                        break;
                    }
                    else {
                        cout << "Not ultimate password , please try again." << endl;
                    }
                }
                else {
                    playerArray[(i + 1) % 2].setFailed(true);
                    cout << "Congratulations! ultimate password is " << guessNumber << endl;
                    isFinish = true;
                }
            }
        }
    }
    whoWin(playerArray[0], playerArray[1]);
}

void Game::play1() {
    string name1, name2;
    cout << "Enter player1's name: ";
    cin >> name1;
    cout << "Enter player2's name: ";
    cin >> name2;

    Player player1(name1);
    Player player2(name2);
    playFunction1(player1, 1);
    playFunction1(player2, 2);

    cout << "Player1:";
    player1.print();
    cout << "Player2:";
    player2.print();
    whoWin(player1, player2);
}

void Game::play2() {
    string name1, name2;
    cout << "Enter player1's name: ";
    cin >> name1;
    cout << "Enter player2's name: ";
    cin >> name2;

    Player player1(name1);
    Player player2(name2);
    playFunction2(player1, player2);
}
