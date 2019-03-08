package ru.servers.databaseserver.data.dao;

import ru.servers.databaseserver.data.entity.User;

public class test {
    public static void main(String[] args) {
        UsersRespositoryImpl users = new UsersRespositoryImpl();

        User user = users.findByEmail("12312");
        if (user == null){
            System.out.println("user not found");
        } else {
            System.out.println(user.getPassword());
            System.out.println(user.getEmail());
            System.out.println(user.getId());
        }
    }
}
