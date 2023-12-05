#include "databasemanager.h"
#include <iostream>
#include <mysql.h>
#include <qDebug>

DatabaseManager::DatabaseManager(QObject* parent)
    : QObject(parent)
{
    initMysql();
}

DatabaseManager::~DatabaseManager()
{}

int DatabaseManager::initMysql()
{
    MYSQL* conn;
    conn = mysql_init(NULL);
    if (conn == NULL) {
        std::cout << "Error: " << mysql_error(conn) << std::endl;
        return 1;
    }
    conn = mysql_real_connect(conn, "localhost", "root", "194910", "", 3306, NULL, 0);
    if (conn) {
        qDebug() << "Connected to MySQL server";

        if (mysql_query(conn, "CREATE DATABASE IF NOT EXISTS manager_system_database") != 0) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }

        if (mysql_query(conn, "USE manager_system_database") != 0) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }

        if (mysql_query(conn, "CREATE TABLE IF NOT EXISTS user_table (id INT AUTO_INCREMENT PRIMARY KEY, username VARCHAR(50), password VARCHAR(50), age INT, gender VARCHAR(10), birthday DATE, created_at TIMESTAMP)") != 0) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }

        for (int Index = 0; Index < 1000; Index++)
        {
            if (mysql_query(conn, "INSERT INTO user_table (username, password, age, gender, birthday, created_at) VALUES ('john_doe', 'password123', 30, 'male', '1992-05-15', NOW())") != 0) {
                fprintf(stderr, "Error: %s\n", mysql_error(conn));
                mysql_close(conn);
                return 1;
            }
        }

        std::cout << "Record inserted successfully" << std::endl;


        if (mysql_query(conn, "SELECT * FROM user_table")) {
            fprintf(stderr, "Error: %s\n", mysql_error(conn));
            mysql_close(conn);
            return 1;
        }
        MYSQL_RES* res;
        MYSQL_ROW row;
        res = mysql_use_result(conn);
        while ((row = mysql_fetch_row(res)) != NULL) {
            for (int i = 0; i < mysql_num_fields(res); i++) {


                qDebug() << mysql_fetch_field_direct(res, i)->name << ":" << (row[i] ? row[i] : "NULL");
            }
            qDebug() << "-----------------------------------";
        }
        mysql_free_result(res);

        mysql_close(conn);
    }
    else {
        qDebug() << "Connection failed: " << mysql_error(conn);
    }
    return 0;
}
