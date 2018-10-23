#! /usr/bin/env bash

ARGS="$*"

ROOT_DIR=`pwd`

#帮助文档函数
help(){
	echo ""
	echo "自动生成SVN评审文件，生成的文件目录在执行脚本的当前路径下，生成的文件名为$TARGET_DIR"
	echo "$TARGET_DIR是一个目录，目录中有两个子目录Old_xxx 和New_xxxx"
	echo "其中Old_xxx目录存放原始文件(SVN仓库中的文件), New_xxxx存放修改后的文件"
	echo "默认动作只添加被修改的文件到评审文件中，且Old_xxx目录保留svn信息"
	echo  -e "备注：新增文件需要手动加入到svn版本控制后才能生效(svn status显示状态为A)"
	echo -e "\e[1;31m$1 [-options]; 注意不要组合选项参数, 如：-ad,不能识别 ！！\e[m"
	echo -e "\e[1;31m例子:\t$1\t$1 -a\t$1 -a -d \e[m"
	echo -e "-h | help:\t\t帮助文档"
	echo -e "-A | -a:\t\t\t新增文件也加入到评审文件中"
	echo -e "-D | -d:\t\t\t删去Old_xxx目录中的svn信息"
}


#添加评审文件，两个参数
#param1： 需要添加的文件列表
#param2：是否需要导入svn版本到OLD目录中去(Y/N)
addReviewFile(){
	T_FILE=($1)
	for f in ${T_FILE[@]};do
		TMP_DIR=
		if [ "$(echo $f | grep '/')" ];then
			TMP_DIR=$(echo $f | sed 's;\(.*\)\/\(.*\);\1;')
			#echo "TMP_DIR: $TMP_DIR"
			mkdir -p $NEW_DIR/$TMP_DIR
			if [ "$2" = "Y" ];then
				mkdir -p $OLD_DIR/$TMP_DIR
			fi
		fi
		
		#拷贝修改的文件到$NEW_DIR 目录中
		if [ -f "$f" ];then
			echo "add $f to $NEW_DIR"
			cp $f $NEW_DIR/$TMP_DIR
		fi
		
		#源文件更新到$OLD_DIR,svn不支持导出单个文件，这里导出整个目录
		if [ "$2" = "Y" ];then
			if [ -z "$(find $OLD_DIR/$TMP_DIR -type d -name "\.svn")" ];then
				#echo "svn co --depth=empty $PRO_URL/$TMP_DIR $OLD_DIR/$TMP_DIR"
				svn co --depth=empty $PRO_URL/$TMP_DIR $OLD_DIR/$TMP_DIR >> /dev/null
			fi
			echo "add $f to $OLD_DIR"
			cd $OLD_DIR;svn update $f -r $PRO_VER >> /dev/null;cd - >>/dev/null;
		fi
	done
}

if [ $(echo "$*" | grep -i '\-h') ] || [ $(echo "$*" | grep -i 'help') ];then
	help "$0";
	exit 0;
fi

#删除SVN信息标志
DEL_SVN_INFO=$(echo "$*" | grep -i '\-d')

#添加新增文件到评审列表标志
APPEND_NEW=$(echo "$*" | grep -i '\-a')

echo -e "当前工作路径:\t\t\e[33m$PWD\e[m"

#svn 路径URL
PRO_URL=$(svn info | grep "^URL" | sed 's;URL:;;')
echo -e "工作区SVN路径:\t\t\e[1;33m$PRO_URL\e[m"

#svn 当前版本
PRO_VER=$(svn info | grep "Revision" | sed 's;Revision:;;' | tr -d -c [0-9])
echo -e "工作区SVN版本:\t\t\e[1;33m$PRO_VER\e[m"

TARGET_DIR=code.review
rm -rf $TARGET_DIR

#新建评审文件存放的主路径
OLD_DIR=$PWD/$TARGET_DIR/Old_$PRO_VER
NEW_DIR=$PWD/$TARGET_DIR/New_xxxxx
mkdir -p $OLD_DIR
mkdir -p $NEW_DIR


#被修改文件列表
M_FILE_T=$(svn status | grep "^M" | sed 's;^M *;;')
echo -e "\e[1;31m########## 以下文件被修改 ################\e[m"
echo "$M_FILE_T"
echo -e "\e[1;31m########## 被修改文件列表结束 #############\e[m"

#把修改文件导入到比较文件夹中
addReviewFile "${M_FILE_T}" "Y"

if [ "$APPEND_NEW" ];then
	#新增文件列表
	echo -e "\e[1;31m########## 以下文件为新增 ################\e[m"
	A_FILE_T=$(svn status | grep "^A" | sed 's;^A *;;')
	echo "$A_FILE_T"
	echo -e "\e[1;31m########## 新增文件列表结束 ################\e[m"
	
	#新增文件导入评审列表
	addReviewFile "$A_FILE_T" "N"
fi


#最后把OLD_DIR 中的svn信息强制删去
if [ "$DEL_SVN_INFO" ];then
	echo "开始删除$OLD_DIR中的.svn信息"
	find $OLD_DIR -name ".svn" | xargs rm -rf;
	echo "删除$OLD_DIR中的.svn信息完成"
fi





















