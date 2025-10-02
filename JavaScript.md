# JavaScript



> 示例代码

```javascript
<script>
	alert("Hello world!");//显示一个弹窗    
</script>
```



## 定义变量

```javascript
<!DOCTYPE html>
<html>
	<head>
    
    	<script>
    		var num=1;
			//定义局部变量
			let i=1;
			alert(num);
    	</script>
	</head>
	<body>
    	
    </body>
</html>
```



## 数据类型

> =赋值
>
> ==等于 （无论数据类型是否一样，只要内容一样就一样）
>
> ===绝对等于 （数据类型和值都必须一样）

> 数值类型(包括整数，浮点数。。。),字符串类型,数组,对象
>
> NAN   not a number
>
> 判断一个数字是不是越界 isNan(num);
>
> Infinity//表示无限大

> 数组
>
> var arr=[1,"hello",12.1];//var类似 object类型,数组用中括号定义

> 对象
>
> var person={
>
> ​	name: "王浩楠",
>
> ​	age: 21
>
> }

### 字符串

```javascript
//长字符串
var name=`王
			浩楠`;
//  \" 运用转义的方式在字符串内打印“ 运用 ${} 获取变量值插入到字符串中
console.log(`My name is ${name},\"I'm coding\" `);
//字符串值的不可变
let student="student";
student[0]='1';//实际上没有被改变
//获得字符串的长度
console.log(student.length);
//
```

### 数组

1. 长度

```javascript
arr.length
```

> 注意：加入给arr.length赋值，数组的大小就会发生变化~如果数值过小，元素就会丢失

2. indexOf,通过元素获得下标索引

```javascript
arr.indexOf(2);
```

> 字符串“1”和数字 1 是不同的

3. slice() 截取Array的一部分，返回一个新数组，类似String中的substring();
4. push(),pop()尾部

```javascript
push:压入尾部
pop:弹出尾部的一个元素
```

5. unshift(),shift()头部

```javascript
unshift:压入到头部
shift:弹出头部
```

6. 排序sort()

```javascript
let arr=['c','b','a'];
arr.sort();
['a','b','c'];
```

7. 元素反转reverse()

```javascript
let arr=['a','b','c'];
arr.reverse();
['c','b','a'];
```

8. concat();在数组后面拼接新的数组，但是不会改变原数组的内容

```javascript
let arr=['c','b','a'];
arr.concat([1,2,3]);
['c','b','a',1,2,3];
```

9. 连接符 join

```javascript
let arr=['c','b','a'];
arr.join('-');
"c-b-a"
```

10. 多维数组

```javascript
let arr=[[1,2],[2,3],[3,4]];
```

### 对象

若干键值对

```javascript
var 对象名={
    属性名: 属性值,
    属性名: 属性值,
    属性名: 属性值
}
```

