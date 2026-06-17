# Blackjack (C++)

`Autorzy: Mateusz Partyka, Szymon Potępa`

## Krótki opis

Projekt to kompletna implementacja gry Blackjack napisana w C++. Gra zawiera
pełną logikę rozgrywki oraz prosty interfejs wejścia/wyjścia.

## Najważniejsze cechy

- Kompletna logika gry: rozdawanie kart, obsługa rąk gracza i dealera, reguły
  Blackjack.
- Obsługa wieloręcznej rozgrywki (po splicie), tasowanie i obsługa kart.
- Warstwa IO: implementacja wyświetlania wejściowego opartego na bibliotece
  niestandardowej `raylib`.
- Projekt skonfigurowany za pomocą `CMake` (budowanie lokalne i testy).

## Struktura repozytorium

- `src/` – źródła programu (`main.cpp`, moduły `blackjack/`, `card/`, `IO/`,
  `util/`).
- `include/` – pliki nagłówkowe projektu.
- `assets/` – zasoby (obrazy kart itp.).
- `tests/` – testy jednostkowe (Catch2).
- `build/` – katalog budowania (generowany przez CMake).

## Wkład własny (co dodaliśmy)

Gra była w całości tworzona przez nas.

## Użyte biblioteki i zależności

- raylib — używane opcjonalnie do prostej warstwy graficznej (biblioteka
  niestandardowa).
- Catch2 — framework testowy

## Instrukcja budowania (Windows - PowerShell / CMD)

1. Utwórz katalog budowania i skonfiguruj projekt:

```powershell
mkdir build
cd build
cmake .. -S .. -B .
```

2. Zbuduj projekt:

```powershell
cmake --build . --config Release
```

3. Uruchom program (z katalogu `build`):

```powershell
.\blackjack.exe
```

Jeśli używasz generatora `Ninja` lub innego, zamień odpowiednio polecenia CMake.

## Uruchamianie testów

Po zbudowaniu uruchom testy z katalogu `build`:

```powershell
ctest --output-on-failure
```

Jeśli chcesz uruchomić pojedynczy plik testowy, znajdź plik wykonywalny w
katalogu `build` i uruchom go bezpośrednio.

## Użycie AI

- wybór biblioteki interfejsu graficznego (raylib) - ChatGPT
- Dokument `README.md` wygenerowny przy pomocy AI - GPT-5 mini (GitHub Copilot)
- testy
- template CMake (ChatGPT)
- generowanie obrazów kart (ChatGPT)
