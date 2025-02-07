package com.sklois.SecureCloudStorageSystem.service;

import com.alibaba.fastjson.JSONArray;
import com.alibaba.fastjson.JSONObject;

public interface DockingSecurityCloudSer {


    public String uploadkey(String sessionid ,String encryptkey,String fileuniqueid);
    public String getkey(String sessionid ,String fileuniqueid);
    public String deletekey(String fileuniqueid);
    public String uploadcipherindex(JSONObject cipherindex);
    public String searchcipherindex(String condition, JSONArray keywords);
    public String deletecipherindex(String fileuniqueid);//定义密文索引删除接口
    //public Object listAuditLog(LocalDateTime fromtime , LocalDateTime totime , String user, String module, int pageNo, int pageSize);//定义安全审计接口

}
