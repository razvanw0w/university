//
// Created by razvan on 25.03.2019.
//

#include <iostream>
#include "Tests.h"
#include "../utils/dynamicarray.h"
#include "../repository/repository.h"
#include "../controller/adminController.h"
#include "../controller/userController.h"
#include "../exceptions/validationException.h"
#include "../utils/comparator.h"
#include "../utils/comparatorAscendingByTitle.h"
#include "../utils/comparatorDescendingByLikes.h"

void Tests::testAll() {
    testMovie();
    std::cout << "Movie test passed\n";
    testRepository();
    std::cout << "Repo test passed\n";
    testController();
    std::cout << "Controller test passed\n";
}

void Tests::testMovie() {
    testMovieGetTitle();
    testMovieSetTitle();
    testMovieGetGenre();
    testMovieSetGenre();
    testMovieGetYearOfRelease();
    testMovieSetYearOfRelease();
    testMovieGetNumberOfLikes();
    testMovieSetNumberOfLikes();
    testMovieGetTrailer();
    testMovieSetTrailer();
    testMovieEquality();
    testMovieNonEquality();
    testMovieGetCSVString();
    testMovieGetHTMLString();
    testMovieTokenizeString();
}

void Tests::testMovieGetTitle() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getGenre() == "bang");
    assert(movie2.getGenre() == "kabang");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieSetTitle() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getTitle() == "boom");
    assert(movie2.getTitle() == "kaboom");
    movie.setTitle("bang");
    movie2.setTitle("kabang");
    assert(movie.getTitle() == "bang");
    assert(movie2.getTitle() == "kabang");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetGenre() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getGenre() == "bang");
    assert(movie2.getGenre() == "kabang");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieSetGenre() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getGenre() == "bang");
    assert(movie2.getGenre() == "kabang");
    movie.setGenre("boom");
    movie2.setGenre("kaboom");
    assert(movie.getGenre() == "boom");
    assert(movie2.getGenre() == "kaboom");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetYearOfRelease() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getYearOfRelease() == 1990);
    assert(movie2.getYearOfRelease() == 1999);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieSetYearOfRelease() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getYearOfRelease() == 1990);
    assert(movie2.getYearOfRelease() == 1999);
    movie.setYearOfRelease(2000);
    movie2.setYearOfRelease(2001);
    assert(movie.getYearOfRelease() == 2000);
    assert(movie2.getYearOfRelease() == 2001);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetNumberOfLikes() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getNumberOfLikes() == 0);
    assert(movie2.getNumberOfLikes() == 0);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieSetNumberOfLikes() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getNumberOfLikes() == 0);
    assert(movie2.getNumberOfLikes() == 0);
    movie.setNumberOfLikes(1);
    movie2.setNumberOfLikes(2);
    assert(movie.getNumberOfLikes() == 1);
    assert(movie2.getNumberOfLikes() == 2);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetTrailer() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getTrailer() == "a");
    assert(movie2.getTrailer() == "b");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieSetTrailer() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie.getTrailer() == "a");
    assert(movie2.getTrailer() == "b");
    movie.setTrailer("c");
    movie2.setTrailer("d");
    assert(movie.getTrailer() == "c");
    assert(movie2.getTrailer() == "d");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieEquality() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};
    Movie movie3{movie};
    assert(!(movie == movie2));
    movie2.setTitle("boom");
    movie2.setGenre("bang");
    movie2.setYearOfRelease(1990);
    movie2.setTrailer("a");
    assert(movie == movie2);
    assert(movie == movie3);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieNonEquality() {
    Movie movie{"boom", "bang", 1990, 0, "a"};
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};

    assert(movie != movie2);
    movie2.setTitle("boom");
    movie2.setGenre("bang");
    movie2.setYearOfRelease(1990);
    movie2.setTrailer("a");
    assert(!(movie != movie2));
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetCSVString() {
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};
    assert(movie2.getCSVString() == "\"kaboom\",\"kabang\",\"1999\",\"0\",\"b\"");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieGetHTMLString() {
    Movie movie2{"kaboom", "kabang", 1999, 0, "b"};
    assert(movie2.getHTMLString() == "<tr><td>kaboom</td><td>kabang</td><td>1999</td><td>0</td><td><a href=\"b\">Link</a></td>");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testMovieTokenizeString() {
    std::string movie = "\"kaboom\",\"kabang\",\"1999\",\"0\",\"b\"";
    auto tokens = Movie::tokenizeString(movie);
    assert(tokens.size() == 5);
    assert(tokens[0] == "kaboom");
    assert(tokens[1] == "kabang");
    assert(tokens[2] == "1999");
    assert(tokens[3] == "0");
    assert(tokens[4] == "b");
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepository() {
    testRepositoryAddMovie();
    testRepositoryDeleteMovie();
    testRepositoryUpdateMovie();
    testRepositoryGetMovieAtIndex();
    testRepositoryGetNumberOfMovies();
    testRepositoryGetMoviesByGenre();
    testRepositoryGetNumberOfMoviesInWatchlist();
    testRepositoryGetMovieByTitleGenreYear();
    testRepositoryAddMovieToWatchlist();
    testRepositoryDeleteMovieFromWatchlist();
    testRepositoryGetWatchlistMovieAtIndex();
}

void Tests::testRepositoryAddMovie() {
    Repository repo;
    Movie movie1{"a", "b", 1, 2, "c"};
    Movie movie2{"x", "y", 3, 4, "z"};

    assert(repo.getNumberOfMovies() == 0);
    repo.addMovie(movie1);
    assert(repo.getNumberOfMovies() == 1);
    assert(repo.getMovieAtIndex(0) == movie1);
    try {
        repo.getMovieAtIndex(1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    repo.addMovie(movie2);
    assert(repo.getNumberOfMovies() == 2);
    assert(repo.getMovieAtIndex(1) == movie2);
    try {
        repo.addMovie(movie1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryDeleteMovie() {
    Repository repo;
    Movie movie1{"a", "b", 1, 2, "c"};
    Movie movie2{"x", "y", 3, 4, "z"};
    Movie movie3{"a", "a", 100, 200, "a"};

    try {
        repo.deleteMovie(movie1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    repo.addMovie(movie1);
    try {
        repo.deleteMovie(movie2);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    repo.addMovie(movie2);
    assert(repo.getNumberOfMovies() == 2);
    repo.deleteMovie(movie2);
    assert(repo.getNumberOfMovies() == 1);
    try {
        repo.getMovieAtIndex(1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    repo.deleteMovie(movie1);
    assert(repo.getNumberOfMovies() == 0);
    try {
        repo.getMovieAtIndex(0);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryUpdateMovie() {
    Repository repo;
    Movie movie1{"a", "b", 1, 2, "c"};
    Movie movie2{"x", "y", 3, 4, "z"};
    Movie movie3{"a", "b", 1, 200, "a"};

    try {
        repo.updateMovie(movie1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    try {
        repo.updateMovie(movie2);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    repo.addMovie(movie1);
    repo.addMovie(movie2);
    repo.updateMovie(movie3);
    assert(repo.getMovieAtIndex(0) == movie3);
    repo.updateMovie(movie1);
    assert(repo.getMovieAtIndex(0) == movie1);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetMovieAtIndex() {
    Repository repo;
    Movie movie1{"a", "b", 1, 2, "c"};
    Movie movie2{"x", "y", 3, 4, "z"};

    repo.addMovie(movie1);
    repo.addMovie(movie2);
    assert(repo.getMovieAtIndex(0) == movie1);
    assert(repo.getMovieAtIndex(1) == movie2);
    try {
        repo.getMovieAtIndex(-1);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    try {
        repo.getMovieAtIndex(2);
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetNumberOfMovies() {
    Repository repo;
    Movie movie1{"a", "b", 1, 2, "c"};
    Movie movie2{"x", "y", 3, 4, "z"};
    Movie movie3{"a", "b", 99, 200, "a"};

    assert(repo.getNumberOfMovies() == 0);
    repo.addMovie(movie1);
    assert(repo.getNumberOfMovies() == 1);
    repo.addMovie(movie2);
    assert(repo.getNumberOfMovies() == 2);
    repo.addMovie(movie3);
    assert(repo.getNumberOfMovies() == 3);
    repo.deleteMovie(movie3);
    assert(repo.getNumberOfMovies() == 2);
    repo.deleteMovie(movie2);
    assert(repo.getNumberOfMovies() == 1);
    repo.deleteMovie(movie1);
    assert(repo.getNumberOfMovies() == 0);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetMoviesByGenre() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    repo.addMovie(movie1);
    repo.addMovie(movie2);
    repo.addMovie(movie3);

    std::vector<Movie> d1 = repo.getMoviesByGenre("b");
    std::vector<Movie> d2 = repo.getMoviesByGenre("t");
    std::vector<Movie> d3 = repo.getMoviesByGenre("c");
    assert(d1.size() == 2);
    assert(d2.size() == 1);
    assert(d3.size() == 0);
    assert(d1[0] == movie1);
    assert(d1[1] == movie3);
    assert(d2[0] == movie2);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetNumberOfMoviesInWatchlist() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    assert(repo.getNumberOfMoviesInWatchlist() == 0);
    repo.addMovieToWatchlist(movie1);
    assert(repo.getNumberOfMoviesInWatchlist() == 1);
    repo.addMovieToWatchlist(movie2);
    assert(repo.getNumberOfMoviesInWatchlist() == 2);
    repo.addMovieToWatchlist(movie3);
    assert(repo.getNumberOfMoviesInWatchlist() == 3);
    repo.deleteMovieFromWatchlist(movie3);
    assert(repo.getNumberOfMoviesInWatchlist() == 2);
    repo.deleteMovieFromWatchlist(movie2);
    assert(repo.getNumberOfMoviesInWatchlist() == 1);
    repo.deleteMovieFromWatchlist(movie1);
    assert(repo.getNumberOfMoviesInWatchlist() == 0);
    try {
        repo.deleteMovieFromWatchlist(movie1);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetMovieByTitleGenreYear() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    repo.addMovie(movie1);
    repo.addMovie(movie2);
    repo.addMovie(movie3);

    assert(repo.getMovieByTitleGenreYear("a", "b", 1) == movie1);
    assert(repo.getMovieByTitleGenreYear("d", "t", 0) == movie2);
    assert(repo.getMovieByTitleGenreYear("c", "b", 0) == movie3);
    try {
        repo.getMovieByTitleGenreYear("x", "y", 100);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryAddMovieToWatchlist() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    assert(repo.getNumberOfMoviesInWatchlist() == 0);
    repo.addMovieToWatchlist(movie1);
    assert(repo.getNumberOfMoviesInWatchlist() == 1);
    repo.addMovieToWatchlist(movie2);
    assert(repo.getNumberOfMoviesInWatchlist() == 2);
    repo.addMovieToWatchlist(movie3);
    assert(repo.getNumberOfMoviesInWatchlist() == 3);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryDeleteMovieFromWatchlist() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    assert(repo.getNumberOfMoviesInWatchlist() == 0);
    repo.addMovieToWatchlist(movie1);
    assert(repo.getNumberOfMoviesInWatchlist() == 1);
    repo.addMovieToWatchlist(movie2);
    assert(repo.getNumberOfMoviesInWatchlist() == 2);
    repo.addMovieToWatchlist(movie3);
    assert(repo.getNumberOfMoviesInWatchlist() == 3);
    repo.deleteMovieFromWatchlist(movie3);
    assert(repo.getNumberOfMoviesInWatchlist() == 2);
    repo.deleteMovieFromWatchlist(movie2);
    assert(repo.getNumberOfMoviesInWatchlist() == 1);
    repo.deleteMovieFromWatchlist(movie1);
    assert(repo.getNumberOfMoviesInWatchlist() == 0);
    try {
        repo.deleteMovieFromWatchlist(movie1);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testRepositoryGetWatchlistMovieAtIndex() {
    Repository repo;
    Movie movie1{"a", "b", 1, 0, "x"};
    Movie movie2{"d", "t", 0, 0, "z"};
    Movie movie3{"c", "b", 0, 1, "y"};
    repo.addMovieToWatchlist(movie1);
    repo.addMovieToWatchlist(movie3);
    repo.addMovieToWatchlist(movie2);

    assert(repo.getWatchlistMovieAtIndex(0) == movie1);
    assert(repo.getWatchlistMovieAtIndex(1) == movie3);
    assert(repo.getWatchlistMovieAtIndex(2) == movie2);
    try{
        repo.getWatchlistMovieAtIndex(3);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    try{
        repo.getWatchlistMovieAtIndex(-1);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testController() {
    testAdminAddMovie();
    testAdminDeleteMovie();
    testAdminUpdateMovie();
    testAdminGetMovieList();
    testAdminSortVector();
    testUserListMoviesByGenre();
    testUserAddMovieToWatchList();
    testUserGoToNextMovieByGenre();
    testUserDeleteMovieFromWatchlist();
    testUserGetWatchlistMovieByIndex();
    testUserGetWatchListLength();
}

void Tests::testAdminAddMovie() {
    Repository repo;
    AdminController controller{repo};

    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "htt://"};
    std::vector<Movie> correctList;
    correctList.push_back(movie1);
    correctList.push_back(movie2);
    correctList.push_back(movie3);

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    std::vector<Movie> list = controller.adminGetMovieList();
    assert(list.size() == 1);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    list = controller.adminGetMovieList();
    assert(list.size() == 2);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    try {
        controller.adminAddMovie("a", "b", 99, 200, "a");
        assert(false);
    }
    catch (ValidationException& e) {
        assert(true);
    }
    list = controller.adminGetMovieList();
    assert(list.size() == 2);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testAdminDeleteMovie() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    std::vector<Movie> correctList;
    correctList.push_back(movie1);
    correctList.push_back(movie2);
    correctList.push_back(movie3);

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");
    std::vector<Movie> list = controller.adminGetMovieList();
    assert(list.size() == 3);
    controller.adminDeleteMovie("x", "y", 3900);
    list = controller.adminGetMovieList();
    assert(list.size() == 2);
    assert(list[0] == movie1);
    assert(list[1] == movie3);
    controller.adminDeleteMovie("a", "b", 1900);
    list = controller.adminGetMovieList();
    assert(list.size() == 1);
    assert(list[0] == movie3);
    controller.adminDeleteMovie("a", "b", 9900);
    list = controller.adminGetMovieList();
    assert(list.size() == 0);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testAdminUpdateMovie() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 1900, 200, "http://"};

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    try {
        controller.adminUpdateMovie("a", "b", 1900, 200, "a");
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    controller.adminUpdateMovie("a", "b", 1900, 200, "http://");
    auto list = controller.adminGetMovieList();
    assert(list[0] == movie3);
    assert(list[0].getNumberOfLikes() == 200);
    assert(list[1] == movie2);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testAdminGetMovieList() {
    Repository repo;
    AdminController controller{repo};

    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    std::vector<Movie> correctList;
    correctList.push_back(movie1);
    correctList.push_back(movie2);
    correctList.push_back(movie3);

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    std::vector<Movie> list = controller.adminGetMovieList();
    assert(list.size() == 1);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    list = controller.adminGetMovieList();
    assert(list.size() == 2);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    controller.adminAddMovie("a", "b", 9900, 200, "http://");
    list = controller.adminGetMovieList();
    assert(list.size() == 3);
    for (int i = 0; i < list.size(); ++i)
        assert(list[i] == correctList[i]);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserListMoviesByGenre() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    movie = userController.getCurrentMovie();
    assert(movie == movie1);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie3);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie1);

    userController.listMoviesByGenre("y");
    movie = userController.getCurrentMovie();
    assert(movie == movie2);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie2);

    try {
        userController.listMoviesByGenre("m");
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserAddMovieToWatchList() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    assert(userController.getWatchlistLength() == 0);
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 1);
    userController.goToNextMovieByGenre();
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 2);
    assert(userController.getWatchlistMovieByIndex(0) == movie1);
    assert(userController.getWatchlistMovieByIndex(1) == movie3);
    try {
        userController.addMovieToWatchlist();
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserGoToNextMovieByGenre() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    movie = userController.getCurrentMovie();
    assert(movie == movie1);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie3);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie1);

    userController.listMoviesByGenre("y");
    movie = userController.getCurrentMovie();
    assert(movie == movie2);
    userController.goToNextMovieByGenre();
    movie = userController.getCurrentMovie();
    assert(movie == movie2);

    try {
        userController.listMoviesByGenre("m");
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserDeleteMovieFromWatchlist() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"k", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("k", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    assert(userController.getWatchlistLength() == 0);
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 1);
    userController.goToNextMovieByGenre();
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 2);
    userController.deleteMovieFromWatchlist("k", "b", 9900, true);
    assert(userController.getWatchlistLength() == 1);
    userController.deleteMovieFromWatchlist("a", "b", 1900, false);
    assert(userController.getWatchlistLength() == 0);

    try {
        userController.deleteMovieFromWatchlist("x", "y", 0, false);
        assert(false);
    }
    catch (std::exception& e) {
        assert(true);
    }

    std::vector<Movie> list = controller.adminGetMovieList();
    movie3.setNumberOfLikes(201);
    assert(list[0] == movie1);
    assert(list[2] == movie3);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserGetWatchlistMovieByIndex() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    assert(userController.getWatchlistLength() == 0);
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 1);
    userController.goToNextMovieByGenre();
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 2);
    assert(userController.getWatchlistMovieByIndex(0) == movie1);
    assert(userController.getWatchlistMovieByIndex(1) == movie3);
    try {
        userController.addMovieToWatchlist();
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testUserGetWatchListLength() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 4, "https://"};
    Movie movie3{"a", "b", 9900, 200, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 4, "https://");
    controller.adminAddMovie("a", "b", 9900, 200, "http://");

    UserController userController{repo};
    userController.listMoviesByGenre("b");
    assert(userController.getWatchlistLength() == 0);
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 1);
    userController.goToNextMovieByGenre();
    userController.addMovieToWatchlist();
    assert(userController.getWatchlistLength() == 2);
    assert(userController.getWatchlistMovieByIndex(0) == movie1);
    assert(userController.getWatchlistMovieByIndex(1) == movie3);
    try {
        userController.addMovieToWatchlist();
        assert(false);
    }
    catch (std::exception& ex) {
        assert(true);
    }
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}

void Tests::testAdminSortVector() {
    Repository repo;
    AdminController controller{repo};
    Movie movie1{"a", "b", 1900, 2, "http://"};
    Movie movie2{"x", "y", 3900, 200, "https://"};
    Movie movie3{"f", "b", 9900, 3, "http://"};
    Movie movie;

    controller.adminAddMovie("a", "b", 1900, 2, "http://");
    controller.adminAddMovie("x", "y", 3900, 200, "https://");
    controller.adminAddMovie("f", "b", 9900, 3, "http://");
    std::vector <Movie> list1 = controller.adminGetMovieList();
    std::vector <Movie> list2 = controller.adminGetMovieList();
    Comparator <Movie> *comparatorTitle = new ComparatorAscendingByTitle;
    Comparator <Movie> *comparatorLikes = new ComparatorDescendingByLikes;

    AdminController::sortMoviesByCriteria(list1, *comparatorTitle);
    AdminController::sortMoviesByCriteria(list2, *comparatorLikes);
    delete comparatorLikes;
    delete comparatorTitle;

    assert(list1.size() == 3 && list2.size() == 3);
    assert(list1[0] == movie1);
    assert(list1[1] == movie3);
    assert(list1[2] == movie2);
    assert(list2[0] == movie2);
    assert(list2[1] == movie3);
    assert(list2[2] == movie1);
    std::cout << "Passed " << __PRETTY_FUNCTION__ << '\n';
    std::cout.flush();
}
