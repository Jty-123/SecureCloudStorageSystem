package com.sklois.SecureCloudStorageSystem.service;

import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;

import java.time.LocalDateTime;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

public interface DatabaseSer {
    public HashMap<String,Object> findByName(String name);
    public HashMap<String,Object> save(String name, String password, String role, Date date);
    public HashMap<String,Object> findAll();
    public Object findOneByName(String name);

    public HashMap<String,Object> findAll( String username, String userrole);

    public Object modifyuser(String username , String email);

    public Object deleteuser(String username);

}
