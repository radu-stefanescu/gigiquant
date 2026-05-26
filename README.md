# GigiQuant - Algoritmi și Structuri de Date în Finanțe

Acest proiect conține rezolvarea a 4 probleme de analiză financiară, implementate în limbajul C. 
Programul primește ca argumente un fișier de intrare și unul de ieșire, determinând automat ce algoritm să ruleze prin parsarea indexului din numele fișierului.

## Compilare și Rulare

Programul așteaptă exact două argumente la linia de comandă:
`./a.out <cale_fisier_intrare> <cale_fisier_iesire>`

*Exemplu:* `./a.out in/data12.in out/data12.out` (Programul va detecta indexul `12` și va rula logică pentru Task 3).

## Logica Implementată pe Task-uri

* **Task 1: Sharpe Ratio (Teste 1-5)**
  * **Structuri:** Liste simplu înlănțuite.
  * **Logică:** Prețurile sunt citite și inserate la finalul listei, calculându-se on-the-fly randamentul față de ziua anterioară.
  * Urmează o a doua parcurgere a listei pentru a calcula randamentul meddiu și volatilitatea (deviația standard), rezultând în final indicatorul Sharpe.
  * Valorile sunt trunchiate matematic la 3 zecimale.

* **Task 2: Arbitraj Statistic (Teste 6-10)**
  * **Structuri:** Stive (pentru procesarea datelor istorice) și Cozi (pentru stocarea rezultatelor).
  * **Logică:** Prețurile de pe 3 piețe distincte sunt extrase și puse în 3 stive.
  * Elementele sunt extrase (pop) simultan zi de zi.
  * Algoritmul verifică oportunitățile de arbitraj: dacă exact două piețe au același preț și a treia diferă, datele tranzacției (ziua, diferența absolută și piața atipică)
  *  sunt introduse într-o coadă (enqueue) și ulterior afișate.

* **Task 3: Diversificarea Portofoliului (Teste 11-15)**
  * **Structuri:** Arbori binari.
  * **Logică:** Se construiește un arbore binar pre-alocat cu adâncimea egală cu numărul de zile.
  * Acțiunile coboară pe ramuri (stânga/dreapta) în funcție de fluctuația zilnică a prețului.
  * Pentru a găsi portofolii stabile, algoritmul caută acțiuni "în oglindă" parcurgând recursiv calea diametral opusă în arbore pentru fiecare acțiune dată.

* **Task 4: Lanțuri Markov (Teste 16-20)**
  * **Structuri:** Grafuri/Matrici de tranziție, Structuri custom pentru fracții.
  * **Logică:** Axa prețurilor este discretizată în intervale (stări). Matricea de tranziție este populată numărând trecerile dintr-o stare în alta, apoi normalizată.
  * Pentru a asigura precizia și a evita erorile tip `float`, logica folosește o structură custom `fractie` cu operații de adunare, înmulțire și simplificare (prin CMMDC).
  * Evoluția prețului este simulată recursiv timp de `K` zile, afișând probabilitatea exactă de a atinge targetul.
