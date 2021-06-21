# HTTP Server

Autor: Danila Kost

# Téma z Progtestu

Úkolem je naprogramovat jednoduchý HTTP server s podporou různých generátorů obsahu. Generátor obsahu musí podporovat:

- výpis obsahu adresáře
- konkrétní html stránka (statický obsah)
- externí skript nebo program

Server musí implementovat:

- načítání konfiguračního souboru
- parametry naslouchání na síti (IP adresa, port)
- omezení na práci s konkrétním adresářem
- log přenosů (kam se má ukládat, v jakém formátu, jak má vypadat hlavička každého záznamu, ...)
- vypnutí serveru na (konfigurovatelné) URL adrese

HTTP server může umět obsloužit více domén nebo poskytovat virtuální filesystém (mapování virtuálních URL na fyzické cesty na disku)

Volitelně: Podpora HTTPS (openssl), vícevláknové obsloužení klientů

Kde lze využít polymorfismus? (doporučené)

- Druh souboru: adresář, HTML soubor, obrázek, skript, nepodporovaný formát, ...
- Logování: na konzoli, do souboru, do databáze, ...
- Styl logování: jednoduchá hlavička, kompletní požadavek (např. pouze pro chybové stavy), statistika přístupů, ...

# Vlastní zadání

Vytvořím jednoduchý asinchronni HTTP server s načítáním konfigurace a logováním.

Uživatel může spustit server z příkazového řádku s zadáním konfiguračního souboru.
například: ./Server config.cfg

## Config file structure

Bílé znaky v konfiguračním souboru jsou ignorovány
Konfigurační soubor se skládá z dvojic v podobě
"key=value;"

Podporované nastavení:
- logfile) value ma být cesta k souboru kde budou uloženy logy
Pokud není zadán, logy budou zapisovány do konzoly
- listen) value  ma být ip a port naslouchání síti
Pokud není zadán, výchozí hodnota je "0.0.0.0:8080"
- virtualfs) value musí být seznam pár url = obsah oddělený čárkami ve složených závorkách
tyto páry definují mapování virtuálních URL na generátory obsahu

## Podporované generátory obsahu
- Soubor) file:path - umožňuje zobrazit obsah souboru
- Adresar) dir:path - umožňuje zobrazit obsah složky 
- Script) script:path - umožňuje získat výsledek spuštění skriptu nebo programu
podporuje dotazy v url, například, url?a&b&c znamená volání skriptu s argumenty a b c
- Vypinac) special:terminator - umožňuje nastavit adresu v konfiguraci (pridadně více adres), na které bude server vypnut

Server přesměruje request na generátor obsahu podle nejdelší shody začátku URL adresy

## Logovani
Server uchovává logy v Common Log Formátu a podporuje jejich zápis do souboru nebo konzoly.
Každý řádek popisuje jeden obsloužený HTTP požadavek. Formát řádku je:
```klient ident uživatel [datum] "požadavek" status délka```

## Kde mám polymorfismus?
Abstraktní třída `Actor` má virtuálnou metodu `Run`, ktera je přetěžena v potomcích
Tato metod je odpovědná za provádění akcí aktérem v případě IO události. Například třída `Receiver` voláním této metody neblokujícím způsobem čte data ze soketu, dokud se vyčerpá, `Accepter` přijímá nové klienty a `Queuer` zpracovává zprávy
`Run` se vola v metodě `Start` třídy `HTTPServer`, ktera v cyklu přijímá z epollu dalšího aktéra s nimž se stala nějaká událost a volá jeho metodu

Abstraktní třídy `Queuer` představující aktéra, který postupně zpracovává frontu zpráv, má virtuální metodu `Handle`, přetěžene varianty které ve třídách potomkách skutečně definují reakce na každou zprávu.
Například třída `Logger` zpracovává zápis přijatého logu do odpovídajícího streamu zatímco třídy generátory obsahu přijímají HTTP requesty a v metodě `Handle` implementují logiku zpracování těchto requestu

Třída `Queuer` navíc implementuje parametrický polymorfismus konkrétně v tom, že typ zprávy je zadán šablonou.
Např `Sender` a `Logger` pracujou se stringy a `ContentGenerator`y s `HTTPRequest`y

## Příklady
Adresar examples obsahuje ukázkový konfigurační soubor: server.cfg a 2 skripty: sum.sh a factorial.sh pro demonstraci.

Сonfig konfiguruje server tak, aby 
- poslouchal adresu 0.0.0.0 na portu 8080, 
- vypisoval logy do souboru examples/server.log,
- zobrazoval na adrese http://127.0.0.1:8080 adresar doc/ s dokumentací projektu,
- na adrese http://127.0.0.1:8080/sum je k dispozici volání skriptu, který přidává dvě čísla,
- na adrese http://127.0.0.1:8080/factorial je k dispozici volání skriptu, který počítá faktoriál daného čísla,
- na adrese http://127.0.0.1:8080/exit server se vypíná
