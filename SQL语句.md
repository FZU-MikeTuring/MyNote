# SQL语句



## 基础语法



## 不常见语法



> WHERE逻辑判断时运用子查询



```sql
#子句运用 SELECT 语法查出与查询时间有冲突的柜号，然后逻辑中用NOT IN去除这些柜号，达到查询目的--子查询
SELECT cab.cab_id,cab.area FROM cab
	WHERE cab.cab_id NOT IN (
        SELECT DISTINCT a.cab_id FROM appointment a
    	WHERE a.start_time<:target_end_time
    	  AND a.end_time>:target_start_time);
```



> CASE 
>
> ​	 WHEN 条件1 THEN ‘result1’
>
> ​	  WHEN 条件2 THEN 'result2'
>
> ​	...
>
> ​	ELSE 'result_last'
>
> END AS 'column_name'



```sql
#EXISTS的意思时存在，也就是子查询语句只要能查到东西就会设置appointment_state列的位置为unavailable,因此要注意里面的逻辑判断
#语句
SELECT cab.cab_id,cab.area,
	CASE 
		WHEN EXISTS(
        	SELECT 1 FROM appointment a
            	WHERE cab.cab_id=a.cab_id
            	  AND a.start_time<:target_end_time
            	  AND a.end_time>:target_start_time 
        )THEN 'unavailable'
        ELSE 'available'
     END AS 'appointment_state'
FROM cab;
```

