"Copyright [2017] <Gavan Adrian-George, 314CA><Nicola Mihai-Eduard, 314CA"

Nume, prenume: Gavan, Adrian-George

Nume, prenume: Nicola, Mihai-Eduard

Grupa, seria: 314CA

Tema 3: Internet Movie Database

Data inceperii temei: 13-05-2017

Data finalizarii temei: 21-05-2017

Mod de lucru:
=============

- Echipa noastra nu a facut incarcari pe git pentru ca am lucrat unul langa 
celalalt la un laptop cu un ecran atasat.
- Cand unul din noi scria codul, in timp ce amandoi veneam cu idei, celalalt 
era atent ca nu cumva cel care scrie sa faca vreo greseala de cod. Cand cel care 
scria obosea, rolurile se inversau.
- Prima data, am facut analiza temei. Pentru gasirea celor mai bune solutii, 
am stabilit ca pentru o zi fiecare dintre noi sa gandeasca tema separat, sa se 
gandeasca ce structuri ar folosi si cum ar realiza functiile. Am facut acest lucru 
pentru ca in acest mod am fi avut 2 idei si am fi putut alege ce este mai bun din 
fiecare. Altfel, daca cineva ar fi spus o idee, amandoi ne-am fi concentrat pe acea 
idee si nu ne-am mai fi gandit la alta, poate mai buna.
- S-au scris toate structurile pe care am stabilit ca le vom folosi pe o tabla 
magnetica si am realizat cateva schite pentru fiecare functie.
- Desi amandoi gandeam problema, unul o scria si unul era atent la eventualele 
greseli de cod, a fost inevitabil sa nu avem multe erori de compilare, pe care 
le-am rezolvat ca o echipa.
- Lucrand amandoi unul langa celalalt pe tot parcursul temei nu am pus fisierele 
pe git pentru ca ar fi insemnat ca la final, dupa ce am facut toata tema 
impreuna, sa ne impartim functiile si sa le incarcam una cate una alternativ, 
ceea ce nu ar fi ajutat deloc pentru ca nu acesta era scopul temei.

Probleme intampinate:
=====================

1. Fiind o tema pe echipe, a fost ceva oarecum nou pentru majoritatea dintre noi. 
Eu si cu colegul meu am lucrat foarte bine in echipa, dar la inceput au fost 
probleme cu analiza situatiei, referitoare la ce structuri ar fi mai bine sa 
folosim si cum ar fi mai bine sa abordam tema.
2. Folosind foarte mult STL, amandoi am intampinat probleme la intelegerea 
structurilor din STL si cum pot fi acestea utilizate (in special la iteratori). 
3. Initial am realizat tema dupa un plan agreat de amandoi, dar cand au aparut 
testele am realizat ca aveam cateva timeout-uri si a trebuit sa regandim problema.
4. Am intampinat probleme la functia get_2nd_degree_colleagues pentru ca initial 
apareau dubluri. Nu tratam cazul cand de ex.: Ana joaca cu Mihai si Maria, iar
Ana joaca cu Ioana si Maria. In acest caz, inainte sa corectam eroarea, ar fi 
aparut de 2 ori Maria.
5. Functia get_avg_rating_in_range ne-a creat cele mai multe probleme, pentru 
ca nu am reusit sa o facem suficient de rapida cat sa treaca si ultimul test 
(local ruleaza in aproximativ 1 minut si 40-45 de secunde).

Prezentarea implementarii:
==========================

A. Functii folosite:
1. Functiile cerute:
- void add_movie(std::string movie_name, std::string movie_id, int timestamp,
                   std::vector<std::string> categories,
                   std::string director_name,
                   std::vector<std::string> actor_ids); - functie numerotata cu 11;
- void add_user(std::string user_id, std::string name); - functie numerotata cu 12;
- void add_actor(std::string actor_id, std::string name); - functie numerotata cu 13;
- void add_rating(std::string user_id, std::string movie_id, int rating); - functie numerotata cu 14;
- void update_rating(std::string user_id, std::string movie_id, int rating); - functie numerotata cu 15;
- void remove_rating(std::string user_id, std::string movie_id); - functie numerotata cu 16;
- std::string get_rating(std::string movie_id); - functie numerotata cu 1;
- std::string get_longest_career_actor(); - functie numerotata cu 2;
- std::string get_most_influential_director(); - functie numerotata cu 3;
- std::string get_best_year_for_category(std::string category); - functie numerotata cu 4;
- std::string get_2nd_degree_colleagues(std::string actor_id); - functie numerotata cu 5;
- std::string get_top_k_most_recent_movies(int k); - functie numerotata cu 6;
- std::string get_top_k_actor_pairs(int k); - functie numerotata cu 7;
- std::string get_top_k_partners_for_actor(int k, std::string actor_id); - functie numerotata cu 8;
- std::string get_top_k_most_popular_movies(int k); - functie numerotata cu 9;
- std::string get_avg_rating_in_range(int start, int end); - functie numerotata cu 10;
2. Functii suplimentare:
- Functie de comparare a 2 filme dupa numarul de rating-uri:
bool Compare(Film_NrRating i, Film_NrRating j);
- Functie de comparare a partenerilor dupa numarul de filme jucate:
bool Compare_Parteneri(Partener_Filme i, Partener_Filme j);
- Functie de comparare a perechilor de actori dupa numarul de filme jucate:
bool Compare_Perechi(Actors_Pairs i, Actors_Pairs j);

B. Structuri folosite:
- Unordered map in care se stocheaza date despre filme (Interogari 1,9):
std::unordered_map<std::string, Date_Film> Film;
- Unordered map pentru directori (directorul si cu ce actori a jucat) 
(Interogarea 3):
std::unordered_map<std::string, std::unordered_set<std::string> > Director;
- Unordered map cu date despre actori (Interogarile 2, 5, 8, 7):
std::unordered_map<std::string, Date_Actor> Actori;
- Unordered map pentru categorii (Interogarea 4):
std::unordered_map<std::string,
std::unordered_map<int, std::unordered_set<std::string> > > Categorie;
- Map in care se stocheaza un film id si timestampul acestuia (Interogarea 6):
std::map<int, std::string> Lansare;
- Se retine rezultatul ultimei sortari pentru interogarea "get top k actor pairs":
std::vector<Actors_Pairs> perechi_actori;
- Se retine rezultatul ultimei sortari pentru interogare "get top k most 
popular movies":
std::vector<Film_NrRating> popularitate;
- Map-ul in care se retine timestamp-ul si rating-ul pentru filmul corespunzator 
timestamp-ului:
std::map<int, double> time_rating;
- Structura pentru a retine partenerul unui actor si in cate filme au jucat impreuna:
struct Partener_Filme;
- Structura ce contine date despre un film:
struct Date_Film;
- Structura ce contine date despre un actor:
struct Date_Actor;
- Structura ce contine date despre o pereche de actori:
struct Actors_Pairs;
- Structura ce contine id-ul unui film si numarul de rating-uri:
struct Film_NrRating;

C. Algoritm utilizat:

- Functiile de adaugare:
1. add_movie:
- In variabila care retine ultima functie apelata se retine numarul functiei (11).
- Variabila in care se retine daca a fost adaugat un film se face "true".
- Se adauga movie_id, numele filmului si timestampul in umap-ul (unordered_map) Film.
- Se adauga directorul si actorii cu care a jucat acesta in umap-ul Director.
- In umap-ul Actori se adauga noii actori si toti colegii actorilor din noul film 
si se actualizeaza data_vechi si data_nou (in care se retin cel mai recent film 
si cel mai vechi film in care a jucat actorul).
- Se calculeaza anul filmului si se adauga filmul in umap-ul Categorie, in fiecare 
categorie din care face parte, in anul in care a aparut (structura Categorie 
contine categoriile filmelor si fiecare categorie contine anii in care au aparut 
filmele, iar fiecare an contine filmele care au aparut in acel an).
- Se introduce timestamp-ul si movie_id in map-ul Lansare (pentru interogarea 6).
2. add_user:
- In implementarea aleasa se foloseste doar user_id, care este luat din functia 
de add_rating. Se folosesc doua variabile a si b in care se retine user_id si 
name pentru a nu aparea warning-uri la compilare.
3. add_actor:
- In implementarea aleasa se foloseste doar user_id, care este luat din functia 
de add_movie. Se folosesc doua variabile a si b in care se retine actor_id si 
name pentru a nu aparea warning-uri la compilare.
4. add_rating:
- In variabila care retine ultima functie apelata se retine numarul functiei (14).
- In structura Film se adauga user_id-ul si rating-ul acestuia la filmul specific, 
se recalculeaza suma rating-urilor filmului si se incrementeaza numarul total de 
rating-uri al filmului.
- In structura time_rating se retine noul rating.
5. update_rating:
- In variabila care retine ultima functie apelata se retine numarul functiei (15).
- Se retine vechiul rating al user-ului si se scade din suma totala a rating-urilor 
filmului. User-ului i se atribuie noua valoare a rating-ului sau. Se recalculeaza 
suma cu noul rating.
- In structura time_rating se retine noul rating.
6. remove_rating:
- In variabila care retine ultima functie apelata se retine numarul functiei (16).
- Se retine vechiul rating al user-ului si se scade din suma totala a rating-urilor 
filmului. Se decrementeaza numarul total de rating-uri al filmului.
- Se elimina user_id-ul (al carui rating a fost sters) din structura.
- In structura time_rating se retine noul rating. Daca numarul de rating-uri este 0 
(deci nu mai este niciun rating pentru un anume film), se elimina din time_rating 
timestamp-ul corespunzator.

- Functiile de interogare:
1. get_rating:
- In variabila care retine ultima functie apelata se retine numarul functiei (1).
- Se returneaza "none" cand nu se regaseste filmul sau cand nu are niciun rating.
- Se calculeaza rating-ul.
- Se aproximeaza rating-ul si se converteste in string.
- Se elimina ultimele 4 zecimale.
- Se returneaza string-ul.
2. get_longest_career_actor:
- Daca ultima functie apelata a fost tot aceasta functie, returneaza rezultatul 
anterior.
- In variabila care retine ultima functie apelata se retine numarul functiei (2).
- Daca nu sunt actori, returneaza "none".
- Se retine cea mai lunga activitate.
- Pentru toti actorii, calculam activitatea lor si comparam cu cea mai lunga 
activitate.
- Daca 2 actori au cea mai lunga activitate, se retine actorul cu id-ul mai mic.
- Se returneaza string-ul.
3. get_most_influential_director:
- Daca ultima functie apelata a fost tot aceasta functie, returneaza rezultatul 
anterior.
- In variabila care retine ultima functie apelata se retine numarul functiei (3).
- Daca nu este niciun director, returneaza "none".
- Se verifica numarul de actori cu care a lucrat fiecare director si se retine 
numele celui care a lucrat cu cei mai multi actori.
- Daca doi directori au lucrat cu acelasi numar de actori, se retine primul 
ordonat crescator dupa nume.
- Se returneaza string-ul.
4. get_best_year_for_category:
- In variabila care retine ultima functie apelata se retine numarul functiei (4).
- In umap-ul Categorie se trece prin toti anii pentru categoria ceruta.
- Pentru fiecare film dintr-un an se calculeaza media rating-urilor filmului 
respectiv.
- Se face suma mediilor rating-urilor filmelor pentru anul respectiv si se imparte 
la numarul total de medii. 
- Se retine anul rating-ului maxim.
- Daca 2 rating-uri sunt la fel, se retine anul mai mic.
- Se transforma anul in string.
- Se returneaza string-ul.
5. get_2nd_degree_colleagues
- In variabila care retine ultima functie apelata se retine numarul functiei (5).
- Daca actor_id-ul nu se gaseste, returneaza "none".
- Se trece prin toti colegii de grad 1 ai actor_id.
- Se trece prin toti colegii de grad 1 ai actorilor (adica prin actorii de grad 2 
pentru actor_id).
- Se verifica ca actor_id nu se regaseste printre actorii cu care au jucat actorii 
de grad 2.
- Daca actor_id nu se regaseste se insereaza actorul in set-ul actori_grad2 
(inseamna ca actorul este coleg de grad 2 cu actor_id).
- Daca actori_grad2 are dimensiunea 0, se returneaza "none".
- Se trece prin toti actorii de grad 2 si se concateneaza la string-ul 
actori_grad2_str.
- Se extrage ultimul spatiu din sir si se returneaza actori_grad2_str.
6. get_top_k_most_recent_movies
- In variabila care retine ultima functie apelata se retine numarul functiei (6).
- Daca nu este niciun film, returneaza "none".
- Se parcurge map-ul lansare si se concateneaza cele k filme la string-ul 
top_recent_movies.
- Se extrage spatiul de la final.
- Se returneaza string-ul.
7. get_top_k_actor_pairs
- Daca nu este niciun actor, se returneaza "none".
- Avem cazul cand intre 2 apelari ale functiei a fost adaugat un film nou, si cand 
nu a fost adaugat un film nou.
- Daca un film nou a fost adaugat, se reseteaza variabila film_modificat in "false". 
In variabila care retine ultima functie apelata se retine numarul functiei (7). Daca 
vectorul in care trebuie introduse perechile de actori nu este gol, atunci trebuie 
golit. Se trece prin toti actorii si prin toti actorii cu care a jucat un actor si se 
introduc doar perechile care au id_1 < id_2 (pentru ca de ex.: Ion a jucat cu Mihai, 
dar actorul Mihai a jucat si el cu Ion. Daca luam toate perechile, am insera de 2 ori 
aceeasi pereche, asa ca luam doar perechile cu id_1<id_2 pentru a evita dublurile si 
pentru ca ne trebuie perechile sortate dupa id). Pe langa numele celor 2 actori se 
introduce si numarul de filme in care au jucat impreuna. Daca toate filmele au cate un 
actor si niciun actor nu a jucat cu alt actor, se returneaza "none". Se sorteaza noile 
date din vectorul perechi_actori.
- Daca nu a fost adaugat un film de la ultima apelare a functiei, se va executa doar 
bucata de algoritm urmatoare, pentru a extrage noul top k (chiar daca sunt aceleasi 
date in vector, k variaza). Daca a fost adaugat un film, aceasta bucata de algoritm 
tot va fi apelata pentru a extrage top k.
- Se verifica daca toate filmele au cate un actor si niciun actor nu a jucat cu alt 
actor (altfel, daca nu s-ar fi adaugat un alt film, cazul nu ar fi fost verificat).
- Se extrag cele k elemente si se concateneaza la sirul perechi_str.
- Se extrage ultimul spatiu si se returneaza string-ul.
8. get_top_k_parteners_for_actor
- In variabila care retine ultima functie apelata se retine numarul functiei (8).
- Daca nu se gaseste actor_id se returneaza "none".
- Se introduc in vectorul Parteneri toti actorii cu care a jucat actor_id si in cate 
filme au jucat cei 2 actori impreuna.
- Daca actorul nu a mai jucat cu nimeni se returneaza "none".
- Se sorteaza vectorul.
- Se extrag primii k parteneri si se concateneaza la string-ul parteneri_str.
- Se elimina spatiul de la final.
- Se returneaza parteneri_str.
9. get_top_k_most_popular_movies
- Daca nu este niciun film se returneaza "none".
- Avem cazul cand intre 2 apelari ale functiei a fost apelata alta functie si cand 
nu a fost apelata alta functie.
- Daca a fost apelata alta functie, in variabila care retine ultima functie apelata 
se retine numarul functiei (9). Daca vectorul in care trebuie introduse filmele nu 
este gol, atunci trebuie  golit. Se introduc filmele in vectorul popularitate si 
numarul de rating-uri al fiecaruia. Se sorteaza noile date din vectorul popularitate.
- Daca nu a fost apelata o functie diferita de la ultima apelare a functiei,
se va executa doar urmatoarea bucata din algoritm, pentru a extrage top k (chiar 
daca sunt aceleasi date in vector, k variaza). Daca a fost apelata alta functie, 
aceasta bucata de cod tot va fi apelata pentru a extrage top k.
- Se extrag primele k filme si se concateneaza la string-ul popularitate_str.
- Se extrage ultimul spatiu si se returneaza string-ul.
10. get_avg_rating_in_range
- In variabila care retine ultima functie apelata se retine numarul functiei (10).
- Se gaseste range-ul in care se va cauta in map-ul time_rating.
- Daca intervalul nu cuprinde nicio valoare din time_rating returneaza "none".
- Se trece prin toate valorile din range si se adauga media rating-urilor fiecarui 
film la suma mediilor si se incrementeaza numarul total de filme.
- Daca nu a fost niciun film in range se returneaza "none".
- Se calculeaza media finala, se rotunjeste media, se transforma in string si se 
scot zecimalele in plus. Rezultatul se retine in string-ul medie_finala_str.
- Se returneaza medie_finala_str.

Complexitatea temei: 10
=======================

Alte precizari:
===============
- Echipa noastra nu a utilizat git pentru ca (dupa cum am explicat si in "Mod de 
lucru") nu ne-a fost necesar, noi lucrand unul langa celalt la un calculator cu 
un monitor atasat, incercand sa scriem din prima un cod fara multe erori de 
compilare (amandoi veneam cu idei, unul scria si unul era mai atent la ce scrie 
celalalt, iar cand cel care scria obosea rolurile se inversau).
- Pe forumul temei s-a specificat ca nu este obligatorie folosirea github-ului si 
sper ca prin sectiunea "Mod de lucru" de la inceputul README am dat suficiente 
detalii despre cum am lucrat ca si echipa.
