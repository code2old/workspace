#!/bin/sh

#变量定义

System="LINUX_X64"
version="V2.0.0"

Productname="TRANSCODER"

PROJECT_PATH_DIR=${PWD}

OPEN_CV       = ${PROJECT_PATH_DIR}/cv
FFMPEG        = ${PROJECT_PATH_DIR}/ffmpeg
CODE_FFMPEG   = ${PROJECT_PATH_DIR}/code/ffmpeg-4.3.1.tar.xz
CODE_JEMALLOC = ${PROJECT_PATH_DIR}/code/jemalloc-5.2.1.tar
CODE_REDIS    = ${PROJECT_PATH_DIR}/code/redis-5.0.10.tar.gz
CODE_YASM     = ${PROJECT_PATH_DIR}/code/yasm-1.3.0.tar.gz

function tar_save()
{
    FILE_NAME=${Productname}_${System}_${version}_Build$(date +%y%m%d)
    ZIP_NAME=${FILE_NAME}.zip 
    echo "******start zip $ZIP_NAME***********"
    echo ""
    if [ -e "${FILE_NAME}.zip" ]; then
        rm ${FILE_NAME}.zip
    fi
    zip -r ${ZIP_NAME} ${PROJECT_PATH_DIR} -x ${PROJECT_PATH_DIR}/ffmpeg/3rdparty  ${PROJECT_PATH_DIR}/code/yasm-1.3.0  ${PROJECT_PATH_DIR}/code/ffmpeg-4.3.1
    #txt文件存在时先删除文件
    if [ -e "${FILE_NAME}.txt" ]; then
        rm ${FILE_NAME}.txt
    fi

    echo "dav_md5:$ATTR_LIB_MD5" >> ${FILE_NAME}.txt
    ATTR_ZIP_MD5=`md5sum $ZIP_NAME | cut -d ' ' -f1` 
    echo "zip_md5=$ATTR_ZIP_MD5" >> ${FILE_NAME}.txt
    
    if [ -n "${output_dir}" ]; then 
        mv ${ZIP_NAME} ${output_dir}
        mv ${FILE_NAME}.txt ${output_dir}
    fi
    echo ""
    echo "*******end zip $ZIP_NAME*********"
}



#-------------------- 脚本执行入口 --------------------#
# 脚本传参：
# 1).自动化打包：$1为jenkins自动化标志 $2为字符串参数
# 2).本地编译时：$1为执行动作 $2为语言选项

# 判断是自动化打包还是本地打包

echo '"${PROJECT_PATH_DIR}/ffmpeg/3rdparty"'

tar_save

if [ $? -ne 0 ]; then
    echo "action func failed!!!"
    return 1
fi  

    
exit 0