package com.databasedemo.databasedemo;

import org.junit.Test;
import org.junit.runner.RunWith;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.boot.test.context.SpringBootTest;
import org.springframework.test.context.junit4.SpringRunner;

import java.util.Date;
import java.util.List;

@RunWith(SpringRunner.class)
@SpringBootTest
public class DatabasedemoApplicationTests {
    @Autowired
    private TestUserRepository testuserrepository;

    @Test
    public void contextLoads() {
    }

    @Test
    public void testdb() {
        TestUser testuser = new TestUser();
        testuser.setName("jiangtianyi");
        Date now = new Date();
        testuser.setDate(now);
        testuserrepository.save(testuser);
        List<TestUser> findout= testuserrepository.findAll();
        for (TestUser one : findout) {
            System.out.println(one.getId()+"  "+one.getName()+"  "+one.getDate());
        }

    }
}
