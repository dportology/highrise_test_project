//
//  MovieController.cpp
//  Highrise
//
//  Created by Jimmy Xu on 12/19/18.
//  Copyright © 2018 Pocketz World. All rights reserved.
//

#include "MovieController.hpp"
#include <vector>
#include <iterator>
#include <algorithm>
#include <iostream>
#include <fstream>

using namespace movies;

class MovieController::Impl {
public:
    ~Impl() {
    }
    
    std::vector<Movie*> movies;
    std::map<std::string, MovieDetail*> details;
};


MovieController::MovieController(const std::string &imageDirectoryPath): _impl(new Impl(),[](Impl *impl) { delete impl; }) {
    
    _imageDirectoryPath = imageDirectoryPath;
    
    for (int i = 0; i < 10; i++) {
        auto movie = new Movie();
        movie->name = "Top Gun " + std::to_string(i);
        movie->lastUpdated = i * 10000;
        _impl->movies.push_back(movie);
        
        auto movieDetail = new MovieDetail();
        movieDetail->name = movie->name;
        movieDetail->score = rand() % 10;
        movieDetail->description = "As students at the United States Navy's elite fighter weapons school compete to be best in the class, one daring young pilot learns a few things from a civilian instructor that are not taught in the classroom.";
        
        auto tomCruise = Actor();
        tomCruise.name = "Tom Cruise";
        tomCruise.age = 50;

        auto valKilmer = Actor();
        valKilmer.name = "Val Kilmer";
        valKilmer.age = 46;
        valKilmer.imageUrl = "https://m.media-amazon.com/images/M/MV5BMTk3ODIzMDA5Ml5BMl5BanBnXkFtZTcwNDY0NTU4Ng@@._V1_UY317_CR4,0,214,317_AL_.jpg";
    
        movieDetail->actors.push_back(tomCruise);
        movieDetail->actors.push_back(valKilmer);
        
        if (i % 2 == 0) {
            auto timRobbins = Actor();
            timRobbins.name = "Tim Robbins";
            timRobbins.age = 55;
            timRobbins.imageUrl = "https://m.media-amazon.com/images/M/MV5BMTI1OTYxNzAxOF5BMl5BanBnXkFtZTYwNTE5ODI4._V1_UY317_CR16,0,214,317_AL_.jpg";
            
            movieDetail->actors.push_back(timRobbins);
        } else {
            auto jenniferConnelly = Actor();
            jenniferConnelly.name = "Jennifer Connelly";
            jenniferConnelly.age = 39;
            jenniferConnelly.imageUrl = "https://m.media-amazon.com/images/M/MV5BOTczNTgzODYyMF5BMl5BanBnXkFtZTcwNjk4ODk4Mw@@._V1_UY317_CR12,0,214,317_AL_.jpg";
            
            movieDetail->actors.push_back(jenniferConnelly);
        }
        
        _impl->details[movie->name] = movieDetail;
    }
}

std::vector<Movie*> MovieController::getMovies() {
    return _impl->movies;
}

MovieDetail* MovieController::getMovieDetail(std::string name) {
    for (auto item:_impl->details) {
        if (item.second->name == name) {
            return item.second;
        }
    }
    return nullptr;
}

std::vector<unsigned char> MovieController::getMovieImage(std::string name) {

    // Converting image here for sake of the practice problem
    std::ifstream file("drawable/top_gun.jpg", std::ios::binary);

    std::istream_iterator<unsigned char> begin(file), end;

    // Reading the file content using the iterator!
    std::vector<unsigned char> buffer(begin,end);

    std::copy(buffer.begin(), buffer.end(), std::ostream_iterator<unsigned int>(std::cout, ","));

    return buffer;
}
