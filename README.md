# MiniShell 的设计与实现

## 实验目标

- [ ] 支持后台符号 `&`
- [x] 支持串行执行多个命令 `;`
- [x] 支持管道 `|`
- [x] 支持环境变量 `export` `env`
- [x] 支持字符串的输出 `echo`
- [x] 重定向 `>>` `>` `<`
- [x] 支持变量 `$`
- [x] 支持历史 `history` `-c` `-a` `n`
- [x] 支持 `alias`

## 编译

```bash
make build
```

## 测试

```bash
make test
```

![minishell](./assets/demo1.png)

## 设计

