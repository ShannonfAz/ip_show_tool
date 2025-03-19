/*********************************************************************************************************************
* LS2K0300 Opensourec Library 即（LS2K0300 开源库）是一个基于官方 SDK 接口的第三方开源库
* Copyright (c) 2022 SEEKFREE 逐飞科技
*
* 本文件是LS2K0300 开源库的一部分
*
* LS2K0300 开源库 是免费软件
* 您可以根据自由软件基金会发布的 GPL（GNU General Public License，即 GNU通用公共许可证）的条款
* 即 GPL 的第3版（即 GPL3.0）或（您选择的）任何后来的版本，重新发布和/或修改它
*
* 本开源库的发布是希望它能发挥作用，但并未对其作任何的保证
* 甚至没有隐含的适销性或适合特定用途的保证
* 更多细节请参见 GPL
*
* 您应该在收到本开源库的同时收到一份 GPL 的副本
* 如果没有，请参阅<https://www.gnu.org/licenses/>
*
* 额外注明：
* 本开源库使用 GPL3.0 开源许可证协议 以上许可申明为译文版本
* 许可申明英文版在 libraries/doc 文件夹下的 GPL3_permission_statement.txt 文件中
* 许可证副本在 libraries 文件夹下 即该文件夹下的 LICENSE 文件
* 欢迎各位使用并传播本程序 但修改内容时必须保留逐飞科技的版权声明（即本声明）
*
* 文件名称          main
* 公司名称          成都逐飞科技有限公司
* 适用平台          LS2K0300
* 店铺链接          https://seekfree.taobao.com/
*
* 修改记录
* 日期              作者           备注
* 2025-02-27        大W            first version
********************************************************************************************************************/
#include <iostream>
#include <cstring>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>
#include <unistd.h>
#include "zf_common_headfile.h"

#define KEY_0       "/dev/zf_driver_gpio_key_0"



int16_t data_index = 0;
char eth0[INET_ADDRSTRLEN];
int show_eth0_on_screen(){
	    // 创建socket
		int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sockfd < 0) {
			//std::cerr << "无法创建socket" << std::endl;
		}
	
		struct ifreq ifr;
		memset(&ifr, 0, sizeof(ifr));
		strncpy(ifr.ifr_name, "eth0", IFNAMSIZ - 1);
	
		// 获取IPv4地址
		if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
			//std::cerr << "无法获取IP地址（请检查接口名称和权限）" << std::endl;
			close(sockfd);
			return 0;
		}
	
		// 转换二进制地址为字符串
		struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
		if (inet_ntop(AF_INET, &ipaddr->sin_addr, eth0, sizeof(eth0))) {
			std::cout << "eth0 IP地址: " << eth0 << std::endl;
			ips200_show_string( 0 , 0,   "eth0:");
			ips200_show_string( 0 , 16,   eth0);
		} else {
			//std::cerr << "地址转换失败" << std::endl;
			close(sockfd);
		}
		
		close(sockfd);
		return 0;
}
char wlan0[INET_ADDRSTRLEN];
int show_wlan0_on_screen(){
	    // 创建socket
		int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
		if (sockfd < 0) {
			//std::cerr << "无法创建socket" << std::endl;
		}
	
		struct ifreq ifr;
		memset(&ifr, 0, sizeof(ifr));
		strncpy(ifr.ifr_name, "wlan0", IFNAMSIZ - 1);
	
		// 获取IPv4地址
		if (ioctl(sockfd, SIOCGIFADDR, &ifr) == -1) {
			//std::cerr << "无法获取IP地址（请检查接口名称和权限）" << std::endl;
			close(sockfd);
			return 0;
		}
	
		// 转换二进制地址为字符串
		struct sockaddr_in* ipaddr = (struct sockaddr_in*)&ifr.ifr_addr;
		if (inet_ntop(AF_INET, &ipaddr->sin_addr, wlan0, sizeof(wlan0))) {
			//std::cout << "wlan0 IP地址: " << wlan0 << std::endl;
			ips200_show_string( 0 , 32,   "wlan0:");
			ips200_show_string( 0 , 48,   wlan0);
		} else {
			//std::cerr << "地址转换失败" << std::endl;
			close(sockfd);
		}
	
		close(sockfd);
		return 0;
}
int main(int, char**) 
{

    ips200_init("/dev/fb0");
	ips200_clear();
    while(1)
    {
        // 此处编写需要循环执行的代码
		show_eth0_on_screen();
		show_wlan0_on_screen();
		ips200_show_string(0,64,"press P13 key");
		ips200_show_string(0,80,"for 0.2s to quit");
		if(!gpio_get_level(KEY_0)){
			system_delay_ms(200);
			if(!gpio_get_level(KEY_0)){
				//ips200_show_string(0,96,"quit");
				ips200_clear();
				return 0;
			}
		}
		system_delay_ms(1);
    }
}