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
 
  * ## Structura Fișierelor și Rolul Acestora

Proiectul este modularizat pentru a separa clar logica fiecărei structuri de date de fluxul principal al programului:

* **`main.c`**
  * **Rol:** Punctul de intrare al programului. 
  * **Ce face:** Parsează argumentele din linia de comandă, extrage numărul testului, deschide fișierele de intrare/ieșire și folosește un bloc `if-else` pentru a direcționa fluxul de execuție către logica task-ului corespunzător (1, 2, 3 sau 4). Aici se face citirea și parsarea principală a datelor.

* **`liste.c` & `liste.h` (Task 1)**
  * **Rol:** Implementarea listelor simplu înlănțuite.
  * **Ce face:** Definește structura `Node` care reține prețul și randamentul calculat. Conține funcția `addAtEnd` pentru a adăuga secvențial observațiile din piață și a calcula randamentul on-the-fly, precum și funcția `trunk` pentru formatarea matematică a output-ului.

* **`stive.c` & `stive.h` (Task 2)**
  * **Rol:** Implementarea structurii de tip Stivă (LIFO).
  * **Ce face:** Oferă funcțiile de bază (`push`, `pop`, `isStackEmpty`, `deleteStack`). În contextul proiectului, cele 3 stive sunt folosite pentru a reține prețurile de pe cele 3 piețe (Londra, Berlin, Paris) și a le extrage sincronizat pentru a compara diferențele de preț dintr-o anumită zi.

* **`cozi.c` & `cozi.h` (Task 2)**
  * **Rol:** Implementarea structurii de tip Coadă (FIFO).
  * **Ce face:** Conține operațiile clasice (`enQueue`, `deQueue`, `createQueue`). Este folosită pentru a stoca oportunitățile de arbitraj (ziua, diferența absolută, piața atipică) pe măsură ce sunt găsite în istoricul extras din stive, garantând afișarea lor în ordinea cronologică corectă la final.

* **`arbori.c` & `arbori.h` (Task 3)**
  * **Rol:** Implementarea logicii pentru Arbori Binari.
  * **Ce face:** Conține funcțiile de alocare a arborelui (`createEmptyTree`), popularea acestuia în funcție de creșterile/scăderile prețurilor (`insertStock`) și cel mai important, funcția recursivă `findMirroredStock`, care traversează arborele pe un drum diametral opus pentru a găsi acțiunile complementare necesare diversificării portofoliului.

* **`markov.c` & `markov.h` (Task 4)**
  * **Rol:** Motorul matematic și de simulare pentru Lanțurile Markov.
  * **Ce face:** Pe de o parte, definește structura custom `fractie` și implementează operațiile matematice necesare calculului exact, fără erori de virgulă mobilă (`cmmdc`, `adunare`, `inmultire`, `ireductibil`). Pe de altă parte, conține algoritmul recursiv `markov` care primește matricea de tranziție a stărilor și simulează trecerea timpului, calculând probabilitatea exactă ca o acțiune să atingă prețul țintă în ziua `K`.
