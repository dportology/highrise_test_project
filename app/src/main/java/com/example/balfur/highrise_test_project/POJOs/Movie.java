package com.example.balfur.highrise_test_project.POJOs;

public class Movie {

    Movie(String name, int lastUpdated){
        this.name = name;
        this.lastUpdated = lastUpdated;
    }

    private String name;
    private int lastUpdated;

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public int getLastUpdated() { return lastUpdated; }
    public void setLastUpdated(int lastUpdated) { this.lastUpdated = lastUpdated; }


}
