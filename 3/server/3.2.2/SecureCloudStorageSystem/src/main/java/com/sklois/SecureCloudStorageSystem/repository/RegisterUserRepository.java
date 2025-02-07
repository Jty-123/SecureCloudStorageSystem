package com.sklois.SecureCloudStorageSystem.repository;

import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import org.springframework.data.jpa.repository.JpaRepository;

import java.util.List;

public interface RegisterUserRepository extends JpaRepository<RegisterUser, Integer> {
    public List<RegisterUser> findByName(String name);
    public RegisterUser findOneByName(String name);

    public List<RegisterUser> findByRoleAndNameContains(String role,String name);
    public List<RegisterUser> findByRole(String role);
}
