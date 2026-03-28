CREATE DATABASE ssh_monitor;

USE ssh_monitor;

CREATE TABLE ssh_logs (
    id INT AUTO_INCREMENT PRIMARY KEY,
    login_time DATETIME,
    username VARCHAR(50),
    result VARCHAR(10),
    ip_address VARCHAR(45)
);