Projekt indywidualny - Warcaby Angielskie
Wykonał: Jordan Wiszniewski

Projekt wymaga c++11 (lub nowszego).
Komenda do kompilacji w GCC w pliku: 'kompilacja.sh'
Należy uruchomić go z terminalu obługującego czcionki z unicode (UTF-8).
Większość terminali ma czarne tło, dlatego przy wyświetlaniu 
np. symboli domyślnie czarnych tworzy ich negatyw tak aby były kontrastowe.
Z tego powodu można manipulować zamianą kolorów tak aby symbole wyświetlały faktycznie to co reprezentują za pomocą pliku: 
'warcaby.config' (zamiana dla 'COLORSWAP=TRUE')
Testowane dla czcionek: inconsolata regular, freemono regular

Rozgrywka:
Program działa zgodnie z zasadami angielskiego wariantu warcabów 8x8 (ang. Checkers).
Kiedy następuje tura gracza wyświetla się warcabnica wraz z jej aktualną zawartością.
Następnie wyświetle się lista wszystkich możliwych ruchów zgodnych z zasadami (z którego pola na które można przesunąć piona).
Grę można zakończyć przez poddanie (ostatnia opcja z listy ruchów),
przez zwycięstwo jednego z nich lub remis (pat).

