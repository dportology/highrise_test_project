package com.example.balfur.highrise_test_project.POJOs;

public class Actor {

    Actor(String name, int age, String imageUrl){
        this.name = name;
        this.age = age;
        this.imageUrl = imageUrl;
    }

    private String name;
    private int age;
    private String imageUrl;

    public String getName() { return name; }
    public void setName(String name) { this.name = name; }
    public int getAge() { return age; }
    public void setAge(int age) { this.age = age; }
    public String getImageUrl() { return imageUrl; }
    public void setImageUrl(String imageUrl) { this.imageUrl = imageUrl; }

}
