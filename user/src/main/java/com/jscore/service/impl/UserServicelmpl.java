package com.jscore.service.impl;

import com.jscore.dao.UserMapper;
import com.jscore.service.UserService;
import com.jscore.bean.User;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;
@Service
public class UserServicelmpl implements UserService {
    @Autowired
    private UserMapper userMapper;

    @Override
    public List<User> getUser() {
        List<User> list = userMapper.getUser();
        return list;
    }
}
