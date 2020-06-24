#!/bin/bash

function detectNeworkAndStartMqtt()
{
    while :
    do
        ping -c 1 114.114.114.114 > /dev/null 2>&1
        if [ $? -eq 0 ];then
            echo 检测网络正常
            echo 启动mqtt-client
            ./mqtt_demo
            break;
        else
            echo 检测网络连接异常
        fi
        sleep 5
    done
}

#检测网络连通性
function detectNetwork()
{
    #! /bin/bash
    #检测网络连接
    ping -c 1 114.114.114.114 > /dev/null 2>&1
    if [ $? -eq 0 ];then
        echo 检测网络正常
        echo 启动mqtt-client
        break;
    else
        echo 检测网络连接异常
    fi
}

#检测网络链接畅通一次
function networkOnce()
{
    #超时时间
    local timeout=1

    #目标网站
    local target=www.baidu.com

    #获取响应状态码
    local ret_code=`curl -I -s --connect-timeout ${timeout} ${target} -w %{http_code} | tail -n1`

    if [ "x$ret_code" = "x200" ]; then
        #网络畅通
        return 1
    else
        #网络不畅通
        return 0
    fi

    return 0
}

#启动wifi配网server
function startWifi()
{
    echo "start wifi server"
    sudo ./server &
}

#删除wifi配置文件
function delWifiConfig()
{
    echo "delete wifi config file:/etc/wpa_supplicant/wpa_supplicant.conf"
    #删除指定行，例如第5行
    sudo sed -i '11d' ./a.txt
    sudo sed -i '11d' ./a.txt
    sudo sed -i '11d' ./a.txt
    sudo sed -i '11d' ./a.txt
    sudo sed -i '11d' ./a.txt
    # sudo rm /etc/wpa_supplicant/wpa_supplicant.conf
}



# network
# if [ $? -eq 0 ];then
# 	echo "网络不畅通，请检查网络设置！"
# 	exit -1
# fi

# echo "网络畅通，你可以上网冲浪！"

# exit 0


#1.删除wifi配置文件
delWifiConfig
# #2.启动wifi配置配网server
startWifi
#3.启动网络检测->网络畅通则启动
detectNeworkAndStartMqtt