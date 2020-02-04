//
// Created by razvan on 25.03.2019.
//

#ifndef OOP5_TESTS_H
#define OOP5_TESTS_H

#include "../utils/dynamicarray.h"
#include "../domain/movie.h"
#include <cassert>

class Tests {
private:
    static void testDynamicArrayCopyConstructor();
    static void testDynamicArrayCopyAssignmentOperator();
    static void testDynamicArrayAppend();
    static void testDynamicArrayRemove();
    static void testDynamicArraySearch();
    static void testDynamicArrayUpdate();
    static void testDynamicArrayIndexingOperator();
    static void testDynamicArrayLength();
    static void testDynamicArrayPlusOperators();
    static void testMovie();
    static void testMovieGetTitle();
    static void testMovieSetTitle();
    static void testMovieGetGenre();
    static void testMovieSetGenre();
    static void testMovieGetYearOfRelease();
    static void testMovieSetYearOfRelease();
    static void testMovieGetNumberOfLikes();
    static void testMovieSetNumberOfLikes();
    static void testMovieGetTrailer();
    static void testMovieSetTrailer();
    static void testMovieEquality();
    static void testMovieNonEquality();
    static void testMovieGetCSVString();
    static void testMovieGetHTMLString();
    static void testMovieTokenizeString();
    static void testRepository();
    static void testRepositoryAddMovie();
    static void testRepositoryDeleteMovie();
    static void testRepositoryUpdateMovie();
    static void testRepositoryGetMovieAtIndex();
    static void testRepositoryGetNumberOfMovies();
    static void testRepositoryGetMoviesByGenre();
    static void testRepositoryGetNumberOfMoviesInWatchlist();
    static void testRepositoryGetMovieByTitleGenreYear();
    static void testRepositoryAddMovieToWatchlist();
    static void testRepositoryDeleteMovieFromWatchlist();
    static void testRepositoryGetWatchlistMovieAtIndex();
    static void testController();
    static void testAdminAddMovie();
    static void testAdminDeleteMovie();
    static void testAdminUpdateMovie();
    static void testAdminGetMovieList();
    static void testAdminSortVector();
    static void testUserListMoviesByGenre();
    static void testUserAddMovieToWatchList();
    static void testUserGoToNextMovieByGenre();
    static void testUserDeleteMovieFromWatchlist();
    static void testUserGetWatchlistMovieByIndex();
    static void testUserGetWatchListLength();

public:
    static void testAll();
};


#endif //OOP5_TESTS_H
