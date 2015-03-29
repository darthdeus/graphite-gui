# Vizualizace grafovych algoritmů

Tématem práce je vizualizace grafových algoritmů, konkrétně prohledávání do hloubky, do šířky, Dijkstrův algoritmus a hledání Eulerovské kružnice v neorientovaných grafech (nakreslení grafu jedním tahem).

Všechny algoritmy jsou krokovatelné uživatelem, který zadá libovolný graf (viz dále), a poté může krok po kroku sledovat, jak algoritmus probíhá, a případně ho může pustit znovu z jiného počátečního vrcholu.

## Kompilace & spuštění

Pro kompilaci je potřeba překladač který umí C++11, např. Clang/LLVM verze 3.5, který je dostupný v labu. Dále je potřeba Qt5, zde by na konkrétní verzi nemělo záležet, ale Qt4 nestačí.

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
- Nastavení ohodnocení hrany `0-9`, nejprve je ale potřeba mít vybraný Dijkstrův algoritmus, jinak se ohodnocení hran nezobrazí, a poté kliknout na vybrané ohodnocení (*ne na hranu*).

Grafy je také možné uložit do souboru `Ctrl-S` a znovu načíst `Ctrl-S`, přičemž se zachová i rozložení vrcholů v prostoru (pokud je uživatel přesunul.)

## Používání

Nejjednodušší je vybrat jeden z přiložených grafů v souboru, a otevřít jej přes `File -> Open`, např. kompletní graf na 5 vrcholech v souboru `examples/k5.g`

![k5-screenshot](http://i.imgur.com/iYrD1VK.png)

v seznamu algoritmů vybrat Eulerovský tah

![alg-selection](http://i.imgur.com/ewrHxRO.png)

kliknout na libovolný vrchol, vybrat ho jako počáteční (stisknutím `F`), inicializovat algoritmus (stisknutím `R`), a poté již krokovat stisknutím `N`.

V libovolnou chvíli je možné znovu stiknout `R`, čímž se algoritmus resetuje a začne pracovat odznova. **Pokud uživatel graf jakkoliv změní v průběhu algoritmu, je nutné algoritmus resetovat stisktnutím `R`**.

TODO - resetovat rucne

TODO - popsat dalsi alg

## Generování náhodných grafů

Aby bylo možné aplikaci jednoduše používat, obsahuje možnost vygenerování náhodného souvislého grafu (žádný ze zabudovaných algoritmů nedává smysl vizualizovat na nesouvislých grafech.)

Graf je generován následujícím způsobem:

- vygeneruje se 10-15 vrcholů, které se postupně spojí hranami, dohromady tvořící jednu velkou cestu
- každému vrcholu se s pravděpodobností 2/5 přidělí jedna další náhodná hrana

Takto vygenerovaný graf bude vždy souvislý, a díky malému počtu hran i relativně přehledný. Graf je vždy generovaný jako neorientovaný. Pokud si uživatel přeje, může poté náhodně zorientovat hrany (`Ctrl-R, D`).

## Generování Eulerovských grafů

Protože pro Eulerovské grafy musí platit, že každý vrchol má sudý stupeň, je také jednoduché nahlédnout, že musí ležet na nějaké kružnici. Generování grafu tedy probíhá tak, že se nejprve vytvoří jednovrcholový hraf, a potom se 5-7krát vybere náhodný vrchol z grafu, a přilepí se na něj další kružnice délky 3-5 (pro přehlednost.)

Výsledný graf pak vypadá např. takto

![random-euler](http://i.imgur.com/LQNxfKa.png)

Takto vygenerovaný graf má opět výhodu, že je díky menšímu počtu hran přehledný.

## Rozmístění vrcholů

Při generování náhodného grafu jsou vrcholy vždy rozmístěny na spirálu, která se rozvijí _zevnitř ven_.



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


