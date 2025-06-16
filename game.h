//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_GAME_H
#define SCHAKEN_GAME_H

#include "SchaakStuk.h"
#include <map>
using namespace std;

class Game {
// variabelen om de status van het spel/bord te bewaren

public:
    Game();
    ~Game();

    bool move(SchaakStuk* s,int r, int k); // Verplaats stuk s naar rij r en kolom k


    bool schaak(zw kleur);
    bool schaakmat(zw kleur);
    bool pat(zw kleur);
    void setStartBord();
    void clearbord();

    SchaakStuk* getPiece(int r, int k);
    void setPiece(int r, int k, SchaakStuk* s);
    bool lastMoves(zw kleur);

    const map<pair<int, int>, SchaakStuk *> &getBord() const;

    void setBord(const map<pair<int, int>, SchaakStuk *> &bord);
private:
    // Hier zet jij jouw datastructuur neer om het bord te bewaren
    map<pair<int,int>, SchaakStuk*> bord;



};


#endif //SCHAKEN_GAME_H
