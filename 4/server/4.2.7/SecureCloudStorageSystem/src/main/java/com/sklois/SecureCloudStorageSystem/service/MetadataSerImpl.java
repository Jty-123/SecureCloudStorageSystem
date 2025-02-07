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
    private EntityManager entityManager;

    @Autowired
    private MetadataRepository metadatarepository;




    @Autowired
    private RegisterUserRepository registeruserrepository;



    public List<JSONObject> folderlist(String username) {
        List<JSONObject> ret = get_folder_list("根目录", username);
        return ret;
    }

    List<JSONObject> get_folder_list(String parentid, String username) {

        List<JSONObject> listItems = new ArrayList<>();
        List<Metadata> result = metadatarepository.findAllByTypeAndParentidAndFileowner("dir", parentid, username);//
        if (null != result && result.size() > 0) {
            for (Metadata one : result) {
                if (0 == "dir".compareToIgnoreCase(one.getType())) {
                    JSONObject listItem = new JSONObject(true);
                    listItem.put("id", one.getId());
                    listItem.put("currentid", one.getCurrentid());
                    listItem.put("opened", one.isIfopened());
                    listItem.put("foldername", one.getFilename());
                    listItem.put("ctime", one.getCtime());
                    listItem.put("mtime", one.getMtime());
                    listItem.put("lastaccesstime", one.getLastaccesstime());
                    listItem.put("uploadtime", one.getUploadtime());
                    List<JSONObject> listItem_recursive = get_folder_list(one.getCurrentid(), username);
                    if (null != listItem_recursive && listItem_recursive.size() > 0) {
                        listItem.put("children", listItem_recursive);
                    }
                    listItems.add(listItem);
                }
            }
        }
        return listItems;
    }

    public List<JSONObject> filelist(
            int pageNo,
            int pageSize,
            String folderuniqueid,
            String username) {
        Page<Metadata> findoutpage = null;
        Sort sort = new Sort(Sort.Direction.DESC, "id");
        Pageable pageable = new PageRequest(pageNo, pageSize, sort);
        ExampleMatcher matcher = ExampleMatcher.matching()
                .withStringMatcher(ExampleMatcher.StringMatcher.EXACT)  //改变默认字符串匹配为:模糊查询
                .withMatcher("parentid", ExampleMatcher.GenericPropertyMatchers.exact())
                .withMatcher("fileowner", ExampleMatcher.GenericPropertyMatchers.exact())
                .withIgnorePaths("id")
                .withIgnorePaths("ciphertextsize")
                .withIgnorePaths("currentid")
                .withIgnorePaths("filename")
                .withIgnorePaths("filesize")
                .withIgnorePaths("fileuniqueid")
                .withIgnorePaths("ifopened")
                .withIgnorePaths("ifshared"); //忽略id字段
        System.out.println("username is " + username);
        Metadata filemetadata = new Metadata();
        filemetadata.setParentid(folderuniqueid);
        filemetadata.setFileowner(username);
        Example<Metadata> ex = Example.of(filemetadata, matcher); //动态查询
        findoutpage = metadatarepository.findAll(ex, pageable);

        List<Metadata> listout = findoutpage.getContent();
        System.out.println("listout size is " + listout.size());
        List<JSONObject> listItems = new ArrayList<>();
        if (null != listout && listout.size() > 0) {
            for (Metadata one : listout) {
                JSONObject listItem = new JSONObject(true);
                listItem.put("id", one.getId());
                listItem.put("filename", one.getFilename());
                listItem.put("filesize", one.getFilesize());
                listItem.put("ctime", one.getCtime());
                listItem.put("mtime", one.getMtime());
                listItem.put("lastaccesstime", one.getLastaccesstime());
                listItem.put("uploadtime", one.getUploadtime());
                listItem.put("plaintexthash", one.getPlaintexthash());
                listItem.put("ciphertexthash", one.getCiphertexthash());
                listItem.put("ciphertextsize", one.getCiphertextsize());
                listItem.put("keyhash", one.getKeyhash());
                listItem.put("fileuniqueid", one.getFileuniqueid());
                listItem.put("type", one.getType());
                listItem.put("currentid", one.getCurrentid());
                listItem.put("parentid", one.getParentid());
                listItem.put("ifshared", one.isIfshared());
                listItem.put("opened", one.isIfopened());
                listItems.add(listItem);
            }
        }
        return listItems;
    }

    public long countByParentidAndFileowner(String parentid, String fileowner) {
        long filenumber = metadatarepository.countByParentidAndFileowner(parentid, fileowner);
        return filenumber;
    }



}
