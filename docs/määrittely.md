# Määrittelydokumentti

Koulutusohjelma: tietojenkäsittelytieteen kandidaatti

Ainakin seuraavia kieliä voin vertaisarvioida:
- C, C++, C#
- Python, JavaScript
- Rust

Useimmat C-syntaksiset kielet luultavasti onnistuu.


Ohjelma on C-kielellä toteutettava terminaalikäyttöliittymän (TUI) kautta käytettävä tieteellinen laskin. 
Käyttäjä voi syöttää laskimeen lausekkeita ja ohjelma antaa lausekkeen arvon.




## Ominaisuudet
- Syöte voi sisältää kokonaislukuja ja desimaalilukuja
- Tavalliset aritmeettiset operaatiot: `+`, `-`, `*`, `/`, ja `^`.
- Funktioita yhdellä parametrilla: `sin(x)`, `cos(x)`, `tan(x)`.
- Funktioita kahdella parametrilla: `min(x; y)`, `max(x; y)`.
- Arvon tallentaminen muuttujaan ja muuttujan käyttö lausekkeissa. 
Muuttuja on kirjaimia ja numeroita sisältävä merkkijono, joka alkaa kirjaimella.
Muuttujan määrittely (`muuttuja=`) voi esiintyä vain syötteen alussa.

## Toteutus

Käyttäjän syöttämä lauseke muunnetaan infix- muodosta [Reverse Polish Notation](https://en.wikipedia.org/wiki/Reverse_Polish_notation) -muotoon 
[Shunting Yard](https://en.wikipedia.org/wiki/Shunting_yard_algorithm) -algoritmilla. 
Shunting Yard -algoritmin aikavaativuus on $O(n)$.
Algoritmi käyttää tietorakenteina pinoa ja jonoa.
RPN-muodosta lopullinen lasketaan lopullinen arvo, mahdolliset lausekkeessa käytetyt muuttujat huomioonottaen.

Ohjelma erottaa muuttujat ja funktion nimet siitä, että funktion nimeä seuraa `(` -symboli.
Mikäli syöte on virheellinen, tai syöte sisältää funtiota tai muuttujia joita ei ole olemassa, palautetaan virhe.

### Ulkoiset riippuvuudet
- Terminaalikäyttöliittymän toteutuksen helpottamiseen käytetään [termbox2](https://github.com/termbox/termbox2) -kirjastoa.
- Yksikkötestaus toteutetaan [Unity](https://github.com/ThrowTheSwitch/Unity) -kehyksellä.
