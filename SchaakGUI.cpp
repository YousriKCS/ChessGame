//
// Created by toonc on 12/17/2021.
//

#include "SchaakGUI.h"
#include "guicode/message.h"
#include "guicode/fileIO.h"
using namespace std;
// Constructor
SchaakGUI::SchaakGUI():ChessWindow(nullptr) {
    g.setStartBord();
    update();

}

// Deze functie wordt opgeroepen telkens er op het schaakbord
// geklikt wordt. x,y geeft de positie aan waar er geklikt
// werd; r is de 0-based rij, k de 0-based kolom
void SchaakGUI::clicked(int r, int k) {
    //Eerste spel wordt opgeslagen om te undo en redo commands te balanceren
    bool first = true;
    if (first) {
        movesHistory.push_back(g.getBord());
    }
    if (selected == nullptr) {
        selected = g.getPiece(r, k);

        if (selected == nullptr) {
            // Display an error message if no piece is selected
            message("No piece selected. Click on a valid piece.");
            return;
        }

        if (selected->getKleur() != turn) {
            message("Wrong color selected.");
            selected = nullptr;
            return;
        }

        setTileSelect(r, k, true);
        vector<pair<int, int>> validMoves = selected->valid_moves(g);
        for (auto move: validMoves) {
            if (displayMoves()) {
                setTileFocus(move.first, move.second, true);
            }
        }
    } else {
        vector<pair<int, int>> validMoves = selected->valid_moves(g);
        if (::find(validMoves.begin(), validMoves.end(), make_pair(r, k)) != validMoves.end()) {
            // save previous location of the chess piece
            int prev_r = selected->getRow();
            int prev_c = selected->getColumn();
            if (g.move(selected, r, k)) {
                clearBoard();
                update();
                turn = (turn == wit) ? zwart : wit;

                // After updating the board and checking for valid moves
                if (g.schaakmat(wit)) {
                    message("Checkmate! Black wins!");
                } else if (g.schaakmat(zwart)) {
                    message("Checkmate! White wins!");
                } else if (g.schaak(zwart)) {
                    message("Black is in check!");
                } else if (g.schaak(wit)) {
                    message("White is in check!");
                } else if (g.pat(turn)) {
                    message("No more moves, It's a draw! ");
                }
            }
            // clear highlight on previous location of the chess piece
            setTileSelect(prev_r, prev_c, false);
            // clear mark on threatened positions
            setTileThreat(prev_r, prev_c, false);
        } else {
            message("Invalid move.");
        }

        for (auto move: validMoves) {
            setTileFocus(move.first, move.second, false);
        }
        selected = nullptr;

    }
    if (displayKills()) {
        /*
          Works only sometimes...
         //Mark threatened positions in red for opponent pieces
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (g.getPiece(i, j) && g.getPiece(i, j)->getKleur() != turn) {
                    vector<pair<int, int>> validMoves = g.getPiece(i, j)->valid_moves(g);
                    for (auto pos: validMoves) {
                        bool leeg = false;
                        auto testpion = new Pion(g.getPiece(i,j)->getKleur());
                        if (g.getPiece(pos.first,pos.second) == nullptr){
                            testpion->setRow(pos.first);
                            testpion->setColumn(pos.second);
                            leeg = true;
                            g.setPiece(pos.first,pos.second,testpion);
                        }
                        for (int a = 0; a < 8; a++){
                            for(int b = 0; b < 8; b++){
                                if (g.getPiece(a,b) != nullptr and g.getPiece(a,b)->getKleur() != g.getPiece(i,j)->getKleur()){
                                    for(auto move : g.getPiece(a,b)->valid_moves(g)){
                                        if (move == pos){
                                            setTileThreat(pos.first, pos.second, true);
                                        }
                                    }
                                }
                            }
                        }
                        if (leeg){
                            g.setPiece(pos.first, pos.second,nullptr);
                            delete testpion;
                        }
                    }
                }
            }
        }
         */
    }

    // Mark threatened Pieces in red
    if (displayThreats()) {

        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                if (g.getPiece(i, j) && g.getPiece(i, j)->getKleur() != turn) {
                    vector<pair<int, int>> threatened_pos = g.getPiece(i, j)->valid_moves(g);
                    for (auto pos: threatened_pos) {
                        if (g.getPiece(pos.first, pos.second) &&
                            g.getPiece(pos.first, pos.second)->getKleur() == turn) {
                            setPieceThreat(pos.first, pos.second, true);
                        }
                    }
                }
            }
        }

    }
    update();
    redoHistory.push_back(g.getBord());
}


    void SchaakGUI::newGame() {
        g.clearbord();
        removeAllMarking();
        removeAllPieceThreats();
        g.setStartBord();
        turn = wit;
        update();
    }

void SchaakGUI::save() {
    QFile file;
    if (openFileToWrite(file)) {
        QDataStream out(&file);

        // Create a mapping of piece types to their string representations
        QMap<Piece::Type, QString> pieceTypeToStr;
        pieceTypeToStr[Piece::Rook] = "R";
        pieceTypeToStr[Piece::Knight] = "H";
        pieceTypeToStr[Piece::Bishop] = "B";
        pieceTypeToStr[Piece::Queen] = "Q";
        pieceTypeToStr[Piece::King] = "K";
        pieceTypeToStr[Piece::Pawn] = "P";

        // Save the pieces on the board
        for (int r = 0; r < 8; r++) {
            for (int k = 0; k < 8; k++) {
                SchaakStuk *piece = g.getPiece(r, k);
                if (piece) {
                    QString pieceStr = pieceTypeToStr[piece->piece().type()];
                    pieceStr += (piece->getKleur() == wit) ? "w" : "b";
                    out << pieceStr;
                } else {
                    out << QString(".");
                }
            }
        }


    }
}

void SchaakGUI::open() {
    QFile file;
    if (openFileToRead(file)) {
        try {
            QDataStream in(&file);
            g.clearbord();
            // Load the positions of the pieces on the chessboard
            for (int row = 0; row < 8; row++) {
                for (int col = 0; col < 8; col++) {
                    QString pieceStr;
                    in >> pieceStr;
                    auto piece = createPieceFromStr(pieceStr);
                    if (piece != nullptr){
                        g.setPiece(row, col, piece);
                        piece->setRow(row);
                        piece->setColumn(col);

                    }

                }
            }
            update();

            // Display a message indicating successful load
            message("Game loaded successfully");
        } catch (const QString& e) {
            message(e);
        }
    }
}





// SchaakGUI.cpp

void SchaakGUI::undo() {
    // Check for redo history
    if (!movesHistory.empty()) {

        // Toggle the color to replay the correct move for the opposite player
        turn = (turn == wit) ? zwart : wit;

        // Push the latest redo move into the movesHistory vector for possible redo
        movesHistory.push_back(redoHistory[redoHistory.size() - 1]);
        redoHistory.pop_back(); // Remove the last redo move

        // Clear the board to restore the previous state, then update to display it
        g.clearbord();
        g.setBord(redoHistory[redoHistory.size() - 1]);
        update();
        message("You have chosen to undo.");

        // If no redo moves are available, display a message
    } else {
        message("No undos available.");
    }
}



void SchaakGUI::redo() {

    // The pop_back operation is executed later to ensure the change is applied first before removing it
    // In the undo function, it is executed first because the last game state is the current state, which is not needed
    if (!movesHistory.empty()) {

        // Toggle the color to replay the correct move for the opposite player
        turn = (turn == wit) ? zwart : wit;

        // Push the latest move from history into the redoHistory vector for possible redo
        redoHistory.push_back(movesHistory[movesHistory.size() - 1]);

        // Clear the board to restore the previous state, then update to display it
        g.clearbord();
        g.setBord(movesHistory[movesHistory.size() - 1]);


        // Remove the last move from history
        movesHistory.pop_back();

        // Update the display
        update();
        message("You have chosen to redo.");

    } else {
        message("No redos available.");
    }
}

    void SchaakGUI::visualizationChange() {
        QString visstring =
                QString(displayMoves() ? "T" : "F") + (displayKills() ? "T" : "F") + (displayThreats() ? "T" : "F");
        message(QString("Visualization changed : ") + visstring);
    }

// Update de inhoud van de grafische weergave van het schaakbord (scene)
// en maak het consistent met de game state in variabele g.
    void SchaakGUI::update() {
        clearBoard();

        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                auto piece = g.getPiece(row, col);

                if (piece != nullptr) {
                    setItem(row, col, piece);
                }
            }
        }


    }

SchaakStuk *SchaakGUI::createPieceFromStr(const QString &pieceStr) {
        SchaakStuk* piece = nullptr;

        if (pieceStr == "Rb") {
            piece = new Toren(zwart);
        } else if (pieceStr == "Hb") {
            piece = new Paard(zwart);
        } else if (pieceStr == "Bb") {
            piece = new Loper(zwart);
        } else if (pieceStr == "Qb") {
            piece = new Koningin(zwart);
        } else if (pieceStr == "Kb") {
            piece = new Koning(zwart);
        } else if (pieceStr == "Pb") {
            piece = new Pion(zwart);
        } else if (pieceStr == "Rw") {
            piece = new Toren(wit);
        } else if (pieceStr == "Hw") {
            piece = new Paard(wit);
        } else if (pieceStr == "Bw") {
            piece = new Loper(wit);
        } else if (pieceStr == "Qw") {
            piece = new Koningin(wit);
        } else if (pieceStr == "Kw") {
            piece = new Koning(wit);
        } else if (pieceStr == "Pw") {
            piece = new Pion(wit);
        }

        return piece;
    }







