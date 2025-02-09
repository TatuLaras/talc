# Testausdokumentti

Ohjelman toimivuutta testataan yksikkötestein, jossa testataan sekä infix-postfix muunnosta, postfix lausekkeen laskentaa sekä näiden kahden yhteistoimintaa. 
Testit koostuvat pääosin erinäisistä monimutkaisista lausekkeista ja reunatapauksista.

On (automaatio)testattu, että:

- Ohjelma käsittelee oikein erinäiset virhetilat (syötteessä jotain sinne kuulumatonta, vääränlaiset sulkulausekkeet, muuttujaa tai funktiota ei olemassa)
- Sulkulausekkeet tulkitaan oikein
- Erinäiset operaattoreista, funktioista ja sulkulausekkeista koostuvat lausekkeet käännetään laskujärjestyksen mukaiseen oikeaan postfix-muotoon
- Ohjelma osaa tulkita negatiiviset luvut oikein (esim `5+-2=3`)
- Tuplamiinukset (`--2`) käsitellään tyyliin `-(-2)` (`2`)

## Tiedostojen / käännösyksiköiden rivikattavuudet
Mitattu `gcov` -työkalulla (kts. [README](../README.md)).
| Tiedosto | Kattavuus |
| --- | --- |
| TBD | |
<!-- | `src/symbol_stack.c`      | 100%      | -->
<!-- | `src/calculate.c`         | 100%      | -->
<!-- | `src/infix_to_postfix.c`  | 100%      | -->
