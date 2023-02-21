在 GIT BASH中的操作

//配置用户基本信息
git config --global user.name <用户名>
git config --global user.email <用户邮箱>

git init  			//创建新仓库
//下载项目
git clone <远程仓库的项目链接>（https://github.com/dragen1860/Deep-Learning-with-TensorFlow-book.git）

git status  		//显示当前工作目录下的提交文件状态
git add 文件名		//将指定文件Stage(标记为将要被提交的文件)，从工作区到暂存区
git reset <文件路径>	//将指定文件UnStage(取消标记为将要被提交的文件)

git commit -m "提交信息"	//创建一个提交并提供提交信息 ，从暂存区到仓库

git log  			//查看提交历史

git push 			//向远程仓库推送
git pull			//从远程仓库拉取

git checkout HEAD 需恢复上次操作的文件名(main.py)