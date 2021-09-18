package com.jscore.dao;

import com.jscore.bean.User;

import java.util.List;

public interface UserMapper {
    //查询所有用户
    List<User> getUser();
}