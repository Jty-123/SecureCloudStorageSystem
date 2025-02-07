package com.sklois.SecureCloudStorageSystem.service;

import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import com.sklois.SecureCloudStorageSystem.repository.RegisterUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Service;
import java.util.Base64.Decoder;
import java.util.Base64.Encoder;
import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import java.io.IOException;
import java.io.UnsupportedEncodingException;
import java.security.*;
import java.security.spec.AlgorithmParameterSpec;
import java.util.*;


@Service
public class DatabaseSerImpl implements DatabaseSer {
    String lowercase = "^.*[a-z]+.*$";
    String uppercase = "^.*[A-Z]+.*$";
    String numbercase = "^.*[0-9]+.*$";
    String usernameRange = "^[a-zA-Z0-9]+$";
    @Autowired
    private RegisterUserRepository registeruserrepository;

    @Override
    public HashMap<String, Object> findByName(String name) {
        HashMap<String, Object> retmap = new HashMap<String, Object>();
        List<RegisterUser> findout = new ArrayList<RegisterUser>();
        if (name.length() < 8 || name.length() > 20) {
            retmap.put("result", false);
            retmap.put("message", "username length error");
            return retmap;
        }
        if (!name.matches(usernameRange)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        if (!name.matches(lowercase) &&
                !name.matches(uppercase)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        if (!name.matches(numbercase)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        findout = registeruserrepository.findByName(name);
        retmap.put("result", true);
        retmap.put("message", "success");
        retmap.put("findout", findout);
        return retmap;
    }

    @Value("${sklois.database.saltvalue}")
    private String saltvalue;

    @Value("${example.database.encryption.key}")
    private String databaseencryptkey;


    public HashMap<String, Object> save(String name, String password, String role, Date date) {
        HashMap<String, Object> retmap = new HashMap<String, Object>();
        if (name.length() < 8 || name.length() > 20) {
            retmap.put("result", false);
            retmap.put("message", "username length error");
            return retmap;
        }
        if (!name.matches(usernameRange)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        if (!name.matches(lowercase) &&
                !name.matches(uppercase)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        if (!name.matches(numbercase)) {
            retmap.put("result", false);
            retmap.put("message", "username error");
            return retmap;
        }
        if (password.length() != 44) {
            retmap.put("result", false);
            retmap.put("message", "password error");
            return retmap;
        }
        if (null == role || 0 != role.compareTo("普通用户")) {
            retmap.put("result", false);
            retmap.put("message", "role error");
            return retmap;
        }

        System.out.println("password is " + password);
        System.out.println("saltvalue is " + saltvalue);

        List<RegisterUser> findout = new ArrayList<RegisterUser>();
        //查询数据库是否存在
        findout = registeruserrepository.findByName(name);
        if (null != findout && findout.size() > 0) {
            retmap.put("result", false);
            retmap.put("message", "username exist");
            return retmap;
        }


        MessageDigest messageDigest;

        byte[] savedigest = new byte[0];
        try {
            messageDigest = MessageDigest.getInstance("SHA-256");
            messageDigest.update((saltvalue + password).getBytes("UTF-8"));
            savedigest = messageDigest.digest();
        } catch (NoSuchAlgorithmException e) {
            System.out.println("encode password error");
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            System.out.println("encode password error");
            e.printStackTrace();
        }
        String encryptpassword = null;
        byte[] encryptout = aesCbcEncrypt(savedigest);
        encryptpassword = Base64.getEncoder().encodeToString(encryptout);
        System.out.println("encrypt password is " + encryptpassword);

//解密
//        byte[] encryptedBytes = Base64.getDecoder().decode(encryptpassword);
//        byte[] decrepttext = aesCbcDecrypt(encryptedBytes);
//
//
//        if(Arrays.equals(decrepttext, savedigest)){
//            System.out.println("√√√√√");
//        }


        RegisterUser registeruser = new RegisterUser();
        registeruser.setName(name);
        registeruser.setPassword(encryptpassword);
        registeruser.setRole(role);
        registeruser.setDate(date);




        RegisterUser retentity = registeruserrepository.save(registeruser);

        if (null != retentity) {
            retmap.put("result", true);
            retmap.put("message", "user register success");
            retmap.put("username", retentity.getName());
            retmap.put("role", retentity.getRole());
            return retmap;
        } else {
            retmap.put("result", false);
            retmap.put("message", "save error");
            return retmap;
        }


    }


    public byte[] aesCbcEncrypt(byte[] input){
        Cipher cipher = null;
        byte[] cipherout = null;
        try {
            cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            Key secretKey = new SecretKeySpec(databaseencryptkey.getBytes(), "AES");
            byte[] iv = new byte[cipher.getBlockSize()];
            AlgorithmParameterSpec algorithmParameters = new IvParameterSpec(iv);
            cipher.init(Cipher.ENCRYPT_MODE, secretKey, algorithmParameters);
            cipherout = cipher.doFinal(input);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        }
        return cipherout;
    }

    public byte[] aesCbcDecrypt(byte[] input){
        Cipher cipher = null;
        byte[] cipherout = null;
        try {
            cipher = Cipher.getInstance("AES/CBC/PKCS5Padding");
            Key secretKey = new SecretKeySpec(databaseencryptkey.getBytes(), "AES");
            byte[] iv = new byte[cipher.getBlockSize()];
            AlgorithmParameterSpec algorithmParameters = new IvParameterSpec(iv);
            cipher.init(Cipher.DECRYPT_MODE, secretKey, algorithmParameters);
            cipherout = cipher.doFinal(input);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (NoSuchPaddingException e) {
            e.printStackTrace();
        } catch (InvalidKeyException e) {
            e.printStackTrace();
        } catch (InvalidAlgorithmParameterException e) {
            e.printStackTrace();
        } catch (BadPaddingException e) {
            e.printStackTrace();
        } catch (IllegalBlockSizeException e) {
            e.printStackTrace();
        }
        return cipherout;
    }

    public HashMap<String, Object> findAll() {

        HashMap<String, Object> findoutmap = new HashMap<String, Object>();
        List<RegisterUser> findout = registeruserrepository.findAll();

        if (null != findout) {
            findoutmap.put("result", true);
            findoutmap.put("message", "user find success");
            findoutmap.put("findout", findout);
            return findoutmap;
        }
        return findoutmap;
    }


    public HashMap<String,Object> findAll( String username, String userrole){
        HashMap<String, Object> findoutmap = new HashMap<String, Object>();
        List<RegisterUser> findout = null;
        if(null==username||0==username.compareToIgnoreCase("")){
            findout= registeruserrepository.findByRole(userrole);
        }else{
            findout = registeruserrepository.findByRoleAndNameContains(userrole,username);
        }
        if (null != findout) {
            findoutmap.put("result", true);
            findoutmap.put("message", "user find success");
            findoutmap.put("findout", findout);
            return findoutmap;
        }
        return findoutmap;
    }


    public Object findOneByName(String name) {
        RegisterUser registeruser = registeruserrepository.findOneByName(name);
        return registeruser;
    }



    public Object modifyuser(String username , String email) {
        RegisterUser registeruser = registeruserrepository.findOneByName(username);
        if(null!=registeruser){
            registeruser.setEmail(email);
            RegisterUser ret = registeruserrepository.save(registeruser);
            return ret;
        }
        return null;
    }

    public Object deleteuser(String username){
        RegisterUser registeruser = registeruserrepository.findOneByName(username);
        if(null!=registeruser){
            registeruserrepository.deleteById(registeruser.getId());
            return registeruser;
        }
        return null;
    }
}
