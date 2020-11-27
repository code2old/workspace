#! /bin/bash
#set -x
tatol_cpu_usage=0
app_cpu_usage=0
tatol_mem_usage=0
app_mem_usage=0

#进行CPU使用率统计
#Cpu(s): 12.9%us,  3.2%sy,  0.0%ni, 83.8%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
#top -n表示退出之前刷新的次数，-b表示输出编排成适合输出到文件的格式，一定要加-b选项
#否则得到的idle值不能进行正常处理，而且对其进行dos2unix处理也会显示有不明二进制符号
idle=`top -n 1 -b |  sed -e 's/ //g' | \
grep "Cpu(s):" | awk -F ":" '{print $2}' | \
awk -F "," '{print $4}' | awk -F "%" '{print $1}'`
#echo $idle
#以下展示了几种在shell脚本中进行浮点计算的几种方法
tatol_cpu_usage=$(echo $idle | awk '{printf("%.2f",100-$1)}')
#tatol_cpu_usage=$(echo "100-${idle}" | bc)
#tatol_cpu_usage=`echo "100-${idle}" | bc`
echo $tatol_cpu_usage
