package com.example.balfur.highrise_test_project.POJOs;

import java.io.Serializable;
import java.util.Arrays;
import java.util.List;

public class MovieDetail implements Serializable {

//    MovieDetail(String name, float score, List<Actor> actors, String description){
//        this.name = name;
//        this.score = score;
//        this.actors = actors;
//        this.description = description;
//    }

    MovieDetail(float score, String name, String description, Actor[] actorsArray){
        this.name = name;
        this.score = score;
        this.description = description;
        this.actors = Arrays.asList(actorsArray);
    }

    private String name;
    private float score;
    private List<Actor> actors;
    private String description;

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public float getScore() { return score; }
    public void setScore(float score) { this.score = score; }
    public List<Actor> getActors() { return actors; }
    public void setActors(List<Actor> actors) { this.actors = actors; }
    public String getDescription() { return description; }
    public void setDescription(String description) { this.description = description; }

}
