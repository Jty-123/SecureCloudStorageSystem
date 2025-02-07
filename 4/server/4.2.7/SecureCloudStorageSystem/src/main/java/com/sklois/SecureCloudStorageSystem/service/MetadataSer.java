package com.sklois.SecureCloudStorageSystem.service;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.sklois.SecureCloudStorageSystem.entity.Metadata;

import java.util.List;

public interface MetadataSer {
    public List<JSONObject> folderlist(String username);
    public List<JSONObject> filelist(int pageNo , int pageSize ,String folderuniqueid,String username);
    public long countByParentidAndFileowner(String parentid,String fileowner);
}
