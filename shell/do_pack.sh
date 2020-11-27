#!/bin/sh

#变量定义

System="LINUX_X64"
version="V2.0.0"

HISI="workspace"
INCLUDE="ZLMediaKit"
LIB="ZLToolKit"
DOC="DESIGN_PATERN"
Productname="TRANSCODER"

PROJECT_PATH_DIR=${pwd}

function tar_save()
{
	FILE_NAME=${Productname}_${System}_${version}_Build$(date +%y%m%d)
	ZIP_NAME=${FILE_NAME}.zip 
	echo "******start zip $ZIP_NAME***********"
	echo ""
	if [ -e "${FILE_NAME}.zip" ]; then
        rm ${FILE_NAME}.zip
    fi
	zip -r ${ZIP_NAME} ${PROJECT_PATH_DIR}
	#txt文件存在时先删除文件
    if [ -e "${FILE_NAME}.txt" ]; then
        rm ${FILE_NAME}.txt
    fi

    echo "dav_md5:$ATTR_LIB_MD5" >> ${FILE_NAME}.txt
	ATTR_ZIP_MD5=`md5sum $ZIP_NAME | cut -d ' ' -f1` 
	echo "zip_md5=$ATTR_ZIP_MD5" >> ${FILE_NAME}.txt
	echo "type:STD">>${FILE_NAME}.txt
    echo "lang:CN">>${FILE_NAME}.txt
    echo "pack_ver:"${version}_$(date +%y%m%d)>>${FILE_NAME}.txt
    echo "dav_name:"${LIBNAME}>>${FILE_NAME}.txt
    echo "platform:"${platform%_*}>>${FILE_NAME}.txt
    echo "plat_ver:"${platform#*_}>>${FILE_NAME}.txt
	
	if [ -n "${output_dir}" ]; then 
        mv ${ZIP_NAME} ${output_dir}
        mv ${FILE_NAME}.txt ${output_dir}
    fi
	echo ""
	echo "*******end zip $ZIP_NAME*********"

}


function Action()
{
    tar_save
}

#-------------------- 脚本执行入口 --------------------#
# 脚本传参：
# 1).自动化打包：$1为jenkins自动化标志 $2为字符串参数
# 2).本地编译时：$1为执行动作 $2为语言选项

# 判断是自动化打包还是本地打包


Action 
if [ $? -ne 0 ]; then
	echo "action func failed!!!"
	return 1
fi  

    
exit 0