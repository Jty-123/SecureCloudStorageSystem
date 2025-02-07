package com.example.frameworkdemo.repository;

import com.example.frameworkdemo.entity.TestUser;
import org.springframework.data.jpa.repository.JpaRepository;

public interface TestUserRepository extends JpaRepository<TestUser, Integer> {
}
