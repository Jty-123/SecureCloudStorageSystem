package com.example.frameworkdemo.controller;

import com.example.frameworkdemo.entity.TestUser;
import com.example.frameworkdemo.service.DatabaseSer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.bind.annotation.RestController;

import java.util.Date;
import java.util.List;

@RestController
public class TestUserController {

    @Autowired
    DatabaseSer databaseser;
    @RequestMapping("/testuser")
    @ResponseBody
    public Object testuser(@RequestParam String name){
        databaseser.save(name);
        List<TestUser> findout=databaseser.findall();
        return findout;
    }
}
