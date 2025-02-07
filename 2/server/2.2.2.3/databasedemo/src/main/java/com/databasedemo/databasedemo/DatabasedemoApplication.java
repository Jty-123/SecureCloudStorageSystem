package com.databasedemo.databasedemo;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.SpringApplication;
import org.springframework.boot.autoconfigure.SpringBootApplication;

import javax.annotation.Resource;
import java.util.Date;
import java.text.SimpleDateFormat;

@SpringBootApplication
public class DatabasedemoApplication {



    public static void main(String[] args) {
        SpringApplication.run(DatabasedemoApplication.class, args);
    }

}
