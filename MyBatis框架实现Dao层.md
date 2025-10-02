# MyBatis框架实现Dao层

> [XML 映射器_MyBatis中文网](https://mybatis.net.cn/sqlmap-xml.html)

## 配置pom.xml文件



```xml
<!--依赖-->      
<dependency>
          <groupId>junit</groupId>
          <artifactId>junit</artifactId>
          <version>4.12</version>
          <scope>test</scope>
      </dependency>
<!--      mybatis依赖-->
      <dependency>
          <groupId>org.mybatis</groupId>
          <artifactId>mybatis</artifactId>
          <version>3.5.19</version>
      </dependency>
      <!--mysql驱动-->
      <dependency>
          <groupId>mysql</groupId>
          <artifactId>mysql-connector-java</artifactId>
<!--          <version>5.1.37</version>-->
          <version>8.0.33</version>
      </dependency>
<!--lombok依赖-->
<dependency>
          <groupId>org.projectlombok</groupId>
          <artifactId>lombok</artifactId>
          <version>1.18.4</version>
      </dependency>
```



使得resource和java中的xml文件能被过滤出来的build



```xml
<build>
      <resources>
          <resource>
              <directory>src/main/resources</directory>
              <includes>
                  <include>**/*.properties</include>
                  <include>**/*.xml</include>
              </includes>
              <filtering>true</filtering>
          </resource>
          <resource>
              <directory>src/main/java</directory>
              <includes>
                  <include>**/*.properties</include>
                  <include>**/*.xml</include>
              </includes>
              <filtering>true</filtering>
          </resource>
      </resources>
  </build>
```





## resources中获取数据库连接 mybatis-config.xml



```properties
#db.properties
jdbc.driver=com.mysql.cj.jdbc.Driver
jdbc.url=jdbc:mysql://localhost:3306/mybatis_database?useSSL=true&useUnicode=true&characterEncoding=UTF-8
jdbc.username=root
jdbc.pwd=pzl945464
```



```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE configuration
        PUBLIC "-//mybatis.org//DTD Config 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-config.dtd">
<configuration>
    <properties resource="db.properties" />
    <settings>
        <setting name="logImpl" value="STDOUT_LOGGING"/>
    </settings>
    <typeAliases>
        <typeAlias type="com.tur.pojo.Student" alias="Student"/>
        <typeAlias type="com.tur.pojo.Teacher" alias="Teacher"/>
    </typeAliases>
    <environments default="development">
        <environment id="development">
            <transactionManager type="JDBC"/>
            <dataSource type="POOLED">
                <property name="driver" value="${jdbc.driver}}"/>
                <property name="url" value=""/>
                <property name="username" value="${jdbc.username}}"/>
                <property name="password" value="${jdbc.pwd}"/>
            </dataSource>
        </environment>
    </environments>
    <mappers>
        <!--注意这里是 / ，但是如果 这里是不同的Mapper实现应该怎么写？-->
        <mapper resource="com/tur/DAO/UserMapper.xml"/>
    </mappers>
</configuration>
```



## 获取sqlSessionFactory的工具类



```java
public class MyBatisUtils {
    public static SqlSessionFactory sqlSessionFactory;
    static{
        try {
            String resource = "mybatis-config.xml";
            InputStream inputStream = Resources.getResourceAsStream(resource);
            sqlSessionFactory = new SqlSessionFactoryBuilder().build(inputStream);
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    public static SqlSession getSqlSession(){
        return  sqlSessionFactory.openSession();
    }
}
```



## DAO层



### interface

```java
public interface UserDao {
    List<Student> getStudents();
}
```



### implement

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.tur.DAO.UserDao">
    <select id="getStudents" resultType="com.tur.POJO.Student">
        select * from mybatis_database.students
    </select>
</mapper>
```



## @Test

```java
public class UserDaoTest {
    @Test
    public void test(){
        SqlSession sqlSession= MyBatisUtils.getSqlSession();
        try{
            UserDao userDao = sqlSession.getMapper(UserDao.class);
            List<Student> students = userDao.getStudents();
            for(Student student:students){
                System.out.println(student);
            }
        }catch (Exception e){
            e.printStackTrace();
        }finally {
            sqlSession.close();
        }
    }

}
```



## 使用Map来传参

```xml
<insert id="insertUser" parameterType="map" resultType="int">
    insert into students (id,name,pwd) values (#{_id},#{_name},#{_pwd})
</insert>
```



```java
SqlSession sqlSession=MybatisUtils.getSqlSession();
studentDao=sqlSession.getMapper(studentDao.class);
Map<String,Object> map;
map.put("_id","102301325");
map.put("_name","王浩楠");
map.put("_pwd","123456");
studentDao.insertUser(map);
sqlSession.close();
```



## 模糊查询

1.“%”#{}“%”   字符串拼写

2.传参的时候就传带有%的



个人感觉如果模糊查询的关键字不是字符串类型还是用第一种方法会比较好。





## 映射器说明

```xml
<!-- 使用映射器接口实现类的完全限定类名 -->
<mappers>
  <mapper class="org.mybatis.builder.AuthorMapper"/>
  <mapper class="org.mybatis.builder.BlogMapper"/>
  <mapper class="org.mybatis.builder.PostMapper"/>
</mappers>
```



> 最推荐的方法，但注意这里是用 "/" 分隔

```xml
<!-- 使用相对于类路径的资源引用 -->
<mappers>
  <mapper resource="org/mybatis/builder/AuthorMapper.xml"/>
  <mapper resource="org/mybatis/builder/BlogMapper.xml"/>
  <mapper resource="org/mybatis/builder/PostMapper.xml"/>
</mappers>
```



```xml
<!-- 将包内的映射器接口实现全部注册为映射器 -->
<mappers>
  <package name="org.mybatis.builder"/>
</mappers>
```







## resultMap结果集映射

> 应对pojo实例类型中的参数名称和数据库中的字段名不匹配的情况。可以用resultMapper映射。
>
> 由于mybatis有auto_map功能，所以如果我的类中的属性的名称和数据库中的字段你的名称相近也可以匹配到



```xml
<!--需要引入resultMap标签-->
<resultMap>
	<result property="uid" column="id"/>
</resultMap>
```



## settings

```xml
<settings>
    <!--可以查文档-->
    <setting name="" value=""/>
</settings>
```



## 日志工厂

### log4j

```xml
<!--pom.xml导入依赖-->
<!-- Log4j 2 API （必选） -->
      <dependency>
          <groupId>org.apache.logging.log4j</groupId>
          <artifactId>log4j-api</artifactId>
          <version>2.23.1</version> <!-- 请检查并使用最新版本 -->
      </dependency>

      <!-- Log4j 2 Core Implementation （必选） -->
      <dependency>
          <groupId>org.apache.logging.log4j</groupId>
          <artifactId>log4j-core</artifactId>
          <version>2.23.1</version> <!-- 请检查并使用最新版本 -->
      </dependency>
```



```xml
<!--写配置文件 log4j.properties-->
# 根日志级别和输出目标
rootLogger.level = info
rootLogger.appenderRef.stdout.ref = Console

# 控制台输出器
appender.console.type = Console
appender.console.name = Console
appender.console.layout.type = PatternLayout
appender.console.layout.pattern = %d{HH:mm:ss.SSS} [%t] %-5level %c{1} - %msg%n
```



```java
private static final Logger logger= (Logger) LogManager.getLogger(studentDaoTest.class);//需要调用的类加入Logger属性
//然后在函数中利用logger调用相应的函数即可
logger.info("");
logger.debug("");
```



## 配置别名



```xml
<typeAliases>
    <!--type是类的实际位置 alias就是这个位置的别名-->
	<typeAlias type="com.tur.pojo.Student" alias="Student"/>
</typeAliases>
```





## 多对一



> 方法一 sql简单，resultMap写的比较复杂

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.tur.dao.StudentMapper">
    <select id="getStudents" resultMap="StudentTeacher">
        select * from students;
    </select>
    <resultMap id="StudentTeacher" type="Student">
        <id property="id" column="id"/>
        <result property="name" column="name"/>
        <association javaType="Teacher" property="teacher" column="tid" select="getTeacher"/>
    </resultMap>
    <select id="getTeacher" resultType="Teacher">
        select * from teachers where id=#{tid};
    </select>
</mapper>
```



> 单sql的映射 多对一，如果希望返回的元素作为instance存储到一个类中的时候需要用association标签

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.tur.dao.StudentMapper">
    <select id="getStudents" resultMap="StudentTeacher">
        select s.id as sid,s.name as sname,t.name as tname,t.id as tid from students s,teachers t where s.tid=t.id
    </select>

    <resultMap id="StudentTeacher" type="Student">
        <id property="id" column="sid"/>
        <result property="name" column="sname"/>
        <association javaType="Teacher" property="teacher">
            <result property="name" column="tname"/>
            <result property="id" column="tid"/>
        </association>
    </resultMap>
</mapper>
```



## 一对多

> 但sql的映射 一对多，如果希望返回的相同的一对应的不同的多存储到一个列表中，应该用collection标签,其中的ofType表示列表的每一个元素的类型

```xml
<?xml version="1.0" encoding="UTF-8" ?>
<!DOCTYPE mapper
        PUBLIC "-//mybatis.org//DTD Mapper 3.0//EN"
        "http://mybatis.org/dtd/mybatis-3-mapper.dtd">
<mapper namespace="com.tur.dao.TeacherMapper">
    <select id="getTeachers" resultMap="studentTeacher">
        select t.id as tid,t.name as tname,s.id as sid,s.name as sname from students s,teachers t where t.id=s.tid;
    </select>
    <resultMap id="studentTeacher" type="Teacher">
        <result property="id" column="tid"/>
        <result property="name" column="tname"/>
        <collection property="students" ofType="Student">
            <result property="id" column="sid"/>
            <result property="name" column="sname"/>
        </collection>
    </resultMap>
</mapper>
```



## 动态sql

> 标签

```xml
<if test="id != null">
	sql语句
</if>
<choose>
	<when test="">
    </when>
    <when test="">
    </when>
    <otherwise>
    
    </otherwise>
</choose>

<!--会自动去除头部多余的AND |OR-->
<where>
	<if test="">
    </if>
</where>

<!--会自动去除尾部多余的 ","-->
<set>
	<if test="">
    
    </if>
    
</set>

<foreach collection="ids" item="id" open="(" close=")" separator=“ or ”>
    id=#{id}
</foreach>
<!--
collection表示列表的名称(key)
item表示每一个元素的名称代号
open表示结果的开始字符，也可以是一个字符串
close表示结果的结束字符，同样也可以是一个字符串
separator表示中间的元的分割符，也可以是字符串
效果类似：
(id=1 or id=2 or id=3)
-->
```



```xml
<!--
where标签的模拟
prefix表示前缀值
prefixOverrides表示最开始如果有就去掉这个字符串，此处如果最开始是AND |OR就去掉
-->
<trim prefix="WHERE" prefixOverrides="AND |OR ">
  ...
</trim>
<!--
set标签的模拟
prefix表示前缀值
suffixOverrides表示最后果有就去掉这个字符串，此处如果最后是 , 就去掉
-->
<trim prefix="SET" suffixOverrides=",">
  ...
</trim>
```



## 缓存提速

### MyBatis提供有两个级别的缓存

一级缓存默认是开的，可以通过<setting>标签设置查官网配置相关的参数

```xml
<setting name="cacheEnabled" value="true"/>
```

二级缓存可以在sql文件中配置 **Mapper.xml这样的文件

里面加上<cache/>标签就可以使用了。

```xml
<cache/>
```

当然这个标签也可以设置其他的参数可以通过官网查阅



### 自定义缓存

ehcache
