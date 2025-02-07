package com.example.frameworkdemo.service;

import com.example.frameworkdemo.entity.TestUser;
import com.example.frameworkdemo.repository.TestUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.Date;
import java.util.List;
@Service
public class DatabaseSerImpl implements DatabaseSer  {
    @Autowired
    private TestUserRepository testuserrepository;
    @Override
    public TestUser save(String name) {
        if(null==name||name.length()<=0){
            return null;
        }
        TestUser testuser = new TestUser();
        testuser.setName(name);
        Date now = new Date();
        testuser.setDate(now);

        return testuserrepository.save(testuser);
    }

    @Override
    public List<TestUser> findall() {
        return testuserrepository.findAll();
    }
}
