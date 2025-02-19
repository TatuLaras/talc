# Toteutusdokumentti

## Aika- ja tilavaativuudet
Shunting-yard algoritmi on aikavaativuudeltaan $O(n)$, sama postfix-lausekkeen laskennankin kanssa, eli kokonaisuudessaan ohjelma käsittelee syötteen $O(n)$ aikavaativuudella. Vaadittu tilakin kasvaa lineaarisesti.

## Työn mahdolliset puutteet ja parannusehdotukset
Työn ajatuksena oli alunperin kurssin jälkeenkin pikkuhiljaa kehittyä näppäimistöorientoituneeksi TUI-versioksi Speedcrunch-laskimesta. 
Lisää funktioita ja muuttujia tarvitaan siihen että ne olisivat verrattavissa, sekä käyttäjän omien funktioiden määrittely.
Myös kehittyneempi käyttöliittymä jossa on komentorivityylinen aikaisempien lausekkeiden muokkaus ja muita toiminnallisuuksia, kuten asteiden ja radiaanien välillä vaihtaminen.
Lauseketta muokatessa olisi myös hyvä päästä liikuttamaan kursoria ja muokkaamaan aiemmin kirjoitettua.
Tuloksia olisi myös hyvä pystyä näkemään heksadesimaali- ja binäärimuodossa, sekä syöttää lukuarvoja näitä muotoja käyttäen.
Myös laskutoimitukset ovat rajoitettu niihin lukuihin jotka yksi `double` pystyy ilmaisemaan, esimerkiksi Speedcrunchissa tätä rajoitusta ei ole vaan tulos voi olla kuinka suuri tahansa.

## Laajojen kielimallien (ChatGPT yms.) käyttö
Ei ole käytetty.


## Viitteet
- [Shunting yard algorithm - Wikipedia](https://en.wikipedia.org/wiki/Shunting_yard_algorithm)

