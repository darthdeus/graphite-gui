# Vizualizace grafovych algoritmů

Tématem práce je vizualizace grafových algoritmů, konkrétně prohledávání do hloubky,
do šířky, Dijkstrův algoritmus a hledání Eulerovské kružnice (nakreslení grafu jedním tahem).

Všechny algoritmy jsou krokovatelné uživatelem, který zadá libovolný graf (viz dále),
a poté může krok po kroku sledovat, jak algoritmus probíhá, a případně ho může
pustit znovu z jiného počátečního vrcholu.

## Kompilace & spuštění

Pro kompilaci je potřeba překladač který umí C++11, např. Clang/LLVM verze 3.5,
který je dostupný v labu. Dále je potřeba Qt5, zde by na konkrétní verzi nemělo záležet,
ale Qt4 nestačí.

Kompilace a spuštění se pak provede následovně

  $ qmake .
  $ make
  $ ./build/debug/graphite

Testováno na různých distribucích Linuxu, včetně labu, a OS X 10.10.



TODO spuštění bez Qt?


## Základní ovládání

Program se ovládá klávesnicí i myší, kde všechny příkazy jdou zadat buď přes hlavní menu

SCREENSHOT

a nebo pomocí klávesové zkratky. Zde je jejich úplný seznam:

- Vygenerování náhodného grafu `Ctrl-R G`.
- Náhodná oritentace hran `Ctrl-R D`.
- Vygenerování náhodného Eulerovského grafu `Ctrl-R E`.
- Náhodné ohodnocení hran `Ctrl-R W`.
- Odstranění orientace hran `Ctrl-R U`.

- Přidání vrcholu `A`.
- Spojení dvou vrcholů hranou `C`. Je potřeba napřed vybrat první,
  zmáčknout `C`, vybrat druhý, a zmáčknout `C` znovu.
- Smazání vrcholu nebo hrany `D`. (nejprve je potřeba hranu nebo vrchol vybrat kliknutím myši.)
- Označení počátečního vrcholu `S`.
- Start/Restart algoritmu `R`.
- Krok algoritmu `N`.
- Změna orientace hrany `O` (nejprve je potřeba hranu vybrat kliknutím myši.)
- Nastavení ohodnocení hrany `0-9`, nejprve je ale potřeba mít vybraný Dijkstrův algoritmus,
  jinak se ohodnocení hran nezobrazí, a poté kliknout na vybrané ohodnocení (*ne na hranu*).

Grafy je také možné uložit do souboru `Ctrl-S` a znovu načíst `Ctrl-S`, přičemž se zachová
i rozložení vrcholů v prostoru (pokud je uživatel přesunul.)



Tema: Vizualizace grafovych algoritmu
Funkce:
- Vygenerovani vhodne nahodneho grafu pro vybrany algoritmus
- Nakresleni grafu zpusobem, kdy se vrcholy rozmisti do nejake nahodne mrizky, mezi ne nakresli hrany, a uzivatel pak muze vrcholy libovolne presouvat, aby graf vypadal tak jak si predstavuje.
- Moznost rucni editace grafu - pridavani/odebirani vrcholu/hran, apod.
- Moznost ulozeni grafu do souboru a jeho znovunacteni, napr. po tom co uzivatel nejak graf zmenil

- Moznost vybrat algoritmus ktery se bude na zadanem grafu vizualizovat. Aplikace bude obsahovat 4 algoritmy: prohledavani do hloubky a do sirky, Dijkstruv algoritmus, a nakresleni grafu jednim tahem (pruchod kazdou hranou prave jednou).
- Prubeh zvoleneho algortimu bude zobrazovan na vybranem grafu
- Kazdy algoritmus bude mit predpripravenou moznost vygenerovat pro nej vhodny graf (aby se usetril cas uzivateli ktery chce pouze videt jak algoritmus funguje a nechce pracne zadavat cely graf rucne)

- Aplikace bude napsana v C++ a Qt a pobezi primarne na Linuxu


