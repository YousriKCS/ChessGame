# ChessGame

````markdown
# SchaakGUI Project

Een grafische schaakapplicatie geschreven in C++.

## Inhoud

- `main.cpp` – Startpunt van de applicatie
- `SchaakGUI.cpp` / `SchaakGUI.h` – Beheert de grafische gebruikersinterface
- `game.cpp` / `game.h` – Spelregels en spelbeheer
- `SchaakStuk.cpp` / `SchaakStuk.h` – Representatie van schaakstukken
- `resources/` – Bevat afbeeldingen en andere middelen
- `guicode/` – GUI-componenten
- `chessGames/` – Mogelijke opgeslagen spelbestanden
- `CMakeLists.txt` – CMake buildconfiguratie

## Vereisten

- C++ compiler (bijv. `g++`)
- CMake 3.10+
- Een GUI-library indien gebruikt (bijv. Qt of SFML – voeg toe indien van toepassing)

## Builden en uitvoeren

```bash
mkdir build
cd build
cmake ..
make
./SchaakGUI
````

> Zorg ervoor dat je CMake geïnstalleerd hebt op je systeem.

## Features

* Grafisch schaakbord
* Interactie met stukken
* Mogelijkheid om spellen op te slaan (map `chessGames`)





