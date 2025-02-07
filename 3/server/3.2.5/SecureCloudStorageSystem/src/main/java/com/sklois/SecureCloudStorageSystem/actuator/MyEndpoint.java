package com.sklois.SecureCloudStorageSystem.actuator;

import org.springframework.boot.actuate.endpoint.annotation.Endpoint;
import org.springframework.boot.actuate.endpoint.annotation.ReadOperation;

import java.util.HashMap;
import java.util.Map;

@Endpoint(id = "myendpoint")
public class MyEndpoint {

    @ReadOperation
    public Map<String,String> test(){

        Map<String,String> result = new HashMap<>();
        result.put("name","myendpoint");

        return result;
    }
}
