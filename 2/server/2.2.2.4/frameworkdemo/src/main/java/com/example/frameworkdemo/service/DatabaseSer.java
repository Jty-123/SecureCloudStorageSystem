package com.example.frameworkdemo.service;

import com.example.frameworkdemo.entity.TestUser;

import java.util.List;

public interface DatabaseSer {
    public TestUser save(String name);
    public List<TestUser> findall();
}
