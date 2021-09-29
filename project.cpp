#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <set>
using namespace std;

class imdbMovie
{
private:
    string titleId;
    int ordering;
    string title;
    string region;
    string language;
    list<string> types;
    list<string> attributes;
    bool isOriginalTitle;
    double averageRating;
    int numVotes;

public:
    //setter
    void set_titleId(string titleId)
    {
        this->titleId = titleId;
    }
    void set_ordering(int ordering)
    {
        this->ordering = ordering;
    }
    void set_title(string title)
    {
        this->title = title;
    }
    void set_region(string region)
    {
        this->region = region;
    }
    void set_laguage(string language)
    {
        this->language = language;
    }
    void set_types(list<string> types)
    {
        this->types = types;
    }
    void set_attributes(list<string> attributes)
    {
        this->attributes = attributes;
    }
    void set_isOriginalTitle(bool isOriginalTitle)
    {
        this->isOriginalTitle = isOriginalTitle;
    }
    void set_averageRating(double averageRating)
    {
        this->averageRating = averageRating;
    }
    void set_numVotes(int numVotes)
    {
        this->numVotes = numVotes;
    }
    //getter
    string get_titleId() const
    {
        return this->titleId;
    }
    int get_ordering() const
    {
        return this->ordering;
    }
    string get_title() const
    {
        return this->title;
    }
    string get_region() const
    {
        return this->region;
    }
    string get_laguage() const
    {
        return this->language;
    }
    list<string> get_types() const
    {
        return this->types;
    }
    list<string> get_attributes() const
    {
        return this->attributes;
    }
    bool get_isOriginalTitle() const
    {
        return this->isOriginalTitle;
    }
    double get_averageRating() const
    {
        return this->averageRating;
    }
    int get_numVotes() const
    {
        return this->numVotes;
    }
    //constractor
    imdbMovie()
    {
    }
    imdbMovie(string titleId, int ordering, string title, string region, string language, list<string> types, list<string> attributes, bool isOriginalTitle, double averageRating = 0, int numVotes = 0)
    {
        this->titleId = titleId;
        this->ordering = ordering;
        this->title = title;
        this->region = region;
        this->language = language;
        this->types = types;
        this->attributes = attributes;
        this->isOriginalTitle = isOriginalTitle;
        this->averageRating = averageRating;
        this->numVotes = numVotes;
    }
    //print
    void print(int i)
    {
        cout <<'(' << i + 1 << ")\t" << this->titleId << '\t' << this->ordering << '\t'<< this->title << '\t' << this->region << '\t' << this->language << '\t';
        for(auto it = this->types.begin(); it != this->types.end(); it++)
            cout << *it <<' ';
        cout << '\t';
        for(auto it = this->attributes.begin(); it != this->attributes.end(); it++)
            cout << *it <<' ';
        cout << '\t' <<  boolalpha <<this->isOriginalTitle << '\t' << this->averageRating << '\t' << this->numVotes << endl;
    }
};
class user{
private:
    string username;
    string password;
    set<string> ratedFilm;
public:
    //setter
    void set_username(string username)
    {
        this->username = username;
    }
    void set_password(string password)
    {
        this->password = password;
    }
    void set_ratedFilm(set<string> ratedFilm){
        this->ratedFilm = ratedFilm;
    }
    //getter
    string get_username() const
    {
        return this->username;
    }
    string get_password() const
    {
        return this->password;
    }
    set<string> get_ratedFilm() const
    {
        return this->ratedFilm;
    }
    //
    user()
    {
    }
    user(string username, string password, set<string> ratedFilm)
    {
        this->username = username;
        this->password = password;
        this->ratedFilm = ratedFilm;
    }
    //operator
    bool operator==(user second)
    {
        if(this->username == second.username && this->password == second.password)
            return true;
        return false;
    }
    void Voting(vector<imdbMovie> &film, int row, double rate)
    {
        double new_rate = ((film[row].get_averageRating() * film[row].get_numVotes()) + rate) / (film[row].get_numVotes() + 1);
        new_rate = round(new_rate * 10) / 10;
        film[row].set_averageRating(new_rate);
        film[row].set_numVotes(film[row].get_numVotes() + 1);
    }
    void addFilm(string titleId)
    {
        this->ratedFilm.insert(titleId);
    }
};

int main()
{
    return 0;
}