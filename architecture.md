        +--------------------+
        |   SSHD Service     |
        | (/var/log/auth.log |
        |  or /var/log/secure)|
        +---------+----------+
                  |
                  v
        +--------------------+
        | Log Monitor Script |
        | (C++ / Shell)      |
        | - Parse logs       |
        | - Detect login     |
        | - Extract fields   |
        +---------+----------+
                  |
                  v
        +--------------------+
        |   MySQL Database   |
        | ssh_login_logs     |
        +--------------------+
                  |
                  v
        +--------------------+
        |  Security Reports  |
        |  Monitoring Tools  |
        +--------------------+

        System Architecture

1. SSH daemon generates logs.

2. Logs stored in:
/var/log/auth.log or /var/log/secure

3. Monitoring script reads logs using tail command.

4. Script extracts:
- login time
- username
- success/failure
- client IP

5. Data stored in MySQL database.

6. Security team analyzes logs for attacks.