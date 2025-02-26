# Testausdokumentti

Ohjelman toimivuutta testataan yksikkötestein, jossa testataan sekä infix-postfix muunnosta, postfix lausekkeen laskentaa sekä näiden kahden yhteistoimintaa. 
Testit koostuvat pääosin erinäisistä monimutkaisista lausekkeista ja reunatapauksista.

On (automaatio)testattu, että:

- Ohjelma käsittelee oikein erinäiset virhetilat (syötteessä jotain sinne kuulumatonta, vääränlaiset sulkulausekkeet, muuttujaa tai funktiota ei olemassa)
- Sulkulausekkeet tulkitaan oikein
- Erinäiset operaattoreista, funktioista ja sulkulausekkeista koostuvat lausekkeet käännetään laskujärjestyksen mukaiseen oikeaan postfix-muotoon
- Ohjelma osaa tulkita negatiiviset luvut oikein (esim `5+-2=3`)
- Tuplamiinukset (`--2`) käsitellään tyyliin `-(-2)` (`2`)


Ohjelma ajettu Valgrindilla ja sitä hyödyntäen korjattu vikoja muistinhallinnassa.

## Tiedostojen / käännösyksiköiden rivikattavuudet
Mitattu `gcov` -työkalulla (kts. [README](../README.md)).
| Käännösyksikkö | Kattavuus | |
| --- | --- | --- |
| calculate | 100% |
| double_stack | 100% |
| queue | 100% |
| infix_to_postfix | 100% |
| symbol_stack | 100% |
| ui_helpers | 100% |
| variables | 100% |
| results_buffer | 100% |
| queue | 100% |
| symbol | 60.82% | `num_operands` -funktio |
