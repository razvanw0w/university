#ifndef OOP5_MOVIE_H
#define OOP5_MOVIE_H

#include <string>
#include <vector>

class Movie {
private:
    std::string title;
    std::string genre;
    int yearOfRelease;
    int numberOfLikes;
    std::string trailer;

public:
    static std::vector<std::string> tokenizeString(const std::string &movieString);
    explicit Movie(const std::string &title = "", const std::string &genre = "", int yearOfRelease = 1900, int numberOfLikes = 0, const std::string &trailer = "");
    const std::string &getTitle() const;
    void setTitle(const std::string &title);
    const std::string &getGenre() const;
    void setGenre(const std::string &genre);
    int getYearOfRelease() const;
    void setYearOfRelease(int yearOfRelease);
    int getNumberOfLikes() const;
    void setNumberOfLikes(int numberOfLikes);
    const std::string &getTrailer() const;
    void setTrailer(const std::string &trailer);
    bool operator==(const Movie &rhs) const;
    bool operator!=(const Movie &rhs) const;
    Movie(const Movie& otherMovie);
    friend std::ostream& operator<< (std::ostream& outStream, const Movie& movie);
    friend std::istream& operator>> (std::istream& inStream, Movie& movie);
    std::string getCSVString() const;
    std::string getHTMLString() const;
};


#endif //OOP5_MOVIE_H
