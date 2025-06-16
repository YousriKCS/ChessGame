//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "game.h"

Game::Game() {
    setStartBord();
}

Game::~Game() {}

// Zet het bord klaar; voeg de stukken op de jusite plaats toe
void Game::setStartBord() {
    SchaakStuk* TorenWit1 = new Toren(wit);
    setPiece(7,0,TorenWit1);
    TorenWit1->setRow(7);
    TorenWit1->setColumn(0);
    SchaakStuk* TorenWit2 = new Toren(wit);
    setPiece(7,7,TorenWit2);
    TorenWit2->setRow(7);
    TorenWit2->setColumn(7);
    SchaakStuk* TorenZwart1 = new Toren(zwart);
    setPiece(0,0,TorenZwart1);
    TorenZwart1->setRow(0);
    TorenZwart1->setColumn(0);
    SchaakStuk* TorenZwart2 = new Toren(zwart);
    setPiece(0,7,TorenZwart2);
    TorenZwart2->setRow(0);
    TorenZwart2->setColumn(7);
    SchaakStuk* LoperWit1 = new Loper(wit);
    setPiece(7,2,LoperWit1);
    LoperWit1->setRow(7);
    LoperWit1->setColumn(2);
    SchaakStuk* LoperWit2 = new Loper(wit);
    setPiece(7,5,LoperWit2);
    LoperWit2->setRow(7);
    LoperWit2->setColumn(5);
    SchaakStuk* LoperZwart1 = new Loper(zwart);
    setPiece(0,2,LoperZwart1);
    LoperZwart1->setRow(0);
    LoperZwart1->setColumn(2);
    SchaakStuk* LoperZwart2 = new Loper(zwart);
    setPiece(0,5,LoperZwart2);
    LoperZwart2->setRow(0);
    LoperZwart2->setColumn(5);
    SchaakStuk* PaardWit1 = new Paard(wit);
    setPiece(7,6,PaardWit1);
    PaardWit1->setRow(7);
    PaardWit1->setColumn(6);
    SchaakStuk* PaardWit2 = new Paard(wit);
    setPiece(7,1,PaardWit2);
    PaardWit2->setRow(7);
    PaardWit2->setColumn(1);
    SchaakStuk* PaardZwart1 = new Paard(zwart);
    setPiece(0,6,PaardZwart1);
    PaardZwart1->setRow(0);
    PaardZwart1->setColumn(6);
    SchaakStuk* PaardZwart2 = new Paard(zwart);
    setPiece(0,1,PaardZwart2);
    PaardZwart2->setRow(0);
    PaardZwart2->setColumn(1);
    SchaakStuk* KoninginWit = new Koningin(wit);
    setPiece(7,3,KoninginWit);
    KoninginWit->setRow(7);
    KoninginWit->setColumn(3);
    SchaakStuk* KoninginZwart = new Koningin(zwart);
    setPiece(0,3,KoninginZwart);
    KoninginZwart->setRow(0);
    KoninginZwart->setColumn(3);
    SchaakStuk* KoningWit = new Koning(wit);
    setPiece(7,4,KoningWit);
    KoningWit->setRow(7);
    KoningWit->setColumn(4);
    SchaakStuk* KoningZwart = new Koning(zwart);
    setPiece(0,4,KoningZwart);
    KoningZwart->setRow(0);
    KoningZwart->setColumn(4);

    int i = 1;
    int h = 0;
    while (h< 8){
        SchaakStuk* PionZwart = new Pion(zwart);
        setPiece(i,h,PionZwart);
        PionZwart->setRow(i);
        PionZwart->setColumn(h);
        h++;
    }
    i = 6;
    h = 0;
    while(h < 8){
        SchaakStuk* PionWit = new Pion(wit);
        setPiece(i,h,PionWit);
        PionWit->setRow(i);
        PionWit->setColumn(h);
        h++;
    }

}

// Verplaats stuk s naar positie (r,k)
// Als deze move niet mogelijk is, wordt false teruggegeven
// en verandert er niets aan het schaakbord.
// Anders wordt de move uitgevoerd en wordt true teruggegeven
bool Game::move(SchaakStuk* s, int r, int k) {
    if (s->piece().type() == Piece::King) {
        // Check for checkmate and stalemate
        if (schaakmat(wit)) {
            return false;
        } else if (schaakmat(zwart)) {
            return false;
        } else if (pat(wit)) {
            return false;
        } else if (pat(zwart)) {
            return false;
        }
        vector<pair<int, int>> threatened_positions;
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (getPiece(i, j) && getPiece(i, j)->getKleur() != s->getKleur()) {
                    vector<pair<int, int>> threatened_pos = getPiece(i, j)->valid_moves(*this);
                    threatened_positions.insert(threatened_positions.end(), threatened_pos.begin(), threatened_pos.end());
                }
            }
        }
        if (find(threatened_positions.begin(), threatened_positions.end(), make_pair(r, k)) != threatened_positions.end()) {
            return false; // King cannot move to a threatened position
        }
    }
    // Store the original position of the piece
    int originalRow = s->getRow();
    int originalColumn = s->getColumn();

    // Move the piece temporarily to the new position
    setPiece(r, k, s);
    setPiece(originalRow, originalColumn, nullptr);
    s->setRow(r);
    s->setColumn(k);

    // Check for check after the move
    bool moveIsSafe = true;
    if (s->getKleur() == wit && schaak(wit)) {
        moveIsSafe = false;
    } else if (s->getKleur() == zwart && schaak(zwart)) {
        moveIsSafe = false;
    }

    // If the move is safe, update the game state
    if (moveIsSafe) {

            // Move the piece and update the game state
            setPiece(r, k, s);
            setPiece(originalRow, originalColumn, nullptr);
            s->setRow(r);
            s->setColumn(k);


            return true;
        }

    // If the move is not safe, restore the original position of the piece
    setPiece(originalRow, originalColumn, s);
    setPiece(r, k, nullptr);
    s->setRow(originalRow);
    s->setColumn(originalColumn);

    return false;
}




// Geeft true als kleur schaak staat
bool Game::schaak(zw kleur) {
    for (int i = 0; i < 8; i++) {
        for (int k = 0; k < 8; k++) {
            SchaakStuk* king = getPiece(i, k);
            if (king != nullptr && king->piece().type() == Piece::King && king->getKleur() == kleur) {
                for (auto& square : bord) {
                    SchaakStuk* piece = square.second;
                    if (piece != nullptr && piece->getKleur() != kleur) {
                        vector<pair<int, int>> valid_moves = piece->valid_moves(*this);
                        for (auto move : valid_moves) {
                            if (move == make_pair(i, k)) {
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

bool Game::schaakmat(zw kleur) {
    // if schaak & no moves left for the king
    if (schaak(kleur) && !lastMoves(kleur)){
        // Schaakmat
        return true;
    }
    // Otherwhise if there are moves left schaakmat is false
    return false;

}



// Geeft true als kleur pat staat
// (pat = geen geldige zet mogelijk, maar kleur staat niet schaak;
// dit resulteert in een gelijkspel)
bool Game::pat(zw kleur) {
    // if schaak & no moves left for the king
    if (!schaak(kleur) && !lastMoves(kleur)){
        // Schaakmat
        return true;
    }
    // Otherwhise if there are moves left schaakmat is false
    return false;

}

// Geeft een pointer naar het schaakstuk dat op rij r, kolom k staat
// Als er geen schaakstuk staat op deze positie, geef nullptr terug
SchaakStuk* Game::getPiece(int r, int k) {
    SchaakStuk* s = bord[{r,k}];
    if (s== NULL){
        return nullptr;
    }
    // Hier komt jouw code om op te halen welk stuk op rij r, kolom k staat
    return s;
}

// Zet het schaakstuk waar s naar verwijst neer op rij r, kolom k.
// Als er al een schaakstuk staat, wordt het overschreven.
// Bewaar in jouw datastructuur de *pointer* naar het schaakstuk,
// niet het schaakstuk zelf.
void Game::setPiece(int r, int k, SchaakStuk* s)
{
    bord[{r,k}] = s;
    // Hier komt jouw code om een stuk neer te zetten op het bord
}


bool Game::lastMoves(zw kleur) {
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            SchaakStuk* piece = getPiece(i, j);
            if (piece != nullptr && piece->getKleur() == kleur) {
                vector<pair<int, int>> validMoves = piece->valid_moves(*this);
                for (const auto& move : validMoves) {
                    // Simulate the move temporarily and check if king is still in check
                    SchaakStuk* originalTarget = getPiece(move.first, move.second);
                    setPiece(move.first, move.second, piece);
                    setPiece(i, j, nullptr);

                    bool isInCheck = schaak(kleur); // Check if king is in check

                    setPiece(i, j, piece); // Restore original position
                    setPiece(move.first, move.second, originalTarget); // Restore original target

                    if (!isInCheck) {
                        return true; // At least one move found
                    }
                }
            }
        }
    }
    return false; // No legal moves found
}

void Game::clearbord() {
    bord.clear();

}

const map<pair<int, int>, SchaakStuk *> &Game::getBord() const {
    return bord;
}

void Game::setBord(const map<pair<int, int>, SchaakStuk *> &bord) {
    // Clear the current game state
    clearbord();

    // Iterate through the provided bord map and update the game state
    for (const auto &entry : bord) {
        pair<int, int> position = entry.first;
        SchaakStuk *piece = entry.second;

        if (piece) {
            // Set the piece's position and update the game state
            piece->setRow(position.first);
            piece->setColumn(position.second);
            setPiece(position.first, position.second, piece);
        }
    }
}










