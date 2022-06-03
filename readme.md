В первом терминале: 
```
roscore
```
Во втором терминале:

 ```
 rosrun lab1 lab1_node
 ```

В третьем терминале;

```
rosservice call /quadratic_equation "a: 1.0
b: 8.0
c: 3.0" 
```
