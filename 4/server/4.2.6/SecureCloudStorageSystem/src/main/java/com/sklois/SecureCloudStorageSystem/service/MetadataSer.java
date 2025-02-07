package com.sklois.SecureCloudStorageSystem.service;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;
import com.sklois.SecureCloudStorageSystem.entity.Metadata;

import java.util.List;

public interface MetadataSer {
    public Metadata savemetadata(String metadata);

}
