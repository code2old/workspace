#! /bin/bash
#set -x
tatol_cpu_usage=0
app_cpu_usage=0
tatol_mem_usage=0
app_mem_usage=0

#����CPUʹ����ͳ��
#Cpu(s): 12.9%us,  3.2%sy,  0.0%ni, 83.8%id,  0.0%wa,  0.0%hi,  0.0%si,  0.0%st
#top -n��ʾ�˳�֮ǰˢ�µĴ�����-b��ʾ������ų��ʺ�������ļ��ĸ�ʽ��һ��Ҫ��-bѡ��
#����õ���idleֵ���ܽ��������������Ҷ������dos2unix����Ҳ����ʾ�в��������Ʒ���
idle=`top -n 1 -b |  sed -e 's/ //g' | \
grep "Cpu(s):" | awk -F ":" '{print $2}' | \
awk -F "," '{print $4}' | awk -F "%" '{print $1}'`
#echo $idle
#����չʾ�˼�����shell�ű��н��и������ļ��ַ���
tatol_cpu_usage=$(echo $idle | awk '{printf("%.2f",100-$1)}')
#tatol_cpu_usage=$(echo "100-${idle}" | bc)
#tatol_cpu_usage=`echo "100-${idle}" | bc`
echo $tatol_cpu_usage
