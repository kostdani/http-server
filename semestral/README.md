# HTTP Server

V tomto adresáři doporučujeme vyvíjet vaší semestrální práci. Struktura semestrální práce a tedy i tohoto adresář by měla odpovídat informacím na [Courses PA2 - Semestrální práce](https://courses.fit.cvut.cz/BI-PA2/semestral.html).

Přímo v tomto adresáři doporučujeme vyvořit podadresář `<login>`, kde `<login>` je tvůj username a v tomto podadresáři dále vyvíjet. Dále si zde můžeš například vytvořit skript `pack.sh`, který zabalí tvoji semestrální práci do `.zip` souboru, přesně podle pokynů na Courses.

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
- HTTP server může umět obsloužit více domén nebo poskytovat virtuální filesystém (mapování virtuálních URL na fyzické cesty na disku)

Volitelně: Podpora HTTPS (openssl), vícevláknové obsloužení klientů

Kde lze využít polymorfismus? (doporučené)

- Druh souboru: adresář, HTML soubor, obrázek, skript, nepodporovaný formát, ...
- Logování: na konzoli, do souboru, do databáze, ...
- Styl logování: jednoduchá hlavička, kompletní požadavek (např. pouze pro chybové stavy), statistika přístupů, ...