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
TBD

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
