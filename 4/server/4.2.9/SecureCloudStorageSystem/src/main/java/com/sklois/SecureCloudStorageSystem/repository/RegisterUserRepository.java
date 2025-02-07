package com.sklois.SecureCloudStorageSystem.repository;

import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface RegisterUserRepository extends JpaRepository<RegisterUser, Integer> {
    public List<RegisterUser> findByName(String name);
    RegisterUser findOneByName(String name);
    RegisterUser findOneById(Integer id);
    RegisterUser findOneBySessionid(String sessionid);
}
