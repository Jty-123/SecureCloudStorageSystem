package com.databasedemo.databasedemo;

import org.springframework.data.jpa.repository.JpaRepository;

public interface TestUserRepository extends JpaRepository<TestUser, Integer> {
}
