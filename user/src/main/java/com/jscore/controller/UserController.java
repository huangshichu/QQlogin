package com.jscore.controller;
import com.alibaba.fastjson.JSONObject;
import com.jscore.service.UserService;
import com.jscore.bean.User;

import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.bind.annotation.PostMapping;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RestController;

import java.util.List;

@RestController
@RequestMapping("/UserController")
public class UserController {
    @Autowired
    private UserService userService;

    @RequestMapping("/login")
    public String login(String user_name, String user_password){
        System.out.println(user_name+" "+user_password);
        List<User> list=userService.getUser();
        for(int i=0;i<list.size();i++){
            if(user_name.equals(list.get(i).getUser_name())&&user_password.equals(list.get(i).getUser_password())){
                System.out.println("登陆成功");
                String js ="{\"hsc\":\"登陆成功\"}";
                JSONObject jsonObj = new JSONObject(Boolean.parseBoolean(js));
                return "true";
            }
        }
        System.out.println("登录失败");
        String js ="{\"name\":\"用户名或密码错误\"}";
        JSONObject jsonObj = new JSONObject(Boolean.parseBoolean(js));
        return "false";
    }
}
