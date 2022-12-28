# MiniShell 的设计与实现

## 实验目标

- [x] 支持后台符号 `&`
- [x] 支持串行执行多个命令 `;`
- [x] 支持管道 `|`
- [x] 支持环境变量 `export` `env`
- [x] 支持字符串的输出 `echo`
- [x] 重定向 `>>` `>` `<`
- [x] 支持变量 `$`
- [x] 支持历史 `history`
- [x] 支持 `alias`

## 编译

```bash
make build
```

## 测试

```bash
make test
```

![minishell](/assets/demo1.png)

### 串行执行

```bash
date;ls;cd ..
```

![demo2](/assets/demo2.png)

### 命令别名

```bash
ll # ls -alF --color=auto
```

![demo3](/assets/demo3.png)

### 历史命令

```bash
history
```

删除历史命令

```bash
history -c
```

将内存中的命令写入 `.history` 文件中

```bash
history -a
```

![demo4](/assets/demo4.png)

### 管道

```bash
ll | grep s
```

![demo5](/assets/demo5.png)

### 输入输出重定向

```bash
echo hello world >> test.txt
```

![demo6](/assets/demo6.png)

```bash
echo override > test.txt
```

![demo7](/assets/demo7.png)

```bash
wc -l < README.md
```

![demo8](/assets/demo8.png)

### 环境变量

```bash
env user_name=ARCTURUS
```

```bash
env | grep user_name
```

![demo9](/assets/demo9.png)

输出环境变量

```bash
echo $user_name
```

![demo10]()

shell 变量导出

```bash
abc=10
```

```bash
export abc
```

```bash
export | grep abc
```

![demo11](/assets/demo10.png)

### 后台运行

```bash
wget http://ftp.tku.edu.tw/Linux/Deepin/deepin-cd/20/deepin-desktop-community-1002-amd64.iso &
```

查看守护进程

```bash
ps xj | grep xxx
```

![demo12](/assets/demo12.png)

## 设计

