//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#ifndef SCHAKEN_SCHAAKSTUK_H
#define SCHAKEN_SCHAAKSTUK_H
#include <guicode/chessboard.h>

class Game;
using namespace std;


enum zw{zwart,wit};

class SchaakStuk {
private:
    int column;
    int row;
    bool selected;
public:
    int getColumn() const {
        return column;
    }

    void setColumn(int column) {
        SchaakStuk::column = column;
    }

    int getRow() const {
        return row;
    }

    void setRow(int row) {
        SchaakStuk::row = row;
    }

    SchaakStuk(){
        selected = false;
    }
    bool isSelected() {
        return selected;
    }
    void setSelected(bool b) {
        selected = b;
    }
    SchaakStuk(zw kleur): kleur(kleur) {}

    virtual Piece piece() const=0;      // Verander deze functie niet!
                                        // Deze functie wordt gebruikt door
                                        // setItem(x,y,SchaakStuk*) van
                                        // SchaakGUI

    zw getKleur() const { return kleur; }
    virtual vector<pair<int,int>> valid_moves(Game& g){
        return{};

    }

public:
   virtual const string &getType() const {
        return type;
    }
private:
    zw kleur;
    string type;
};

class Pion:public SchaakStuk {
public:
    Pion(zw kleur):SchaakStuk(kleur) {}
    virtual Piece piece() const override {
        return Piece(Piece::Pawn,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) override;
    string getType()  { return "Pion"; }

};

class Toren:public SchaakStuk {
public:
    Toren(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Rook,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) override;
    string getType()  { return "Toren"; }

};

class Paard:public SchaakStuk {
public:
    Paard(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Knight,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) override;
    string getType()  { return "Paard"; }
};

class Loper:public SchaakStuk {
public:
    Loper(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::Bishop,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) override;
    string getType()  { return "Loper"; }
};

class Koning:public SchaakStuk {
public:
    Koning(zw kleur):SchaakStuk(kleur) {}

    Piece piece() const override {
        return Piece(Piece::King,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) ;
    string getType()  { return "Koning"; }
};

class Koningin:public SchaakStuk {
public:
    Koningin(zw kleur):SchaakStuk(kleur) {}


    Piece piece() const override {
        return Piece(Piece::Queen,getKleur()==wit?Piece::White:Piece::Black);
    }
    vector<pair<int,int>> valid_moves(Game& g) override;
    string getType()  { return "Koningin"; }
};


#endif //SCHAKEN_SCHAAKSTUK_H
