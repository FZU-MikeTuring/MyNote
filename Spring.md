# Spring

> 配置地狱

## 依赖



```xml
<dependencies>
        <!--测试依赖-->
        <dependency>
            <groupId>junit</groupId>
            <artifactId>junit</artifactId>
            <version>4.12</version>
        </dependency>
        <!--mybatis依赖-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis</artifactId>
            <version>3.5.19</version>
        </dependency>
        <!--mysql驱动-->
        <dependency>
            <groupId>mysql</groupId>
            <artifactId>mysql-connector-java</artifactId>
            <version>8.0.33</version>
        </dependency>
        <!--lombok依赖-->
        <dependency>
            <groupId>org.projectlombok</groupId>
            <artifactId>lombok</artifactId>
            <version>1.18.4</version>
        </dependency>
		<!--spring mvc依赖-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-webmvc</artifactId>
            <version>5.3.23</version>
        </dependency>
    	<!--使用AOP织入需要导入一个依赖包-->
    	<dependency>
            <groupId>org.aspectj</groupId>
            <artifactId>aspectjweaver</artifactId>
            <version>1.9.4</version>
    	</dependency>
    	<!--spring操作数据库还需要spring-jdbc-->
        <dependency>
            <groupId>org.springframework</groupId>
            <artifactId>spring-jdbc</artifactId>
            <version>5.1.9.RELEASE</version>
        </dependency>
    	<!--mybatis-spring依赖-->
        <dependency>
            <groupId>org.mybatis</groupId>
            <artifactId>mybatis-spring</artifactId>
            <version>2.1.1</version>
    	</dependency>
    </dependencies>
```

## build注意资源过滤

```xml
<build>
        <resources>
            <resource>
                <directory>src/main/java</directory>
                <includes>
                    <include>**/*.xml</include>
                    <include>**/*.properties</include>
                </includes>
                <filtering>true</filtering>
            </resource>

            <resource>
                <directory>src/main/resources</directory>
                <includes>
                    <include>**/*.xml</include>
                    <include>**/*.properties</include>
                </includes>
                <filtering>true</filtering>
            </resource>
        </resources>
    </build>

```



## beans.xml配置

> 本配置包括了注解需要的context和aop切面需要的aop部分

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <!--bean标签实现装配-->
</beans>
```





## IOC理论推导

> IOC--inversion of control控制反转

同一个接口可能对应多个不同的是实现类

例如一个UserDao分别对应UserDaoServerImpl、UserDaoMysqlImpl、UserDaoOracleImpl,

对于一个Service层的接口UserService。在UserService中需要调用UserDao层的方法，但是因为有多个实现类，一旦我要改变需求就要在Service层不断改变代码，但是如果我在Service层写一个setUserDao的方法，参数是UserDao的接口，而实际传参的时候可以是UserDao的任意一个是任意一个实现类，那么就可以不改动Service层的代码使用不同实现类的实现。从这个角度来看，接口类实在是太伟大了。

IOC控制反转就是将控制权从程序员手中转移到了用户手中，用户可以根据需求设置自己想要的操作。



![](D:\MyCode\MarkDown\IMG\约柜系统 (1).jpg)



## HelloSpring





## IoC创建对象的方法

1.使用无参构造创建对象

```xml
<bean id="" class="">
	<property name="" value="">
<property name="" ref="">
</bean>
```



2.使用有参构造创建函数

```xml
<bean id="" class="">
    <!--根据参数的下标进行赋值-->
	<constructor-arg index="0" value=""/>
    <!--根据参数的名称进行赋值-->
	<constructor-arg name="" value=""/>
</bean>
```



## spring配置

### 别名

```xml
<!--可以通过name来取别名，当别处调用的时不仅可以用id来调用,也可以通过别名来使用-->
<bean id="" class="" name="">
</bean>
```



### import

> 假设项目中有多个人开发，可能会产生多个文件，通过import可以将多个Bean文件合成为一个Bean文件

```xml
<import resource="bean1.xml"/>
<import resource="bean2.xml"/>
<import resource="bean3.xml"/>
```



## 依赖注入

### 构造器注入



### set方式注入(*重点)

> 依赖注入
>
> 依赖：bean的对象的创建依赖容器
>
> 注入：bean对象的所有属性由容器来注入



```xml
 <bean id="student" class="com.tur.pojo.Student">
        <!--    第一种普通值注入-->
        <property name="name">
            <value>王浩楠</value>
        </property>
<!--        第二种，bean注入，ref-->
        <property name="address" ref="Address"/>
<!--        第三种，数组注入-->
        <property name="books">
            <array>
                <value>红楼梦</value>
                <value>三国演义</value>
                <value>水浒传</value>
                <value>西游记</value>
            </array>
        </property>
<!--        第四种,list-->
        <property name="hobbys">
            <list>
                <value>听歌</value>
                <value>打篮球</value>
                <value>游泳</value>
            </list>
        </property>
<!--        map-->
        <property name="card">
            <map>
                <entry key="身份证" value="131181200409092730"/>
                <entry key="银行卡" value="46546854564564646"/>
            </map>
        </property>
<!--        set-->
        <property name="game">
            <set>
                <value>LOL</value>
                <value>王者荣耀</value>
            </set>
        </property>
        <property name="wife">
            <null/>
        </property>
        <property name="info">
            <props>
                <prop key="administrator">administrator@example.org</prop>
                <prop key="support">support@example.org</prop>
                <prop key="development">development@example.org</prop>
            </props>
        </property>
    </bean>
```

### 拓展注入

> p标签和c标签

```xml
xmlns:p="http://www.springframework.org/schema/p"
xmlns:c="http://www.springframework.org/schema/c"
```



## bean的作用域

```xml
<!--instance只有一个，大家共用-->
<bean id="student" class="com.tur.pojo.student" scope="sigleton"></bean>
<!--instance每次都创建一个新的，比较消耗资源-->
<bean id="student" class="com.tur.pojo.student" scope="prototype"></bean>
```



## bean自动装配



三种装配方式：

1.在xml中显示装配

2.在java中显示装配

3.隐式的自动装配

1)可以使用注解来实现

### 配置文件方式

> 分为byName和byType两种方式

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <bean id="dog" class="com.tur.pojo.Dog"/>
    <bean id="cat" class="com.tur.pojo.Cat"/>
    <!--byName自动装配是通过查找自己类的set方法后面的字段的字符串相同的来装配的，如果对应的类的bean的id与set后的字段字符不一样就找不到了-->
    <bean id="people" class="com.tur.pojo.People" autowire="byName">
        <property name="age" value="12"/>
    </bean>
</beans>
```



```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <bean id="dog" class="com.tur.pojo.Dog"/>
    <bean id="cat" class="com.tur.pojo.Cat"/>
    <!--byType会查找和自己的类中的类型相同的bean来装配，但是如果通过一个bean文件中有多个对应类的bean标签就会出现错误-->
    <bean id="people" class="com.tur.pojo.People" autowire="byType">
        <property name="age" value="12"/>
    </bean>
</beans>
```



### 使用注解

> jdk1.5支持注解，spring2.5支持注解

```xml
<!--如果运用注解实现自动装配需要用一下的标签-->
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
    xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
    xmlns:context="http://www.springframework.org/schema/context"
    xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd">

    <context:annotation-config/>

</beans>
```



```java

//可以在属性上加这个注解，也可以在set方法上加这个注解。
//默认使用byname的方式找到,
@Autowired
private Dog dog;

//通过set后的字段dog22查找id为dog22的bean对应的类的实例进行装配
@Autowired
public void setDog22(Dog dog22){
    this.dog=dog22;
}
//指定相同类型的某个id的bean
@Autowired
@Qualifier("dog22")

//如果显示的定义了Autowired的属性为false，则说明这个属性可以为null
@Autowired(required=false)

在定义的函数的参数列表的某一个参数前加这个注解说明这个参数可以为null
@Nullable
```



```java
//java内置的注解来实现自动装配
@Resource
@Resource(name="cat22")
```



小结：

@Autowired 通过byName的方式实现，并且这个对象必须存在.byName不行的话就需要借用其他标签@Qualifier("id")

@Resource通过byName的方式实现，如果找不到名字则通过byType的方式来找，如果都找不到就报错



## 使用注解开发

```java
package com.tur.dao;

import org.springframework.beans.factory.annotation.Value;
import org.springframework.stereotype.Component;

//表示将本类加入到spring容器中
@Component
public class User {
    private String name;
    
    //给属性赋值
    //<property name="name" value="Tur"/>
    @Value("Tur")
    public void setName(String name) {
        this.name = name;
    }
}

/*
@Component衍生注解
@Repository    dao层的
@Service       service层的
@Controller    controller层的
*/

//设置作用域
@Scope("sigleton")
```



### 完全用Java类代替beans.xml配置文件

```java
package com.tur.config;

import com.tur.pojo.Cat;
import com.tur.pojo.Dog;
import org.springframework.context.annotation.Bean;
import org.springframework.context.annotation.ComponentScan;
import org.springframework.context.annotation.Configuration;
import org.springframework.context.annotation.Import;

@Import({MyConfig2.class})
@Configuration
@ComponentScan("com.tur")
public class MyConfig {
    @Bean
    public Dog getDog() {
        return new Dog();
    }

    //注册一个bean就相当于我们之前的一个bean标签
    //这个方法的名字就相当于bean标签中的属性
    //这个方法的返回值就相当于bean标签的class属性
    @Bean
    public Cat getCat() {
        return new Cat();
    }
}
//@Configuration 表示本类是一个配置类，相当于之前的beans标签
//@Bean 相当于其中的一个bean标签
//@Import({MyConfig2.class}) 导入其他的配置类
//@ComponentScan("com.tur") 扫描包，使得该包的注解生效
```



## 代理模式

### 静态代理

### 动态代理

```java
package com.tur.Configur;

import java.lang.reflect.InvocationHandler;
import java.lang.reflect.Method;
import java.lang.reflect.Proxy;

public class ProxyInvercationHandler implements InvocationHandler {
    Object target;
    public void setTarget(Object target) {
        this.target = target;
    }
    //获取代理实例
    public Object getProxy() {
        return Proxy.newProxyInstance(target.getClass().getClassLoader(), target.getClass().getInterfaces(), this);
    }
    //通过代理类操作实被代理对象的方法
    @Override
    public Object invoke(Object proxy, Method method, Object[] args) throws Throwable {
        Object result = method.invoke(target, args);
        return result;
    }
}

```



```java
package com.tur.pojo;

import com.tur.Configur.ProxyInvercationHandler;

public class main {
    public static void main(String[] args) {
        ProxyInvercationHandler pih = new ProxyInvercationHandler();
        pih.setTarget(new UserDaoImpl());
        UserDao userDao=(UserDao) pih.getProxy();
        userDao.getUsers();
        userDao.getUserById(1);
    }
}
```



![](D:\MyCode\MarkDown\IMG\动态代理.jpg)

## AOP

### 方式一使用Spring的API接口

#### xml配置

````xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <!--bean标签实现装配-->
    <bean name="User" class="com.tur.pojo.User"/>
    <!--对接口的第一实现类-->
    <bean name="UserDaoImpl" class="com.tur.dao.UserDaoImpl"/>
    <!--切面类-->
    <bean name="Log" class="com.tur.log.Log"/>
    <!--aop注册-->
    <aop:config>
        <aop:aspect ref="Log">
            <aop:pointcut id="log1" expression="execution(* com.tur.dao.UserDao.*(..))"/>
            <aop:before method="before" pointcut-ref="log1"/>
            <aop:before method="after" pointcut-ref="log1"/>
        </aop:aspect>
    </aop:config>
</beans>
````





### 方式二 注解+Java



```java
package com.tur.log;

import org.aspectj.lang.annotation.After;
import org.aspectj.lang.annotation.Aspect;
import org.aspectj.lang.annotation.Before;

@Aspect
public class Log{
    
    @Before("execution(* com.tur.dao.UserDaoImpl.*(..))")
    public void before(){
        System.out.println("在主函数之前");
    }
    
    @After("execution(* com.tur.dao.UserDaoImpl.*(..))")
    public void after(){
        System.out.println("在主函数之后");
    }
}
```



```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <!--bean标签实现装配-->
    <bean name="UserDaoImpl" class="com.tur.dao.UserDaoImpl"/>
    <bean name="User" class="com.tur.pojo.User"/>
    <bean name="Log" class="com.tur.log.Log"/>

    <!--自动代理，表示使用注解来实现-->
    <aop:aspectj-autoproxy/>

</beans>
```





## 整合MyBatis

> dataSource->sqlSessionFactory->sqlSessionTemplate->userMapperImpl

```xml
<?xml version="1.0" encoding="UTF-8"?>
<beans xmlns="http://www.springframework.org/schema/beans"
       xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance"
       xmlns:p="http://www.springframework.org/schema/p"
       xmlns:c="http://www.springframework.org/schema/c"
       xmlns:context="http://www.springframework.org/schema/context"
       xmlns:aop="http://www.springframework.org/schema/aop"
       xsi:schemaLocation="http://www.springframework.org/schema/beans
        https://www.springframework.org/schema/beans/spring-beans.xsd
        http://www.springframework.org/schema/context
        https://www.springframework.org/schema/context/spring-context.xsd
        http://www.springframework.org/schema/aop
        https://www.springframework.org/schema/aop/spring-aop.xsd">
    <!--bean标签实现装配-->
    <bean id="dataSource" class="org.springframework.jdbc.datasource.DriverManagerDataSource">
        <property name="driverClassName" value="com.mysql.cj.jdbc.Driver"/>
        <property name="url" value="jdbc:mysql://localhost:3306/mybatis_database?useSSL=true&amp;userUnicode=true&amp;characterEncoding=UTF-8"/>
        <property name="username" value="root"/>
        <property name="password" value="pzl945464"/>
    </bean>

    <bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <property name="dataSource" ref="dataSource" />
        <!--绑定mybatis配置文件-->
        <property name="configLocation" value="classpath:Mybatis.xml"/>
        <property name="mapperLocations" value="classpath:com/tur/dao/*.xml"/>
    </bean>

    <bean id="SqlSession" class="org.mybatis.spring.SqlSessionTemplate">
        <!--只能用构造器来注入不能用set方法，因为SqlSessionTemplate没有set方法-->
        <constructor-arg index="0" ref="sqlSessionFactory"/>
    </bean>

    <bean id="UserDaoImpl" class="com.tur.dao.UserDaoImpl">
        <property name="sqlSession" ref="SqlSession"/>
    </bean>
</beans>
```



## 事务管理

```xml
<!--注意：为事务管理器指定的 DataSource 必须和用来创建 SqlSessionFactoryBean 的是同一个数据源，否则事务管理器就无法工作了
-->
<bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
        <constructor-arg ref="dataSource" />
</bean>

<bean id="sqlSessionFactory" class="org.mybatis.spring.SqlSessionFactoryBean">
        <property name="dataSource" ref="dataSource" />
    	
    	<!--事务管理关键设置-->
        <property name="transactionFactory">
            <bean class="org.apache.ibatis.transaction.managed.ManagedTransactionFactory"/>
        </property>
        <!--绑定mybatis配置文件-->
        <property name="configLocation" value="classpath:Mybatis.xml"/>
        <property name="mapperLocations" value="classpath:com/tur/dao/*.xml"/>
</bean>
```



### 配置的方式事务管理

```xml
	<bean id="transactionManager" class="org.springframework.jdbc.datasource.DataSourceTransactionManager">
        <constructor-arg ref="dataSource"/>
    </bean>
	<!--定义一个事务通知-->
    <tx:advice id="txAdvice" transaction-manager="transactionManager">
        <tx:attributes>
            <tx:method name="getUsers" propagation="REQUIRED"/>
        </tx:attributes>
    </tx:advice>
    <!--配置事务的切入-->
    <aop:config>
        <aop:pointcut id="txPointCut" expression="execution(* com.tur.dao.*.*(..))"/>
        <aop:advisor advice-ref="txAdvice" pointcut-ref="txPointCut"/>
    </aop:config>
```



```xml
<aop:config>
        <aop:pointcut id="txPointCut" expression="execution(* com.tur.dao.*.*(..))"/>
        <aop:advisor advice-ref="txAdvice" pointcut-ref="txPointCut"/>
    </aop:config>
```

```xml
<aop:config>
	<aop:advisor advice-ref="txAdvice" pointcut="execution(* com.tur.dao.*.*(..))"/>
</aop:config>
```

