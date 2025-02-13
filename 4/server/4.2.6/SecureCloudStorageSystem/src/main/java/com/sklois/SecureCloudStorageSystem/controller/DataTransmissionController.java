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
            System.out.println("encrypted_index is " + encrypted_index);
            System.out.println("encryptkey is " + encryptkey);
        }
        Metadata saveresult = metadataser.savemetadata(metadata);
        if (0 == (saveresult.getFileuniqueid()).compareTo(fileuniqueid)) {
            System.out.println("save metadata success");
        }
        alidockingcloudstorageser.uploaddata(file, fileuniqueid);
        dockingsecuritycloudserimpl.uploadkey(sessionid, encryptkey, fileuniqueid);
//        dockingsecuritycloudserimpl.getkey(sessionid,fileuniqueid);
//        dockingsecuritycloudserimpl.deletekey(fileuniqueid);

//        cipherindex = "{" +
//                "\"fileuniqueid1\":{" +
//                "\"keyword1\":6," +
//                "\"keyword2\":6," +
//                "\"keyword3\":6," +
//                "\"keyword4\":6," +
//                "\"keyword5\":6," +
//                "\"keyword6\":6" +
//                "}" +
//                "}";
        JSONObject cipherindexjsonObject = new JSONObject();
        cipherindexjsonObject = JSONObject.parseObject(encrypted_index);


        dockingsecuritycloudserimpl.uploadcipherindex(cipherindexjsonObject);

//        				try
//				{
//				    Thread.sleep(1000);
//				}
//				catch (InterruptedException e)
//				{
//				    e.printStackTrace();
//				}
//        dockingsecuritycloudserimpl.searchcipherindex("keyword1");
//        dockingsecuritycloudserimpl.deletecipherindex("fileuniqueid1");
//        swiftDockingCloudStorageSer.uploaddata(file,fileuniqueid);

        return response("dataupload", "success", "8000",
                "dataupload success", null);

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
