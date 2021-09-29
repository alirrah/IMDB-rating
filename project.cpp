#include <iostream>
#include <string>
#include <list>
#include <vector>
#include <cmath>
#include <set>
#include <climits>
#include <cstring>
#include <algorithm>
using namespace std;

#define pause system("pause")
#define clean system("cls")

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
        cout << '(' << i + 1 << ")\t" << this->titleId << '\t' << this->ordering << '\t' << this->title << '\t' << this->region << '\t' << this->language << '\t';
        for (auto it = this->types.begin(); it != this->types.end(); it++)
            cout << *it << ' ';
        cout << '\t';
        for (auto it = this->attributes.begin(); it != this->attributes.end(); it++)
            cout << *it << ' ';
        cout << '\t' << boolalpha << this->isOriginalTitle << '\t' << this->averageRating << '\t' << this->numVotes << endl;
    }
};
class user
{
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
    void set_ratedFilm(set<string> ratedFilm)
    {
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
        if (this->username == second.username && this->password == second.password)
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

vector<imdbMovie> readFile();
bool vote(vector<imdbMovie> &, user &);
int menu(vector<user> &, vector<imdbMovie> &, bool &);
void showTop(vector<imdbMovie>);
bool comparator(const imdbMovie &, const imdbMovie &);

int main()
{
    vector<imdbMovie> film = readFile();
    bool change = false;
    vector<user> member;
    while(menu(member, film, change));
    if(change){
        try
        {
            vector<imdbMovie> tmp;
            FILE *fptr;
            char sentence[1000];
            string tmpSentence = "tconst\taverageRating\tnumVotes";
            fptr = fopen("title.akas.txt", "w");
            if (fptr == NULL)
                throw "Error!!! title.akas.txt could not be opened";
            strcpy(sentence, tmpSentence.c_str());
            fputs(sentence, fptr);
            for(auto itr = film.begin(); itr != film.end(); itr++)
            {
                tmpSentence.clear();
                tmpSentence = '\n' + itr->get_titleId() + '\t';
                string tmp = to_string(itr->get_averageRating());
                for(int i = 0; i < tmp.size(); i++)
                {
                    if(tmp[i] == '.')
                    {
                        tmpSentence += tmp[i] ;
                        tmpSentence += tmp[i + 1];
                        break;
                    }
                    else
                        tmpSentence += tmp[i];
                }
                tmpSentence += '\t' ;
                tmpSentence += to_string(itr->get_numVotes());
                strcpy(sentence, tmpSentence.c_str());
                fputs(sentence, fptr);
            }
            fclose(fptr);
        }
        catch (char const *message)
        {
            cout << message << endl;
            pause;
            exit(1);
        }
    }
    return 0;
}

vector<imdbMovie> readFile()
{
    try
    {
        vector<imdbMovie> tmp;
        FILE *fptr;
        int j;
        char fileSentence[1000];
        fptr = fopen("title.akas.txt", "r");
        if (fptr == NULL)
            throw "Error!!! title.akas.txt could not be opened";
        fgets(fileSentence, 1000, fptr);
        while (fgets(fileSentence, 1000, fptr))
        {
            string sentence = "";
            j = 0;
            imdbMovie temp;
            for (int i = 0; fileSentence[i] != 0; i++)
            {
                if (fileSentence[i] != '\t')
                    sentence += fileSentence[i];
                else
                {
                    list<string> t;
                    string tmpSentence = "";
                    switch (j)
                    {
                    case 0:
                        temp.set_titleId(sentence);
                        break;
                    case 1:
                        temp.set_ordering(stoi(sentence));
                        break;
                    case 2:
                        temp.set_title(sentence);
                        break;
                    case 3:
                        temp.set_region(sentence);
                        break;
                    case 4:
                        temp.set_laguage(sentence);
                        break;
                    case 5:
                        for (int k = 0; k < sentence.size(); k++)
                        {
                            if (sentence[k] != ' ')
                                tmpSentence += sentence[k];
                            else
                            {
                                t.push_back(tmpSentence);
                                tmpSentence.clear();
                            }
                        }
                        t.push_back(tmpSentence);
                        tmpSentence.clear();
                        temp.set_types(t);
                        break;
                    case 6:
                        for (int k = 0; k < sentence.size(); k++)
                        {
                            if (sentence[k] != ' ')
                                tmpSentence += sentence[k];
                            else
                            {
                                t.push_back(tmpSentence);
                                tmpSentence.clear();
                            }
                        }
                        t.push_back(tmpSentence);
                        tmpSentence.clear();
                        temp.set_attributes(t);
                        break;
                    }
                    j++;
                    sentence.clear();
                }
            }
            if (sentence == "0\n")
                temp.set_isOriginalTitle(false);
            else
                temp.set_isOriginalTitle(true);
            tmp.push_back(temp);
        }
        fclose(fptr);
        FILE *fp;
        fp = fopen("title.ratings.txt", "r");
        if (fp == NULL)
            throw "Error!!! title.ratings.txt could not be opened";
        fgets(fileSentence, 1000, fp);
        while (fgets(fileSentence, 1000, fp))
        {
            string tmp_sentence[3], sentense = "";
            j = 0;
            for (int i = 0; fileSentence[i] != '\n'; i++)
            {
                if (fileSentence[i] != '\t')
                    sentense += fileSentence[i];
                else
                {
                    tmp_sentence[j++] = sentense;
                    sentense.clear();
                }
            }
            tmp_sentence[2] = sentense;
            for (auto itr = tmp.begin(); itr != tmp.end(); itr++)
            {
                if (itr->get_titleId() == tmp_sentence[0])
                {
                    itr->set_averageRating(stod(tmp_sentence[1]));
                    itr->set_numVotes(stoi(tmp_sentence[2]));
                    break;
                }
            }
        }
        fclose(fp);
        return tmp;
    }
    catch (char const *message)
    {
        cout << message << endl;
        pause;
        exit(1);
    }
}

bool vote(vector<imdbMovie> &film, user &member)
{
    bool change = false;
    int row ;
    double rate;
    while(true)
    {
        try
        {
            clean;
            cout << "row\ttitleId\tordering\ttitle\tregion\tlanguage\ttypes\tattributes\tisOriginalTitle\taverageRating\tnumVotes" << endl;
            for(int i = 0 ; i < film.size(); i++)
                film[i].print(i);
            cout << "\nselect the movie by row(1 - " << film.size() << ") [(0) Exit] : ";
            cin >> row;
            //input validation
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                throw "\n\nError!!! You can only enter number";
            }
            if(row < 0 || row > film.size())
                throw "\n\nError!!! You enter a number out of range";
            if (row == 0)
                break;
            if(member.get_ratedFilm().count(film[row -1 ].get_titleId()))
                throw "\n\nError!!! You have already voted for this movie";
            cout  << "\nrow : " << row << endl;
            row--;
            cout << "titleId : " << film[row].get_titleId() << endl;
            cout << "ordering : " << film[row].get_ordering() << endl;
            cout << "title : " << film[row].get_title() << endl;
            cout << "region : " << film[row].get_region() << endl;
            cout << "language : " << film[row].get_laguage() << endl;
            cout << "types : " ;
            list<string> itr_type = film[row].get_types();
            for(auto it = itr_type.begin(); it != itr_type.end(); it++)
                cout << *it <<' ';
            cout << "\nattributes : " ;
            list<string> itr_atttributes = film[row].get_attributes();
            for(auto it = itr_atttributes.begin(); it != itr_atttributes.end(); it++)
                cout << *it <<' ';
            cout << boolalpha << "\nisOriginalTitle : " << film[row].get_isOriginalTitle() << endl;
            cout << "averageRating : " << film[row].get_averageRating() << endl;
            cout << "numVotes : " << film[row].get_numVotes() << endl;
            cout << "\nyour rate (0 - 10) : ";
            cin >> rate;
            //input validation
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                throw "\n\nError!!! You can only enter number";
            }
            if(rate < 0 || rate > 10)
                throw "\n\nError!!! You enter a number out of range";
            member.Voting(film, row, rate);
            member.addFilm(film[row].get_titleId());
            change = true;
        }
        catch (char const *message)
        {
            cout << message << endl;
            pause;
        }
    }
    return change;
}

int menu(vector<user> &member, vector<imdbMovie> &film, bool &change)
{
    /*
0 -> finish
1 -> finish successfully
2 -> error
*/
    try
    {
        clean;
        int number;
        string username, password;
        user tmp;
        cout << "--------- Welcome to the IMDb Rating System ---------" << endl;
        cout << "(1) Rating\n(2) Top Movies\n(3) Exit\nEnter a number : ";
        cin >> number;
        //input validation
        while(cin.fail())
        {
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            throw "\n\nError!!! You can only enter number";
        }
        switch (number)
        {
        case 1:
            cout << "\n(1) Signup\n(2) Login\nEnter a number : ";
            cin >> number;
            //input validation
            while(cin.fail())
            {
                cin.clear();
                cin.ignore(INT_MAX, '\n');
                throw "\n\nError!!! You can only enter number";
            }
            cin.ignore();
            cout << "\nEnter your username: ";
            getline(cin, username);
            cout << "Enter your password: ";
            getline(cin, password);
            tmp.set_username(username);
            tmp.set_password(password);
            tmp.set_ratedFilm({});
            switch (number)
            {
            case 1:
                for(int i = 0; i < member.size(); i++)
                    if(member[i] == tmp)
                    {
                        tmp.set_ratedFilm(member[i].get_ratedFilm());
                        cout << "\n\nYou have successfully logged in" << endl;
                        pause;
                        change = vote(film, tmp);
                        return 1;
                    }
                throw "\n\nWarning!!! Your information  is not found. Please login";
            case 2:
                member.push_back(tmp);
                cout << "\n\nYour information  is successfully registered" << endl;
                pause;
                change = vote(film, tmp);
                return 1;
            default:
                throw "\n\nError!!! You enter a number out of range";
            }
            return 1;
        case 2:
            showTop(film);
            return 1;
        case 3:
            return 0;
        default:
            throw "\n\nError!!! You enter a number out of range";
        }
    }
    catch (char const *message)
    {
        cout << message << endl;
        pause;
        return 2;
    }
}

void showTop(vector<imdbMovie> film)
{
    clean;
    cout << "row\ttitle\taverageRating" << endl;
    vector<imdbMovie> tmp = film;
    sort(tmp.begin(), tmp.end(), &comparator);
    for(int i = 0; (i < 10) && (i < tmp.size()); i++)
        cout << i + 1 << ") " << tmp[i].get_title() << '\t' << tmp[i].get_averageRating() << endl;
    pause;
}

bool comparator(const imdbMovie &lhs, const imdbMovie &rhs)
{
    return lhs.get_averageRating() > rhs.get_averageRating();
}