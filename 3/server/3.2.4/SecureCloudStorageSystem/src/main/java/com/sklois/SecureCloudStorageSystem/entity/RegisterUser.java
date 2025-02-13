package com.sklois.SecureCloudStorageSystem.entity;


import javax.persistence.*;
import java.time.LocalDateTime;
import java.util.Date;

@Entity //实体类注解
public class RegisterUser {
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    private Integer id;
    private String name;
    private String password;
    private String role;
    private LocalDateTime registerdate ;//用户注册时间

    private String sessionid;
    private String sessionkey;
    private LocalDateTime sessiontime;
    private LocalDateTime lastauthtime;//上次登录时间
    private String lastauthipaddress;



    public Integer getId() {
        return id;
    }
    public void setId(Integer id) {
        this.id = id;
    }
    public String getName() {
        return name;
    }
    public void setName(String name) {
        this.name = name;
    }

    public String getPassword() {
        return password;
    }

    public String getRole() {
        return role;
    }

    public void setRole(String role) {
        this.role = role;
    }

    public void setPassword(String password) {
        this.password = password;
    }

    public void setRegisterdate(LocalDateTime registerdate) {
        this.registerdate = registerdate;
    }

    public String getSessionid() {
        return sessionid;
    }

    public void setSessionid(String sessionid) {
        this.sessionid = sessionid;
    }

    public String getSessionkey() {
        return sessionkey;
    }

    public void setSessionkey(String sessionkey) {
        this.sessionkey = sessionkey;
    }

    public LocalDateTime getSessiontime() {
        return sessiontime;
    }

    public void setSessiontime(LocalDateTime sessiontime) {
        this.sessiontime = sessiontime;
    }


    public LocalDateTime getLastauthtime() {
        return lastauthtime;
    }

    public void setLastauthtime(LocalDateTime lastauthtime) {
        this.lastauthtime = lastauthtime;
    }

    public LocalDateTime getRegisterdate() {
        return registerdate;
    }
    public void setDate(LocalDateTime Registerdate) {
        this.registerdate = registerdate;
    }

    public String getLastauthipaddress() {
        return lastauthipaddress;
    }

    public void setLastauthipaddress(String lastauthipaddress) {
        this.lastauthipaddress = lastauthipaddress;
    }
}
