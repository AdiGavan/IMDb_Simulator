/* Copyright 2017 Andrei Petre */

#include <math.h>
#include <utility>
#include <iterator>
#include <string>
#include <vector>
#include <algorithm>
#include <set>

#include "include/imdb.h"

#define MIN_TIME -2147483647

// Structura pentru a retine partenerul unui actor si in cate filme
// au jucat impreuna
struct Partener_Filme {
  int numar_filme;
  std::string nume_partener;
};

// Functie de comparare a 2 filme dupa numarul de rating-uri
bool Compare(Film_NrRating i, Film_NrRating j) {
  if (i.numar_rating > j.numar_rating) {
    return true;
  }
  if (i.numar_rating == j.numar_rating) {
    if (i.id_film < j.id_film) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

// Functie de comparare a partenerilor dupa numarul de
// filme jucate
bool Compare_Parteneri(Partener_Filme i, Partener_Filme j) {
  if (i.numar_filme > j.numar_filme) {
    return true;
  }
  if (i.numar_filme == j.numar_filme) {
    if (i.nume_partener < j.nume_partener) {
      return true;
    } else {
      return false;
    }
  }
  return false;
}

// Functie de comparare a perechilor de actori dupa
// numarul de filme jucate
bool Compare_Perechi(Actors_Pairs i, Actors_Pairs j) {
  if (i.numar_filme > j.numar_filme) {
    return true;
  }
  if (i.numar_filme == j.numar_filme) {
    if (i.actor_id1 < j.actor_id1) {
      return true;
    } else if (i.actor_id1 == j.actor_id1) {
      if (i.actor_id2 < j.actor_id2) {
        return true;
      }
    }
    return false;
  }
  return false;
}

IMDb::IMDb() {
    // initialize what you need here.
}

IMDb::~IMDb() {}

void IMDb::add_movie(std::string movie_name,
                     std::string movie_id,
                     int timestamp,  // unix timestamp when movie was launched
                     std::vector<std::string> categories,
                     std::string director_name,
                     std::vector<std::string> actor_ids) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 11;

  // A fost adaugat un film nou
  film_modificat = true;

  // Se adauga numele filmului si id-ul in
  // map-ul Film pentru interogarile 1 si 9;
  Film[movie_id].nume_film = movie_name;

  // Se adauga timestamp-ul filmului pentru interogarea 10
  Film[movie_id].timestamp = timestamp;

  // Se trece prin toti actorii filmului si se adauga in
  // map-ul Director si in Actori
  for (auto it = actor_ids.begin(); it != actor_ids.end(); it++) {
    // Pentru directori (pentru interogarea 3)
    Director[director_name].insert(*it);
    // Pentru structura cu actori (interogarile 2, 5, 7, 8)
    if (Actori[*it].data_vechi == MIN_TIME) {  // Cazul cand e primul film
      Actori[*it].data_vechi = timestamp;
      Actori[*it].data_nou = timestamp;
    } else {
      if (timestamp < Actori[*it].data_vechi) {
        Actori[*it].data_vechi = timestamp;
      }
      if (timestamp > Actori[*it].data_nou) {
        Actori[*it].data_nou = timestamp;
      }
    }

    // Tot pentru map-ul cu actori
    // (Setul cu actorii ce contine actorii care au jucat un actor)
    for (auto it2 = actor_ids.begin(); it2 != actor_ids.end(); it2++) {
      if (*it2 != *it) {
        Actori[*it].actor_filme[*it2]++;
      }
    }
  }

  // Pentru map-ul Categorie (interogarea 4)
  // Se calculeaza timestamp-ul
  time_t t = timestamp;
  struct tm tm;
  gmtime_r(&t, &tm);

  // Se introduce movie_id in categoriile respective filmului,
  // in anii corespunzatori
  for (auto it = categories.begin(); it != categories.end(); it++) {
    Categorie[*it][tm.tm_year + 1900].insert(movie_id);
  }

  // Se introduce timestamp-ul si movie_id in
  // map-ul pentru interogarile 6
  Lansare.insert(std::pair<int, std::string>(timestamp, movie_id));
}

void IMDb::add_user(std::string user_id, std::string name) {
  // In implementarea aleasa se foloseste doar user_id,
  // care este luat din functia add_rating.
  // Se folosesc doua variabile a si b pentru a nu aparea
  // warning-uri la compilare
  std::string a = user_id;
  std::string b = name;
}

void IMDb::add_actor(std::string actor_id, std::string name) {
  // In implementarea aleasa se foloseste doar actor_id,
  // care este luat din functia add_movie.
  // Se folosesc doua variabile a si b pentru a nu aparea
  // warning-uri la compilare
  std::string a, b;
  a = actor_id;
  b = name;
}

void IMDb::add_rating(std::string user_id, std::string movie_id, int rating) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 14;

  // Se gaseste filmul
  auto it = Film.find(movie_id);
  if (it == Film.end()) {  // Cazul cand filmul nu se gaseste
    return;
  } else {
    // Se adauga user-ul si rating-ul corespunzator
    Film[movie_id].user_rating[user_id] = rating;
    // Se adauga valoarea rating-ului la suma rating-urilor filmului
    Film[movie_id].suma_rating += rating;
    // Se incrementeaza numarul de rating-uri al filmului
    Film[movie_id].nr_rating++;

    // Se retine in time_rating noul rating al filmului
    time_rating[Film[movie_id].timestamp] = (double)Film[movie_id].suma_rating
                                            / (double)Film[movie_id].nr_rating;
  }
}

void IMDb::update_rating(std::string user_id, std::string movie_id,
                         int rating) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 15;

  // Se gaseste si se scade vechea valoare din suma rating-urilor filmului
  int old_rating = Film[movie_id].user_rating[user_id];
  Film[movie_id].suma_rating -= old_rating;
  // Se updateaza valoarea rating-ului
  Film[movie_id].user_rating[user_id] = rating;
  // Se adauga noua valoare la suma rating-urilor filmului
  Film[movie_id].suma_rating += rating;

  // Se retine in time_rating noul rating al filmului
  time_rating[Film[movie_id].timestamp] = (double)Film[movie_id].suma_rating
                                          / (double)Film[movie_id].nr_rating;
}

void IMDb::remove_rating(std::string user_id, std::string movie_id) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 16;

  // Se gaseste si se scade valoarea din suma rating-urilor filmului
  int old_rating = Film[movie_id].user_rating[user_id];
  Film[movie_id].suma_rating -= old_rating;
  // Se decrementeaza numarul total de rating-uri
  Film[movie_id].nr_rating--;
  // Se sterge rating-ul user_id-ului
  Film[movie_id].user_rating.erase(user_id);

  // Daca filmul nu mai are niciun rating, se elimina din
  // time_rating
  if (Film[movie_id].nr_rating == 0){
    time_rating.erase(Film[movie_id].timestamp);
    // Daca mai are rating-uri, se retine in time_rating noul rating al filmului
  } else {
    time_rating[Film[movie_id].timestamp] = (double)Film[movie_id].suma_rating
                                            / (double)Film[movie_id].nr_rating;
  }
}

std::string IMDb::get_rating(std::string movie_id) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 1;

  if (Film.find(movie_id) == Film.end()) {  // Cazul cand nu este filmul
    return "none";
  }

  if (Film[movie_id].nr_rating == 0) {  // Cazul cand nu este niciun rating
    return "none";
  }

  double rating_film;  // Variabila pentru rating-ul filmului
  std::string rating_film_str;  // Stringul care va fi returnat

  // Se calculeaza rating-ul
  rating_film = (double)Film[movie_id].suma_rating /
                (double)Film[movie_id].nr_rating;
  // Se aproximeaza si se transforma in string
  rating_film_str = std::to_string(round(rating_film * 100) / 100);
  size_t dotIndex = rating_film_str.find(".");
  rating_film_str = rating_film_str.substr(0, dotIndex + 3);

  return rating_film_str;
}

std::string IMDb::get_longest_career_actor() {
  // Daca ultima functie apelata a fost tot aceasta functie,
  // se returneaza ultimul rezultat
  if (functie_anterioara == 2) {
    return nume_activitate_maxima;
  }

  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 2;

  if (Actori.size() == 0) {   // Cazul cand nu sunt actori
    return "none";
  }

  // Variabila in care se retine cea mai mare activitate
  int activitate_maxima = -1;

  // Se verifica toti actorii
  for (auto it = Actori.begin(); it != Actori.end(); it++) {
    // Cazul cand nu a jucat in niciun film
    if (Actori[it->first].data_vechi == MIN_TIME) {
      continue;
      // Cazul cand actorul verificat are activitate mai mare
    } else if (Actori[it->first].data_nou - Actori[it->first].data_vechi >
               activitate_maxima) {
      activitate_maxima = Actori[it->first].data_nou -
                          Actori[it->first].data_vechi;
      nume_activitate_maxima = it->first;
      // Cazul cand au aceeasi activitate
    } else if (Actori[it->first].data_nou - Actori[it->first].data_vechi ==
               activitate_maxima) {
      if (it->first < nume_activitate_maxima) {
        nume_activitate_maxima = it->first;
      }
    }
  }

  // Cazul cand toti actorii nu au jucat in niciun film
  if (activitate_maxima == -1) {
    return "none";
  }

  return nume_activitate_maxima;
}

std::string IMDb::get_most_influential_director() {
  // Daca ultima functie apelata a fost tot aceasta functie,
  // se returneaza ultimul rezultat
  if (functie_anterioara == 3) {
    return director_maxim;
  }

  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 3;

  // Se retine numarul maxim de actori cu care a jucat un director
  unsigned int numar_actori_maxim = 0;

  // Daca nu este niciun director
  if (Director.size() == 0) {
    return "none";
  }

  // Se verifica toti directorii
  for (auto it = Director.begin(); it != Director.end(); it++) {
    // Cazul cand directorul verificat are mai multi actori
    if (numar_actori_maxim < Director[it->first].size()) {
      numar_actori_maxim = Director[it->first].size();
      director_maxim = it->first;
      // Cazul cand au acelasi numar de actori
    } else if (numar_actori_maxim == Director[it->first].size()) {
      if (director_maxim > it->first) {
        director_maxim = it->first;
      }
    }
  }

  return director_maxim;
}

std::string IMDb::get_best_year_for_category(std::string category) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 4;

  // Cand tot map-ul Categorie este gol (nu a fost adaugat niciun film)
  if (Categorie.size() == 0) {
    return "none";
  }

  // Cazul cand nu a fost adaugat niciun film din categoria respectiva
  if (Categorie.find(category) == Categorie.end()) {
    return "none";
  }

  // Variabila in care se retine numarul total de medii
  int numar_total_medii = 0;
  int an = -1;  // Variabila in care se retine cel mai bun an
  std::string an_str;  // String-ul ce va fi returnat
  double rating_maxim = -1;  // Variabila in care se retine rating-ul maxim
  // Variabila in care se va retine suma mediilor
  // rating-urilor filmelor din fiecare an
  double suma_total_medii = 0;
  // Variabila in care se retine media rating-urilor fiecarui film
  double medie_film = 0;

  // Se verifica fiecare an
  for (auto it = Categorie[category].begin();
       it != Categorie[category].end(); it++) {
    // Se reinitializeaza variabilele pentru fiecare an
    suma_total_medii = 0;
    numar_total_medii = 0;
    // Se verifica toate filmele din fiecare an
    for (auto it2 = Categorie[category][it->first].begin();
         it2 != Categorie[category][it->first].end(); it2++) {
      if (Film[*it2].nr_rating == 0) {  // Cand filmul nu are niciun rating
        continue;
      }
      // Se calculeaza media rating-urilor unui film
      medie_film = (double)Film[*it2].suma_rating /
                   (double)Film[*it2].nr_rating;
      // Se adauga media unui film la totalul mediilor
      suma_total_medii += medie_film;
      // Se incrementeaza numarul de medii
      numar_total_medii++;
    }
    // Cazul cand ratingul maxim e mai mic decat
    // media rating-urilor din alt an
    if (numar_total_medii != 0 && (rating_maxim < suma_total_medii /
                                   numar_total_medii)) {
      rating_maxim = suma_total_medii / numar_total_medii;
      an = (it->first);
      // Cazul cand ratingul e egal
    } else if (numar_total_medii != 0 && (rating_maxim == suma_total_medii /
                                          numar_total_medii)) {
      if (an > (it->first)) {
        an = (it->first);
      }
    }
  }

  // Cazul cand niciun film din Categorie nu are rating
  if (an == -1) {
    return "none";
  }

  // Se transforma anul in string
  an_str = std::to_string(an);

  return an_str;
}

std::string IMDb::get_2nd_degree_colleagues(std::string actor_id) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 5;

  // Cazul cand nu se gaseste actorul
  if (Actori.find(actor_id) == Actori.end()) {
    return "none";
  }

  // String-ul ce va fi returnat
  std::string actori_grad2_str;
  // Set-ul in care se adauga toti actorii de grad 2
  std::set<std::string> actori_grad2;

  // Se verifica toti colegii de grad 1 ai actorului dat
  for (auto it = Actori[actor_id].actor_filme.begin(); it !=
       Actori[actor_id].actor_filme.end(); it++) {
    // Se verifica toti colegii de grad 2 ai actorului dat
    for (auto it2 = Actori[it->first].actor_filme.begin(); it2 !=
         Actori[it->first].actor_filme.end(); it2++) {
      // Actor1 - Actor2 apare si ca Actor2 - Actor1
      // si trebuie sarita "dublura"
      if (it2->first == actor_id) {
        continue;
      }
      // Daca printre actorii cu care au jucat actorii de grad 2
      // nu se regaseste si actor_id, inseamna ca sunt colegi
      // de grad 2 si se adauga in set-ul actorilor
      if (Actori[it2->first].actor_filme.find(actor_id) ==
          Actori[it2->first].actor_filme.end()) {
        actori_grad2.insert(it2->first);
      }
    }
  }

  // Cazul cand actorul nu are niciun coleg de grad 2
  if (actori_grad2.size() == 0) {
    return "none";
  }

  // Se concateneaza toti actorii intr-un string
  for (auto it = actori_grad2.begin(); it != actori_grad2.end(); it++) {
    actori_grad2_str += *it;
    actori_grad2_str += " ";
  }

  // Se extrage ultimul spatiu din sir
  actori_grad2_str = actori_grad2_str.substr(0, actori_grad2_str.size() - 1);

  return actori_grad2_str;
}

std::string IMDb::get_top_k_most_recent_movies(int k) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 6;

  // String-ul ce va fi returnat
  std::string top_recent_movies;
  // Contor pentru a stii cand s-au extras top k filme
  int contor_recent_movies = 1;
  // Cazul cand nu este niciun film
  if (Lansare.size() == 0) {
    return "none";
  }

  // Se parcurge ordered map-ul Lansare
  for (auto rit = Lansare.rbegin(); rit != Lansare.rend(); ++rit) {
    if (contor_recent_movies <= k) {
      // Se concateneaza id-ul fimului
      top_recent_movies = top_recent_movies + rit->second;
      // Se incrementeaza contorul
      contor_recent_movies++;
      // Se adauga spatiu
      top_recent_movies += " ";
    } else {  // Cazul cand k este mai mare decat numarul de filme
      // Se scoate spatiul de la final si se returneaza string-ul
      top_recent_movies = top_recent_movies.substr
                          (0, top_recent_movies.size() - 1);
      return top_recent_movies;
    }
  }

  // Cazul cand k este mai mic decat numarul de filme
  // Se scoate spatiul de la final si se returneaza string-ul
  top_recent_movies = top_recent_movies.substr(0, top_recent_movies.size() - 1);
  return top_recent_movies;
}

std::string IMDb::get_top_k_actor_pairs(int k) {
  // String-ul ce va fi returnat
  std::string perechi_str;

  // Cazul cand nu este niciun actor
  if (Actori.size() == 0) {
    return "none";
  }

  // Cazul cand a fost adaugat un nou film
  if (film_modificat == true) {
    // Se reseteaza valoarea lui film_modificat pentru ca ultima functie
    // apelata va fi chiar aceasta functie
    film_modificat = false;
    // Se seteaza valoarea ultimei functii apelate
    functie_anterioara = 7;

    Actors_Pairs temp;

    // Daca vectorul in care vor fi introduse perechile de actori nu este gol
    // trebuie sa fie golit
    if (perechi_actori.size() != 0) {
      perechi_actori.clear();
    }

    // Se trece prin fiecare actor
    for (auto it = Actori.begin(); it != Actori.end(); it++) {
      // Se introduc doar perechile cu id1 < id2 pentru ca dublurile
      // vor fi in ordine inversa
      // Se trece prin toti actorii cu care a jucat un actor
      for (auto it2 = Actori[it->first].actor_filme.begin(); it2 !=
           Actori[it->first].actor_filme.end(); it2++) {
        if (it->first < it2->first) {
          temp.actor_id1 = it->first;
          temp.actor_id2 = it2->first;
          temp.numar_filme = it2->second;
          perechi_actori.push_back(temp);
        }
      }
    }
    // Cazul cand toate filmele au cate un actor si niciun
    // actor nu a jucat cu alt actor
    if (perechi_actori.size() == 0) {
      return "none";
    }

    // Se sorteaza vectorul
    std::sort(perechi_actori.begin(), perechi_actori.end(), Compare_Perechi);
  }

  /* Daca nu a fost adaugat un film de la ultima apelare a functiei,
     se va executa doar aceasta bucata de cod (de mai jos), pentru a extrage
     top k (chiar daca sunt aceleasi perechi de actori, k variaza). Daca a fost
     adaugat un film, aceasta bucata de cod tot va fi apelata pentru a
     extrage top k */

  // Cazul cand toate filmele au cate un actor
  // si niciun actor nu a jucat cu alt actor
  if (perechi_actori.size() == 0) {
    return "none";
  }

  // Se extrag k elementa si se concateneaza la sirul ce va fi returnat
  for (auto it = perechi_actori.begin(); it != perechi_actori.end(); it++) {
    if (k == 0) {
      break;
    }
    k--;
    perechi_str += "(";
    perechi_str += it->actor_id1;
    perechi_str += " ";
    perechi_str += it->actor_id2;
    perechi_str += " ";
    perechi_str += std::to_string(it->numar_filme);
    perechi_str += ") ";
  }

  // Se extrage ultimul spatiu si se returneaza sirul
  perechi_str = perechi_str.substr(0, perechi_str.size() - 1);
  return perechi_str;
}

std::string IMDb::get_top_k_partners_for_actor(int k, std::string actor_id) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 8;

  // Vectorul in care se introduc toti actorii cu care a jucat actor_id
  std::vector<Partener_Filme> Parteneri;
  // String-ul ce va fi returnat
  std::string parteneri_str;
  Partener_Filme temp;

  // Cazul cand nu se gaseste actor_id
  if (Actori.find(actor_id) == Actori.end()) {
    return "none";
  }

  // Se introduc in vector toti actorii cu care a jucat actor_id
  for (auto it = Actori[actor_id].actor_filme.begin(); it !=
       Actori[actor_id].actor_filme.end(); it++) {
    temp.nume_partener = it->first;
    temp.numar_filme = it->second;
    Parteneri.push_back(temp);
  }

  // Cazul cand actorul nu a mai jucat cu nimeni
  if (Parteneri.size() == 0) {
    return "none";
  }

  // Se sorteaza vectorul
  std::sort(Parteneri.begin(), Parteneri.end(), Compare_Parteneri);

  // Se extrag k elemente din vector si se concateneaza la parteneri_str
  for (auto it = Parteneri.begin(); it != Parteneri.end(); it++) {
    if (k == 0) {
      break;
    }
    k--;
    parteneri_str += it->nume_partener;
    parteneri_str += " ";
  }

  // Se extrage ultimul spatiu si se returneaza string-ul
  parteneri_str = parteneri_str.substr(0, parteneri_str.size() - 1);
  return parteneri_str;
}

std::string IMDb::get_top_k_most_popular_movies(int k) {
  // Cazul cand nu este niciun film
  if (Film.size() == 0) {
    return "none";
  }

  // String-ul ce va fi returnat
  std::string popularitate_str;

  // Cazul cand a fost apelata o alta functie diferita inainte de aceasta
  if (functie_anterioara != 9) {
    // Se seteaza valoarea ultimei functii apelate
    functie_anterioara = 9;

    Film_NrRating temp;

    // Daca vectorul in care vor fi introduse filmele nu este gol
    // trebuie sa fie golit
    if (popularitate.size() != 0) {
      popularitate.clear();
    }
    // Se introduc filmele in vectorul popularitate
    for (auto it = Film.begin(); it != Film.end(); it++) {
      temp.numar_rating = Film[it->first].nr_rating;
      temp.id_film = it->first;
      popularitate.push_back(temp);
    }

    // Se sorteaza vectorul
    std::sort(popularitate.begin(), popularitate.end(), Compare);
  }

  /* Daca nu a fost apelata o functie diferita de la ultima apelare a functiei,
     se va executa doar aceasta bucata de cod (de mai jos), pentru a extrage
     top k (chiar daca sunt aceleasi date in vector, k variaza). Daca a fost
     apelata alta functie, aceasta bucata de cod tot va fi apelata pentru
     a extrage top k */


  // Se extrag k elementa si se concateneaza la string-ul popularitate_str
  for (auto it = popularitate.begin(); it != popularitate.end(); it++) {
    if (k == 0) {
      break;
    }
    k--;
    popularitate_str += it->id_film;
    popularitate_str += " ";
  }

  // Se extrage ultimul spatiu si se returneaza string-ul
  popularitate_str = popularitate_str.substr(0, popularitate_str.size() - 1);
  return popularitate_str;
}

std::string IMDb::get_avg_rating_in_range(int start, int end) {
  // Se seteaza valoarea ultimei functii apelate
  functie_anterioara = 10;

  // Variabila in care se retine numarul total de filme
  int nr_filme = 0;
  // Variabila in care se retine suma mediilor filmelor
  double suma_medii = 0;
  // Variabila in care se retine media finala
  double medie_finala = 0;
  // String-ul ce va fi returnat
  std::string medie_finala_str;

  // Se gaseste range-ul in care se va cauta in map-ul time_rating
  auto margine_sup = time_rating.lower_bound(start);
  // Cazul cand intervalul nu cuprinde nicio valoare time_rating
  if (margine_sup->first > end){
    return "none";
  }
  auto margine_inf = time_rating.upper_bound(end);

  // Se trece prin toate valorile din range
  for (auto it = margine_sup; it != margine_inf; it++) {
    // Se adauga media rating-urilor filmului la suma mediilor
    // si se incrementeaza numarul de filme
      suma_medii += it->second;
      nr_filme++;
  }

  // Cazul cand nu a fost niciun film in range
  if (nr_filme == 0) {
    return "none";
  }

  // Se calculeaza media finala
  medie_finala = suma_medii / nr_filme;
  // Se rotunjeste media, se transforma in string si se scot zecimalele in plus
  medie_finala_str = std::to_string(round(medie_finala * 100) / 100);
  medie_finala_str = medie_finala_str.substr(0, medie_finala_str.size() - 4);

  return medie_finala_str;
}
