package com.sklois.SecureCloudStorageSystem.service;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.sklois.SecureCloudStorageSystem.entity.AuditEntity;
import com.sklois.SecureCloudStorageSystem.entity.Metadata;
import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import com.sklois.SecureCloudStorageSystem.repository.MetadataRepository;
import com.sklois.SecureCloudStorageSystem.repository.RegisterUserRepository;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.data.domain.*;
import org.springframework.stereotype.Service;

import javax.persistence.EntityManager;
import javax.persistence.Query;
import java.math.BigInteger;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.*;

@Service
public class MetadataSerImpl implements MetadataSer {



    @Autowired
    private MetadataRepository metadatarepository;

    @Autowired
    DockingSecurityCloudSer dockingsecuritycloudser;


    @Autowired
    private RegisterUserRepository registeruserrepository;

    public Metadata savemetadata(String metadata) {

        JSONObject jsonObject = JSONObject.parseObject(metadata);

        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");

        String filename = jsonObject.getString("filename");
        long filesize = jsonObject.getLong("filesize");
        LocalDateTime ctime = LocalDateTime.parse(jsonObject.getString("ctime"), formatter);
        LocalDateTime mtime = LocalDateTime.parse(jsonObject.getString("mtime"), formatter);
        LocalDateTime lastaccesstime = LocalDateTime.parse(jsonObject.getString("lastaccesstime"), formatter);
        LocalDateTime uploadtime = LocalDateTime.parse(jsonObject.getString("uploadtime"), formatter);
        String fileowner = jsonObject.getString("fileowner");
        String plaintexthash = jsonObject.getString("plaintexthash");
        String ciphertexthash = jsonObject.getString("ciphertexthash");
        long ciphertextsize = jsonObject.getLong("ciphertextsize");
        String keyhash = jsonObject.getString("keyhash");
        String fileuniqueid = jsonObject.getString("fileuniqueid");

        String type = jsonObject.getString("type");

        String currentid = jsonObject.getString("currentid");

        String parentid = jsonObject.getString("parentid");


        Metadata findout = metadatarepository.findOneByFileuniqueid(fileuniqueid);
        if (null == findout) {
            Metadata metadataobj = new Metadata();
            metadataobj.setFilename(filename);
            metadataobj.setFilesize(filesize);
            metadataobj.setCtime(ctime);
            metadataobj.setMtime(mtime);
            metadataobj.setLastaccesstime(lastaccesstime);
            metadataobj.setUploadtime(uploadtime);
            metadataobj.setFileowner(fileowner);
            metadataobj.setPlaintexthash(plaintexthash);
            metadataobj.setCiphertexthash(ciphertexthash);
            metadataobj.setCiphertextsize(ciphertextsize);
            metadataobj.setKeyhash(keyhash);
            metadataobj.setFileuniqueid(fileuniqueid);
            metadataobj.setType(type);
            metadataobj.setCurrentid(currentid);
            metadataobj.setParentid(parentid);
            Metadata saveresult = metadatarepository.save(metadataobj);
            return saveresult;
        } else {
            return null;
        }


    }
    public boolean checkauth(String fileuniqueid,String sessionid){
        RegisterUser fuser = registeruserrepository.findOneBySessionid(sessionid); //根据sessionid查询用户标识信息
        Metadata ret= metadatarepository.findOneByFileuniqueidAndFileowner(fileuniqueid,fuser.getName());//根据文件唯一id和用户查询元信息
        if(null!=ret){//如果查询结果不为空，则返回true
            return true;
        }else{
            return false;
        }
    }



}
