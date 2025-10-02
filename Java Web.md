# Java Web

## dependencies

```xml
<dependencies>
    <!-- Servlet API 依赖 -->
    <dependency>
        <groupId>javax.servlet</groupId>
        <artifactId>javax.servlet-api</artifactId>
        <version>4.0.1</version>
    </dependency>

    <!-- JSP API 依赖 -->
    <dependency>
        <groupId>javax.servlet.jsp</groupId>
        <artifactId>javax.servlet.jsp-api</artifactId>
        <version>2.3.3</version>
    </dependency>

    <!-- JSTL API 依赖 -->
    <dependency>
        <groupId>javax.servlet.jsp.jstl</groupId>
        <artifactId>jstl-api</artifactId>
        <version>1.2</version>
    </dependency>

    <!-- JSTL 标签库标准实现 -->
    <dependency>
        <groupId>taglibs</groupId>
        <artifactId>standard</artifactId>
        <version>1.1.2</version>
    </dependency>
<!--        mysql依赖-->
    <dependency>
        <groupId>mysql</groupId>
        <artifactId>mysql-connector-java</artifactId>
        <version>8.0.32</version>
    </dependency>

    <!-- JavaMail API -->
    <dependency>
        <groupId>com.sun.mail</groupId>
        <artifactId>javax.mail</artifactId>
        <version>1.6.2</version> <!-- 版本可根据需要调整 -->
    </dependency>
</dependencies>
```

## WEB-INF/web.xml

```XML
<?xml version="1.0" encoding="UTF-8"?>
<web-app xmlns="http://xmlns.jcp.org/xml/ns/javaee"
         xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
         xsi:schemaLocation="http://xmlns.jcp.org/xml/ns/javaee
http://xmlns.jcp.org/xml/ns/javaee/web-app_4_0.xsd"
         version="4.0">
</web-app>
```



## Pojo (实体类，装数据库一行的值)



## Dao



### BaseDao

> 这个类是java通过jdbc对数据库直接操作的基层类

```java
package com.tur.Dao;

import java.io.InputStream;
import java.sql.*;
import java.util.Properties;

public class BaseDao {
    private static String driver;
    private static String url;
    private static String username;
    private static String psw;
    static{
        Properties p=new Properties();
        InputStream in=BaseDao.class.getClassLoader().getResourceAsStream("db.properties");
        try{
           p.load(in);
           driver=p.getProperty("driver");
           url=p.getProperty("url");
           username=p.getProperty("username");
           psw=p.getProperty("psw");
        }catch (Exception e){
            e.printStackTrace();
        }
    }
    public static Connection getConnection(){
        Connection conn=null;
        try{
            Class.forName(driver);
            conn=DriverManager.getConnection(url,username,psw);
        }catch (Exception e){
            e.printStackTrace();
        }
        return conn;
    }
    //select操作
    public static ResultSet execute(Connection conn, PreparedStatement pst, String sql, Object[] params, ResultSet rs){
        try {
            pst=conn.prepareStatement(sql);
            if(params!=null){
                for(int i=0;i<params.length;i++){
                    pst.setObject(i+1,params[i]);
                }
            }
            rs=pst.executeQuery();
        } catch (SQLException e) {
            throw new RuntimeException(e);
        }
        return rs;
    }
    //增删改操作
    public static int execute(Connection conn,PreparedStatement pst,String sql,Object[] params){
        int updateCount=0;
        try {
            pst=conn.prepareStatement(sql);
            if(params!=null){
                for(int i=0;i<params.length;i++){
                    pst.setObject(i+1,params[i]);
                }
            }
            updateCount=pst.executeUpdate();
        }catch (Exception e){
            e.printStackTrace();
        }
        return updateCount;
    }
    //清理资源
    public static boolean closeRes(Connection conn,PreparedStatement pst,ResultSet rs){
        boolean result=true;
        try {
            if(rs!=null){
                rs.close();
            }
            if(pst!=null){
                pst.close();
            }
            if(conn!=null){
                conn.close();
            }
        }catch (Exception e){
            result=false;
            e.printStackTrace();
        }
        return result;
    }
}

```



## Service



## Servlet



## Utils

> 这个类 是在撰写其他类时的一个工具类



### Java Mail

```java
package com.tur.Utils;

import javax.activation.DataHandler;
import javax.activation.FileDataSource;
import javax.mail.*;
import javax.mail.internet.*;
import java.util.Properties;

public class MyEmail{
    private String host;
    private String port;
    private String username;
    private String pwd;
    private String recipient;
    private String subject;
    private String textMessage;
    private String filePath;
    public MyEmail(String recipient,String subject,String textMessage){
        this.host="smtp.qq.com";
        this.port="465";
        this.username="1831780773@qq.com";
        this.pwd="fzrdwxpjdntschec";
        this.recipient=recipient;
        this.subject=subject;
        this.textMessage=textMessage;
    }
    public void sendTextMail() throws MessagingException {
        //设置服务器属性
        Properties prop=new Properties();
        prop.put("mail.smtp.host",host);
        prop.put("mail.smtp.prot",port);
        prop.put("mail.smtp.auth","true");
        prop.put("mail.smtp.ssl.enable","true");
        //创建会话
        Authenticator auth=new Authenticator(){
            public PasswordAuthentication getPasswordAuthentication(){
                return new PasswordAuthentication(username,pwd);
            }
        };
        Session session=Session.getInstance(prop,auth);
        //设置消息
        MimeMessage msg=new MimeMessage(session);
        msg.setFrom(new InternetAddress(username));
        msg.setRecipient(MimeMessage.RecipientType.TO,new InternetAddress(recipient));
        msg.setSubject(subject);
        msg.setText(textMessage);
        //发送消息
        Transport.send(msg);
    }
    public MyEmail(String recipient,String subject,String textMessage,String filePath){
        this.host="smtp.qq.com";
        this.port="465";
        this.username="1831780773@qq.com";
        this.pwd="fzrdwxpjdntschec";
        this.recipient=recipient;
        this.subject=subject;
        this.textMessage=textMessage;
        this.filePath=filePath;
    }
    public void sendMimeMessage() throws MessagingException {
        //设置服务器属性
        Properties prop=new Properties();
        prop.put("mail.smtp.host",host);
        prop.put("mail.smtp.prot",port);
        prop.put("mail.smtp.auth","true");
        prop.put("mail.smtp.ssl.enable","true");
        //创建会话
        Authenticator auth=new Authenticator(){
            public PasswordAuthentication getPasswordAuthentication(){
                return new PasswordAuthentication(username,pwd);
            }
        };
        Session session=Session.getInstance(prop,auth);
        //创建消息
        MimeMessage msg=new MimeMessage(session);
        Multipart mp=new MimeMultipart();
        //设置图片或者文件消息
        BodyPart bp=new MimeBodyPart();
        bp.setDataHandler(new DataHandler(new FileDataSource(filePath)));
        mp.addBodyPart(bp);
        //设置文本消息
        bp=new MimeBodyPart();
        bp.setText(textMessage);
        mp.addBodyPart(bp);
        msg.setContent(mp);
        //发送消息
        Transport.send(msg);
    }
}
```



### Constants

> 本类用来存一些常量，方便后期运维



```java
package com.tur.Utils;

public class Constants {
    public static final String USER_SESSION="userSession";
}

```



