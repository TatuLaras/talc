# Talc: tieteellinen laskin terminaalikäyttöliittymässä
(WIP) Ohjelma on C-kielellä toteutettu terminaalikäyttöliittymän (TUI) kautta käytettävä tieteellinen laskin. 

[Määrittelydokumentti](https://github.com/TatuLaras/talc/blob/master/docs/m%C3%A4%C3%A4rittely.md)

## Kääntöohjeet
Tämä ohje olettaa että käytät Unix-pohjaista käyttöjärjestelmää, sekä `gcc` -kääntäjä ja `make` -ohjelma ovat asennettuina. 

Kääntääksesi koko projektin aja projektin juuressa:
```bash
$ make
```

Voit kääntää ja ajaa projektin samalla komennolla käyttämällä:

```bash
$ make run
```


## Käyttöohjeet
Ohjelmassa voit kirjoittaa operaattoreista, funktioista, desimaaliluvuista ja kokonaisluvuista koostuvia matemaattisia lausekkeita ja laskea ne Enter-näppäintä painamalla.
Ohjelma tukee operaattoreita `+`, `-`, `*`, `/`, ja `^`, sekä sulkuja ja funktioita (esim. `sin(3.14)`).
Desimaalierottimena ohjelma käyttää pistettä ja funktioiden argumenttien välissä on pilkku.

Omia muuttujia pystyy määrittelemään kirjoittamalla laskutoimituksen alkuun muuttujan nimen ja `=`-merkin (esim. `omamuuttuja1 = 5 + 5`).
Tämän jälkeen muuttujaa voi käyttää lukuarvon tilalla.
Ohjelmassa on myös joitain sisäänrakennettuja muuttujia, jotka on listattu alempana.

Tulokset voi pyyhkiä `ctrl+l` -näppäinyhdistelmällä. Ohjelmasta poistuminen onnistuu `ctrl-c` -näppäinyhdistelmällä.

### Funktiot
| Funktio | |
| --- | --- |
| sin(x) | Sinifunktio |
| cos(x) | Kosinifunktio |
| tan(x) | Tangenttifunktio |
| asin(x) | Sinifunktion käänteisfunktio |
| acos(x) | Kosinifunktion käänteisfunktio |
| atan(x) | Tangenttifunktion käänteisfunktio |
| max(x, y) | Palauttaa luvuista suuremman |
| min(x, y) | Palauttaa luvuista pienemmän |
| ln(x) | Luonnollinen (e-kantainen) logaritmi |
| lg(x) | Yleinen (10-kantainen) logaritmi |
| log(kanta, x) | N-kantainen logaritmi |

### Sisäänrakennetut muuttujat

| Muuttuja | |
| --- | --- |
| ans | Viimeisimmän laskutoimituksen tulos |
| pi ||
| e | Neperin luku|

## Testit
Projektin yksikkötestit sijaitsevat projektin juuren `/tests` -kansiossa. Kääntääksesi kaikki testit voit käyttää `/tests` -kansiossa ollessasi:
```bash
$ make
```
tai ajaaksesi ne samalla:
```bash
$ make run
```


### Rivikattavuus
Rivikattavuutta on mahdollista mitata `gcov` -työkalun avulla. Luodaksesi rivikattavuustiedot sisältävät tiedostot, testit on käännettävä käyttäen `gcc`-kääntäjän `--coverage` -asetusta, jonka jälkeen testiohjelmat ovat ajettava. Helpoimmin tämä onnistuu seuraavasti (`/tests/` -kansion juuressa):

```bash
$ make run CUSTOM_FLAGS=--coverage
```

Tämän jälkeen build-kansioon ilmestyy läjä `.gcno` -tiedostoja, jotka ovat nimetty seuraavan kaavan mukaan:
```
[ testitiedosto ]-[ mitä tiedostoa se ajaa ].gcno
```

Kyseisiä tiedostoja voi lukea `gcov` -ohjelmalla seuraavasti:
```bash
$ gcov [ tiedosto ]
```

Tämä tulostaa terminaaliin prosentuaalisen rivikattavuuden, sekä luo nykyiseen työkansioon `.gcov` -tiedoston, jossa kerrotaan mitä rivejä suoritettiin ja ei suoritettu.
