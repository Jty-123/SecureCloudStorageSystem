package com.sklois.SecureCloudStorageSystem.controller;

import com.alibaba.fastjson.JSONObject;
import com.sklois.SecureCloudStorageSystem.entity.Metadata;
import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import com.sklois.SecureCloudStorageSystem.intercepter.Auth;
import com.sklois.SecureCloudStorageSystem.repository.MetadataRepository;
import com.sklois.SecureCloudStorageSystem.repository.RegisterUserRepository;
import com.sklois.SecureCloudStorageSystem.service.*;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.util.FileCopyUtils;
import org.springframework.web.bind.annotation.*;
import org.springframework.web.client.RestTemplate;
import org.springframework.web.multipart.MultipartFile;

import javax.crypto.BadPaddingException;
import javax.crypto.Cipher;
import javax.crypto.IllegalBlockSizeException;
import javax.crypto.NoSuchPaddingException;
import javax.crypto.spec.IvParameterSpec;
import javax.crypto.spec.SecretKeySpec;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import javax.servlet.http.Part;
import java.io.*;
import java.net.URLEncoder;
import java.security.InvalidAlgorithmParameterException;
import java.security.InvalidKeyException;
import java.security.Key;
import java.security.NoSuchAlgorithmException;
import java.security.spec.AlgorithmParameterSpec;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.Base64;
import java.util.Collection;

@RestController
public class DataTransmissionController {

    @Autowired
    private HuaweiDockingCloudStorageSerImpl huaweicloudstorageser;

    @Autowired
    private AliDockingCloudStorageSerImpl alidockingcloudstorageser;
    @Autowired
    private MetadataSer metadataser;
    @Autowired
    private DockingSecurityCloudSerImpl dockingsecuritycloudserimpl;
    @Autowired
    SwiftDockingCloudStorageSerImpl swiftDockingCloudStorageSer;
    @Autowired
    AuditSer auditser;

    @Autowired
    MetadataRepository metadatadao;
    @Autowired
    private MetadataSerImpl metadataserimpl;

    @Autowired
    private DataShareSerImpl datashareserimpl;

    @RequestMapping("/dataupload")
    @ResponseBody
    @Auth(normaluser = "普通用户")
    public Object dataupload(HttpServletRequest request,
                             @RequestParam("file") MultipartFile file) throws IOException, ServletException {

        System.out.println("in dataupload");

        String sessionid = request.getHeader("sessionid");
        Collection<Part> parts = request.getParts();
        String metadata = "";
        String encrypted_index = "";
        String encryptkey = "";
        String fileuniqueid = "";
        for (Part part : parts) {
            metadata = part.getHeader("metadata");
            fileuniqueid = part.getHeader("fileuniqueid");
            encrypted_index = part.getHeader("encrypted_index");
            encryptkey = part.getHeader("encryptkey");
            System.out.println("metadata is " + metadata);
            System.out.println("fileuniqueid is " + fileuniqueid);
            if (null != encrypted_index && encrypted_index.length() > 0) {
                System.out.println("encrypted_index is " + encrypted_index);
            }
            System.out.println("encryptkey is " + encryptkey);
        }
        Metadata saveresult = metadataser.savemetadata(metadata);
        if (0 == (saveresult.getFileuniqueid()).compareTo(fileuniqueid)) {
            System.out.println("save metadata success");
        }


        alidockingcloudstorageser.uploaddata(file, fileuniqueid);
//        huaweicloudstorageser.uploaddata(file, fileuniqueid);

        dockingsecuritycloudserimpl.uploadkey(sessionid, encryptkey, fileuniqueid);
//        dockingsecuritycloudserimpl.getkey(sessionid,fileuniqueid);
//        dockingsecuritycloudserimpl.deletekey(fileuniqueid);

        JSONObject cipherindexjsonObject = new JSONObject();
        if (null != encrypted_index && encrypted_index.length() > 0) {
            cipherindexjsonObject = JSONObject.parseObject(encrypted_index);
        }


        if (null != cipherindexjsonObject && null != cipherindexjsonObject.getJSONObject("retdata")) {
            dockingsecuritycloudserimpl.uploadcipherindex(cipherindexjsonObject);
        }


//        dockingsecuritycloudserimpl.searchcipherindex("keyword1");
//        dockingsecuritycloudserimpl.deletecipherindex("fileuniqueid1");
//        swiftDockingCloudStorageSer.uploaddata(file,fileuniqueid);

        return response("dataupload", "success", "8000",
                "dataupload success", null);

    }

    @RequestMapping("datadownload")
    @Auth(normaluser = "普通用户")
    public void datadownload(@RequestBody JSONObject json,
                             HttpServletResponse response,
                             HttpServletRequest request) throws Exception {


        if (null == json) {
            return;
        }
        System.out.println("json is " + json.toJSONString());
        String method = json.getString("method");
        String version = json.getString("version");
        String timestamp = json.getString("timestamp");
        JSONObject requestjsonobj = json.getJSONObject("request");
        String fileuniqueid = requestjsonobj.getString("fileuniqueid");

        String sessionid = request.getHeader("sessionid");
        /*判断该用户是否有权限下载该文件。包括：1. 该文件是否属于自己，2. 该文件是否被分享给了自己*/
        boolean mret = metadataserimpl.checkauth(fileuniqueid, sessionid); //调用MetadataSerImpl类的checkauth()方法判断该文件是否属于这个用户，该函数的实现方法请参考上文4.2.6.5.2密钥获取中的介绍
        boolean sret = datashareserimpl.checkauth(fileuniqueid, sessionid); //调用DataShareSerImpl类的checkauth()方法判断该文件是否被分享给该用户，这个方法的实现将在下文4.2.9.5被分享数据下载和打开中进行介绍

        if (mret || sret) {
            InputStream stream = alidockingcloudstorageser.downloaddata(fileuniqueid);
            Metadata metadata = metadatadao.findOneByFileuniqueid(fileuniqueid);
            if (null != stream) {
                String mimeType = "application/octet-stream";
                response.setContentType(mimeType);
                response.setHeader("Content-disposition",
                        String.format("attachment; filename=\"%s\"",
                                URLEncoder.encode(metadata.getFilename(), "UTF-8")));
                try (
                        InputStream inputStream = new BufferedInputStream(stream)) {
                    FileCopyUtils.copy(inputStream, response.getOutputStream());
                    System.out.println("已返回数据流");
                }
            }

        }
    }


    @RequestMapping("/singledataupload")
    @ResponseBody
    @Auth(normaluser = "普通用户")
    public Object singledataupload(HttpServletRequest request,
                                   @RequestParam("file") MultipartFile file) throws IOException, ServletException {
        System.out.println("in singledataupload");
        String sessionid = request.getHeader("sessionid");
        Collection<Part> parts = request.getParts();
        String fileuniqueid = "";
        for (Part part : parts) {
            fileuniqueid = part.getHeader("fileuniqueid");
            System.out.println("fileuniqueid is " + fileuniqueid);
        }
        alidockingcloudstorageser.uploaddata(file, fileuniqueid);
//        swiftDockingCloudStorageSer.uploaddata(file,fileuniqueid);
        return response("singledataupload", "success", "8000",
                "singledataupload success", null);
    }

    @RequestMapping("/otherdataupload")
    @ResponseBody
    @Auth(normaluser = "普通用户")
    public Object otherdataupload(
            HttpServletRequest request,
            @RequestBody JSONObject json,
            HttpServletResponse response,
            HttpSession session
    ) throws IOException, ServletException {
        System.out.println("in otherdataupload");
        String sessionid = request.getHeader("sessionid");
        String metadata = "";
        String encrypted_index = "";
        String encryptkey = "";
        String fileuniqueid = "";
        System.out.println("json is " + json.toJSONString());
        String method = json.getString("method");
        String version = json.getString("version");
        String timestamp = json.getString("timestamp");
        JSONObject requestjsonobj = json.getJSONObject("request");
        metadata = requestjsonobj.getString("metadata");
        fileuniqueid = requestjsonobj.getString("fileuniqueid");
        encrypted_index = requestjsonobj.getString("encryptedindex");
        encryptkey = requestjsonobj.getString("outencryptkey");
        System.out.println("metadata is " + metadata);
        System.out.println("fileuniqueid is " + fileuniqueid);
        if (null != encrypted_index && encrypted_index.length() > 0) {
            System.out.println("encrypted_index is " + encrypted_index);
        }
        System.out.println("encryptkey is " + encryptkey);
        Metadata saveresult = metadataser.savemetadata(metadata);
        if (0 == (saveresult.getFileuniqueid()).compareTo(fileuniqueid)) {
            System.out.println("save metadata success");
        }
        dockingsecuritycloudserimpl.uploadkey(sessionid, encryptkey, fileuniqueid);
        JSONObject cipherindexjsonObject = new JSONObject();
        if (null != encrypted_index && encrypted_index.length() > 0) {
            cipherindexjsonObject = JSONObject.parseObject(encrypted_index);
        }
        if (null != cipherindexjsonObject && null != cipherindexjsonObject.getJSONObject("retdata")) {
            dockingsecuritycloudserimpl.uploadcipherindex(cipherindexjsonObject);
        }
        return response("otherdataupload", "success", "8000",
                "otherdataupload success", null);
    }

    /**
     * InputStream转 File类型
     *
     * @param ins
     * @param file
     */
    public static void inputStreamToFile(InputStream ins, File file) {
        try {
            OutputStream os = new FileOutputStream(file);
            int bytesRead = 0;
            byte[] buffer = new byte[8192];
            while ((bytesRead = ins.read(buffer, 0, 8192)) != -1) {
                os.write(buffer, 0, bytesRead);
            }
            os.close();
            ins.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    private JSONObject response(String method, String result, String code,
                                String message, JSONObject details) {
        JSONObject ret = new JSONObject();
        ret.put("method", method);
        ret.put("result", result);
        ret.put("code", code);
        ret.put("message", message);
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        LocalDateTime currentTime = LocalDateTime.now(); // get the current date and time
        String currenttimestr = currentTime.format(formatter);
        ret.put("timestamp", currenttimestr);
        ret.put("details", details);
        return ret;
    }


}
