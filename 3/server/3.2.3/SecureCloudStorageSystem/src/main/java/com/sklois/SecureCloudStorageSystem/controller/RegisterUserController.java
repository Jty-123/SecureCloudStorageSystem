package com.sklois.SecureCloudStorageSystem.controller;

import com.sklois.SecureCloudStorageSystem.entity.RegisterUser;
import com.sklois.SecureCloudStorageSystem.service.DatabaseSer;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.*;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.time.LocalDateTime;
import java.time.format.DateTimeFormatter;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;

import com.alibaba.fastjson.JSONObject;

import javax.servlet.http.HttpServletRequest;

@RestController
public class RegisterUserController {

    @Autowired
    DatabaseSer databaseser;

    @RequestMapping("/checkusernameexistence")
    @ResponseBody
    public Object checkusernameexistence(@RequestBody JSONObject json) {
        if (null == json) {
            return null;
        }
        String method = json.getString("method");
        String version = json.getString("version");
        String timestamp = json.getString("timestamp");
        JSONObject request = json.getJSONObject("request");
        String username = request.getString("username");

        /**
         * 检查参数是否合格
         */
        if (null == method || 0 != method.compareTo("checkusernameexistence")) {
            return response(method, "failed", "8001", "method error", null);
        }
        if (null == version || 0 != version.compareTo("1.0")) {
            return response(method, "failed", "8002", "version error", null);
        }
        if (null == timestamp) {
            return response(method, "failed", "8003", "timestamp error", null);
        }
        if (null == username) {
            return response(method, "failed", "8004", "username error", null);
        }

        System.out.println("method is " + method);
        System.out.println("version is " + version);
        System.out.println("timestamp is " + timestamp);
        System.out.println("username is " + username);

        HashMap<String, Object> findout = databaseser.findByName(username);

        boolean retresult = (boolean) findout.get("result");
        String retmessage = (String) findout.get("message");
        List<RegisterUser> findoutlist = (List<RegisterUser>) findout.get("findout");

        System.out.println("retresult is " + retresult);
        System.out.println("message is " + retmessage);

        if (retresult) {
            if (null != findoutlist && findoutlist.size() > 0) {
                JSONObject findresult = new JSONObject();
                findresult.put("ifexist", "true");
                return response(method, "success", "8000", retmessage, findresult);
            } else {
                JSONObject findresult = new JSONObject();
                findresult.put("ifexist", "false");
                return response(method, "success", "8000", retmessage, findresult);
            }
        } else {
            JSONObject findresult = new JSONObject();
            findresult.put("ifexist", "false");
            return response(method, "success", "8000", retmessage, findresult);
        }
    }

    @RequestMapping("/userregister")
    @ResponseBody
    public Object userregister(@RequestBody JSONObject json, HttpServletRequest servletrequest) throws ParseException {
        if (null == json) {
            return null;
        }
        System.out.println("json is " + json.toJSONString());
        String method = json.getString("method");
        String version = json.getString("version");
        String timestamp = json.getString("timestamp");
        JSONObject request = json.getJSONObject("request");
        String username = request.getString("username");
        String password = request.getString("password");
        String role = request.getString("role");

        System.out.println("method is " + method);
        System.out.println("version is " + version);
        System.out.println("timestamp is " + timestamp);
        System.out.println("username is " + username);
        System.out.println("password is " + password);
        System.out.println("role is " + role);
        /**
         * 检查参数是否合格
         */
        if (null == method || 0 != method.compareTo("userregister")) {
            return response(method, "failed", "8001", "method error", null);
        }
        if (null == version || 0 != version.compareTo("1.0")) {
            return response(method, "failed", "8002", "version error", null);
        }
        if(null==timestamp||timestamp.length()<=0){
            return response(method, "failed", "8003", "timestamp error", null);

        }
        if(null==username||username.length()<=0){
            return response(method, "failed", "8004", "username error", null);

        }if(null==password||password.length()<=0){
            return response(method, "failed", "8005", "password error", null);

        }if(null==role||role.length()<=0){

        }

//        SimpleDateFormat simpleDateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
//        String dateStr = "2019-01-03 10:59:27";
        DateTimeFormatter formatter = DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss");
        LocalDateTime localdatetime = LocalDateTime.parse(timestamp,formatter);
        System.out.println("date is " + localdatetime.toString());
        HashMap<String, Object> saveresult = databaseser.save(username,password,role,localdatetime);

        boolean retresult = (boolean) saveresult.get("result");
        String retmessage = (String) saveresult.get("message");
        System.out.println("retresult is " + retresult);
        System.out.println("message is " + retmessage);
        if(retresult){
            String saveusername = (String) saveresult.get("username");
            String saverole = (String) saveresult.get("role");

            JSONObject retresultjson = new JSONObject();
            retresultjson.put("username",saveusername);
            retresultjson.put("role",saverole);
            return response(method, "success", "8000", retmessage, retresultjson);
        }else{
            if(0==retmessage.compareTo("save error")){
                JSONObject retresultjson = new JSONObject();
                retresultjson.put("username", null);
                return response(method, "fail", "8005", retmessage, retresultjson);
            }else if(0==retmessage.compareTo("username exist")){
                JSONObject retresultjson = new JSONObject();
                return response(method, "fail", "8006", retmessage, retresultjson);
            }else{
                JSONObject retresultjson = new JSONObject();
                return response(method, "fail", "8007", retmessage, retresultjson);
            }
        }
    }


    @RequestMapping("/userlist")
    @ResponseBody
    public Object userlist(@RequestBody JSONObject json, HttpServletRequest servletrequest) throws ParseException {
        if (null == json) {
            return null;
        }

        HashMap<String, Object> findmap =databaseser.findAll();
        boolean retresult = (boolean) findmap.get("result");
        String retmessage = (String) findmap.get("message");
        List<RegisterUser> findout = (List<RegisterUser>)findmap.get("findout");
        if(retresult&&null!=findout){
            JSONObject retresultjson = new JSONObject();
            retresultjson.put("findout",findout);
            return response("userlist", "success", "8000", retmessage, retresultjson);
        }
        return null;
    }

    @RequestMapping("/userfind")
    @ResponseBody
    public Object userfind(@RequestBody JSONObject json, HttpServletRequest servletrequest) throws ParseException {
        if (null == json) {
            return null;
        }
        //用户鉴别
        //权限鉴别
        System.out.println("json is " + json.toJSONString());
        String method = json.getString("method");
        String version = json.getString("version");
        String timestamp = json.getString("timestamp");
        JSONObject request = json.getJSONObject("request");
        String username = request.getString("username");
        String password = request.getString("password");
        String role = request.getString("role");
        return null;
    }


    @RequestMapping("/usermodify")
    @ResponseBody
    public Object usermodify(@RequestBody JSONObject json, HttpServletRequest servletrequest) throws ParseException {
        if (null == json) {
            return null;
        }

        return null;
    }


    @RequestMapping("/userdelete")
    @ResponseBody
    public Object userdelete(@RequestBody JSONObject json, HttpServletRequest servletrequest) throws ParseException {
        if (null == json) {
            return null;
        }

        return null;
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
