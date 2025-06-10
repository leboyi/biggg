#ifndef GAME_H
#define GAME_H

#include "Player.h"

class Game {
public:
void start(); // 選擇模式並開始遊戲
private:
void play1(); // 模式1邏輯
void play2(); // 模式2邏輯
void playFunction1(Player& player, int playerNumber);
void playFunction2(Player& player1, Player& player2);
void whoWin(Player& p1, Player& p2);
};

#endif
