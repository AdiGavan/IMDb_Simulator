/* Copyright 2017 Andrei Petre */

#ifndef _HOME_STUDENT_RESOURCES_INCLUDE_IMDB_H_
#define _HOME_STUDENT_RESOURCES_INCLUDE_IMDB_H_

#include <string>
#include <vector>
#include <unordered_map>
#include <map>
#include <unordered_set>

#define NONE                            "none"

#define ADD_MOVIE                       "add_movie"
#define ADD_USER                        "add_user"
#define ADD_ACTOR                       "add_actor"
#define ADD_RATING                      "add_rating"
#define UPDATE_RATING                   "update_rating"
#define REMOVE_RATING                   "remove_rating"
// queries
#define GET_RATING                      "get_rating"
#define GET_LONGEST_CAREER_ACTOR        "get_longest_career_actor"
#define GET_MOST_INFLUENTIAL_DIRECTOR   "get_most_influential_director"
#define GET_BEST_YEAR_FOR_CATEGORY      "get_best_year_for_category"
#define GET_2ND_DEGREE_COLLEAGUES       "get_2nd_degree_colleagues"
#define GET_TOP_K_MOST_RECENT_MOVIES    "get_top_k_most_recent_movies"
#define GET_TOP_K_ACTOR_PAIRS           "get_top_k_actor_pairs"
#define GET_TOP_K_PARTNERS_FOR_ACTOR    "get_top_k_partners_for_actor"
#define GET_TOP_K_MOST_POPULAR_MOVIES   "get_top_k_most_popular_movies"
#define GET_AVG_RATING_IN_RANGE         "get_avg_rating_in_range"
#define MIN_TIME -2147483647

// Structura ce contine date despre un film
struct Date_Film {
  // Unordered map pentru fiecare user ce a dat rating la un anume film
  // si rating-ul userului respectiv
  std::unordered_map<std::string, int> user_rating;
  int suma_rating = 0;
  int nr_rating = 0;
  int timestamp;
  std::string nume_film;
};

// Structura ce contine date despre un actor
struct Date_Actor {
  // Unordered map pentru toti actorii cu care a jucat un actor
  std::unordered_map<std::string, int> actor_filme;
  // Se retine cel mai vechi si cel mai nou film in care a jucat un actor
  int data_vechi = MIN_TIME;
  int data_nou = MIN_TIME;
};

// Structura ce contine date despre o pereche de actori
struct Actors_Pairs {
  std::string actor_id1;
  std::string actor_id2;
  int numar_filme;
};

// Structura ce contine id-ul unui film si numarul de rating-uri
struct Film_NrRating {
  int numar_rating;
  std::string id_film;
};

class IMDb {
 public:
    IMDb();
    ~IMDb();

    void add_movie(std::string movie_name, std::string movie_id, int timestamp,
                   std::vector<std::string> categories,
                   std::string director_name,
                   std::vector<std::string> actor_ids);

    void add_user(std::string user_id, std::string name);
    void add_actor(std::string actor_id, std::string name);

    void add_rating(std::string user_id, std::string movie_id, int rating);
    void update_rating(std::string user_id, std::string movie_id, int rating);
    void remove_rating(std::string user_id, std::string movie_id);

    // queries
    std::string get_rating(std::string movie_id);
    std::string get_longest_career_actor();
    std::string get_most_influential_director();
    std::string get_best_year_for_category(std::string category);
    std::string get_2nd_degree_colleagues(std::string actor_id);
    std::string get_top_k_most_recent_movies(int k);
    std::string get_top_k_actor_pairs(int k);
    std::string get_top_k_partners_for_actor(int k, std::string actor_id);
    std::string get_top_k_most_popular_movies(int k);
    std::string get_avg_rating_in_range(int start, int end);

    // input reader helper.
    std::string read_input_line(const std::string& line);

 private:
    // add any variables you need here.
    // Unordered map in care se stocheaza date despre filme (Interogari 1,9)
    std::unordered_map<std::string, Date_Film> Film;

    // Unordered map pentru directori (directorul si cu ce actori a jucat)
    // (Interogarea 3)
    std::unordered_map<std::string, std::unordered_set<std::string> > Director;

    // Unordered map cu date despre actori (Interogarile 2, 5, 8, 7)
    std::unordered_map<std::string, Date_Actor> Actori;

    // Unordered map pentru categorii (Interogarea 4)
    // Se pun filmele pe categorii si ani
    std::unordered_map<std::string,
    std::unordered_map<int, std::unordered_set<std::string> > > Categorie;

    // Map in care se stocheaza un film id si timestampul acestuia
    // (Interogarea 6)
    std::map<int, std::string> Lansare;

    // Se retine rezultatul ultimei interogari "get longest career actor"
    std::string nume_activitate_maxima = "none";

    // Se retine rezultatul ultimei interogari "most influential director"
    std::string director_maxim = "none";

    // Se retine rezultatul ultimei sortari pentru interogarea
    // "get top k actor pairs"
    std::vector<Actors_Pairs> perechi_actori;

    // Se retine rezultatul ultimei sortari pentru interogare
    // "get top k most popular movies"
    std::vector<Film_NrRating> popularitate;

    // Map-ul in care se retine timestamp-ul si rating-ul
    // pentru filmul corespunzator timestamp-ului
    std::map<int, double> time_rating;

    // Variabila in care se retine daca s-a adaugat un nou film
    bool film_modificat = true;

    // Variabila in care se retine ultima functia apelata
    // 11-16 pentru adaugari, 1-10 pentru interogari
    int functie_anterioara = 0;
};

#endif  // _HOME_STUDENT_RESOURCES_INCLUDE_IMDB_H_
