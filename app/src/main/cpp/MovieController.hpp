//
//  MovieController.hpp
//  Highrise
//
//  Created by Jimmy Xu on 12/19/18.
//  Copyright © 2018 Pocketz World. All rights reserved.
//

#ifndef MovieController_hpp
#define MovieController_hpp

#include <stdio.h>
#include <string>
#include <vector>
#include <map>

namespace movies {
    class Actor {
    public:
        std::string name;
        int age;
        
        //optional challenge 1: Load image from URL
        std::string imageUrl;
    };
    
    class Movie {
    public:
        std::string name;
        int lastUpdated;
        
        //optional challenge 2: Load image from data
        std::vector<unsigned char*> imageData;
    };
    
    class MovieDetail {
    public:
        std::string name;
        float score;
        std::vector<Actor> actors;
        std::string description;
    };
    
    class MovieController {
    public:
        MovieController(const std::string &imageDirectoryPath);
        std::vector<Movie*> getMovies();
        MovieDetail* getMovieDetail(std::string name);
        
        //optional challenge 2: Load image from data
        std::vector<unsigned char> getMovieImage(std::string name);
        
    private:
        class Impl;
        std::unique_ptr<Impl, void (*)(Impl *impl)> _impl;

        std::string _imageDirectoryPath;
    };
}

#endif /* MovieController_hpp */
