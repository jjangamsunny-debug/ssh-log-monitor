#include <iostream>
#include <string>
#include <mysql/mysql.h>
#include <sstream>
#include "db_config.h"

using namespace std;

MYSQL *conn;

void insert_log(string username, string result, string ip)
{
    string query = "INSERT INTO ssh_logs(login_time,username,result,ip_address) VALUES(NOW(),'" 
                    + username + "','" + result + "','" + ip + "')";

    if(mysql_query(conn, query.c_str()))
    {
        cout<<"Insert error: "<<mysql_error(conn)<<endl;
    }
}

string extract_value(string line, string key)
{
    size_t pos = line.find(key);

    if(pos == string::npos)
        return "unknown";

    pos += key.length();

    size_t end = line.find(" ", pos);

    return line.substr(pos, end - pos);
}

int main()
{
    conn = mysql_init(NULL);

    if(!mysql_real_connect(conn, DB_HOST, DB_USER, DB_PASS, DB_NAME, 0, NULL, 0))
    {
        cout<<"Database connection failed\n";
        return 1;
    }

    FILE *pipe = popen("tail -F /var/log/auth.log", "r");

    char buffer[1024];

    while(fgets(buffer, sizeof(buffer), pipe))
    {
        string line(buffer);

        if(line.find("Failed password") != string::npos)
        {
            string user = extract_value(line, "for ");
            string ip = extract_value(line, "from ");

            insert_log(user, "Failure", ip);

            cout<<"Failed login: "<<user<<" "<<ip<<endl;
        }

        else if(line.find("Accepted password") != string::npos)
        {
            string user = extract_value(line, "for ");
            string ip = extract_value(line, "from ");

            insert_log(user, "Success", ip);

            cout<<"Successful login: "<<user<<" "<<ip<<endl;
        }
    }

    mysql_close(conn);

    return 0;
}