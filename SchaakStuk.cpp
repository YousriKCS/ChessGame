//  Student:
//  Rolnummer:
//  Opmerkingen: (bvb aanpassingen van de opgave)
//

#include "SchaakStuk.h"
#include "Game.h"

vector<pair<int, int>> Pion::valid_moves(Game &g) {
    vector<pair<int, int>> moves;
    int r = getRow();
    int c = getColumn();
    int direction = (getKleur() == wit) ? -1 : 1; // direction for pawn movement depends on color

    // move forward if empty
    if(g.getPiece(r + direction, c) == nullptr) {
        moves.emplace_back(r + direction, c);

        // move two spaces forward if on starting position
        if(r == (getKleur() == wit ? 6 : 1) && g.getPiece(r + 2 * direction, c) == nullptr) {
            moves.emplace_back(r + 2 * direction, c);
        }
    }

    // move diagonally if there is an enemy piece
    if(g.getPiece(r + direction, c + 1) != nullptr && g.getPiece(r + direction, c + 1)->getKleur() != getKleur()) {
        moves.emplace_back(r + direction, c + 1);
    }
    if(g.getPiece(r + direction, c - 1) != nullptr && g.getPiece(r + direction, c - 1)->getKleur() != getKleur()) {
        moves.emplace_back(r + direction, c - 1);
    }

    return moves;
}

vector<pair<int, int>> Koningin::valid_moves(Game &g) {
    vector<pair<int,int>> moves;
    int r = getRow();
    int c = getColumn();
    for (int i = getRow() + 1, j = getColumn() + 1; i < 8 && j < 8; i++, j++) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() - 1, j = getColumn() - 1; i >= 0 && j >= 0; i--, j--) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() - 1, j = getColumn() + 1; i >= 0 && j < 8; i--, j++) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() + 1, j = getColumn() - 1; i < 8 && j >= 0; i++, j--) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }for (int i = c - 1; i >= 0; i--) {
        if (g.getPiece(r, i) == nullptr) {
            moves.emplace_back(r, i);
        } else {
            if (g.getPiece(r, i)->getKleur() != getKleur()) {
                moves.emplace_back(r, i);
            }
            break;
        }
    }

    for (int i = c + 1; i < 8; i++) {
        if (g.getPiece(r, i) == nullptr) {
            moves.emplace_back(r, i);
        } else {
            if (g.getPiece(r, i)->getKleur() != getKleur()) {
                moves.emplace_back(r, i);
            }
            break;
        }
    }

    for (int i = r - 1; i >= 0; i--) {
        if (g.getPiece(i, c) == nullptr) {
            moves.emplace_back(i, c);
        } else {
            if (g.getPiece(i, c)->getKleur() != getKleur()) {
                moves.emplace_back(i, c);
            }
            break;
        }
    }

    for (int i = r + 1; i < 8; i++) {
        if (g.getPiece(i, c) == nullptr) {
            moves.emplace_back(i, c);
        } else {
            if (g.getPiece(i, c)->getKleur() != getKleur()) {
                moves.emplace_back(i, c);
            }
            break;
        }
    }
    return moves;

}

vector<pair<int, int>> Koning::valid_moves(Game& g) {
    vector<pair<int, int>> valid_positions;
    int r = getRow();
    int c = getColumn();
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            int new_r = r + i;
            int new_c = c + j;
            if (new_r < 0 || new_r >= 8 || new_c < 0 || new_c >= 8) {
                continue;
            }
            if (g.getPiece(new_r, new_c) == nullptr || g.getPiece(new_r, new_c)->getKleur() != getKleur()){
                valid_positions.emplace_back(new_r, new_c);
            }
        }
    }
    return valid_positions;
}

vector<pair<int, int>> Loper::valid_moves(Game &g) {
    vector<pair<int,int>> moves;
    for (int i = getRow() + 1, j = getColumn() + 1; i < 8 && j < 8; i++, j++) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() - 1, j = getColumn() - 1; i >= 0 && j >= 0; i--, j--) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() - 1, j = getColumn() + 1; i >= 0 && j < 8; i--, j++) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    for (int i = getRow() + 1, j = getColumn() - 1; i < 8 && j >= 0; i++, j--) {
        if (g.getPiece(i, j) == nullptr) {
            moves.emplace_back(i, j);
        } else if (g.getPiece(i, j)->getKleur() != getKleur()) {
            moves.emplace_back(i, j);
            break;
        } else {
            break;
        }
    }
    return moves;
}

vector<pair<int, int>> Paard::valid_moves(Game &g) {
    vector<pair<int, int>> valid_moves;
    vector<pair<int, int>> moves;
    int x = getRow();
    int y = getColumn();
    int dx[] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int dy[] = {-1, 1, -2, 2, -2, 2, -1, 1};
    for(int i = 0; i < 8; i++) {
        int a = x + dx[i];
        int b = y + dy[i];
        if(a >= 0 && a <= 7 && b >= 0 && b <= 7) {
            if(g.getPiece(a, b) == nullptr) {
                moves.emplace_back(a, b);
            } else if(g.getPiece(a, b)->getKleur() != getKleur()) {
                moves.emplace_back(a, b);
            }
        }
    }
    return moves;
}


vector<pair<int, int>> Toren::valid_moves(Game &g) {
    vector<pair<int, int>> moves;
    int r = getRow();
    int c = getColumn();
    // Check all positions to the left of the rook
    for (int i = c - 1; i >= 0; i--) {
        if (g.getPiece(r, i) == nullptr) {
            moves.emplace_back(r, i);
        } else {
            if (g.getPiece(r, i)->getKleur() != getKleur()) {
                moves.emplace_back(r, i);
            }
            break;
        }
    }
    // Check all positions to the right of the rook
    for (int i = c + 1; i < 8; i++) {
        if (g.getPiece(r, i) == nullptr) {
            moves.emplace_back(r, i);
        } else {
            if (g.getPiece(r, i)->getKleur() != getKleur()) {
                moves.emplace_back(r, i);
            }
            break;
        }
    }
    // Check all positions above the rook
    for (int i = r - 1; i >= 0; i--) {
        if (g.getPiece(i, c) == nullptr) {
            moves.emplace_back(i, c);
        } else {
            if (g.getPiece(i, c)->getKleur() != getKleur()) {
                moves.emplace_back(i, c);
            }
            break;
        }
    }
    // Check all positions below the rook
    for (int i = r + 1; i < 8; i++) {
        if (g.getPiece(i, c) == nullptr) {
            moves.emplace_back(i, c);
        } else {
            if (g.getPiece(i, c)->getKleur() != getKleur()) {
                moves.emplace_back(i, c);
            }
            break;
        }
    }
    return moves;
}
