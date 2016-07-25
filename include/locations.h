# pragma once
#include <string>
using namespace std;

class Locations
{
  public:
    /*
     * @brief: initthe locations server
     * dbPath_ and server_ are defined in Env.h
     */
    Locations();

    /*
     * @brief: try to fetch the locations data from server
     */
    void fetchLocations();

    /*
     * @brief: get the current locations data version in db
     */
    int getDataVersion();

    /*
     * @brief: return suggestions based on user input
     * @return: suggestions, merged as a big comma separated string
     */
    string getSuggestions(const string& query);

  private:
    /*
     * @brief: a 'helper' method of 'fetchLocations()', that download and insert location data to database
     */
    void updateLocationTable();

    string dbPath_;
    string server_; // url of the api server
};

