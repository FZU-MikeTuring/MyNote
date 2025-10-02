# Git



## 下载

> 会自动配置环境变量

[Git - Downloads](https://git-scm.com/downloads)

## 常用的Linux命令

```bash
cd #改变目录
cd.. #回退到上一个目录，直接俄cd进入默认目录
pwd #显示当前目录路径
ls #列出当前文件夹下的所有文件
touch [file name]#新建一个文件
rm [file name]#移除一个文件
mkdir [dir name]#新建一个目录，也就是新建一个文件夹
rm -r [dir name]#删除一个文件夹， 
rm -r / #递归删除所有文件，谨慎哦，要重装系统的！！！
mv [source file] [des dir]   #将源文件移动到目标位置
clear#清屏
reset #重新设置终端
history#查看开始到目前用过的命令
help#帮助
exit#退出bash
#代表注释
```

## 配置git

> 必须要配置的，配置用户名
>
> 会在c/用户/1831/.gitconfig 的文件

```bash
git config --gloabal user.name "FZU_MikeTuring" #名称
git config --global user.email 1831780773@qq.com #邮箱
```

## Git基本理论

- Git本地由三个工作区域:工作目录，暂存区，资源库(Repository),Remote

- 工作目录就是本地存放我的一些我自己写的代码、文案、markdown笔记的文件夹，在这里通过git init 或者git clone等操作就会在这个文件夹中生成一个本地仓库(.git文件夹)，如果把 .git 文件删了，那么仓库内容也就被删了，暂存区和local repository都在这里

- main/master是主分支，还可以创建一些子分支



```bash
git add .
git commit -m "message"
git push -u [本地仓库名] [分支名]

git init
git clone
git checkout
git fetch
git merge
git pull
```

## 创建git项目

### 初始化项目

```bash
git init##会在当前文件夹搞出一个.git文件(隐藏文件)
```



#### 配置SSH

```bash
#生成一个ssh密钥
ssh-keygen -t rsa
#-t rsa 表示用什么算法加密，此指令用来生成密钥 在c/用户/1831/.ssh，将pub公钥用记事本打开，将内容复制到github添加ssh key的部分即可
```



> 在.ssh文件夹下创建一个config文件，注意这个文件没有拓展名 ,改用443端口

```config
Host github.com
  Hostname ssh.github.com
  Port 443
  User git
  IdentityFile ~/.ssh/id_rsa
  TCPKeepAlive yes
  IdentitiesOnly yes
```



> 测试连接

```bash
ssh -T git@github.com
```



#### 本地仓库连接到remote respository

```bash
git remote add 本地仓库名 git@github.com:github用户名/云端仓库名.git
git remote add GitStudy git@github.com:FZU-MikeTuring/GitStudy.git
#respository name 仓库名称
# url https://github.com/FZU-MikeTuring/GitStudy
```



### 克隆项目



```bash
git clone [url] #此种方式克隆得到的仓库的本地仓库名称默认为origin
git clone -o [本地仓库名] [url] #此种方式克隆可以自定义仓库名
```



> 如何找ssh版本的url?
>
> 在github的仓库主界面 点击 code 按钮会看到一个菜单，点击ssh按钮后就会看到对应url可以复制以及其他的一些相关信息



## 分支

### 查看分支

```bash
git branch#查看当前的分支
```



### 创建分支

```bash
git branch [分支名]#创建一个新的分支
```



### 切换分支

```bash
git checkout [分支名]#切换分支
```



```bash
git switch [分支名]#切换分支
```



### 创建并切换到新分支

```bash
git checkout -b [分支名]
```





### 将分支从本地上传到云端

```bash
git push -u 本地仓库名 [分支名]
```



### 删除分支

> 删除分支(删除本地的分支，删除云端的分支)

```bash
# 1. 首先，切换到其他分支（不能删除当前所在分支）
git checkout main
# 或
git checkout master

# 2. 删除本地分支（可选）
git branch -d 分支名

# 3. 删除远程分支
git push 本地仓库名 --delete 分支名
```





### 拉取分支合并分支

>  git pull = git fetch(查看更新) + git merge (直接更新)
>
> 用git fetch + git merge 的方法更安全

```bashe
# 1. 先查看有什么更新
git fetch origin

# 2. 比较本地和远程的差异
git log HEAD..origin/main --oneline

# 3. 如果确认要更新，再执行合并
git merge origin/main

# 或者直接一步到位
git pull origin main
```



